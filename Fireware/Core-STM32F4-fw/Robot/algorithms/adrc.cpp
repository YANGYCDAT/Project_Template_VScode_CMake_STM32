#include "adrc.h"
#include "math.h"


/**
*@brief     symbolic function
*
*@param     pNumber original value
*
*@return    float 0 or 1 or -1
*/
float Sgn(float fpNumber)
{
	if(fpNumber > 0)
	{
		return 1;
	}
	else if(fpNumber < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}



/**
*@brief Adrc-TD 
* 
*@param 
*/
Adrc_TD::Adrc_TD(float r_value, float h_value, float t_value)
{
    m_r = r_value;
    m_h = h_value;
    m_T = t_value;
}



/**
*@brief Adrc-TD algorithm
* 
*@param float aim: aim position
*/
void Adrc_TD::CalAdrcTD(float aim)
{
    float d,d0,y,a0,a=0,fhan;
    m_aim = aim;
	m_x = m_x1 - m_aim;
	d = m_r * m_h;
	d0 = m_h * d;
	y = m_x + m_h * m_x2;
	a0 = sqrt(d * d + 8 * m_r * fabs(y));

	if(fabs(y) > d0)
		a = m_x2 + (a0 - d) * Sgn(y) / 2;
	else
		a = m_x2 + y / m_h;

	if(fabs(a) > d)
		fhan = -1 * m_r * Sgn(a);
	else
		fhan = -1 * m_r * a / d;

	m_x1 += m_T * m_x2;
	m_x2 += m_T * fhan;
}