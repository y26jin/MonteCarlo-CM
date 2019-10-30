#pragma once

class EuropeanGenerator
{
public:
	EuropeanGenerator(double d, double v, double rf, double init, int num): dt_(d), volatility_(v), rfRate_(rf), initPrice_(init), numSteps_(num){}
	double priceOption();
private:
	double dt_;
	double volatility_;
	double rfRate_;// risk-free interest rate
	double initPrice_;
	int numSteps_;
};