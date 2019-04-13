#ifndef SCIENTIFIC_CALCULATOR_BASE_H
#define SCIENTIFIC_CALCULATOR_BASE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <limits>

#include <stack>
//#include <queue>

#include <string>
#include <vector>
#include <list>

enum token_type{
	BL_OPERATOR, 
	BR_OPERATOR, 
	SEPARATOR, //","
	L_PARENTHESIS, //"("
	R_PARENTHESIS, //")"
	FUNCTION, //may have some argments. If no argments, it is considered as a constant - if you need you should put "()" after the name
	VARIABLE //it is almost same as the functionthe but the value is evaluated when putFunction() is called
};

template <class T>
class Token{
	typedef double (T::*pFuncType)(std::list<double> &);
public:

	std::string name;
	token_type type;
	int param; //priority for binary operators or number of arguments for functions and variables
	pFuncType calc;

	Token(){;}
	Token(const char* n, token_type tt, int p, pFuncType func){
		initialize(n, tt, p, func);
	}

	int initialize(const char* n, token_type tt, int p, pFuncType func);
};

template <class T>
class ScientificCalculatorBase{
public:
	typedef double (T::*pFuncType)(std::list<double> &);

private:
	std::vector< Token<T> > key; //commands to be searched

	std::vector< std::list<int> > type_list; //-1:Number, N(>=0):Function or operator which takes N arguments, -N(>0):Variable which takes *N-2* arguments
	std::vector< std::list<double> > value_list; //calculated values
	std::vector< std::list<pFuncType> > action_list; //functions to be executed

	std::vector<double> const_vect; //array of user defined constants

	bool isPositiveNumber(std::string &st);

	virtual double exec_calc(pFuncType p, std::list<double> &arg_list) =0;

protected:
	void registerKey(Token<T> &tk){key.push_back(tk);}
	int toRPN(std::string &st);
	int reduceFunction();
	int evaluateRPN(int ind, double &val);

	//functions
	double calc_pow(std::list<double> &a_list);
	double calc_mul(std::list<double> &a_list);
	double calc_div(std::list<double> &a_list);
	double calc_mod(std::list<double> &a_list);
	double calc_add(std::list<double> &a_list);
	double calc_sub(std::list<double> &a_list);
	double calc_sign(std::list<double> &a_list);
	double calc_abs(std::list<double> &a_list);
	double calc_ceil(std::list<double> &a_list);
	double calc_floor(std::list<double> &a_list);
	double calc_sqrt(std::list<double> &a_list);
	double calc_exp(std::list<double> &a_list);
	double calc_ln(std::list<double> &a_list);
	double calc_log(std::list<double> &a_list);
	double calc_sin(std::list<double> &a_list);
	double calc_cos(std::list<double> &a_list);
	double calc_tan(std::list<double> &a_list);
	double calc_asin(std::list<double> &a_list);
	double calc_acos(std::list<double> &a_list);
	double calc_atan(std::list<double> &a_list);
	double calc_sinh(std::list<double> &a_list);
	double calc_cosh(std::list<double> &a_list);
	double calc_tanh(std::list<double> &a_list);
	double calc_atan2(std::list<double> &a_list);
	double calc_pi(std::list<double> &a_list);
	double calc_e(std::list<double> &a_list);
	double calc_random(std::list<double> &a_list);

	double calc_c(std::list<double> &a_list);

public:
	ScientificCalculatorBase(){
		std::srand((unsigned int)time(NULL)); //for random()
	}
	virtual ~ScientificCalculatorBase(){;}

	virtual int initialize();
	std::vector< std::list<int> >::size_type getCommandNum(){return type_list.size();}

	virtual int getFunction(std::string &st);
	virtual int putFunction(std::list<double> &out_list);

	int setConstants(std::vector<double> &data);
};

