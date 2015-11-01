#include <papi.h>
#include <stdio.h>

bool papi_supported = true;
int events[4] = {PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM, PAPI_L1_ICM}; //Only these works

long long values[4] = {0,};

int eventSet = PAPI_NULL;
int eventSet2 = PAPI_NULL;

int papi_err;

void init(){
	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
		fprintf(stderr, "PAPI is unsupported.\n");
		papi_supported = false;
	}

	if (PAPI_num_counters() < 5) {
		fprintf(stderr, "PAPI is unsupported.\n");
		papi_supported = false;
	}

	if ((papi_err = PAPI_create_eventset(&eventSet)) != PAPI_OK) fprintf(stderr, "Could not create event set: %s\n", PAPI_strerror(papi_err));

	for (int i=0; i<4; ++i) if ((papi_err = PAPI_add_event(eventSet, events[i])) != PAPI_OK ) 
		        fprintf(stderr, "Could not add event: %d %s\n", i, PAPI_strerror(papi_err));



	/* start counters */
	if (papi_supported && (papi_err = PAPI_start(eventSet)) != PAPI_OK) 
                fprintf(stderr, "Could not start counters: %s\n", PAPI_strerror(papi_err));
}

void print(){
	if (papi_supported) {
			if ((papi_err = PAPI_stop(eventSet, values)) != PAPI_OK) fprintf(stderr, "Could not get values: %s\n", PAPI_strerror(papi_err));
			printf("\tLevel 1 cache misses: %ld\n", values[0]);
			printf("\tLevel 2 cache misses: %ld\n", values[1]);
			printf("\tLevel 3 cache misses: %ld\n", values[2]);
			printf("\tLevel 1 instruction cache misses: %ld\n", values[3]);
		}
}



