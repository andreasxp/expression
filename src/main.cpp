#include <iostream>
#include <fstream>
#include <map>
#include "zh/eval.hpp"
#include "zh/expression.hpp"

int main(int argc, char** argv) {
	double result = 0;

	if (argc > 1) {
		std::ifstream ifs(argv[1]);
		
		result = eval(ifs);
	}
	else {
		result = eval(std::cin);
	}

	std::cout << "Result: " << result << "\n";

	std::cout << "Result: " << eval("x^3", {{"x", 2}}) << "\n";
	std::cout << "Result: " << eval("x^3", {{"x", 4}}) << "\n";
	std::cout << "Done.";
}