// *****************************************************************************************
//  template <class T> 
//  int Token::initialize(const char* n, token_type tt, int p, pFuncType func)
//   set parameters 
//    n - name of the token
//    tt - token type defined in math_function_base.h
//    p - parameter of the token: 
//        priority for binary operators or number of arguments for functions and variables
//    func - function executed when the token is found
//    return 0 iff no error
// ******************************************************************************************
template <class T>
int Token<T>::initialize(const char* n, token_type tt, int p, pFuncType func){
	name = n;
	if(((tt==FUNCTION)||(tt==VARIABLE)) && (p!=0)){
		name += '(';
	}

	type = tt;
	param = p;
	calc = func;

	return 0;
}

// *********************************************
//  int ScientificCalculatorBase::initialize()
//    initialize - clear stored data
//    return 0 iff no error
// *********************************************
template <class T>
int ScientificCalculatorBase<T>::initialize(){
	type_list.clear();
	value_list.clear();
	action_list.clear();

	return 0;
}

// ****************************************************************************************
//  int ScientificCalculatorBase::getFunction(std::string &st)
//    read commands from the string
//    by dividing by colons (:), multiple commands can be used (e.g. sin(2*pi):cos(pi/2))
//    st - input command
//    return 0 iff no error
// ****************************************************************************************
template <class T>
int ScientificCalculatorBase<T>::getFunction(std::string &st){
	int res;
	std::string strtmp;
	std::string::size_type loc1 = 0;
	std::string::size_type loc2;

	//clear previous settings
	initialize();

	for(;;){
		//deviding multiple commands 
		loc2 = st.substr(loc1).find_first_of(':'); //search separator
		if((loc2 == 0)||(st.empty())){ //string is empty
			std::cerr << "Error in input data: empty string" << std::endl;
			return 1;
		}else{
			strtmp = st.substr(loc1,loc2);
			//std::cout << "loc: " << loc1 << ' ' << loc2 << std::endl;
			//std::cout << "strtmp: " << strtmp << std::endl;
			res = toRPN(strtmp);
			if(res != 0){return res;}

			if(loc2==std::string::npos){ //no more separators
				break;
			}
			
			loc1 += loc2 + 1; //update search starting position
		}
	}

	res = reduceFunction();
	if(res != 0){return res;}

	return 0;
}

