#pragma once



class AbsEncoder {
public:
	unsigned int m_raw_value; // The original value of this encoder
	unsigned int m_pre_raw_value; // The original value of the last encoder
	int m_value_diff; // The difference between the two original values ​​​​of the encoder
	int m_resolution; // encoder lines
	float m_sum_value; // encoder accumulative value
	unsigned int m_zero_value; // encoder zero value(suit the mechanism)

    void EncodeValueUpdate(int value);

	AbsEncoder(unsigned int zero_value, unsigned int resolution) {
		m_zero_value = zero_value;
		m_resolution = resolution;

		m_pre_raw_value = 0;
		m_raw_value = 0;
		m_sum_value = 0;
	};
	~AbsEncoder();
};