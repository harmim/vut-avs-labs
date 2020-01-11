#ifndef COMPLEXFLOAT_HPP
#define COMPLEXFLOAT_HPP

class ComplexFloat
{

public:
	float re;
	float im;

	ComplexFloat(float real, float imag): re(real), im(imag) {};
	ComplexFloat(const ComplexFloat& other): re(other.re), im(other.im) {};
	ComplexFloat(float real): re(real), im(0.0f) {};
	ComplexFloat(): re(0.0f), im(0.0f) {};

	ComplexFloat operator*(const ComplexFloat& other) const
	{
		ComplexFloat tmp;
		tmp.re = this->re * other.re - this->im * other.im;
		tmp.im = this->re * other.im + this->im * other.re;
		return tmp;
	}

	ComplexFloat operator+(const ComplexFloat& other) const
	{
		ComplexFloat tmp;
		tmp.re = this->re + other.re;
		tmp.im = this->im + other.im;
		return tmp;
	}

	ComplexFloat& operator*=(const ComplexFloat& other)
	{
		ComplexFloat tmp;

		tmp.re = this->re * other.re - this->im * other.im;
		tmp.im = this->re * other.im + this->im * other.re;
		
		*this = tmp;

		return *this;
	}

	ComplexFloat& operator+=(const ComplexFloat& other)
	{
		ComplexFloat tmp;
		
		this->re += other.re;
		this->im += other.im;
		
		return *this;
	}

	float length() const
	{
		return sqrt((this->re * this->re) + (this->im * this->im));
	}
};
#endif