// ********************************************************************************************
//  int ScientificCalculatorBase::toRPN(std::string &st)
//    convert the string to lists of commands using Reverse Polish Notation
//    the information is stored in type_list, value_list, action_list
//    st - input command string, e.g. sin(2*pi). the st is not const - changed in the process
//    return 0 iff no error
// ********************************************************************************************
template <class T>
int ScientificCalculatorBase<T>::toRPN(std::string &st){
	unsigned int i;
	std::vector< std::list<int> >::size_type j = getCommandNum();

	Token<T> tk;
	//std::queue<std::string> output_queue; //Reverse Polish Notation of the command string
	std::stack< Token<T> > operator_stack; //stack to change the command string to RPN
	std::stack<int> argnum_check_stack; //stack to check if the number of argments in a function is correct

	std::string::size_type loc;
	int mode = 1; 
	//if the previous key is the following, the mode is changed to
	//0 - Number, R_Parenthesis, Constant, Function, Variable (which takes no arguments)
	//1 - Function, Variable (which takes arguments), Separator, L_Parenthesis
	//2 - BL_Operator, BR_Operator

	bool matched;

	//memory allocation
	type_list.resize(type_list.size()+1);
	value_list.resize(value_list.size()+1);
	action_list.resize(action_list.size()+1);


	while(!st.empty()){	//if not empty, read token
		//ignore spaces
		if(st.substr(0,1) == " "){ //if(st[0] == ' ')
			st.erase(0,1);
			continue;
		}

		matched = false;

		switch(mode){
		case 0: //mode 0 - accept R_PARENTHESIS, SEPARATOR, BL_OPERATOR or BR_OPERATOR
			if(st.substr(0,1) == ")"){ //Right parenthesis -> search left parenthesis or function from the stack
				for(;;){
					if(operator_stack.empty()){
						std::cerr << "Error in input data: mismatched parenthesis" << std::endl;
						return 1;
					}
					tk = operator_stack.top();
					if((tk.type == FUNCTION) || (tk.type == VARIABLE)){
						if((tk.param>0)&&(argnum_check_stack.top() != tk.param)){
							std::cerr << "Error in input data: invalid number of arguments" << std::endl;
							return 1;
						}
						//output_queue.push(tk.name.substr(0,tk.name.size()-1));
						if(tk.type == FUNCTION){type_list[j].push_back(argnum_check_stack.top());}
						else{type_list[j].push_back(-argnum_check_stack.top()-2);} //to identify the variable, the param is changed to -N-2 in the type list
						argnum_check_stack.pop();
						action_list[j].push_back(tk.calc);
						operator_stack.pop();
						break;
					}else if(tk.type == L_PARENTHESIS){
						operator_stack.pop();
						break;
					}else{ //binary operator
						//output_queue.push(tk.name);
						type_list[j].push_back(2);
						action_list[j].push_back(tk.calc);
						operator_stack.pop();
					}
				}
				mode = 0;
				matched = true;
				st.erase(0,1);
				break;
			}else if(st.substr(0,1) == ","){ //Argument separator for functions -> search function from the stack
				for(;;){
					if(operator_stack.empty()){
						std::cerr << "Error in input data: mismatched parenthesis or misplaced separator" << std::endl;
						return 1;
					}
					tk = operator_stack.top();
					if((tk.type == FUNCTION)||(tk.type == VARIABLE)){
						argnum_check_stack.top()++;
						break;
					}else if(tk.type == L_PARENTHESIS){
						std::cerr << "Error in input data: mismatched parenthesis or misplaced separator" << std::endl;
						return 1;
					}else{ //binary operator
						//output_queue.push(tk.name);
						type_list[j].push_back(2);
						action_list[j].push_back(tk.calc);
						operator_stack.pop();
					}
				}
				mode = 1;
				matched = true;
				st.erase(0,1);
				break;
			}else{
				//operators
				for(i=0;i<key.size();i++){ //check if the token is function or constant
					if(st.size() >= key[i].name.size()){ //check string size
						if(st.substr(0, key[i].name.size()) == key[i].name){ //find token
							if(key[i].type == BL_OPERATOR){ //check token type
								while(!operator_stack.empty()){
									tk = operator_stack.top();
									if(((tk.type == BL_OPERATOR)||(tk.type == BR_OPERATOR))&&(key[i].param <= tk.param)){
										//output_queue.push(tk.name);
										type_list[j].push_back(2);
										action_list[j].push_back(tk.calc);
										operator_stack.pop();
									}else{
										break;
									}
								}
							}else if(key[i].type == BR_OPERATOR){
								while(!operator_stack.empty()){
									tk = operator_stack.top();
									if(((tk.type == BL_OPERATOR)||(tk.type == BR_OPERATOR))&&(key[i].param <= tk.param)){
										//output_queue.push(tk.name);
										type_list[j].push_back(2);
										action_list[j].push_back(tk.calc);
										operator_stack.pop();
									}else{
										break;
									}
								}
							}else{
								continue; //unacceptable token (maybe it is a part of another token) - search next token
							}
							operator_stack.push(key[i]);
							mode = 2;
							matched = true;
							st.erase(0, key[i].name.size());
							break;
						}
					}
				}
			}
			break;

		case 1: //mode 1 - accept unary operators "+" and "-", and token also accepted in mode 2
			if(st.substr(0,1) == "+"){ //Unary operator + -> ignore it
				mode = 2;
				matched = true;
				st.erase(0,1);
				break;
			}else if(st.substr(0,1) == "-"){ //Unary operator - -> -1*
				//output_queue.push(std::string("-1"));
				type_list[j].push_back(-1);
				value_list[j].push_back(-1);
				Token<T> tktmp("*", BL_OPERATOR, 3, &T::calc_mul); //!!
				while(!operator_stack.empty()){
					tk = operator_stack.top();
					if(((tk.type == BL_OPERATOR)||(tk.type == BR_OPERATOR))&&(tktmp.param <= tk.param)){
						//output_queue.push(tk.name);
						type_list[j].push_back(2);
						action_list[j].push_back(tk.calc);
						operator_stack.pop();
					}else{
						break;
					}
				}
				operator_stack.push(tktmp);
				mode = 2;
				matched = true;
				st.erase(0,1);
				break;
			}

		case 2: //mode 1 or 2 - accept L_PARENTHESIS, FUNCTION, VARIABLE, numbers
			if(st.substr(0,1) =="("){ //Left parenthesis -> push to the stack
				tk.name = "(";
				tk.type = L_PARENTHESIS;
				operator_stack.push(tk);
				mode = 1;
				matched = true;
				st.erase(0,1);
				break;
			}else if(st.substr(0,1).find_first_of("1234567890")!=std::string::npos){ //Number
				std::string strtmp;
				loc = st.find_first_not_of("1234567890."); //search "not a number"
				strtmp = st.substr(0,loc);
				st.erase(0,loc);
				if(isPositiveNumber(strtmp)){ //get the number
					//output_queue.push(strtmp);
					type_list[j].push_back(-1);
					value_list[j].push_back(std::atof(strtmp.c_str()));
				}else{
					return 1;
				}
				mode = 0;
				matched = true;
				break;
			}else{
				for(i=0;i<key.size();i++){ //check if the token is function or constant
					if(st.size() >= key[i].name.size()){ //check string size
						if(st.substr(0, key[i].name.size()) == key[i].name){ //find token
							if(key[i].type == FUNCTION){ //check token type
								if(key[i].param == 0){ //no argument function
									//output_queue.push(key[i].name.substr(0,tk.name.size()-2));
									type_list[j].push_back(key[i].param);
									action_list[j].push_back(key[i].calc);
									mode = 0;
								}else{
									operator_stack.push(key[i]);
									mode = 1;
									argnum_check_stack.push(1);
								}
							}else if(key[i].type == VARIABLE){
								if(key[i].param == 0){ //no argument function
									//output_queue.push(key[i].name);
									type_list[j].push_back(-key[i].param-2);
									action_list[j].push_back(key[i].calc);
									mode = 0;
								}else{
									operator_stack.push(key[i]);
									mode = 1;
									argnum_check_stack.push(1);
								}
							}else{
								continue; //unacceptable token (maybe it is a part of another token) - search next token
							}
							matched = true;
							st.erase(0, key[i].name.size());
							break;
						}
					}
				}
			}
		}//end switch(mode)

		if(!matched){ //no token matched to the string
			std::cerr << "Error in input data: invalid token" << std::endl;
			return 1;
		}

	}//end while(!st.empty())

	if(mode!=0){
		std::cerr << "Error in input data: invalid last token" << std::endl;
		return 1;
	}

	//Complete the conversion while checking if the command is correct
	while(!operator_stack.empty()){
		tk = operator_stack.top();
		if((tk.type == L_PARENTHESIS)||(tk.type == FUNCTION)||(tk.type == VARIABLE)){
			std::cerr << "Error in input data: mismatched parenthesis" << std::endl;
			return 1;
		}else{ //binary operators
			//output_queue.push(tk.name);
			type_list[j].push_back(2);
			action_list[j].push_back(tk.calc);
			operator_stack.pop();
		}
	}

	/*
	while(!output_queue.empty()){
		std::cout << output_queue.front().c_str() << '|' << std::flush;
		output_queue.pop();
	}
	std::cout << std::endl;

	for(i=0;i<=j;i++){
		std::cout << "type_list[" << i << "]:" << type_list[i].size() << std::endl;
		std::cout << "value_list[" << i << "]:" << value_list[i].size() << std::endl;
		std::cout << "action_list[" << i << "]:" << action_list[i].size() << std::endl;
	}
	*/

	return 0;
}

