#include "Computorv1.hpp"

std::ostream& operator<<(std::ostream& os, const ft_Complex& c) {
        os << c.Re;
		if (c.Im == 0)
			return os;
        else if (c.Im > 0) {
            os << " + " << c.Im << "i";
        } else {
            os << " - " << -c.Im << "i";
        }
        return os;
    }


bool is_zero(double number) {
	if (abs(number) < 0.00000001)
		return true;
	return false;
}

// babylonnian method: 
// x . a/x = a = √a * √a 
//if x > √a then a/x < √a 
//if x < √a then a/x > √a 
// so you just take the avrage of x and a/x to find a closer value 
// This algorithm is quadratically convergent: the number of correct digits x roughly doubles with each iteration. 
double ft_sqrt(double n) {
	double x = 1;
	while (!is_zero(n - (x * x)))
		x = (x + n/x)/2; 

	return x;
}


Computorv1::Computorv1() {

}

Computorv1::~Computorv1() {
	
}

Computorv1::Computorv1(const Computorv1 &copy) {
	*this = copy;
}

Computorv1 & Computorv1::operator=(Computorv1 const & rhs) {
	(void)rhs;
	return *this;
}

Computorv1::Computorv1(const string input_str): _input_str(input_str), degree(0), delta(0) {

	this->_parse_and_reduce();
	this->_set_degree();

	switch (this->degree)
	{
	case 0:
		if (this->reduced_equation[0] == 0)
			cout << "The equation has a infinite number of solutions !" << endl;
		else
			cout << "The equation is FALSE !" << endl;
		break;
	
	case 1:
		this->_find_sol_linear();
		break;
	
	case 2:
		this->_find_delta();
		this->_find_sol_quadratic();
		break;

	default:
		cout << "The equation has a degree bigger than 2 !\nI am not made to calculate this equation :(" << endl;
		break;
	}
}

void Computorv1::_parse_and_reduce() {
	stringstream ss(this->_input_str);
	string word;
	std::vector<string> splitted_line;

	while (ss >> word) {
		splitted_line.push_back(word);
	}

	bool left_side = true;
	for (size_t i = 0; i < splitted_line.size(); i++) {
		int sign = left_side ? 1 : -1;

		if (splitted_line[i] == "=") {
			left_side = false;
			continue;
		}

		if (splitted_line[i] == "+" || splitted_line[i] == "-") {
			sign *= splitted_line[i] == "+" ? 1 : -1;
			if (i == splitted_line.size() - 1)
				throw Computorv1::WrongInputString();
			i++;
		}

		stringstream n_ss;
		n_ss << splitted_line[i];
		double n;
		n_ss >> n;
		n *= sign;
		
		if (i == splitted_line.size() - 1 || splitted_line[i + 1] != "*") {
			this->reduced_equation[0] += n;
			continue ;
		}
		i += 2;

		stringstream ex_ss;
		ex_ss << splitted_line[i].substr(2);
		double exp;
		ex_ss >> exp;
		if (exp < 0 || floor(exp) != exp)
			throw Computorv1::InvalidExponent();
		this->reduced_equation[exp] += n; 
	}
	cout << "Reduced form: ";
	bool first = true;
	for (std::map<int, double>::reverse_iterator it = this->reduced_equation.rbegin(); it != this->reduced_equation.rend(); ++it) {
		if (!is_zero(it->second)) {
			cout << (it->second < 0 ? "-" : (first ? "" : "+"));
			if (!first)
				cout << " ";
			first = false;
			cout << abs(it->second);
			if (it->first != 0)
				cout << " * x^" << it->first;
			cout << " ";
		}
	}
	if (first)
		cout << "0 ";
	cout << "= 0" << endl;
}

void Computorv1::_set_degree() {
	for (std::map<int, double>::reverse_iterator it = this->reduced_equation.rbegin(); it != this->reduced_equation.rend(); ++it) {
		if (!is_zero(it->second)) {
			this->degree = it->first;
			break;
		}
	}
	cout << "Equation of degree: " << this->degree << endl;
}

void Computorv1::_find_sol_linear() {
	this->x1.Re = -1 * this->reduced_equation[0] / this->reduced_equation[1];
	cout << "Solution is: " << this->x1 << endl;
}

void Computorv1::_find_delta() {
	double a = this->reduced_equation[2];
	double b = this->reduced_equation[1];
	double c = this->reduced_equation[0];


	this->delta = (b * b) - 4 * a * c;
	cout << "Discriminant is: " << this->delta << endl; 
}

void Computorv1::_find_sol_quadratic() {
	double a = this->reduced_equation[2];
	double b = this->reduced_equation[1];

	if (is_zero(this->delta)) {
		this->x1.Re = (-1 * b) / (2 * a);
		cout << "The unique solution is " << this->x1.Re << endl;
		return ;
	} else if (this->delta < 0) {
		double sq = ft_sqrt((this->delta * -1));
		this->x1.Re = (-1 * b) / (2 * a);
		this->x1.Im = sq / (2 * a);
		this->x2.Re = (-1 * b) / (2 * a);
		this->x2.Im = (-1 * sq) / (2 * a);
	} else {
		double sq = ft_sqrt(this->delta);
		this->x1.Re = (-1 * b + sq) / (2 * a);
		this->x2.Re = (-1 * b - sq) / (2 * a);	
	}

	cout  << "The solutions are:\n";
	cout << "x1 = " << this->x1 << endl;
	cout << "x2 = " << this->x2 << endl;
}