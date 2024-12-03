#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int part1(const std::string& str) {
	bool enabled = true;
	int ret = 0;

	std::regex r {"mul\\((\\d+),(\\d+)\\)"};

	std::sregex_iterator it(str.begin(), str.end(), r);
	std::sregex_iterator end;

	for (; it != end; ++it) {
		std::smatch m = *it;
		int a = std::stoi(m[1]);
		int b = std::stoi(m[2]);
		ret += a * b;
	}

	return ret;
}

int part2(const std::string& str) {
	bool enabled = true;
	int ret = 0;

	std::regex r {"(mul|do|don't)\\((\\d*),?(\\d*)\\)"};

	std::sregex_iterator it(str.begin(), str.end(), r);
	std::sregex_iterator end;

	for (; it != end; ++it) {
		std::smatch m = *it;
		std::string instr = m[1];
		if (instr == "mul") {
			if (!enabled) continue;
			int a = std::stoi(m[2]);
			int b = std::stoi(m[3]);
			ret += a * b;
			continue;
		}

		if (instr == "do") {
			enabled = true;
			continue;
		}

		if (instr == "don't") {
			enabled = false;
			continue;
		}
	}

	return ret;
}

int main() {
	std::ifstream input("input.txt");

	std::string whole_file;
	std::copy(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), std::back_inserter(whole_file));

	std::cout << "Part 1: " << part1(whole_file) << std::endl;
	std::cout << "Part 2: " << part2(whole_file) << std::endl;
}
