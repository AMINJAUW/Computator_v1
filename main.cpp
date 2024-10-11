#include "Computorv1.hpp"

int main(int argc, char **argv) {
	cout << std::setprecision(6);
	if (argc != 2) {
		cerr << "Wrong number of arguments" << endl;
		cerr << "usage: ./computor \"a * X^2 + b * X^1 + c = 0\"";
	}

	try
	{
		string eq(argv[1]);
		Computorv1 c(eq);
	}
	catch (const std::exception& e)
	{
        std::cerr << e.what() << '\n';
    }
	
}