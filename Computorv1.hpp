#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;

#include <sstream>
using std::stringstream;

#include <map>
#include <vector>
#include <iomanip>

class ft_Complex {
public:
	double Re;
	double Im;

	ft_Complex() :Re(0), Im(0) {}
	ft_Complex(double Re, double Im) :Re(Re), Im(Im) {}
	~ft_Complex() {}
};


class Computorv1 {
private:
	const string 			_input_str;

							Computorv1(const Computorv1 &copy);
							Computorv1();
	Computorv1 & 			operator=(Computorv1 const & rhs);
	void					_parse_and_reduce();
	void					_set_degree();
	void					_find_delta();
	void					_find_sol_quadratic();
	void					_find_sol_linear();


public:
							Computorv1(const string input_str);
							~Computorv1();

	std::map<int, double> 	reduced_equation;
	int						degree;
	double					delta;
	ft_Complex					x1;
	ft_Complex					x2;


	void					print_results() const;				

	class WrongInputString : public std::exception
	{
		public:
		const char *what() const throw () {
			return "wrong format for equation solver";}
	};

	class InvalidExponent : public std::exception
	{
		public:
		const char *what() const throw () {
			return "value for a exponent is invalid";}
	};
		
};


