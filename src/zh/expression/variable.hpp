#pragma once
#include <string>
#include <map>
#include "expr_node.hpp"

using namespace std;


struct Variable : ExprNode {
private:
	string m_name;

public:
	ExprNode* clone() const override {
		return new Variable(m_name);
	}

	Variable(const string& value) :
		m_name(value) {
	}

	span<ExprNode*> args() noexcept final {
		return {};
	}

	span<ExprNode* const> args() const noexcept final {
		return {};
	}

	double evaluate(const map<string, double>& vars) const final {
		return vars.at(m_name);
	}
};
