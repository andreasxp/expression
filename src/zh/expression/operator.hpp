#pragma once
#include <array>
#include <cassert>
#include "expr_node.hpp"

using namespace std;


struct Operator : ExprNode {
private:
	array<ExprNode*, 2> m_args;

	Operator* rotate_right() {
		assert(dynamic_cast<Operator*>(m_args[0]) != nullptr);

		Operator* root = this;
		Operator* pivot = static_cast<Operator*>(m_args[0]);

		m_args[0] = pivot->m_args[1];
		pivot->m_args[1] = root;

		return pivot;
	}

	Operator* rotate_left() {
		assert(dynamic_cast<Operator*>(m_args[1]) != nullptr);

		Operator* root = this;
		Operator* pivot = static_cast<Operator*>(m_args[1]);

		m_args[1] = pivot->m_args[0];
		pivot->m_args[0] = root;

		return pivot;
	}

public:
	Operator(ExprNode* lhs, ExprNode* rhs) :
		m_args{{lhs, rhs}} {}

	virtual uint8_t order() const = 0;

	span<ExprNode*> args() noexcept final {
		return span(m_args);
	}

	span<ExprNode* const> args() const noexcept final {
		return span(m_args);
	}

	Operator* sort() {
		auto left_op = dynamic_cast<Operator*>(m_args[0]);
		auto right_op = dynamic_cast<Operator*>(m_args[1]);

		// Sort children -----------------------------------------------------------------------------------------------
		if (left_op) {
			left_op = left_op->sort();
			m_args[0] = left_op;
		}
		if (right_op) {
			right_op = right_op->sort();
			m_args[1] = right_op;
		}

		// Sort this (rotate left or right or both) --------------------------------------------------------------------
		// If this operation's order comes after left, left is not considered for rotation
		if (left_op && order() > left_op->order()) left_op = nullptr;

		// If this operation's order comes after right, right is not considered for rotation
		if (right_op && order() > right_op->order()) right_op = nullptr;

		if (left_op && right_op) {
			// If both children need to be higher, determine which rotation to perform first
			if (right_op->order() >= left_op->order()) {
				// Right needs to be higher, so rotate tree to the left
				Operator* new_root = rotate_left();
				new_root->m_args[0] = rotate_right();

				return new_root;
			}
			// Left needs to be higher, so rotate tree to the right
			Operator* new_root = rotate_right();
			new_root->m_args[1] = rotate_left();

			return new_root;
		}

		if (left_op) return rotate_right();
		if (right_op) return rotate_left();

		return this;
	}
};
