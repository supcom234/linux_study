/*
Utilites for file reading and writing.
*/
#define _GNU_SOURCE
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <utmp.h>

#include "str-utils.h"

static struct cpu_info {
	int model;
};

static int _process_cpu_line(uint32_t ln, size_t line_size, const char* line, void* data){
	struct cpu_info* info = (struct cpu_info*) data;
    int ret_val = 0;
    char somechar;
    char * matcher = NULL;
    int model_value = 0;
    int is_done = 1;

	//ret_val = snprintf(NULL, 0, "%s", line) + 1;
	matcher = calloc(line_size, sizeof(char));
	//matcher = malloc(ret_val);
	//memset(matcher, 0, ret_val);
	
    ret_val = sscanf(line, "%s %*c %d", matcher, &model_value);
    if (ret_val == EOF){
    	perror("sscanf");
    	is_done = ret_val;
    	goto cleanup;
    }

    if (strncmp("model", matcher, 5) == 0){
    	info->model = model_value;
    	is_done = 0;
    	goto cleanup;
    }

    cleanup:
    if (matcher)
    	free(matcher);

    return is_done;
}

static struct utmp_linked_list{
	struct utmp_linked_list* first;
	struct utmp_linked_list* last;
	struct utmp_linked_list* next;
	struct utmp* data;
};

static int _process_log(void** data, const struct utmp* log){
	struct utmp_linked_list* first_node = NULL;
	struct utmp_linked_list* node = calloc(1, sizeof(struct utmp_linked_list));
	struct utmp* utmp_log = calloc(1, sizeof(struct utmp));
	memcpy(utmp_log, log, sizeof(struct utmp));
	node->data = utmp_log;

	if (*data == NULL){
		node->first = node;
		node->last = node;		
		*data = node;
	} else {
		first_node = (struct utmp_linked_list*)*data;		
		node->first = first_node;
		first_node->last->next = node;
		first_node->last = node;
		node->last = node;

	}

	return 0;
}

int process_file(const char* file_path,
				 void* data,
				 int (*process_line)(uint32_t ln, size_t line_size, const char* line, void* data))
{
	/*
	const char* file_path - absolute or relative path to a given file.	
	void* data - pointer to some type of data structure we wish to save information to.
	int (*process_line)(uint32_t ln, size_t line_size, const char* line, void* data) - function pointer which gets executed for each line in file.
		Returns 0 when it is done processing.
	*/
	int ret_val, func_ptr_ret = 0;
	FILE* fd = fopen(file_path, "r");
	size_t length = 0;
	char * line = NULL;	
	size_t line_size = 0;
	uint32_t line_number = 0;

	if (fd == NULL){
		perror("fopen");
		ret_val = 1;
		goto cleanup;
	}	

	while ( (line_size = getline(&line, &length, fd)) != -1 ){		
        func_ptr_ret = (*process_line)(line_number, line_size, (const char*)line, data);
        if (func_ptr_ret == 0){
        	ret_val = 0;
        	break;
        }

        if (func_ptr_ret != 1){
        	ret_val = func_ptr_ret;
        	break;
        }

        line_number++;
	}

	cleanup:
	if (fd)
		fclose(fd);
	if (line)
		free(line);

	return ret_val;
}

int read_wtmp_or_utmp(const char * utmpOrWtmpPath, 
					  void** data, 
					  int (*process_log)(void** data, const struct utmp* log)) {
	/*
	const char * utmpOrWtmpPath - Must be either /var/run/utmp or /var/log/wtmp
	int (*process_log)(void* data, struct utmp* log	)

	returns 0 on success
	*/
	ssize_t bytes;
	int file;
	struct utmp log;
	int ret_val = 0;

	file = open(utmpOrWtmpPath, O_RDONLY);
	if (file == -1){
		ret_val = 1;
		printf("read_wtmp_or_utmp() open %s", strerror(errno));			
		goto cleanup;
	}

	do {
		bytes = read(file, &log, sizeof(struct utmp));
		if(bytes == -1){
			ret_val = 2;
			printf("read_wtmp_or_utmp() read %s", strerror(errno));
			break;
		}
		(*process_log)(data, &log);
	} while(bytes != 0);

	cleanup:
	if (close(file) == -1){
		ret_val = 3;
		printf("read_wtmp_or_utmp() close %s", strerror(errno));
	}

	return ret_val;
}

