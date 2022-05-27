#ifndef _ARGS_H
#define _ARGS_H 0

#define _UTILS_H_IMPL
#include "utils.h"

#define HELP_FLAG 0
#define ARGS_NOT_2 1
#define INPUT_NOT_EXIST 2
 
typedef struct {
	// Arguments itself
	FILE  *Input_File;

	// Error or not
	bool   Error;
	int    Error_Message;
} Args;

#define ARGS_NOT_2_M      "Invalid Amount of arguments Specified, Use ` $ ./data-analyse -h` or ` $ ./data-analyse --help` For help\n"
#define INPUT_NOT_EXIST_M "Input File doesn't Exist\n"

Args  parse_args (int _argc, char** _argv);
void print_args_error(int error_m);

#ifdef _ARGS_H_IMPL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONSOLE_IMPLEMENTATION
#include "console.h"

Args parse_args(int _argc, char** _argv) {
	if (_argc > 1) {
		if ((strcmp(_argv[1],"--help") == 0) || (strcmp(_argv[1],"-h") == 0)) {
			return (Args){NULL, true, HELP_FLAG};
		}
		if (_argc != 2) {
			return (Args){NULL, true, ARGS_NOT_2};
		}
		FILE* file;
		if ((file = fopen(_argv[1],"r"))) {
			return (Args){file, false, -1};
		} else {
			return (Args){NULL, true, INPUT_NOT_EXIST};
		}
	}
	return (Args){NULL, true, ARGS_NOT_2};
}

void print_args_error(int error_m) {
	switch (error_m) {
		case ARGS_NOT_2:
			ERROR(ARGS_NOT_2_M);
		break;
		case INPUT_NOT_EXIST:
			ERROR(INPUT_NOT_EXIST_M);
		break;
		default:
			console(RED); printf("%d\n", error_m);
			printf("[PANIC IN FILE %s AT LINE %d] NOT A VALID ERROR TYPE\n", __FILE__, __LINE__);
			exit(1);
		break;
	}
}

#endif // _ARGS_H_IMPL

#endif // _ARGS_H