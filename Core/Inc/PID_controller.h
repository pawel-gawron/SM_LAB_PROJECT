/*
 * PID_controller.h
 *
 *  Created on: Jan 31, 2022
 *      Author: Paweł
 */

#ifndef INC_PID_CONTROLLER_H_
#define INC_PID_CONTROLLER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int previous_error;
	int total_error;
	int previous_integral;
	int integral;
	int derivative;
	float Kp;
	float Ki;
	float Kd;
	float dt;
	int anti_windup_limit;
}pid_str;

void pid_init(pid_str *pid_data, float kp_init, float ki_init, float kd_init, float dt_init, int anti_windup_limit_init);

int pid_calculate(pid_str *pid_data, int setpoint, int process_variable);

#endif /* INC_PID_CONTROLLER_H_ */