// ***************************************************************
//  int ScientificCalculatorBase::reduceFunction()
//    simplify the lists of commands if possible
//    return 0 if no error
//           >0 if error
//           <0 if exception occured, e.g. division by zero etc.
// ***************************************************************
template <class T>
int ScientificCalculatorBase<T>::reduceFunction(){
	bool check_exception = false;

	unsigned int i;
	int count;
	std::list<double> arg_list;

	std::list<int>::iterator t_it;
	std::list<double>::iterator v_it;
	typename std::list< pFuncType >::iterator a_it;

	for(i=0;i<getCommandNum();i++){
		count = 0;
		t_it = type_list[i].begin();
		v_it = value_list[i].begin();
		a_it = action_list[i].begin();
		arg_list.clear();

		while(t_it != type_list[i].end()){
			//debug
			//std::cout << "type:" << (*t_it) << " count:" << count << std::endl;
			//end debug

			if((*t_it) == -1){ //Number
				/*
				//debug
				if(v_it==value_list[i].end()){
					std::cerr << "Error in ScientificCalculatorBase::reduceFunction(): insufficient numbers" << std::endl;
					return 1;
				}
				//end debug
				*/
				count++;
				v_it++;
			}else if((*t_it) < -1){ //Variable - do not calculate now since it is updated every time when putFunction is called
				/*
				//debug
				if(a_it==action_list[i].end()){
					std::cerr << "Error in ScientificCalculatorBase::reduceFunction(): insufficient actions" << std::endl;
					return 1;
				}
				//end debug
				*/
				count=0;
				a_it++;
			}else{
				/*
				//debug
				if(a_it==action_list[i].end()){
					std::cerr << "Error in ScientificCalculatorBase::reduceFunction(): insufficient actions" << std::endl;
					return 1;
				}
				//end debug
				*/
				if((*t_it)<=count){
					/*
					//debug
					if(a_it==action_list[i].end()){
						std::cerr << "Error in ScientificCalculatorBase::reduceFunction(): insufficient actions" << std::endl;
						return 1;
					}
					//end debug
					*/

					count = count - (*t_it) + 1;

					arg_list.clear();

					std::list<int>::iterator t_it_arg_begin = t_it;
					std::list<double>::iterator v_it_arg_begin = v_it;

					if((*t_it)!=0){ //if argments are needed -> extract them from value list
						int dist = (int) distance(value_list[i].begin(), v_it) - (*t_it);
						
						advance(t_it_arg_begin, -(*t_it));
						t_it = type_list[i].erase(t_it_arg_begin, t_it); //erase [first, last)

						advance(v_it_arg_begin, -(*t_it));
						arg_list.splice(arg_list.begin(), value_list[i], v_it_arg_begin, v_it);

						v_it = value_list[i].begin();
						advance(v_it, dist);
					}
					
					try{
						v_it = value_list[i].insert(v_it, exec_calc(*a_it, arg_list));
					}
					catch(...){
						std::cerr << "Error in input data: invalid arguments" << std::endl;
						//return 1;

						type_list[i].clear();
						value_list[i].clear();
						action_list[i].clear();

						type_list[i].push_back(-1);
						value_list[i].push_back(std::numeric_limits<double>::quiet_NaN()); 
						/*
						//put 1/0
						type_list[i].push_back(-1);
						type_list[i].push_back(-1);
						type_list[i].push_back(2);
						value_list[i].push_back(1);
						value_list[i].push_back(0);
						action_list[i].push_back(&T::calc_div); //!
						*/
						check_exception = true;

						break;
					}
					v_it++;
					a_it = action_list[i].erase(a_it);
					*t_it = -1; //now a value is obtained
				}else{
					/*
					//debug
					if(a_it==action_list[i].end()){
						std::cerr << "Error in ScientificCalculatorBase::reduceFunction(): insufficient actions" << std::endl;
						return 1;
					}
					//end debug
					*/
					a_it++;
					count=0;
				}
			} //end if(*t_it)

			t_it++;
		} //end while

	}//end for

	/*
	for(i=0;i<type_list.size();i++){
		std::cout << "type_list[" << i << "]:" << type_list[i].size() << std::endl;
		std::cout << "value_list[" << i << "]:" << value_list[i].size() << std::endl;
		std::cout << "action_list[" << i << "]:" << action_list[i].size() << std::endl;
		if((type_list[i].size()==1)&&(value_list[i].size()==1)){
			std::cout << "value[" << i << "]:" << value_list[i].front() << std::endl;
		}
	}
	*/

	if(check_exception){
		return -1;
	}else{
		return 0;
	}
}


