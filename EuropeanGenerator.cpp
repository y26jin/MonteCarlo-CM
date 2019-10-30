#include <iostream>
#include <random>
#include "EuropeanGenerator.h"

double EuropeanGenerator::priceOption() 
{
	unsigned int T = 100;
	std::random_device rd;
	std::mt19937_64 mt(rd()); // generate a random number based on the seed 
	std::normal_distribution<> nd;

	//// use Black-Scholes formula to generate price
	//// assuming it follows brownian motion

	auto newPrice = [v = volatility_, rf = rfRate_, dt = dt_](double prevPrice, double norm) {
		double price = 0.0;
		double arg1 = (rf - (v * v) / 2.0) * dt;
		double arg2 = v * norm * sqrt(dt);
		price = prevPrice * exp(arg1 + arg2);
		return price;
	};

	double finalPrice = initPrice_;
	for (unsigned int i = 0; i < numSteps_; ++i) {
		finalPrice = newPrice(finalPrice, nd(mt));
	}

	return finalPrice;
}