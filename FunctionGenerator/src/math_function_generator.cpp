#include <iostream>

#include <list>

#include "math_function_generator.h"

// *********************************************************
// 	MathFunctionGenerator::MathFunctionGenerator()
//    constructor - register tokens which will be searched
// *********************************************************
MathFunctionGenerator::MathFunctionGenerator(){
	initialize();
	setXParams(0.0, 10.0, 1.0);
	setTParams(0.0, 10.0, 1.0);

	// ***** register operators, functions, etc. ********
	Token<MathFunctionGenerator> tk;

	//operators - Currently, binary operators using infix notation are acceptable
	tk.initialize("^", BR_OPERATOR, 5, &MathFunctionGenerator::calc_pow);
	registerKey(tk);
	tk.initialize("*", BL_OPERATOR, 3, &MathFunctionGenerator::calc_mul);
	registerKey(tk);
	tk.initialize("/", BL_OPERATOR, 3, &MathFunctionGenerator::calc_div);
	registerKey(tk);
	tk.initialize("%", BL_OPERATOR, 3, &MathFunctionGenerator::calc_mod);
	registerKey(tk);
	tk.initialize("+", BL_OPERATOR, 1, &MathFunctionGenerator::calc_add);
	registerKey(tk);
	tk.initialize("-", BL_OPERATOR, 1, &MathFunctionGenerator::calc_sub);
	registerKey(tk);

	//functions
	tk.initialize("sign", FUNCTION, 1, &MathFunctionGenerator::calc_sign);
	registerKey(tk);
	tk.initialize("abs", FUNCTION, 1, &MathFunctionGenerator::calc_abs);
	registerKey(tk);

	tk.initialize("ceil", FUNCTION, 1, &MathFunctionGenerator::calc_ceil);
	registerKey(tk);
	tk.initialize("floor", FUNCTION, 1, &MathFunctionGenerator::calc_floor);
	registerKey(tk);

	tk.initialize("sqrt", FUNCTION, 1, &MathFunctionGenerator::calc_sqrt);
	registerKey(tk);
	tk.initialize("exp", FUNCTION, 1, &MathFunctionGenerator::calc_exp);
	registerKey(tk);

	tk.initialize("ln", FUNCTION, 1, &MathFunctionGenerator::calc_ln);
	registerKey(tk);
	tk.initialize("log", FUNCTION, 1, &MathFunctionGenerator::calc_log);
	registerKey(tk);

	tk.initialize("sin", FUNCTION, 1, &MathFunctionGenerator::calc_sin);
	registerKey(tk);
	tk.initialize("cos", FUNCTION, 1, &MathFunctionGenerator::calc_cos);
	registerKey(tk);
	tk.initialize("tan", FUNCTION, 1, &MathFunctionGenerator::calc_tan);
	registerKey(tk);

	tk.initialize("asin", FUNCTION, 1, &MathFunctionGenerator::calc_asin);
	registerKey(tk);
	tk.initialize("acos", FUNCTION, 1, &MathFunctionGenerator::calc_acos);
	registerKey(tk);
	tk.initialize("atan", FUNCTION, 1, &MathFunctionGenerator::calc_atan);
	registerKey(tk);
	tk.initialize("atan2", FUNCTION, 2, &MathFunctionGenerator::calc_atan2);
	registerKey(tk);

	tk.initialize("sinh", FUNCTION, 1, &MathFunctionGenerator::calc_sinh);
	registerKey(tk);
	tk.initialize("cosh", FUNCTION, 1, &MathFunctionGenerator::calc_cosh);
	registerKey(tk);
	tk.initialize("tanh", FUNCTION, 1, &MathFunctionGenerator::calc_tanh);
	registerKey(tk);

	//constants
	tk.initialize("pi", FUNCTION, 0, &MathFunctionGenerator::calc_pi);
	registerKey(tk);
	tk.initialize("e", FUNCTION, 0, &MathFunctionGenerator::calc_e);
	registerKey(tk);

	//tk.initialize("C", FUNCTION, 1, &MathFunctionGenerator::calc_c);
	//registerKey(tk);


	//variables
	tk.initialize("random()", VARIABLE, 0, &MathFunctionGenerator::calc_random);
	registerKey(tk);
	tk.initialize("x", VARIABLE, 0, &MathFunctionGenerator::calc_x);
	registerKey(tk);
	tk.initialize("t", VARIABLE, 0, &MathFunctionGenerator::calc_t);
	registerKey(tk);
}

// **************************************************************************************
//  int MathFunctionGenerator::setXParams(double min_val, double max_val, double delta)
//    set parameters for variable x
//    min_val - minimum value of x
//    max_val - maximum value of x
//    delta - incremental value of x
//    return 0 iff no error
// **************************************************************************************
int MathFunctionGenerator::setXParams(double min_val, double max_val, double delta){
	if((min_val > max_val)||(delta < 0.0)||((min_val != max_val)&&(delta == 0.0))){
		std::cerr << "Error in MathFunctionGenerator::setXParams(): invalid arguments" << std::endl;
		return 1;
	}

	x_min = min_val;
	x_max = max_val;
	if(delta == 0.0){
		x_delta = 1.0;
	}else{
		x_delta = delta;
	}

	x = min_val;

	return 0;
}

// **************************************************************************************
//  int MathFunctionGenerator::setTParams(double min_val, double max_val, double delta)
//    set parameters for variable t
//    min_val - minimum value of t
//    max_val - maximum value of t
//    delta - incremental value of t
//    return 0 iff no error
// **************************************************************************************
int MathFunctionGenerator::setTParams(double min_val, double max_val, double delta){
	if((min_val > max_val)||(delta < 0.0)||((min_val != max_val)&&(delta == 0.0))){
		std::cerr << "Error in MathFunctionGenerator::setTParams(): invalid arguments" << std::endl;
		return 1;
	}

	t_min = min_val;
	t_max = max_val;
	if(delta == 0.0){
		t_delta = 1.0;
	}else{
		t_delta = delta;
	}

	t = min_val;

	return 0;
}

// **********************************************************************
// 	int MathFunctionGenerator::putFunction(std::list<double> &out_list)
//    calculate the value
//    return 0 if no error
//           >0 if error
//           <0 if exception occured, e.g. division by zero etc.
// **********************************************************************
int MathFunctionGenerator::putFunction(std::list<double> &out_list){
	bool check_exception = false;
	int res;
	double val;

	unsigned int i;

	for(x=x_min;x<=x_max;x+=x_delta){
		for(i=0;i<getCommandNum();i++){
			res = evaluateRPN(i, val);
			if(res>0){return res;}
			else if(res<0){check_exception=true;}

			out_list.push_back(val);
		}
	} //end for(x)

	//update time variable
	t += t_delta;
	if(t>t_max){
		t = t_min;
	}

	if(check_exception){
		return -1;
	}else{
		return 0;
	}
}

// ******** Calclutaion Functions ******************************** //
double MathFunctionGenerator::calc_x(std::list<double> &a_list){
	if(!a_list.empty()){
		throw "Exception: Invalid number of arguments";
	}

	return x;
}

double MathFunctionGenerator::calc_t(std::list<double> &a_list){
	if(!a_list.empty()){
		throw "Exception: Invalid number of arguments";
	}

	return t;
}

