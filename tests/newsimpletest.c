/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newsimpletest.c
 * Author: r2d2
 *
 * Created on March 28, 2016, 10:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "simul_management.h"

/*
 * Simple C Test Suite
 */

void testIs_floor_clean() {
	_Bool* array;
	const unsigned int w;
	const unsigned int h;
	int result = is_floor_clean(array, w, h);
	if (1 /*check result*/) {
		printf("%%TEST_FAILED%% time=0 testname=testIs_floor_clean (newsimpletest) message=error message sample\n");
	}
}

int main(int argc, char** argv) {
	printf("%%SUITE_STARTING%% newsimpletest\n");
	printf("%%SUITE_STARTED%%\n");

	printf("%%TEST_STARTED%%  testIs_floor_clean (newsimpletest)\n");
	testIs_floor_clean();
	printf("%%TEST_FINISHED%% time=0 testIs_floor_clean (newsimpletest)\n");

	printf("%%SUITE_FINISHED%% time=0\n");

	return (EXIT_SUCCESS);
}
