#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>


std::tuple<std::pair<int, int>, std::vector<std::vector<int>>, std::vector<int>> parse_input() {
	std::ifstream file("input.txt");
	std::vector<std::vector<int>> map;
	int x = 0, y = 0;
	while(true) {
		std::string line;
		std::getline(file, line);
		if(line == "") {
			break;
		}
		std::vector<int> row;
		for(int i = 0; i < line.size(); i++) {
			switch(line[i]) {
				case '.':
					row.push_back(0);
					break;
				case '#':
					row.push_back(1);
					break;
				case 'O':
					row.push_back(2);
					break;
				case '@':
					x = i;
					y = map.size();
					row.push_back(0);
					break;
				default:
					exit(1);
			}
		}
		map.push_back(row);
	}

	std::vector<int> directions;
	while(true) {
		std::string line;
		std::getline(file, line);
		if (file.eof()) {
			break;
		}
		for(int i = 0; i < line.size(); i++) {
			switch(line[i]) {
				case '^':
					directions.push_back(0);
					break;
				case '>':
					directions.push_back(1);
					break;
				case 'v':
					directions.push_back(2);
					break;
				case '<':
					directions.push_back(3);
					break;
				default:
					exit(1);
			}
		}
	}

	return std::make_tuple(std::make_pair(x, y), map, directions);
}

bool recur_move(std::vector<std::vector<int>>& map, const std::pair<int, int>& old_pos, const std::pair<int, int>& new_pos) {
	if (map[old_pos.second][old_pos.first] == 0) return true;
	if (map[old_pos.second][old_pos.first] == 1) return false;
	if (map[new_pos.second][new_pos.first] == 0) {
		map[new_pos.second][new_pos.first] = 2;
		map[old_pos.second][old_pos.first] = 0;
		return true;
	}
	if (map[new_pos.second][new_pos.first] == 1) {
		return false;
	}
	if (map[new_pos.second][new_pos.first] == 2) {
		if (recur_move(map, new_pos, std::make_pair(new_pos.first*2 - old_pos.first, new_pos.second*2 - old_pos.second))) {
			map[new_pos.second][new_pos.first] = 2;
			map[old_pos.second][old_pos.first] = 0;
			return true;
		}	
		return false;
	}
	return false;
}

long long part1(std::pair<int, int> pos, std::vector<std::vector<int>> map, const std::vector<int>& directions) {
	for (int dir : directions) {
		switch(dir) {
			case 0:
				if (recur_move(map, std::make_pair(pos.first, pos.second - 1), std::make_pair(pos.first, pos.second - 2))) {
					pos.second--;
				}
				break;
			case 1:
				if (recur_move(map, std::make_pair(pos.first +1, pos.second), std::make_pair(pos.first + 2, pos.second))) {
					pos.first++;
				}
				break;
			case 2:
				if (recur_move(map, std::make_pair(pos.first, pos.second + 1), std::make_pair(pos.first, pos.second + 2))) {
					pos.second++;
				}
				break;
			case 3:
				if (recur_move(map, std::make_pair(pos.first - 1, pos.second), std::make_pair(pos.first - 2, pos.second))) {
					pos.first--;
				}
				break;
		}
	}

	long long sum = 0;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 2) {
				sum += y*100 + x;
			}
		}
	}

	return sum;
}

std::tuple<std::pair<int, int>, std::vector<std::vector<int>>, std::vector<int>> transform_input(const std::tuple<std::pair<int, int>, std::vector<std::vector<int>>, std::vector<int>>& input) {
	auto [pos, map, directions] = input;
	std::vector<std::vector<int>> new_map;
	for (int y = 0; y < map.size(); y++) {
		std::vector<int> row;
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 0) {
				row.push_back(0);
				row.push_back(0);
			}
			else if (map[y][x] == 1) {
				row.push_back(1);
				row.push_back(1);
			}
			else {
				row.push_back(2);
				row.push_back(3);
			}
		}
		new_map.push_back(row);
	}
	pos = std::make_pair(pos.first*2, pos.second);
	return std::make_tuple(pos, new_map, directions);
}

