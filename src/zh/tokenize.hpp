#pragma once
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <variant>
#include "util.hpp"

using namespace std;


struct Token {
	enum Type {
		Eof,
		Identifier,
		NumericLiteral,
		Operator,
		ParenLeft,
		ParenRight,
		Comma,
	};

	variant<monostate, double, string> data;
	Type type = Eof;
};

ostream& operator<<(ostream& os, const Token& t) {
	if (holds_alternative<string>(t.data)) {
		os << "{s" << get<string>(t.data) << "}";
	}
	else if (holds_alternative<double>(t.data)) {
		os << "{d" << get<double>(t.data) << "}";
	}
	else {
		os << "{type: " << t.type << "}";
	}

	return os;
}


istream& skip_whitespace(istream& is) {
	string whitespace = " \t\n";  // Spaces, tabs and newlines

	while(whitespace.find(is.peek()) != string::npos) {
		is.get();
	}

	return is;
}

istream& operator>>(istream& is, Token& t) {
	is >> skip_whitespace;

	char c = is.peek();
	auto& loc = locale::classic();
	if (isalpha(c, loc)) {
		// If the first character is alphabetic, the token must be an identifier
		string str;
		while(isalpha<char>(is.peek(), loc)) {
			is >> c;
			str.push_back(c);
		}

		t = {str, Token::Identifier};
	}
	else if (isdigit(c, loc)) {
		// If the first character is numeric, the token is a number
		double num = 0;
		is >> num;

		t = {num, Token::NumericLiteral};
	}
	else if (c == '(') {
		is.get();
		t = {.type = Token::ParenLeft};
	}
	else if (c == ')') {
		is.get();
		t = {.type = Token::ParenRight};
	}
	else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
		is.get();
		t = {string(1, c), Token::Operator};
	}
	else {
		is.setstate(ios::failbit);
	}

	return is;
}

vector<Token> tokenize(istream& is) {
	vector<Token> result;

	Token t;
	while(is >> t) {
		result.push_back(t);
	}

	result.push_back({});
	return result;
}