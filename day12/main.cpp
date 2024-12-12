#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <array>

std::vector<std::vector<char>> parse_input() {
	std::ifstream file("input.txt");
	std::vector<std::vector<char>> result;
	std::string line;
	while (std::getline(file, line)) {
		std::vector<char> row;
		for (char c : line) {
			row.push_back(c);
		}
		result.push_back(row);
	}
	return result;
}

std::vector<std::vector<int>> group(const std::vector<std::vector<char>>& map) {
	std::vector<std::vector<int>> result;
	result.resize(map.size());
	for (int i = 0; i < map.size(); ++i) {
		result[i].resize(map[i].size());
		for (int j = 0; j < map[i].size(); ++j) {
			result[i][j] = i * map[i].size() + j;
		}
	}

	for (int y = 0; y < result.size(); ++y) {
		for (int x = 0; x < result[y].size(); ++x) {
			if (y-1 >= 0 && map[y][x] == map[y-1][x] && result[y][x] != result[y-1][x]) {
				int to_change = result[y][x];
				int to_change_with = result[y-1][x];

				for (int yy = 0; yy < result.size(); ++yy) {
					for (int xx = 0; xx < result[yy].size(); ++xx) {
						if (result[yy][xx] == to_change)
							result[yy][xx] = to_change_with;
					}
				}
			}

			if (x-1 >= 0 && map[y][x] == map[y][x-1] && result[y][x] != result[y][x-1]) {
				int to_change = result[y][x];
				int to_change_with = result[y][x-1];

				for (int yy = 0; yy < result.size(); ++yy) {
					for (int xx = 0; xx < result[yy].size(); ++xx) {
						if (result[yy][xx] == to_change)
							result[yy][xx] = to_change_with;
					}
				}
			}
		}
	}

	return result;
}

long long part1(const std::vector<std::vector<int>>& groups) {
	std::map<int, std::pair<int, int>> groups_sizes;

	for (int y = 0; y < groups.size(); ++y) {
		for (int x = 0; x < groups[y].size(); ++x) {
			int group = groups[y][x];
			groups_sizes[group].first++;
			groups_sizes[group].second += 4;

			if (x-1 >= 0)
				if (group == groups[y][x-1])
					groups_sizes[group].second -= 2;

			if (y-1 >= 0)
				if (group == groups[y-1][x])
					groups_sizes[group].second -= 2;
		}
	}

	long long sum = 0;
	for (auto& group : groups_sizes) {
		sum += group.second.second * group.second.first;
	}

	return sum;
}

long long part2(const std::vector<std::vector<int>>& groups) {
	std::vector<std::vector<std::array<int, 4>>> sides;
	sides.resize(groups.size());
	for (int y = 0; y < groups.size(); ++y) {
		sides[y].resize(groups[y].size());
		for (int x = 0; x < groups[y].size(); ++x) {
			sides[y][x][0] = -1;
			sides[y][x][1] = -1;
			sides[y][x][2] = -1;
			sides[y][x][3] = -1;
		}
	}
	std::map<int, int> group_area;
	int next_side = 0;
	for (int y = 0; y < groups.size(); ++y) {
		for (int x = 0; x < groups[y].size(); ++x) {
			group_area[groups[y][x]]++;
			// LEFT
			if (x-1 >= 0) {
				if (groups[y][x] != groups[y][x-1]) {
					if (y-1 >= 0 && groups[y][x] == groups[y-1][x]) {
						if (sides[y-1][x][3] != -1)
							sides[y][x][3] = sides[y-1][x][3];
						else
							sides[y][x][3] = next_side++;
					}
					else {
						sides[y][x][3] = next_side++;
					}
				}
			}
			else {
				if (y-1 >= 0 && groups[y][x] == groups[y-1][x]) {
					if (sides[y-1][x][3] != -1)
						sides[y][x][3] = sides[y-1][x][3];
					else
						sides[y][x][3] = next_side++;
				}
				else {
					sides[y][x][3] = next_side++;
				}
			}
			// UP
			if (y-1 >= 0) {
				if (groups[y][x] != groups[y-1][x]) {
					if (x-1 >= 0 && groups[y][x] == groups[y][x-1]) {
						if (sides[y][x-1][0] != -1)
							sides[y][x][0] = sides[y][x-1][0];
						else
							sides[y][x][0] = next_side++;
					}
					else {
						sides[y][x][0] = next_side++;
					}
				}
			}
			else {
				if (x-1 >= 0 && groups[y][x] == groups[y][x-1]) {
					if (sides[y][x-1][0] != -1)
						sides[y][x][0] = sides[y][x-1][0];
					else
						sides[y][x][0] = next_side++;
				}
				else {
					sides[y][x][0] = next_side++;
				}
			}
			// RIGHT
			if (x+1 < groups[y].size()) {
				if (groups[y][x] != groups[y][x+1]) {
					if (y-1 >= 0 && groups[y][x] == groups[y-1][x]) {
						if (sides[y-1][x][1] != -1)
							sides[y][x][1] = sides[y-1][x][1];
						else
							sides[y][x][1] = next_side++;
					}
					else {
						sides[y][x][1] = next_side++;
					}
				}
			}
			else {
				if (y-1 >= 0 && groups[y][x] == groups[y-1][x]) {
					if (sides[y-1][x][1] != -1)
						sides[y][x][1] = sides[y-1][x][1];
					else
						sides[y][x][1] = next_side++;
				}
				else {
					sides[y][x][1] = next_side++;
				}
			}
			// DOWN
			if (y+1 < groups.size()) {
				if (groups[y][x] != groups[y+1][x]) {
					if (x-1 >= 0 && groups[y][x] == groups[y][x-1]) {
						if (sides[y][x-1][2] != -1)
							sides[y][x][2] = sides[y][x-1][2];
						else
							sides[y][x][2] = next_side++;
					}
					else {
						sides[y][x][2] = next_side++;
					}
				}
			}
			else {
				if (x-1 >= 0 && groups[y][x] == groups[y][x-1]) {
					if (sides[y][x-1][2] != -1)
						sides[y][x][2] = sides[y][x-1][2];
					else
						sides[y][x][2] = next_side++;
				}
				else {
					sides[y][x][2] = next_side++;
				}
			}
		}
	}
	std::map<int, std::set<int>> groups_sides;
	for (int y = 0; y < groups.size(); ++y) {
		for (int x = 0; x < groups[y].size(); ++x) {
			if (sides[y][x][0] != -1)
				groups_sides[groups[y][x]].insert(sides[y][x][0]);
			if (sides[y][x][1] != -1)
				groups_sides[groups[y][x]].insert(sides[y][x][1]);
			if (sides[y][x][2] != -1)
				groups_sides[groups[y][x]].insert(sides[y][x][2]);
			if (sides[y][x][3] != -1)
				groups_sides[groups[y][x]].insert(sides[y][x][3]);
		}
	}

	long long sum = 0;
	for (auto& group : groups_sides) {
		sum += group.second.size() * group_area[group.first];
	}
	return sum;
}

int main() {
	auto input1 = parse_input();
	auto input2 = group(input1);

	std::cout << part1(input2) << std::endl;
	std::cout << part2(input2) << std::endl;
}
