#include <stdio.h>
#include <string.h>
#include <errno.h>

#define _UTILS_H_IMPL
#include "include/utils.h"

#define _ARGS_H_IMPL
#include "include/args.h"

#define _DMATH_H_IMPL
#include "include/dmath.h"

#define CONSOLE_IMPLEMENTATION
#include "include/console.h"

#define arr_size(x) sizeof(x)/sizeof(x[0])

// Stolen from https://www.geeksforgeeks.org/selection-sort/

void sel_sort(int a[], int n, int ap) {
	for (int i = 0; i < n-1; i++) {
		int m = i;
		for (int j = i+1; j < n; j++)
			if (a[j] < a[m])
				m = j;
		int t = a[m]; a[m] = a[i]; a[i] = t;
	}

	// This function for some reason places the result at the end of the array
	// and this for loop is to fix it

	for (int i = 0; i < n-1; i++) {
		a[i] = a[n-ap];
		ap--;
	}
}

void usage(char* pr_name) {
	console(CYAN); printf("Usage:\n"); console(RESET);
	printf("\t%s <InputFile>\n", pr_name);
	exit(0);
}

void print_info(int arr_[256], int arr_ap) {
	int arr[256] = {0};
	memcpy(arr,arr_,256);

	printf("The Data:\n```\n");
	for (int i = 0; i < arr_ap; ++i) {
		printf("%i",arr[i]);
		i != arr_ap-1 ? printf(", ") : printf("\n```\n");
	}
	sel_sort(arr,arr_size(arr), arr_ap);

	printf("\n```\n~~~~~~\nThe Sorted Data:\n```\n");
	for (int i = 0; i < arr_ap; ++i) {
		printf("%i",arr[i]);
		i != arr_ap-1 ? printf(", ") : printf("\n```\n");
	}
	printf("The Avg of this data is: %g\n", 	 dm_avg(arr,arr_ap));
	printf("The median of this data is: %g\n",	 dm_med(arr,arr_ap));
}

int main(int argc, char** argv) {
	Args cargs = parse_args(argc,argv);
	if (cargs.Error == true) {
		if (cargs.Error_Message == HELP_FLAG) {usage(argv[0]);}
		print_args_error(cargs.Error_Message);
	}

	char* buffer = NULL;
	size_t len;
	ssize_t bytes_read = getdelim(&buffer, &len, '\0', cargs.Input_File);

	int arr[256] = {0};
	int arr_ap = 0;

	bytes_read == -1 ? ERROR(strerror(errno)) : (void) 0;

	char* ptr = strtok(buffer,",");
	while (ptr != NULL) {
		arr[arr_ap] = atoi(ptr); arr_ap++;
		ptr = strtok(NULL, ",");
	}

	print_info(arr,arr_ap);
}
