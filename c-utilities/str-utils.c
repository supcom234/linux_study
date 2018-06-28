#include "str-utils.h"

int std_str_handler(char **out_str, const char* format_str, ...){
	int ret_val = 0;
	int uri_len = 0;
	va_list arg_list;	
	va_start(arg_list, format_str);
	uri_len = vsnprintf(*out_str, 0, format_str, arg_list) + 1;
	va_end(arg_list);

	*out_str = calloc(uri_len, 1);
	va_start(arg_list, format_str);
	uri_len = vsnprintf(*out_str, uri_len, format_str, arg_list);
	va_end(arg_list);

	if (0 > uri_len){
		ret_val = 1;
		free(*out_str);
		*out_str = NULL;		
	}
	return ret_val;
}
