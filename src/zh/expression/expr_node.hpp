#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>
#include <map>
#include <span>

using namespace std;


struct ExprNode {
private:
	void dump(ostream& os, int offset) const {
		for (int i = 0; i < offset; ++i) os << ' ';
		os << typeid(*this).name() << "\n";

		for (auto& arg : args()) {
			arg->dump(os, offset+2);
		}
	}

public:
	ExprNode() = default;
	ExprNode(const ExprNode& other) = delete;
	virtual ~ExprNode() = default;
	virtual ExprNode* clone() const = 0;

	virtual span<ExprNode*> args() noexcept = 0;
	virtual span<ExprNode* const> args() const noexcept = 0;

	virtual double evaluate(const map<string, double>& vars) const = 0;

	friend ostream& operator<<(ostream& os, const ExprNode& node);
};

ostream& operator<<(ostream& os, const ExprNode& node) {
	node.dump(os, 0);

	return os;
}