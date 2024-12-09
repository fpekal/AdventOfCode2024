#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

std::map<char, std::vector<std::pair<int,int>>> parse_input() {
	std::map<char, std::vector<std::pair<int,int>>> grid;
	std::ifstream file("input.txt");
	std::string line;
	int y = 0;
	while (std::getline(file, line)) {
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == '.') continue;

			grid[line[i]].push_back({i, y});
		}
		++y;
	}
	return grid;
}

bool in_bounds(int x, int y) {
	return x >= 0 && x < 50 && y >= 0 && y < 50;
}

int part1(const std::map<char, std::vector<std::pair<int,int>>>& grid) {
	std::set<std::pair<int,int>> antinodes;

	for (auto& p : grid) {
		auto& v = p.second;

		for (int i = 0; i < v.size() - 1; i++) {
			for (int ii = i + 1; ii < v.size(); ii++) {
				auto& coords1 = v[i];
				auto& coords2 = v[ii];

				std::pair<int,int> antinode_coords1 = { coords1.first*2 - coords2.first, coords1.second*2 - coords2.second };
				std::pair<int,int> antinode_coords2 = { coords2.first*2 - coords1.first, coords2.second*2 - coords1.second };

				if (in_bounds(antinode_coords1.first, antinode_coords1.second)) antinodes.insert(antinode_coords1);
				if (in_bounds(antinode_coords2.first, antinode_coords2.second)) antinodes.insert(antinode_coords2);
			}
		}
	}

	return antinodes.size();
}

int part2(const std::map<char, std::vector<std::pair<int,int>>>& grid) {
	std::set<std::pair<int,int>> antinodes;

	for (auto& p : grid) {
		auto& v = p.second;

		for (int i = 0; i < v.size() - 1; i++) {
			for (int ii = i + 1; ii < v.size(); ii++) {
				auto& coords1 = v[i];
				auto& coords2 = v[ii];

				std::pair<int,int> diff1 = { coords1.first - coords2.first, coords1.second - coords2.second };

				for (int iii = 0;; ++iii) {
					std::pair<int,int> antinode_coords1 = { coords2.first + diff1.first*iii, coords2.second + diff1.second*iii };
					std::pair<int,int> antinode_coords2 = { coords1.first - diff1.first*iii, coords1.second - diff1.second*iii };

					if (!in_bounds(antinode_coords1.first, antinode_coords1.second) &&
							!in_bounds(antinode_coords2.first, antinode_coords2.second)) break;

					if (in_bounds(antinode_coords1.first, antinode_coords1.second)) antinodes.insert(antinode_coords1);
					if (in_bounds(antinode_coords2.first, antinode_coords2.second)) antinodes.insert(antinode_coords2);
				}
			}
		}
	}

	return antinodes.size();
}

int main() {
	auto grid = parse_input();

	std::cout << part1(grid) << "\n";
	std::cout << part2(grid) << "\n";
}