// ******************************************************************
//  int ScientificCalculatorBase::evaluateRPN(int ind, double &val)
//    evaluate the postfix expression and get the value
//    ind - index of the vector where the value is evaluated
//    val - calculated value
//    return 0 if no error
//           >0 if error
//           <0 if exception occured, e.g. division by zero etc.
// ******************************************************************
template <class T>
int ScientificCalculatorBase<T>::evaluateRPN(int ind, double &val){
	int arg_num;

	std::list<double> arg_list;
	std::list<double> res_list;

	std::list<int>::iterator t_it;
	std::list<double>::iterator v_it;
	typename std::list<pFuncType>::iterator a_it;

	t_it = type_list[ind].begin();
	v_it = value_list[ind].begin();
	a_it = action_list[ind].begin();
	while(t_it != type_list[ind].end()){
		if((*t_it) == -1){ //Number
			res_list.push_back(*v_it);
			v_it++;
		}else{
			arg_list.clear();

			std::list<double>::iterator arg_begin = res_list.end();

			if((*t_it)!=-2){ //if argments are needed -> extract them from value list
				if((*t_it)>0){arg_num = *t_it;}
				else{arg_num = -(*t_it)-2;}

				if(res_list.size() < (unsigned int)(arg_num)){
					std::cerr << "Error in input data: insufficient values" << std::endl;
					return 1;
				}

				advance(arg_begin, -arg_num);
				arg_list.splice(arg_list.begin(), res_list, arg_begin, res_list.end());
			}

			try{
				res_list.push_back(exec_calc(*a_it, arg_list));
			}
			catch(...){
				std::cerr << "Error in input data: invalid arguments" << std::endl;
				//val = 0.0;
				val = std::numeric_limits<double>::quiet_NaN();
				return -1;
			}
			a_it++;
		} //end if(*t_it)

		t_it++;
	} //end while

	if(res_list.size()==1){
		//std::cout << "value:" << res_list.front() << std::endl;
		val = res_list.front();
		return 0;
	}else{
		std::cerr << "Error in input data: too many values" << std::endl;
		return 1;
	}

}

