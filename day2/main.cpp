#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> parse_input(std::string filename) {
	std::ifstream file {filename};
	std::vector<std::vector<int>> ret;

	while (file.peek() != EOF) {
		std::string line;
		std::getline(file, line);

		std::vector<int> row;
		std::stringstream ss {line};

		while (ss.peek() != EOF) {
			int x;
			ss >> x;
			row.push_back(x);
		}
		ret.push_back(row);
	}

	return ret;
}

bool second_check(std::vector<int> row) {
	if (
			std::is_sorted(row.begin(), row.end()) ||
			std::is_sorted(row.rbegin(), row.rend())
			) {

		bool good = true;
		for (int i = 1; i < row.size(); i++) {
			int diff = std::abs(row[i] - row[i-1]);
			if (not (diff >= 1 && diff <= 3)) {
				good = false;
				break;
			}
		}

		if (good) {
			return true;
		}
	}

	return false;
}

bool first_check(std::vector<int> row) {
	if (
			std::is_sorted(row.begin(), row.end()) ||
			std::is_sorted(row.rbegin(), row.rend())
			) {

		bool good = true;
		for (int i = 1; i < row.size(); i++) {
			int diff = std::abs(row[i] - row[i-1]);
			if (not (diff >= 1 && diff <= 3)) {
				good = false;
				break;
			}
		}

		if (good) {
			return true;
		}
	}

	for (int i = 0; i < row.size(); ++i) {
		std::vector<int> new_row = row;
		new_row.erase(new_row.begin() + i);
		if (second_check(new_row)) {
			return true;
		}
	}

	return false;
}

int main() {
	int count = 0;

	for (auto row : parse_input("input.txt")) {
		if (first_check(row)) {
			count++;
		}
	}

	std::cout << count;
}
