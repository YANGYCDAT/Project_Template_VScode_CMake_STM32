#pragma once

class Adrc_TD {
public:
    float m_x1;		//位置
    float m_x2;		//速度
    float m_x;		//位移
    float m_r;		//TD阻尼因子（决定跟踪速度，r越大跟得越快，如果追求快速响应，微分预测的滤波效果会变差）
    float m_h;		//TD滤波因子（算法式中的h0，h0越大微分预测的滤波效果越好）
    float m_T;		//TD积分步长（h为步长,h越小滤波效果越好，这个值应该与采样周期一致）
    float m_aim;	//目标位置

    Adrc_TD(float r_value, float h_value, float t_value);
    ~Adrc_TD(){};

    void CalAdrcTD(float aim);
};