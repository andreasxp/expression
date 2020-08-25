#pragma once
#include <map>
#include "expr_node.hpp"

struct Parens : ExprNode {
private:
	ExprNode* m_expr;

public:
	ExprNode* clone() const override {
		return new Parens(m_expr->clone());
	}

	Parens(ExprNode* expr) :
		m_expr(expr) {}

	span<ExprNode*> args() noexcept final {
		return span(&m_expr, 1);
	}

	span<ExprNode* const> args() const noexcept final {
		return span(&m_expr, 1);
	}

	double evaluate(const map<string, double>& vars) const final {
		return m_expr->evaluate(vars);
	}
};
