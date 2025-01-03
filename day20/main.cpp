#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>
#include <map>

std::tuple<std::vector<std::vector<int>>, std::pair<int, int>, std::pair<int, int>> parse_input() {
	std::vector<std::vector<int>> input;
	std::pair<int, int> start_pos;
	std::pair<int, int> end_pos;
	std::ifstream file("input.txt");
	std::string line;
	int y = 0;
	while (std::getline(file, line)) {
		std::vector<int> row;
		int x = 0;
		for (char c : line) {
			if (c == 'S') {
				start_pos.first = x;
				start_pos.second = y;
			}
			else if (c == 'E') {
				end_pos.first = x;
				end_pos.second = y;
			}
			row.push_back(c == '#' ? -1 : 0);
			++x;
		}
		input.push_back(row);
		++y;
	}

	input.at(start_pos.second).at(start_pos.first) = -1;

	auto now = start_pos;
	int i = 1;

	while (true) {
		std::pair<int, int> next;
		if (input.at(now.second).at(now.first + 1) == 0) {
			next.first = now.first + 1;
			next.second = now.second;
		}
		else if (input.at(now.second).at(now.first - 1) == 0) {
			next.first = now.first - 1;
			next.second = now.second;
		}
		else if (input.at(now.second + 1).at(now.first) == 0) {
			next.first = now.first;
			next.second = now.second + 1;
		}
		else if (input.at(now.second - 1).at(now.first) == 0) {
			next.first = now.first;
			next.second = now.second - 1;
		}
		else {
			break;
		}
		now = next;
		input.at(now.second).at(now.first) = i;
		++i;
	}

	input.at(start_pos.second).at(start_pos.first) = 0;

	return { input, start_pos, end_pos };
}

long long part1(std::vector<std::vector<int>> grid, std::pair<int, int> start_pos, std::pair<int, int> end_pos) {
	auto now = start_pos;
	int i = 1;
	long long sum = 0;

	while (true) {
		for (int dy = -2; dy <= 2; ++dy) {
			for (int dx = -2; dx <= 2; ++dx) {
				if (now.first + dx < 0 || now.first + dx >= grid.at(0).size() || now.second + dy < 0 || now.second + dy >= grid.size())
					continue;

				if (std::abs(dy) + std::abs(dx) > 2) continue;

				if (grid.at(now.second + dy).at(now.first + dx) - i - 1 >= 100) {
					sum++;
				}
			}
		}

		std::pair<int, int> next;
		if (grid.at(now.second).at(now.first + 1) == i) {
			next.first = now.first + 1;
			next.second = now.second;
		}
		else if (grid.at(now.second).at(now.first - 1) == i) {
			next.first = now.first - 1;
			next.second = now.second;
		}
		else if (grid.at(now.second + 1).at(now.first) == i) {
			next.first = now.first;
			next.second = now.second + 1;
		}
		else if (grid.at(now.second - 1).at(now.first) == i) {
			next.first = now.first;
			next.second = now.second - 1;
		}
		else {
			break;
		}
		now = next;
		++i;
	}

	return sum;
}

long long part2(std::vector<std::vector<int>> grid, std::pair<int, int> start_pos, std::pair<int, int> end_pos) {
	auto now = start_pos;
	int i = 1;
	long long sum = 0;

	std::map<int, int> test;

	while (true) {
		for (int dy = -20; dy <= 20; ++dy) {
			for (int dx = -20; dx <= 20; ++dx) {
				if (now.first + dx < 0 || now.first + dx >= grid.at(0).size() || now.second + dy < 0 || now.second + dy >= grid.size())
					continue;

				if (std::abs(dy) + std::abs(dx) > 20) continue;

				if (grid.at(now.second + dy).at(now.first + dx) - i + 1 - std::abs(dy) - std::abs(dx) >= 100) {
					sum++;
					test[grid.at(now.second + dy).at(now.first + dx) - i + 1 - std::abs(dy) - std::abs(dx)]++;
				}
			}
		}

		std::pair<int, int> next;
		if (grid.at(now.second).at(now.first + 1) == i) {
			next.first = now.first + 1;
			next.second = now.second;
		}
		else if (grid.at(now.second).at(now.first - 1) == i) {
			next.first = now.first - 1;
			next.second = now.second;
		}
		else if (grid.at(now.second + 1).at(now.first) == i) {
			next.first = now.first;
			next.second = now.second + 1;
		}
		else if (grid.at(now.second - 1).at(now.first) == i) {
			next.first = now.first;
			next.second = now.second - 1;
		}
		else {
			break;
		}
		now = next;
		++i;
	}

	for (auto& [k, v] : test) {
		if (k == 0) continue;
		std::cout << k << ": " << v << std::endl;
	}

	return sum;
}

int main() {
	auto input = parse_input();

	auto& grid = std::get<0>(input);
	auto& start_pos = std::get<1>(input);
	auto& end_pos = std::get<2>(input);

	std::cout << part1(grid, start_pos, end_pos) << std::endl;
	std::cout << part2(grid, start_pos, end_pos) << std::endl;
}