// *************************************************************************
//  int ScientificCalculatorBase::putFunction(std::list<double> &out_list)
//    calculate the value
//    out_list - list of the calculated value
//    return 0 if no error
//           >0 if error
//           <0 if exception occured, e.g. division by zero etc.
// *************************************************************************
template <class T>
int ScientificCalculatorBase<T>::putFunction(std::list<double> &out_list){
	bool check_exception = false;
	int res;
	double val;

	unsigned int i;

	for(i=0;i<getCommandNum();i++){
		res = evaluateRPN(i, val);
		if(res>0){return res;}
		else if(res<0){check_exception=true;}

		out_list.push_back(val);
	}

	if(check_exception){
		return -1;
	}else{
		return 0;
	}
}

// *******************************************************************
//  bool ScientificCalculatorBase::isPositiveNumber(std::string &st)
//    check if the input string is a positive number
//    st - input string
//    return true iff the string represents a positive number
// *******************************************************************
template <class T>
bool ScientificCalculatorBase<T>::isPositiveNumber(std::string &st){
	std::string::size_type loc;

	if((st.empty())||(st.find_first_not_of("0123456789.") != std::string::npos)){ //string is empty
		std::cerr << "Error in input data: invalid number" << std::endl;
		return false;
	}

	loc = st.find_first_of('.');
	if((st.substr(0,1)=="0")&&(st.size()!=1)&&(loc!=1)){ //MSD is 0 and the second character is not '.'
		std::cerr << "Error in input data: invalid number" << std::endl;
		return false;
	}else if((loc == st.find_last_of('.'))&&(loc != st.size()-1)){ //one or no '.' and numbers -> OK
		return true;
	}else{ //more than one '.' or '.' is placed at the end of the number
		std::cerr << "Error in input data: misplaced decimal point" << std::endl;
		return false;
	}
}