bool recur_move2(std::vector<std::vector<int>>& map, const std::pair<int, int>& pos, int direction) {
	if (map[pos.second][pos.first] == 0) return true;
	if (map[pos.second][pos.first] == 1) return false;
	if (map[pos.second][pos.first] == 2) {
		if (direction == 0) {
			auto map_backup = map;
			if (!recur_move2(map, std::make_pair(pos.first, pos.second - 1), 0)) {
				return false;
			}
			if (!recur_move2(map, std::make_pair(pos.first + 1, pos.second - 1), 0)) {
				map = map_backup;
				return false;
			}
			map[pos.second][pos.first] = 0;
			map[pos.second][pos.first+1] = 0;
			map[pos.second-1][pos.first] = 2;
			map[pos.second-1][pos.first+1] = 3;
			return true;
		}
		if (direction == 1) {
			return recur_move2(map, std::make_pair(pos.first + 1, pos.second), 1);
		}
		if (direction == 2) {
			auto map_backup = map;
			if (!recur_move2(map, std::make_pair(pos.first, pos.second + 1), 2)) {
				return false;
			}
			if (!recur_move2(map, std::make_pair(pos.first + 1, pos.second + 1), 2)) {
				map = map_backup;
				return false;
			}
			map[pos.second][pos.first] = 0;
			map[pos.second][pos.first+1] = 0;
			map[pos.second+1][pos.first] = 2;
			map[pos.second+1][pos.first+1] = 3;
			return true;
		}
		if (direction == 3) {
			if (recur_move2(map, std::make_pair(pos.first - 1, pos.second), 3)) {
				map[pos.second][pos.first-1] = 2;
				map[pos.second][pos.first] = 3;
				map[pos.second][pos.first+1] = 0;
				return true;
			}
			return false;
		}
	}
	if (map[pos.second][pos.first] == 3) {
		if (direction == 0) {
			auto map_backup = map;
			if (!recur_move2(map, std::make_pair(pos.first, pos.second - 1), 0)) {
				return false;
			}
			if (!recur_move2(map, std::make_pair(pos.first - 1, pos.second - 1), 0)) {
				map = map_backup;
				return false;
			}
			map[pos.second][pos.first] = 0;
			map[pos.second][pos.first-1] = 0;
			map[pos.second-1][pos.first-1] = 2;
			map[pos.second-1][pos.first] = 3;
			return true;
		}
		if (direction == 1) {
			if (recur_move2(map, std::make_pair(pos.first + 1, pos.second), 1)) {
				map[pos.second][pos.first-1] = 0;
				map[pos.second][pos.first] = 2;
				map[pos.second][pos.first+1] = 3;
				return true;
			}
			return false;
		}
		if (direction == 2) {
			auto map_backup = map;
			if (!recur_move2(map, std::make_pair(pos.first, pos.second + 1), 2)) {
				return false;
			}
			if (!recur_move2(map, std::make_pair(pos.first - 1, pos.second + 1), 2)) {
				map = map_backup;
				return false;
			}
			map[pos.second][pos.first] = 0;
			map[pos.second][pos.first-1] = 0;
			map[pos.second+1][pos.first-1] = 2;
			map[pos.second+1][pos.first] = 3;
			return true;
		}
		if (direction == 3) {
			return recur_move2(map, std::make_pair(pos.first - 1, pos.second), 3);
		}
	}
}

long long part2(std::pair<int, int> pos, std::vector<std::vector<int>> map, const std::vector<int>& directions) {
	for (int dir : directions) {
		switch(dir) {
			case 0:
				if (recur_move2(map, std::make_pair(pos.first, pos.second - 1), 0)) {
					pos.second--;
				}
				break;
			case 1:
				if (recur_move2(map, std::make_pair(pos.first +1, pos.second), 1)) {
					pos.first++;
				}
				break;
			case 2:
				if (recur_move2(map, std::make_pair(pos.first, pos.second + 1), 2)) {
					pos.second++;
				}
				break;
			case 3:
				if (recur_move2(map, std::make_pair(pos.first - 1, pos.second), 3)) {
					pos.first--;
				}
				break;
		}
	//int y = 0;
	//for (auto& row : map) {
	//	int x = 0;
	//	for (auto& cell : row) {
	//		switch(cell) {
	//			case 0:
	//				if (x == pos.first && y == pos.second) std::cout << "@";
	//				else std::cout << ".";
	//				break;
	//			case 1:
	//				std::cout << "#";
	//				break;
	//			case 2:
	//				std::cout << "[";
	//				break;
	//			case 3:
	//				std::cout << "]";
	//				break;
	//		}
	//		x++;
	//	}
	//	y++;
	//	std::cout << "\n";
	//}
	//std::cin.get();
	}



	long long sum = 0;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 2) {
				sum += y*100 + x;
			}
		}
	}


	return sum;
}

int main() {
	auto input = parse_input();

	{
		auto [pos, map, directions] = input;
		std::cout << part1(pos, map, directions) << "\n";
	}
	{
		auto [pos, map, directions] = transform_input(input);
		std::cout << part2(pos, map, directions);
	}
}
