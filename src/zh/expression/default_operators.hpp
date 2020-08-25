#pragma once
#include <map>
#include <cmath>
#include "operator.hpp"

using namespace std;


struct Add : Operator {
	using Operator::Operator;

	ExprNode* clone() const override {
		return new Add(args()[0], args()[1]);
	}

	uint8_t order() const final {
		return 2;
	}

	double evaluate(const map<string, double>& vars) const final {
		return args()[0]->evaluate(vars) + args()[1]->evaluate(vars);
	}
};

struct Substract : Operator {
	using Operator::Operator;

	ExprNode* clone() const override {
		return new Substract(args()[0], args()[1]);
	}

	uint8_t order() const final {
		return 2;
	}

	double evaluate(const map<string, double>& vars) const final {
		return args()[0]->evaluate(vars) - args()[1]->evaluate(vars);
	}
};

struct Multiply : Operator {
	using Operator::Operator;

	ExprNode* clone() const override {
		return new Multiply(args()[0], args()[1]);
	}

	uint8_t order() const final {
		return 1;
	}

	double evaluate(const map<string, double>& vars) const final {
		return args()[0]->evaluate(vars) * args()[1]->evaluate(vars);
	}
};

struct Divide : Operator {
	using Operator::Operator;

	ExprNode* clone() const override {
		return new Divide(args()[0], args()[1]);
	}

	uint8_t order() const final {
		return 1;
	}

	double evaluate(const map<string, double>& vars) const final {
		return args()[0]->evaluate(vars) / args()[1]->evaluate(vars);
	}
};

struct Power : Operator {
	using Operator::Operator;

	ExprNode* clone() const override {
		return new Power(args()[0], args()[1]);
	}

	uint8_t order() const final {
		return 0;
	}

	double evaluate(const map<string, double>& vars) const final {
		return pow(args()[0]->evaluate(vars), args()[1]->evaluate(vars));
	}
};