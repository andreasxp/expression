#pragma once
#include <algorithm>

using namespace std;

template <class T, class C, class = void>
struct ContainsCls {
	bool operator()(const C& container, const T& value) const {
		return find(container.begin(), container.end(), value) != std::end(container);
	}
};

template <class T, class C>
struct ContainsCls<T, C, void_t<decltype(declval<C>().find(declval<T>()))>> {
	bool operator()(const C& container, const T& value) const {
		return container.find(value) != std::end(container);
	}
};

template <class T, class C>
bool contains(const C& container, const T& value) {
	return ContainsCls<T, C>{}(container, value);
}