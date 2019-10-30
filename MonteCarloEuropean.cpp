// MonteCarloEuropean.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <numeric>

#include "MonteCarloEuropean.h"
#include "EuropeanGenerator.h"

// cuda start
#include "test.cuh"
// cuda end

int main()
{
	// multithread
	// simulate 100 scenarios
	std::cout << "Multithreading===" << std::endl;
	unsigned int numScenarios = 100;
	
	std::vector<std::thread> ths;
	std::vector<double> scenarioPrices;
	for(unsigned int i=0;i<numScenarios;++i)
	{
		std::promise<double> promisedPrice;
		std::future<double> futureObj = promisedPrice.get_future();
		auto callback = [](std::promise<double>* promised) {
			// use Black-Scholes formula to generate price
			// assuming it follows brownian motion
			double rfRate{ 0.025 }; // risk-free interest rate
			double volatility{ 0.06 };
			double initPrice{ 100.0 };
			int numTimesteps = 12;
			double delta = 1.0 / numTimesteps;

			EuropeanGenerator eu{ delta, volatility, rfRate, initPrice, numTimesteps };
			double finalPrice = eu.priceOption();
			promised->set_value(finalPrice); 
		};
		
		ths.push_back(std::thread(callback, &promisedPrice));
		double res = futureObj.get();
		std::cout << "scenario" << i + 1 << ", final price = " << res << std::endl;
		scenarioPrices.push_back(res);
	}

	for (std::thread & t : ths)
	{
		if (t.joinable()) t.join();
	}

	// average price of all scenarios
	std::cout << std::accumulate(scenarioPrices.begin(), scenarioPrices.end(), 0.0, [](double a, double b) {return (a + b) / 2; }) << std::endl;
    // cuda start
    myk();
    //int a, b, c;
    //int* dev_c;
    //a = 3;
    //b = 4;
    //cudaMalloc((void**)&dev_c, sizeof(int));
    //add << <1, 1 >> > (a, b, dev_c);
    //cudaMemcpy(&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost);
    //std::cout << a << "+" << b << "=" << c << std::endl;
    //cudaFree(dev_c);
    // cuda end

	return 0;
}
