#ifndef MATH_FUNCTION_GENERATOR_H
#define MATH_FUNCTION_GENERATOR_H

#include <list>

#include "scientific_calculator_base.h"

class MathFunctionGenerator : public ScientificCalculatorBase<MathFunctionGenerator>{
	double x_min;
	double x_max;
	double x_delta;
	double x;

	double t_min;
	double t_max;
	double t_delta;
	double t;

	double exec_calc(pFuncType p, std::list<double> &arg_list){
		return (this->*p)(arg_list);
	}

	//Functions
	double calc_x(std::list<double> &a_list);
	double calc_t(std::list<double> &a_list);

public:
	MathFunctionGenerator();

	int setXParams(double min_val, double max_val, double delta);
	int setTParams(double min_val, double max_val, double delta);

	double getXMin(){return x_min;}
	double getXMax(){return x_max;}
	double getXDelta(){return x_delta;}
	double getTMin(){return t_min;}
	double getTMax(){return t_max;}
	double getTDelta(){return t_delta;}

	int putFunction(std::list<double> &out_list);
};


#endif
