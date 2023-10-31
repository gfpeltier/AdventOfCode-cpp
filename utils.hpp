#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <functional>
#include <vector>

template <typename T>
int pcount(std::vector<T> v, std::function<bool(T)> pred) {
	int count = 0;
	for (auto a : v) {
		if (pred(a)) {
			count++;
		}
	}
	return count;
}

#endif