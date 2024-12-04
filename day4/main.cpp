#include <iostream>
#include <fstream>
#include <vector>

bool xmas_checker(std::vector<std::string>& lines, std::pair<int, int> pos, std::pair<int, int> dir) {
	{
		int x = pos.first + 3 * dir.first;
		int y = pos.second + 3 * dir.second;

		if (x < 0 || x >= lines[0].size()) return false;
		if (y < 0 || y >= lines.size()) return false;
	}
	
	std::pair<int, int> pos1 = std::make_pair(pos.first + 0 * dir.first, pos.second + 0 * dir.second);
	std::pair<int, int> pos2 = std::make_pair(pos.first + 1 * dir.first, pos.second + 1 * dir.second);
	std::pair<int, int> pos3 = std::make_pair(pos.first + 2 * dir.first, pos.second + 2 * dir.second);
	std::pair<int, int> pos4 = std::make_pair(pos.first + 3 * dir.first, pos.second + 3 * dir.second);

	char c1 = lines[pos1.second][pos1.first];
	char c2 = lines[pos2.second][pos2.first];
	char c3 = lines[pos3.second][pos3.first];
	char c4 = lines[pos4.second][pos4.first];

	return c1 == 'X' && c2 == 'M' && c3 == 'A' && c4 == 'S';
}

bool xmas_checker_2(std::vector<std::string>& lines, std::pair<int, int> pos, std::pair<int, int> dir1, std::pair<int, int> dir2) {
	{
		int x1p = pos.first + dir1.first;
		int y1p = pos.second + dir1.second;
		int x1m = pos.first - dir1.first;
		int y1m = pos.second - dir1.second;
		int x2p = pos.first + dir2.first;
		int y2p = pos.second + dir2.second;
		int x2m = pos.first - dir2.first;
		int y2m = pos.second - dir2.second;

		if (x1p < 0 || x1p >= lines[0].size()) return false;
		if (y1p < 0 || y1p >= lines.size()) return false;
		if (x1m < 0 || x1m >= lines[0].size()) return false;
		if (y1m < 0 || y1m >= lines.size()) return false;
		if (x2p < 0 || x2p >= lines[0].size()) return false;
		if (y2p < 0 || y2p >= lines.size()) return false;
		if (x2m < 0 || x2m >= lines[0].size()) return false;
		if (y2m < 0 || y2m >= lines.size()) return false;
	}
	
	std::pair<int, int> pos1 = std::make_pair(pos.first - dir1.first, pos.second - dir1.second);
	std::pair<int, int> pos2 = std::make_pair(pos.first - dir2.first, pos.second - dir2.second);
	std::pair<int, int> pos3 = std::make_pair(pos.first, pos.second);
	std::pair<int, int> pos4 = std::make_pair(pos.first + dir1.first, pos.second + dir1.second);
	std::pair<int, int> pos5 = std::make_pair(pos.first + dir2.first, pos.second + dir2.second);

	char c1 = lines[pos1.second][pos1.first];
	char c2 = lines[pos2.second][pos2.first];
	char c3 = lines[pos3.second][pos3.first];
	char c4 = lines[pos4.second][pos4.first];
	char c5 = lines[pos5.second][pos5.first];

	return c1 == 'M' && c2 == 'M' && c3 == 'A' && c4 == 'S' && c5 == 'S';
}

void part1(std::vector<std::string> lines) {
	int sum = 0;

	for (int y = 0; y < lines.size(); y++) {
		std::string& line = lines[y];
		
		for (int x = 0; x < line.size(); x++) {
			if (xmas_checker(lines, std::make_pair(x, y), std::make_pair(0, 1))) sum++;
			if (xmas_checker(lines, std::make_pair(x, y), std::make_pair(1, 1))) sum++;
			if (xmas_checker(lines, std::make_pair(x, y), std::make_pair(1, 0))) sum++;
			if (xmas_checker(lines, std::make_pair(x, y), std::make_pair(1, -1))) sum++;
			if (xmas_checker(lines, std::make_pair(x, y), std::make_pair(0, -1))) sum++;
			if (xmas_checker(lines, std::make_pair(x, y), std::make_pair(-1, -1))) sum++;
			if (xmas_checker(lines, std::make_pair(x, y), std::make_pair(-1, 0))) sum++;
			if (xmas_checker(lines, std::make_pair(x, y), std::make_pair(-1, 1))) sum++;
		}
	}

	std::cout << sum << std::endl;
}

void part2(std::vector<std::string> lines) {
	int sum = 0;

	for (int y = 0; y < lines.size(); y++) {
		std::string& line = lines[y];
		
		for (int x = 0; x < line.size(); x++) {
			if (xmas_checker_2(lines, std::make_pair(x, y), std::make_pair(1, 1), std::make_pair(1, -1))) sum++;
			if (xmas_checker_2(lines, std::make_pair(x, y), std::make_pair(1, 1), std::make_pair(-1, 1))) sum++;
			if (xmas_checker_2(lines, std::make_pair(x, y), std::make_pair(1, -1), std::make_pair(-1, -1))) sum++;
			if (xmas_checker_2(lines, std::make_pair(x, y), std::make_pair(-1, -1), std::make_pair(-1, 1))) sum++;
		}
	}

	std::cout << sum << std::endl;
}

int main() {
	std::ifstream file("input.txt");
	std::string line;

	std::vector<std::string> lines;
	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	part1(lines);
	part2(lines);
}
