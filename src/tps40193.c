/*
 	This file is part of tps40192/3 calculator.

    tps40192/3 calculator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    tps40192/3 calculator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with tps40192/3 calculator.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * The tps40192/3 calculator is a small tool to simple the design procedure.
 * the detail working flow is follow the content in datasheet page 19~26.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//chip property
const float fsw = 300000;

//system property
//input
const float vin_max = 14.0;		//V
const float vin_min = 10.0;		//V
const float vin_ripple = 0.6; 	//V
//output
const float iout = 10.0;		//A
const float vout = 1.0;			//V
const float vout_Line_reg = 0.005;
const float vout_Load_reg = 0.005;
const float vout_ripple = 0.04;	//V
const float vout_overshoot = 0.05;	//V
const float vout_undershoot = 0.05;	//V
const float iout_load_trans = 4.0;	//A

//inductor property
const float ind_given = (2.2/1000000);	//H

//Output Capacitor property
const float c_out_given = (2000.0/1000000);	//F

//Input Capacitor property
const float c_in_given = (200.0/1000000);	//F

int main(void)
{
	float ind_cal;	//H
	float i_ripple;	//A
	float ind_i_rms;

	float c_out_min;
	float c_out_esr_max;

	float ind_i_charge;
	float ind_i_peak;

	float c_in_min;
	float c_in_esr_max;
	float c_in_v_ripple_cap = 0.4;
	float c_in_v_ripple_esr = 0.2;
	float c_in_i_rms;

	float tmp;

	//Inductor Selection
	ind_cal = ((vin_max - vout)/(0.3 * iout))*(vout/vin_max)*(1/fsw);
	printf("Calculated inductor value is %.2fuH, Given inductor value is %.2fuH.\n", (ind_cal*1000000), (ind_given*1000000));

	i_ripple = (0.3*iout*ind_cal)/ind_given;
	printf("i_ripple = %.2fA\n", i_ripple);

	ind_i_rms = sqrt(((iout*iout)+((i_ripple*i_ripple)/12)));
	printf("ind_i_rms = %.2fA\n", ind_i_rms);

	//Output Capacitor Selection (C8)
	if (vin_min >= vout*2){
		c_out_min = (iout_load_trans*iout_load_trans*ind_given)/(vout*vout_overshoot);
	}
	else
	{
		c_out_min = (iout_load_trans*iout_load_trans*ind_given)/((vin_min - vout)*vout_undershoot);
	}
	printf("Calculated output capacitor value is %.2fuF, Given output capacitor value is %.2fuF.\n", (c_out_min*1000000), (c_out_given*1000000));

	c_out_esr_max = (vout_ripple - (i_ripple/(c_out_given * fsw)))/i_ripple;
	printf("c_out_esr_max = %.2fm¦¸\n", (c_out_esr_max*1000));

	//Peak Current Rating of the Inductor
	ind_i_charge = vout*c_out_given/(0.003);
	printf("ind_i_charge = %.2fmA\n", (ind_i_charge*1000));
	ind_i_peak = iout + (i_ripple/2) + ind_i_charge;
	printf("ind_i_peak = %.2fA\n", ind_i_peak);

	//Input Capacitor Selection (C7)
	c_in_min = (iout*vout)/(c_in_v_ripple_cap*vin_min*fsw);
	printf("Calculated input capacitor value is %.2fuF, Given input capacitor value is %.2fuF.\n", (c_in_min*1000000), (c_in_given*1000000));

	c_in_esr_max = c_in_v_ripple_esr/(iout+(i_ripple/2));
	printf("c_in_esr_max = %.2fm¦¸\n", (c_in_esr_max*1000));

	tmp = sqrt(vout/vin_min);
	c_in_i_rms = ((iout+(i_ripple/12))*tmp) - (vout*iout/vin_min);
	printf("c_in_i_rms = %.2fA\n", c_in_i_rms);

	//TODO

	//MOSFET Switch Selection (Q1, Q2)

	//Boot Strap Capacitor

	//Input Bypass Capacitor (C6)

	//BP5 Bypass Capacitor (C5)

	//Input Voltage Filter Resistor (R11)

	//Short Circuit Protection (R9)

	//Feedback Compensation

	//Feedback Divider (R7, R8)

	//Error Amplifier Compensation (R6, R10, C1, C2, C3)

	return EXIT_SUCCESS;
}