// ***********************************************************************
//  int ScientificCalculatorBase::setConstants(std::vector<double> data)
//    register the user defined constants 
//    data - vector of constants to be registered
//    return 0 iff no error
// ***********************************************************************
template <class T>
int ScientificCalculatorBase<T>::setConstants(std::vector<double> &data){
	const_vect.clear();
	const_vect = data;

	return 0;
}

// ******** Calclutaion Functions ******************************** //
template <class T>
double ScientificCalculatorBase<T>::calc_pow(std::list<double> &a_list){
	int i=0;
	std::list<double>::iterator it = a_list.begin();
	double arg[2];

	if(a_list.size()!=2){
		throw "Exception: Invalid number of arguments";
	}

	while(it != a_list.end()){
		arg[i] = (*it);
		it++;
		i++;
	}
	if(((arg[0]<0)&&(std::ceil(arg[1])!=std::floor(arg[1])))||((arg[0]==0)&&(arg[1]<=0))){
		throw "Exception: Invalid argument";
	}

	return std::pow(arg[0],arg[1]);
}

template <class T>
double ScientificCalculatorBase<T>::calc_mul(std::list<double> &a_list){
	int i=0;
	std::list<double>::iterator it = a_list.begin();
	double arg[2];

	if(a_list.size()!=2){
		throw "Exception: Invalid number of arguments";
	}

	while(it != a_list.end()){
		arg[i] = (*it);
		it++;
		i++;
	}

	return arg[0]*arg[1];
}

template <class T>
double ScientificCalculatorBase<T>::calc_div(std::list<double> &a_list){
	int i=0;
	std::list<double>::iterator it = a_list.begin();
	double arg[2];

	if(a_list.size()!=2){
		throw "Exception: Invalid number of arguments";
	}

	while(it != a_list.end()){
		arg[i] = (*it);
		it++;
		i++;
	}
	if(arg[1]==0){
		throw "Exception: Invalid argument";
	}

	return arg[0]/arg[1];
}
template <class T>
double ScientificCalculatorBase<T>::calc_mod(std::list<double> &a_list){
	int i=0;
	std::list<double>::iterator it = a_list.begin();
	double arg[2];

	if(a_list.size()!=2){
		throw "Exception: Invalid number of arguments";
	}

	while(it != a_list.end()){
		arg[i] = (*it);
		it++;
		i++;
	}
	if(arg[1]==0){
		throw "Exception: Invalid argument";
	}

	return std::fmod(arg[0],arg[1]);
}
template <class T>
double ScientificCalculatorBase<T>::calc_add(std::list<double> &a_list){
	int i=0;
	std::list<double>::iterator it = a_list.begin();
	double arg[2];

	if(a_list.size()!=2){
		throw "Exception: Invalid number of arguments";
	}

	while(it != a_list.end()){
		arg[i] = (*it);
		it++;
		i++;
	}

	return arg[0]+arg[1];
}
template <class T>
double ScientificCalculatorBase<T>::calc_sub(std::list<double> &a_list){
	int i=0;
	std::list<double>::iterator it = a_list.begin();
	double arg[2];

	if(a_list.size()!=2){
		throw "Exception: Invalid number of arguments";
	}

	while(it != a_list.end()){
		arg[i] = (*it);
		it++;
		i++;
	}

	return arg[0]-arg[1];
}

