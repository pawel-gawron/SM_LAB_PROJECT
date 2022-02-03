/*
 * PID_controller.h
 *
 *  Created on: Jan 31, 2022
 *      Author: Paweł
 */

#ifndef INC_PID_CONTROLLER_H_
#define INC_PID_CONTROLLER_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Typedef -------------------------------------------------------------------*/
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

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Initialisation PID controller
 * @param[in] pid_data PID handler
 * @param[in] kp_init Proportional value
 * @param[in] ki_init Integral value
 * @param[in] kd_init Derivative value
 * @param[in] dt_init Sampling value
 * @param[in] anti_windup_limit_init Anti-windup limit
 * @return None
 */
void pid_init(pid_str *pid_data, float kp_init, float ki_init, float kd_init, float dt_init, int anti_windup_limit_init);

/**
 * @brief Calculate PWM value
 * @param[in] pid_data PID handler
 * @param[in] setpoint Set value
 * @param[in] frequency Current speed value
 * @return Value of PWM
 */
int pid_calculate(pid_str *pid_data, int setpoint, int process_variable);

#endif /* INC_PID_CONTROLLER_H_ */
