/*
 * PID_controller.c
 *
 *  Created on: Jan 31, 2022
 *      Author: Paweł
 */

#include "PID_controller.h"

void pid_init(pid_str *pid_data, float kp_init, float ki_init, float kd_init, float dt_init, int anti_windup_limit_init)
{
	pid_data->previous_error = 0;
	pid_data->total_error = 0;
	pid_data->previous_integral = 0;

	pid_data->Kp = kp_init;
	pid_data->Ki = ki_init;
	pid_data->Kd = kd_init;
	pid_data->dt = dt_init;

	pid_data->anti_windup_limit = anti_windup_limit_init;
}

int pid_calculate(pid_str *pid_data, int setpoint, int frequency)
{
	int error;
	float p_term, i_term, d_term;
	uint16_t PID;

	  error = setpoint - frequency;

	  p_term = (float)(pid_data->Kp * error);

	  pid_data->integral = pid_data->previous_integral + (error + pid_data->previous_error);
	  pid_data->previous_integral = pid_data->integral;
	  i_term = pid_data->Ki*pid_data->integral*(pid_data->dt/2);

	  pid_data->derivative = (error - pid_data->previous_error)/pid_data->dt;
	  pid_data->previous_error = error;
	  d_term = pid_data->Kd*pid_data->derivative;

	  if(i_term >= pid_data->anti_windup_limit) i_term = pid_data->anti_windup_limit;
	  else if(i_term <= -pid_data->anti_windup_limit) i_term = -pid_data->anti_windup_limit;

	  PID = (uint16_t)(p_term + i_term + d_term);

	  if (PID > 1000)
	  {
		  PID = 1000;
	  }
	  else if(PID < 0)
	  {
		  PID = 0;
	  }

	  return PID;
}
