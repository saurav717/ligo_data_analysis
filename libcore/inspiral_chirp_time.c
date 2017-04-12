/*
 * inspiral_chirp_time.c
 *
 *  Created on: Apr 12, 2017
 *      Author: marcnormandin
 */

#include "../libcore/inspiral_chirp_time.h"

#include "../libcore/inspiral_chirp.h"

/* this routine was written for the PSO code. The above code should use it. TODO */
void CF_CT_compute(double f_low, double chirp_time0, double chirp_time1_5, inspiral_chirp_time_t *ct) {
	ct->chirp_time0 = chirp_time0;
	ct->chirp_time1_5 = chirp_time1_5;

	double calculated_reduced_mass = Chirp_Calc_CalculatedTotalMass(f_low, chirp_time0, chirp_time1_5);
	double calculated_total_mass = Chirp_Calc_CalculatedTotalMass(f_low, chirp_time0, chirp_time1_5);
	double multi_fac_cal = Chirp_Calc_MultiFacCal(f_low, calculated_total_mass);
	double s_mass_ratio_cal = Chirp_Calc_SMassRatioCal(calculated_reduced_mass, calculated_total_mass);

	ct->chirp_time1 =  Chirp_Calc_Time1(f_low, multi_fac_cal, s_mass_ratio_cal);
	ct->chirp_time2 =  Chirp_Calc_Time1(f_low, multi_fac_cal, s_mass_ratio_cal);

	double calc_tchirp = Chirp_Calc_TChirp(ct->chirp_time0, ct->chirp_time1, ct->chirp_time1_5, ct->chirp_time2);

	/* careful because this doesn't use time of arrival because the network statistic wants it as 0 */
	ct->tc = calc_tchirp;
}
