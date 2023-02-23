#include "pid.h"
#include "math.h"



/**
*@brief clipping function, remove the value beyond the maximum and minimum value, and replace it with the maximum or minimum value
*
*@param value: input data
*@param min: clipping minimum value
*@param max: clipping maximum
*
*@return clipped data
*/
float Clip(float value, float min, float max)
{
	float ret;
	if(value < min)
	{
		ret = min;
	}
	else if(value > max)
	{
		ret = max;
	}
	else
	{
		ret = value;
	}
	return ret;
}



/**
*@brief Pid constructor
* 
*@param 
*/
Pid::Pid(float kp, float ki, float kd, float error_threshold, 
    float output_max, float output_p_max, float output_i_max, float output_d_max)
{
    m_kp = kp;
    m_ki = ki;
    m_kd = kd;
    m_error_threshold = error_threshold;
    m_output_max = output_max;
    m_output_p_max = output_p_max;
    m_output_i_max = output_i_max;
    m_output_d_max = output_d_max;
}



/**
*@brief PID improvement algorithm for weakening in case of limit
* 
*@param float error: input error of pid control
*/
void Pid::CalWeakenPID(float error)
{
	m_error = error;								

    // sum the error
	if(fabs(m_error) < m_error_threshold)																				
	{
		m_error_sum += m_error;																					
	}

    // calculate the PID output
	m_output_p = Clip(m_kp * m_error, -m_output_p_max, m_output_p_max);								
	m_output_i = Clip(m_ki * m_error_sum, -m_output_i_max, m_output_i_max);									
	m_output_d = Clip(m_kd * (m_error - m_error_pre), -m_output_d_max, m_output_d_max);	
	m_output = Clip(m_output_p + m_output_i + m_output_d, -m_output_max, m_output_max);	

	m_error_pre = m_error;										
}






