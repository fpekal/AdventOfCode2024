#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

long long modulo( long long value, long long m) {
    long long mod = value % m;
    if (mod < 0) {
        mod += m;
    }
    return mod;
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> parse_input() {
	std::ifstream file("input.txt");

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> result;
	std::regex r{"p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)"};
	while (true) {
		std::string line;
		std::getline(file, line);
		if (file.eof()) {
			break;
		}

		std::smatch m;
		if (std::regex_match(line, m, r)) {
			result.push_back({{std::stoi(m[1]), std::stoi(m[2])}, {std::stoi(m[3]), std::stoi(m[4])}});
		}
	}

	return result;
}

long long part1(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> input) {
	for (int i = 0; i < 100; ++i) {
		for (auto& p : input) {
			p.first.first += p.second.first;
			p.first.second += p.second.second;

			p.first.first = modulo(p.first.first, 101);
			p.first.second = modulo(p.first.second, 103);
		}
	}

	long long q0 = 0;
	long long q1 = 0;
	long long q2 = 0;
	long long q3 = 0;

	for (auto& p : input) {
		if (p.first.first >= 0 && p.first.first < 50 && p.first.second >= 0 && p.first.second < 51) ++q0;
		else if (p.first.first >= 51 && p.first.first < 101 && p.first.second >= 0 && p.first.second < 51) ++q1;
		else if (p.first.first >= 0 && p.first.first < 50 && p.first.second >= 52 && p.first.second < 103) ++q2;
		else if (p.first.first >= 51 && p.first.first < 101 && p.first.second >= 52 && p.first.second < 103) ++q3;
	}

	return q0 * q1 * q2 * q3;
}

// Found by brute force idk
long long part2(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> input) {
	for (int i = 0; i < 7093; ++i) {
		for (auto& p : input) {
			p.first.first += p.second.first;
			p.first.second += p.second.second;

			p.first.first = modulo(p.first.first, 101);
			p.first.second = modulo(p.first.second, 103);
		}
	}

	for (int y = 0; y < 103; ++y) {
		for (int x = 0; x < 101; ++x) {
			bool found = false;
			for (auto& p : input) {
				if (p.first.first == x && p.first.second == y) {
					found = true;
					break;
				}
			}
			if (!found) {
				std::cout << " ";
			}
			else {
				std::cout << "#";
			}
		}
		std::cout << '\n';
	}

	return 7093;
}

int main() {
	auto input = parse_input();

	std::cout << part1(input) << std::endl;
	std::cout << part2(input) << std::endl;
}
