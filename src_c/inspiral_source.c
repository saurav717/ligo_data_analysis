/*
 * source.c
 *
 *  Created on: Mar 9, 2017
 *      Author: marcnormandin
 */

#include <stdio.h>

#include <gsl/gsl_const_mksa.h>
#include <gsl/gsl_math.h>

#include "inspiral_source.h"

void Source_print(source_t* source) {
	printf("right ascension: %f\n", source->sky.ra);
	printf("declination: %f\n", source->sky.dec);
	printf("polarization angle: %f\n", source->polarization_angle);
	printf("coalesce phase: %f\n", source->coalesce_phase);
	printf("inclination: %f\n", source->inclination_angle);
	printf("binary mass 1: %f\n", source->m1);
	printf("binary mass 2: %f\n", source->m2);
	printf("time of arrival: %f\n", source->time_of_arrival);
	printf("snr: %f\n", source->snr);
}

void Source_load_testsource(source_t* source) {
	source->sky.ra = -2.14;
	source->sky.dec = 0.72;
	source->polarization_angle = 0.0;
	source->coalesce_phase = 0.0;
	source->inclination_angle = 0.0;
	source->m1 = 1.4 * GSL_CONST_MKSA_SOLAR_MASS; /* binary mass 1 */
	source->m2 = 1.4 * GSL_CONST_MKSA_SOLAR_MASS; /* binary mass 2 */
	source->time_of_arrival = 1.0;
	source->snr = 9.0;
}