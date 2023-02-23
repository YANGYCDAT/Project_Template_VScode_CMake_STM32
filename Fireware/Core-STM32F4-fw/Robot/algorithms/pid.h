#pragma once

class Pid {
public:
    float m_kp;
    float m_ki;
    float m_kd;

    float m_output; // PID operation result
	float m_output_p; // proportional output
	float m_output_i; // integral output
	float m_output_d; // differential output

	float m_error; // this error
	float m_error_pre; // last error
	float m_error_sum; // sum error
    float m_error_threshold; // The error threshold involved in the error sum

    float m_output_max; // output limit of PID operation
	float m_output_p_max; //  max limit of proportional output
	float m_output_i_max; //  max limit of integral output
	float m_output_d_max; //  max limit of differential output


    Pid(float kp, float ki, float kd, float error_threshold, 
    float output_max, float output_p_max, float output_i_max, float output_d_max);
    
    void CalWeakenPID(float error);
};