template <class T>
double ScientificCalculatorBase<T>::calc_sign(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	if(arg>0.0){return 1.0;}
	else if(arg==0.0){return 0.0;}
	else{return -1.0;}
}

template <class T>
double ScientificCalculatorBase<T>::calc_abs(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::fabs(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_ceil(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::ceil(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_floor(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::floor(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_sqrt(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();
	if(arg<0.0){
		throw "Exception: Invalid argument";
	}

	return std::sqrt(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_exp(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::exp(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_ln(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();
	if(arg<=0.0){
		throw "Exception: Invalid argument";
	}

	return log(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_log(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();
	if(arg<=0.0){
		throw "Exception: Invalid argument";
	}

	return std::log10(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_sin(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::sin(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_cos(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::cos(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_tan(std::list<double> &a_list){
	double arg;
	double pi = std::acos(-1.0);

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();
	while(arg >= pi){arg -= pi;}
	while(arg < 0){arg += pi;}
	if(arg==pi/2){
		throw "Exception: Invalid argument";
	}

	return std::tan(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_asin(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();
	if((arg<-1)||(arg>1)){
		throw "Exception: Invalid argument";
	}

	return std::asin(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_acos(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();
	if((arg<-1)||(arg>1)){
		throw "Exception: Invalid argument";
	}

	return std::acos(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_atan(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::atan(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_sinh(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::sinh(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_cosh(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::cosh(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_tanh(std::list<double> &a_list){
	double arg;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();

	return std::tanh(arg);
}

template <class T>
double ScientificCalculatorBase<T>::calc_atan2(std::list<double> &a_list){
	int i=0;
	std::list<double>::iterator it = a_list.begin();
	double arg[2];

	if(a_list.size()!=2){
		throw "Exception: Invalid number of arguments";
	}

	while(it != a_list.end()){
		arg[i] = (*it);
		it++;
		i++;
	}
	if((arg[0]==0.0)&&(arg[1]==0.0)){
		throw "Exception: Invalid argument";
	}

	return std::atan2(arg[0],arg[1]);
}


template <class T>
double ScientificCalculatorBase<T>::calc_pi(std::list<double> &a_list){
	if(!a_list.empty()){
		throw "Exception: Invalid number of arguments";
	}

	return std::acos(-1.0);
}

template <class T>
double ScientificCalculatorBase<T>::calc_e(std::list<double> &a_list){
	if(!a_list.empty()){
		throw "Exception: Invalid number of arguments";
	}

	return std::exp(1.0);
}

template <class T>
double ScientificCalculatorBase<T>::calc_random(std::list<double> &a_list){
	if(!a_list.empty()){
		throw "Exception: Invalid number of arguments";
	}

	return (double)rand()/RAND_MAX;
}

template <class T>
double ScientificCalculatorBase<T>::calc_c(std::list<double> &a_list){
	double arg;
	const double epsilon = 1.0e-12;

	if(a_list.size()!=1){
		throw "Exception: Invalid number of arguments";
	}

	arg = a_list.front();
	if(arg-std::floor(arg+epsilon)<=epsilon){
		return const_vect.at((int)std::floor(arg+epsilon));
	}else{
		throw "Exception: Invalid argument";
	}
	/*
	if((std::ceil(arg)-arg)<epsilon){
		return const_vect.at((int)std::ceil(arg));
	}else if((arg-std::floor(arg))<epsilon){
		return const_vect.at((int)std::floor(arg));
	}else{
		throw "Exception: Invalid argument";
	}
	*/
}

#endif
