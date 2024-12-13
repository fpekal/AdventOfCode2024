#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
#include <array>

std::vector<std::array<std::pair<int, int>, 3>> parse_input() {
	std::ifstream file("input.txt");
	std::vector<std::array<std::pair<int, int>, 3>> result;

	while (true) {
		std::array<std::pair<int, int>, 3> current;
		std::regex r{"Button .: X\\+(\\d+), Y\\+(\\d+)"};

		std::smatch m;
		std::string line;

		std::getline(file, line);
		if (file.eof())
			break;
		if (std::regex_match(line, m, r)) {
			current.at(0) = std::make_pair(std::stoi(m[1]), std::stoi(m[2]));
		}

		std::getline(file, line);
		if (std::regex_match(line, m, r)) {
			current.at(1) = std::make_pair(std::stoi(m[1]), std::stoi(m[2]));
		}

		r = std::regex{"Prize: X=(\\d+), Y=(\\d+)"};
		std::getline(file, line);
		if (std::regex_match(line, m, r)) {
			current.at(2) = std::make_pair(std::stoi(m[1]), std::stoi(m[2]));
		}

		std::getline(file, line);

		result.push_back(current);
	}

	return result;
}

// Matrix fuckery
long long part1(const std::vector<std::array<std::pair<int, int>, 3>>& input) {
	long long sum = 0;

	for (auto& i : input) {
		double A = (i[1].second * i[2].first - i[1].first * i[2].second) / (double)(i[0].first * i[1].second - i[0].second * i[1].first);
		double B = (i[0].first * i[2].second - i[0].second * i[2].first) / (double)(i[0].first * i[1].second - i[0].second * i[1].first);

		if (A == (long long)A && B == (long long)B) {
			sum += A*3 + B;
		}
	}

	return sum;
}

long long part2(const std::vector<std::array<std::pair<int, int>, 3>>& input) {
	long long sum = 0;


	for (auto& i : input) {
		long long X = (long long)i[2].first + 10000000000000;
		long long Y = (long long)i[2].second + 10000000000000;

		double A = (i[1].second * X - i[1].first * Y) / (double)(i[0].first * i[1].second - i[0].second * i[1].first);
		double B = (i[0].first * Y - i[0].second * X) / (double)(i[0].first * i[1].second - i[0].second * i[1].first);

		if (A == (long long)A && B == (long long)B) {
			sum += A*3 + B;
		}
	}

	return sum;
}

int main() {
	auto input = parse_input();

	std::cout << part1(input) << std::endl;
	std::cout << part2(input) << std::endl;
}
