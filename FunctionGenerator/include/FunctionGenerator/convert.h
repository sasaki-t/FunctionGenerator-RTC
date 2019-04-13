#ifndef CONVERT_H
#define CONVERT_H

double toUInt8(double val);
double toInt16(double val);
double toUInt16(double val);
double toInt32(double val);
double toUInt32(double val);
double convertIntVal(double val, double ubound, double lbound, double nan, double pinf, double ninf);
float toFloat(double val);

#endif