char* get_time(const time_t* time){
	const char* format = "%4d-%02d-%02dT%02d:%02d:%02dZ";
	char * ret_val = NULL;
	int size = 0;
	struct tm* tm = gmtime(&time);

	size = snprintf(NULL, 0, format, (tm->tm_year + 1900), (tm->tm_mon + 1), 
		tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

	if (size <= -1){
		printf("get_time() close %s", strerror(errno));	
		return NULL;
	}	

	ret_val = calloc((size + 1), sizeof(char));

	snprintf(ret_val, size, format, (tm->tm_year + 1900), (tm->tm_mon + 1), 
		tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

	return ret_val;
}

void loop_over_data(struct utmp_linked_list* node){
	while (node != NULL) {
		printf("type: %d\n", node->data->ut_type);
        printf("pid: %d\n", node->data->ut_pid);
        printf("line: %s\n", node->data->ut_line);
        printf("ut_id: %s\n", node->data->ut_id);
		printf("User: %s\n", node->data->ut_user);
		printf("host: %s\n", node->data->ut_host);

		char* time = get_time(node->data->ut_tv.tv_sec);
		printf("time: %s\n", time);

		if(time)
			free(time);

		node = node->next;
	}
}

void free_data(struct utmp_linked_list* node) {
	struct utmp_linked_list* cache;
	while(node != NULL){
		cache = node;
		node = node->next;

		if (cache->data)
			free(cache->data);		

		if (cache)
			free(cache);
	}
}

static void process_piddir(const char* path, pid_t ps){
	printf("Processing path: %s, pid: %d\n", path, ps);	
}

void process_pid_tree(void (*process_piddir)(const char*, pid_t ps)){
	DIR* dir = opendir("/proc");
	char* psDirPath = NULL;

	if (dir == NULL)
		return;

	struct dirent* entity = readdir(dir);
	while (entity != NULL){
		if (entity->d_type == DT_DIR){
			//Don't process the '..' and the '.' directories
			if (entity->d_name[0] == '.'){
				entity = readdir(dir);
				continue;
			}

			int ps = atoi(entity->d_name);
			if (ps == 0){
				entity = readdir(dir);
				//If it is not a process directory we go to the next directory
				continue;
			}
				
			if (std_str_handler(&psDirPath, "/proc/%s", entity->d_name)){
				printf("std_str_handler\n");				
				goto cleanup;
			}			

			DIR* psDir = opendir(psDirPath);
			if (psDir == NULL){
				entity = readdir(dir);
				continue;
			}			

			(*process_piddir)(psDirPath, ps);

			if (psDirPath){				
				free(psDirPath);
				psDirPath = NULL;
			}

			closedir(psDir);
		}
		entity = readdir(dir);
	}

	cleanup:
	if (psDirPath)
		free(psDirPath);

	closedir(dir);
}


int main(int argc, char* argv[]){
	struct cpu_info info = {0};
	int ret_val = 0;
	struct utmp_linked_list* node = NULL;

	ret_val = process_file("/proc/cpuinfo", (void*)&info, &_process_cpu_line);
	if (ret_val != 0)
		return ret_val;
	
	printf("Model %d\n", info.model);	
	ret_val = read_wtmp_or_utmp("/var/run/utmp", (void*)&node, &_process_log);
	if (ret_val != 0)
		return ret_val;

	loop_over_data(node);
	printf("=====Reset======\n");
	node = node->first;
	loop_over_data(node);
	free_data(node);
	
	process_pid_tree(&process_piddir);

	return 0;
}
