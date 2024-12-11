#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <map>
#include <array>

std::list<long long> parse_input() {
	std::ifstream file("input.txt");
	std::list<long long> result;

	while(true) {
		long long value;
		file >> value;
		if (file.eof()) {
			break;
		}
		result.push_back(value);
	}

	return result;
}

std::array<std::map<long long, long long>, 75> cache;

long long foo(long long a, int depth) {
	if (depth == 0) {
		return 1;
	}

	{
		auto found = cache[depth - 1].find(a);
		if (found != cache[depth - 1].end()) {
			return found->second;
		}
	}


	if (a == 0) {
		auto ret = foo(1, depth - 1);
		cache[depth - 1][0] = ret;
		return ret;
	}

	long long digits = std::log10(a) + 1;
	if (digits % 2 == 0) {
		auto ret1 = foo(a / std::pow(10, digits / 2), depth - 1);
		auto ret2 = foo(a % (long long)std::pow(10, digits / 2), depth - 1);
		cache[depth - 1][a] = ret1 + ret2;
		return ret1 + ret2;
	}

	auto ret = foo(a * 2024, depth - 1);
	cache[depth - 1][a] = ret;
	return ret;
}

int main() {
	auto input = parse_input();

	long long sum1 = 0;
	long long sum2 = 0;
	for (long long a : input) {
		sum1 += foo(a, 25);
		sum2 += foo(a, 75);
	}
	std::cout << sum1 << '\n' << sum2;
}
