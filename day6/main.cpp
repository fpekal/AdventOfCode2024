#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <string>

struct Position {
	int x = 0; int y = 0;

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
} pos;
int direction = 0;

struct PosDir {
	Position pos;
	int direction;

	bool operator==(const PosDir& other) const {
		return pos == other.pos && direction == other.direction;
	}
};

std::vector<std::string> parse_input() {
	std::ifstream input("input.txt");
	std::vector<std::string> result;
	std::string line;
	int y = 0;
	while (std::getline(input, line)) {
		for (int x = 0; x < line.size(); x++) {
			if (line[x] == '^') {
				pos.x = x;
				pos.y = y;
			}
		}
		result.push_back(line);
		y++;
	}
	return result;
}

Position pos_dir(Position pos, int direction) {
	switch (direction) {
		case 0:
			pos.y--;
			break;
		case 1:
			pos.x++;
			break;
		case 2:
			pos.y++;
			break;
		case 3:
			pos.x--;
			break;
	}
	return pos;
}

template<typename T>
class Hash;

template<>
class Hash<Position> {
public:
	std::size_t operator()(const Position& s) const {
		std::hash<std::string> hash;
		return hash(std::to_string(s.x)) ^ hash(std::to_string(s.y));
	}
};

template<>
class Hash<PosDir> {
public:
	std::size_t operator()(const PosDir& s) const {
		std::hash<std::string> hash;
		return hash(std::to_string(s.pos.x)) ^ hash(std::to_string(s.pos.y)) ^ hash(std::to_string(s.direction));
	}
};

std::unordered_set<Position, Hash<Position>> visited = std::unordered_set<Position, Hash<Position>>(512);

void part1() {
	auto input = parse_input();
	visited.insert(pos);

	while(true) {
		Position new_pos = pos_dir(pos, direction);

		if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x >= input[0].size() || new_pos.y >= input.size()) {
			break;
		}

		char c = input[new_pos.y][new_pos.x];

		if (c == '#') {
			direction = (direction + 1) % 4;
			continue;
		}

		visited.insert(new_pos);
		pos = new_pos;
	}

	std::cout << visited.size() << std::endl;
}

std::unordered_set<PosDir, Hash<PosDir>> visited_part2 = std::unordered_set<PosDir, Hash<PosDir>>(512);

void part2() {
	auto input = parse_input();
	auto start_pos = pos;
	//visited_part2.insert({pos, 0});

	int count = 0;

	for (int y = 0; y < input.size(); y++) {
		for (int x = 0; x < input[y].size(); x++) {
			pos = start_pos;
			direction = 0;
			if (y == pos.y && x == pos.x) {
				continue;
			}

			auto new_input = input;
			new_input[y][x] = '#';
			visited_part2.clear();

			while(true) {
				Position new_pos = pos_dir(pos, direction);

				if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x >= input[0].size() || new_pos.y >= input.size()) {
					break;
				}

				char c = new_input[new_pos.y][new_pos.x];

				if (c == '#') {
					direction = (direction + 1) % 4;
					continue;
				}

				if (visited_part2.find({new_pos, direction}) != visited_part2.end()) {
					count++;
					break;
				}
				
				visited_part2.insert({new_pos, direction});
				pos = new_pos;
			}
		}
	}

	std::cout << count << std::endl;
}

int main() {
	part1();
	part2();
}
