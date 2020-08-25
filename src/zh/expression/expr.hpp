#pragma once
#include <iostream>
#include <memory>
#include <map>
#include "expr_node.hpp"

using namespace std;


struct Expr {
public:
	ExprNode* m_data = nullptr;

	Expr(ExprNode* adopt_ptr) :
		m_data(adopt_ptr) {
	}

	Expr(std::nullptr_t) = delete;

public:
	Expr() = delete;

	Expr(const Expr& other) :
		m_data(other.data()->clone()) {
	}

	Expr& operator=(Expr other) {
		swap(*this, other);
		return *this;
	}

	~Expr() {
		delete m_data;
	}

	friend void swap(Expr& first, Expr& second) noexcept;

	ExprNode* data() noexcept {
		return m_data;
	}

	const ExprNode* data() const noexcept {
		return m_data;
	}

	double evaluate(const map<string, double>& vars = {}) const {
		return data()->evaluate(vars);
	}
};

void swap(Expr& first, Expr& second) noexcept {
	using std::swap;

	swap(first.m_data, second.m_data);
}	

ostream& operator<<(ostream& os, const Expr& obj) {
	os << *(obj.data());

	return os;
}
