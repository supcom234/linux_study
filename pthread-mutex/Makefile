all: mutex-example

%: %.c
	@echo gcc -std=c++0x -g $< -o $@
	gcc -pthread $< -o $@

clean:
	rm -f mutex-example

.PHONY: all clean
