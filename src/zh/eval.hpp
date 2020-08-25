#pragma once
#include <istream>
#include <iostream>
#include <string_view>
#include <sstream>
#include <map>

#include "svstream.hpp"
#include "tokenize.hpp"
#include "parse.hpp"

using namespace std;


double eval(istream& is, const State& state = State(), const map<string, double>& vars = map<string, double>()) {
	auto tokens = tokenize(is);
	auto expr = parse(tokens, state);

	return expr.evaluate(vars);
}

double eval(istream& is, const map<string, double>& vars) {
	State state;
	state.variables.reserve(vars.size());

	for (auto&[name, value] : vars) {
		state.variables.push_back(name);
	}

	return eval(is, state, vars);
}

double eval(string_view str, const State& state = State(), const map<string, double>& vars = map<string, double>()) {
	isviewstream is(str);
	return eval(is, state, vars);
}

double eval(string_view str, const map<string, double>& vars) {
	isviewstream is(str);
	return eval(is, vars);
}