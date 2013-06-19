/*
 ============================================================================
 Name        : tps40193.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float fsw = 300000;
const float vin_max = 14.0;
const float vin_min = 10.0;
const float vin_ripple = 0.6;
const float iout = 10.0;
const float i_tran = 10.0;
const float i_ripple = 2.6;
const float vout = 1.0;
const float v_over = 0.05;
const float v_under = 0.05;
const float vout_ripple = 0.04;
const float Line_reg = 0.005;
const float Load_reg = 0.005;



int main(void)
{
	float L_val;
	float I_L_rms;
	float C_out_min_uF;
	float I_charge;
	float I_L_peak;
	L_val = ((vin_max - vout)/(0.3 * iout))*(vout/vin_max)*(1/fsw)*(1000000);
	printf("L = %.2fuH\n", L_val);

	L_val = 1.0;
	I_L_rms = sqrt(((iout*iout)+((i_ripple*i_ripple)/12)));
	printf("I_L_rms = %.2fA\n", I_L_rms);

	if (vin_min >= vout*2){
		C_out_min_uF = (i_tran*i_tran*L_val)/(vout*v_over);
	}
	else
	{
		C_out_min_uF = (i_tran*i_tran*L_val)/((vin_min - vout)*v_under);
	}
	printf("C_out_min_uF = %.2fuF\n", C_out_min_uF);

	I_charge = vout*C_out_min_uF/3;
	printf("I_charge = %.2fmA\n", I_charge);
	I_L_peak = iout + (i_ripple/2) + (I_charge/1000);
	printf("I_L_peak = %.2fA\n", I_L_peak);

	return EXIT_SUCCESS;
}
