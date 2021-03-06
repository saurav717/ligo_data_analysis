/*
 * interp_strain.h
 *
 *  Created on: Mar 4, 2017
 *      Author: marcnormandin
 */

#ifndef SRC_C_STRAIN_INTERPOLATE_H_
#define SRC_C_STRAIN_INTERPOLATE_H_

#include "strain.h"

strain_t* InterpStrain_malloc_and_compute(strain_t* strain, double sampling_frequency, size_t num_time_samples);

#endif /* SRC_C_STRAIN_INTERPOLATE_H_ */
