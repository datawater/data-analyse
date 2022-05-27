#ifndef _DMATH_H
#define _DMATH_H 0

float dm_avg(int arr[],int arr_size);
float dm_med(int arr[],int arr_size);

// TODOOOO(#1): implement more functions

#ifdef _DMATH_H_IMPL
#include <math.h> // TODO: Only for floor so maybe we can implement our own floor??

float dm_avg(int arr[], int arr_size) {
	int sum_ = 0;
	for (int i = 0; i < arr_size; ++i) {sum_ += arr[i];}
	return sum_ / arr_size;
}

float dm_med(int arr[], int arr_size) {
	if (arr_size % 2 != 0) {
		return arr[arr_size/2];
	}
	return (arr[(int) floor((arr_size-1)/2)]+arr[(int) floor((arr_size+1)/2)]);
}

#endif // _DMATH_H_IMPL

#endif // _DMATH_H
