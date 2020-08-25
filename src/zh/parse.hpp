#pragma once
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <variant>
#include "expression.hpp"
#include "tokenize.hpp"
#include "util.hpp"
#include "state.hpp"

using namespace std;

template <class It> ExprNode* parseExpression(It& it, const State& state);
template <class It> ExprNode* parseLiteral(It& it);
template <class It> ExprNode* parseVariable(It& it, const State& state);
template <class It> ExprNode* parseParens(It& it, const State& state);
template <class It> ExprNode* parseBinaryOp(ExprNode* lhs, It& it, const State& state);

ExprNode* sort(ExprNode* expr);
Expr parse(const vector<Token>& tokens, const State& state);


template <class It>
ExprNode* parseVariable(It& it, const State& state) {
	auto token = *it;
	if (token.type != Token::Identifier) return nullptr;
	if (!contains(state.variables, get<string>(token.data))) return nullptr;
	++it;

	return new Variable(get<string>(token.data));
}

template <class It>
ExprNode* parseLiteral(It& it) {
	// A single numeric token
	auto token = *it;
	if (token.type != Token::NumericLiteral) return nullptr;
	++it;

	return new Literal(get<double>(token.data));
}

template <class It>
ExprNode* parseParens(It& it, const State& state) {
	// A single numeric token
	if (it->type != Token::ParenLeft) return nullptr;
	++it;

	auto expr = parseExpression(it, state);

	if (it->type != Token::ParenRight) throw invalid_argument("missing closing parenthesis");
	++it;

	return new Parens(expr);
}

template <class It>
ExprNode* parseBinaryOp(ExprNode* lhs, It& it, const State& state) {
	// binary operation: e1 binary-operator E
	auto saved = it;

	auto token = *it;
	if (token.type != Token::Operator) { it = saved; return nullptr; }
	++it;

	auto rhs = parseExpression(it, state);
	if (!rhs) { it = saved; return nullptr; }

	auto& str = get<string>(token.data);
	if (str == "+") return new Add(lhs, rhs);
	if (str == "-") return new Substract(lhs, rhs);
	if (str == "*") return new Multiply(lhs, rhs);
	if (str == "/") return new Divide(lhs, rhs);
	if (str == "^") return new Power(lhs, rhs);

	throw invalid_argument("unrecognised binary operator");
}

template <class It>
ExprNode* parseExpression(It& it, const State& state) {
	ExprNode* res = nullptr;

	res = parseLiteral(it);
	if (!res) res = parseVariable(it, state);
	if (!res) res = parseParens(it, state);
	
	if (res) {
		if (it->type == Token::Operator) {
			auto binary_expr = parseBinaryOp(res, it, state);
			if (binary_expr) res = std::move(binary_expr);
		}

		return res;
	}
	
	throw invalid_argument("unrecognised expression");
}

ExprNode* sort(ExprNode* expr) {
	for (size_t i = 0; i < expr->args().size(); ++i) {
		expr->args()[i] = sort(expr->args()[i]);
	}

	auto binary_op = dynamic_cast<Operator*>(expr);
	if (binary_op) return binary_op->sort();
	return expr;
}

Expr parse(const vector<Token>& tokens, const State& state = State()) {
	auto it = tokens.begin();
	auto result = parseExpression(it, state);
	
	if (it->type != Token::Eof) {
		stringstream ss;
		ss << "expected EOF, got " << *it;
		throw invalid_argument(ss.str());
	}

	return sort(result);
}