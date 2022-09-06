#include <cmath>
#include <limits>

#include "convert.h"

// **************************************************
// 	double toUInt8(double val)
//    Convert double data to 8bit unsigned int data
//    val - input data
//    return - converted value
// **************************************************
double toUInt8(double val){
	const double ubound = 255; //Maximum number
	const double lbound = 0; //Minimum number

	const double nan = 0; //Not a number
	const double pinf = ubound; //Infinity
	const double ninf = lbound; //-Infinity

	return convertIntVal(val, ubound, lbound, nan, pinf, ninf);
}

// **************************************************
// 	double toInt16(double val)
//    Convert double data to 16bit signed int data
//    val - input data
//    return - converted value
// **************************************************
double toInt16(double val){
	const double ubound = 32767; //Maximum number
	const double lbound = -32768; //Minimum number

	const double nan = 0; //Not a number
	const double pinf = ubound; //Infinity
	const double ninf = lbound; //-Infinity

	return convertIntVal(val, ubound, lbound, nan, pinf, ninf);
}

// ***************************************************
// 	double toUInt16(double val)
//    Convert double data to 16bit unsigned int data
//    val - input data
//    return - converted value
// ***************************************************
double toUInt16(double val){
	const double ubound = 65535; //Maximum number
	const double lbound = 0; //Minimum number

	const double nan = 0; //Not a number
	const double pinf = ubound; //Infinity
	const double ninf = lbound; //-Infinity

	return convertIntVal(val, ubound, lbound, nan, pinf, ninf);
}

// *************************************************
// 	double toInt32(double val)
//    Convert double data to 32bit signed int data
//    val - input data
//    return - converted value
// *************************************************
double toInt32(double val){
	const double ubound = 2147483647.0; //Maximum number
	const double lbound = -2147483648.0; //Minimum number

	const double nan = 0; //Not a number
	const double pinf = ubound; //Infinity
	const double ninf = lbound; //-Infinity

	return convertIntVal(val, ubound, lbound, nan, pinf, ninf);
}

// *************************************************
// 	double toUInt32(double val)
//    Convert double data to 32bit signed int data
//    val - input data
//    return - converted value
// *************************************************
double toUInt32(double val){
	const double ubound = 4294967295.0; //Maximum number
	const double lbound = 0; //Minimum number

	const double nan = 0; //Not a number
	const double pinf = ubound; //Infinity
	const double ninf = lbound; //-Infinity

	return convertIntVal(val, ubound, lbound, nan, pinf, ninf);
}

// **************************************
// 	float toFloat(double val)
//    Convert double data to float data
//    val - input data
//    return - converted value
// **************************************
float toFloat(double val){
	const float ubound = std::numeric_limits<float>::max(); //Maximum number: 0x7f7fffff
	const float lbound = -std::numeric_limits<float>::max(); //Minimum number

	const float nan = std::numeric_limits<float>::quiet_NaN(); //Not a number for single precisition floating-point data: 0x7fc00000
	const float pinf = std::numeric_limits<float>::infinity(); //Infinity for single precisition floating-point data: 0x7f800000
	const float ninf = -std::numeric_limits<float>::infinity(); //-Infinity for single precisition floating-point data: 0xff800000

	//check if val is a special number
	if(std::isnan(val)){ //NaN
		return nan;
	}else if(std::isinf(val)){ //infinity
		if(val>0){ //positive
			return pinf;
		}else{ //negative
			return ninf;
		}
	}else{ //normal number
		if(val>=ubound){ //upper bound
			return ubound;
		}else if(val<=lbound){ //lower bound
			return lbound;
		}else{
			return (float)val;
		}
	}
}

// *******************************************************************************************************
// 	double convertIntVal(double val, double ubound, double lbound, double nan, double pinf, double ninf)
//    Convert double data to int data based on the paramters
//    val - input data
//    ubound - maximum value (if val>=ubound, the return is set to this value)
//    lbound - minimum value (if val<=lbound, the return is set to this value)
//    nan - returned value if val is not a number (NaN)
//    pinf - returned value if val is positive infinity
//    ninf - returned value if val is negative infinity
// *******************************************************************************************************
double convertIntVal(double val, double ubound, double lbound, double nan, double pinf, double ninf){
	const double epsilon = 1.0e-12;

	//check if val is a special number
	if(std::isnan(val)){ //NaN
		return nan;
	}else if(std::isinf(val)){ //infinity
		if(val>0){ //positive
			return pinf;
		}else{ //negative
			return ninf;
		}
	}else{ //normal number
		if(val>=ubound){ //upper bound
			return ubound;
		}else if(val<=lbound){ //lower bound
			return lbound;
		}else{
			return std::floor(val+epsilon); //round down
		}
	}
}
