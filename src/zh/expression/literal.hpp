#pragma once
#include <map>
#include "expr_node.hpp"

struct Literal : ExprNode {
private:
	double m_value = 0;

public:
	ExprNode* clone() const override {
		return new Literal(m_value);
	}

	Literal(double value) :
		m_value(value) {
	}

	span<ExprNode*> args() noexcept final {
		return {};
	}

	span<ExprNode* const> args() const noexcept final {
		return {};
	}

	double evaluate(const map<string, double>& vars) const final {
		return m_value;
	}
};
