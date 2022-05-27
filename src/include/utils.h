#ifndef _UTILS_H
#define _UTILS_H 0

typedef int bool;

#define true 0
#define false 1

char* ERROR(char* e);

#ifdef _UTILS_H_IMPL
#endif // _UTILS_H_IMP

#include <stdio.h>
#include <stdlib.h>

#define CONSOLE_IMPLEMENTATION
#include "console.h"

char* ERROR(char* e) {
	console(RED);
	printf("[ERROR] ");
	console(RESET);
	printf(e);
	exit(1);
}

#endif // _UTILS_H