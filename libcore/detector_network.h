#ifndef SRC_C_DETECTOR_NETWORK_H_
#define SRC_C_DETECTOR_NETWORK_H_

#include "detector.h"
#include "sky.h"

#if defined (__cplusplus)
extern "C" {
#endif

/* The detector network used in the study. */
typedef struct detector_network_s {
	size_t num_detectors;
	detector_t** detector;

} detector_network_t;

detector_network_t* Detector_Network_alloc(size_t num_detectors);

void Detector_Network_free(detector_network_t* net);

void Detector_Network_print(detector_network_t* net);

detector_network_t* Detector_Network_load( const char* detector_mapping_file, size_t num_time_samples, double sampling_frequency, double f_low, double f_high );

double Detector_Network_condition_number_M(detector_network_t* net, sky_t* sky, double polarization_angle);

double Detector_Network_condition_number_F(detector_network_t* net, sky_t* sky, double polarization_angle);


#if defined (__cplusplus)
}
#endif

#endif /* SRC_C_DETECTOR_NETWORK_H_ */
