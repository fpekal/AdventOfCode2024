#include <iostream>
#include <fstream>
#include <array>
#include <vector>

std::pair<std::vector<std::array<int, 5>>, std::vector<std::array<int, 5>>> parse_input() {
	std::ifstream file("input.txt");

	std::vector<std::array<int, 5>> keys;
	std::vector<std::array<int, 5>> locks;

	while(true) {
		std::array<std::array<bool, 5>, 7> grid;

		for(int i = 0; i < 7; i++) {
			std::string line;
			std::getline(file, line);

			for(int j = 0; j < 5; j++) {
				grid[i][j] = line[j] == '#';
			}
		}

		if(file.eof()) {
			break;
		}

		if (grid[0][0] == true) { // lock
			std::array<int, 5> lock;
			for (int i = 0; i < 5; i++) {
				for (int j = 5; j >= 0; j--) {
					if (grid[j][i] == true) {
						lock[i] = j;
						break;
					}
				}
			}
			locks.push_back(lock);
		}
		else { // key
			std::array<int, 5> key;
			for (int i = 0; i < 5; i++) {
				for (int j = 1; j < 7; j++) {
					if (grid[j][i] == true) {
						key[i] = 6 - j;
						break;
					}
				}
			}
			keys.push_back(key);
		}

		{
			std::string tmp;
			std::getline(file, tmp);
		}
	}

	return {keys, locks};
}

long long part1(std::vector<std::array<int, 5>> keys, std::vector<std::array<int, 5>> locks) {
	long long sum = 0;

	for (auto& key : keys) {
		for (auto& lock : locks) {
			bool ok = true;
			for (int i = 0; i < 5; i++) {
				if (key[i] + lock[i] > 5) {
					ok = false;
					break;
				}
			}
			if (ok) ++sum;
		}
	}

	return sum;
}

int main() {
	auto input = parse_input();

	std::cout << part1(input.first, input.second) << std::endl;

	return 0;
}
