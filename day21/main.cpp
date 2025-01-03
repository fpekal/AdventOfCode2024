#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

// +---+---+---+
// | 7 | 8 | 9 |
// +---+---+---+
// | 4 | 5 | 6 |
// +---+---+---+
// | 1 | 2 | 3 |
// +---+---+---+
//     | 0 | A |
//     +---+---+

// +---+---+----+
// | 0 | 1 | 2  |
// +---+---+----+
// | 3 | 4 | 5  |
// +---+---+----+
// | 6 | 7 | 8  |
// +---+---+----+
//     | 9 | 10 |
//     +---+----+

std::string best_paths_doors[11][11] = {
	{"A",">A",">>A","vA","v>A","v>>A","vvA","vv>A","vv>>A","vvv>A","vvv>>A"},
	{"<A","A",">A","<vA","vA","v>A","<vvA","vvA","vv>A","vvvA","vvv>A"},
	{"<<A","<A","A","<<vA","<vA","vA","<<vvA","<vvA","vvA","<vvvA","vvvA"},
	{"^A","^>A","^>>A","A",">A",">>A","vA","v>A","v>>A",">vvA",">>vvA"},
	{"<^A","^A","^>A","<A","A",">A","<vA","vA","v>A","vvA","vv>A"},
	{"<<^A","<^A","^A","<<A","<A","A","<<vA","<vA","vA","<vvA","vvA"},
	{"^^A","^^>A","^^>>A","^A","^>A","^>>A","A",">A",">>A",">vA",">>vA"},
	{"<^^A","^^A","^^>A","<^A","^A","^>A","<A","A",">A","vA","v>A"},
	{"<<^^A","<^^A","^^A","<<^A","<^A","^A","<<A","<A","A","<vA","vA"},
	{"^^^<A","^^^A","^^^>A","^^<A","^^A","^^>A","^<A","^A","^>A","A",">A"},
	{"^^^<<A","<^^^A","^^^A","^^<<A","<^^A","^^A","^<<A","<^A","^A","<A","A"}
};

//     +---+---+
//     | ^ | A |
// +---+---+---+
// | < | v | > |
// +---+---+---+

//     +---+---+
//     | 0 | 1 |
// +---+---+---+
// | 2 | 3 | 4 |
// +---+---+---+

std::string best_paths_keypads[5][5] = {
	{"A",">A","v<A","vA","v>A"},
	{"<A","A","v<<A","<vA","vA"},
	{">^A",">>^A","A",">A",">>A"},
	{"^A","^>A","<A","A",">A"},
	{"<^A","^A","<<A","<A","A"}
};

std::vector<int> parse_line(std::string line) {
	std::vector<int> result;
	for (char c : line) {
		switch(c) {
		case 'A':
			result.push_back(1);
			break;
		case '^':
			result.push_back(0);
			break;
		case '<':
			result.push_back(2);
			break;
		case '>':
			result.push_back(4);
			break;
		case 'v':
			result.push_back(3);
			break;
		default:
			break;
		}
	}
	return result;
}

std::vector<int> parse_line2(std::string line) {
		std::vector<int> row;
		for (char c : line) {
			switch(c) {
			case '0':
				row.push_back(9);
				break;
			case '1':
				row.push_back(6);
				break;
			case '2':
				row.push_back(7);
				break;
			case '3':
				row.push_back(8);
				break;
			case '4':
				row.push_back(3);
				break;
			case '5':
				row.push_back(4);
				break;
			case '6':
				row.push_back(5);
				break;
			case '7':
				row.push_back(0);
				break;
			case '8':
				row.push_back(1);
				break;
			case '9':
				row.push_back(2);
				break;
			case 'A':
				row.push_back(10);
				break;
			default:
				break;
			}
		}
		return row;
}

std::vector<std::string> parse_input() {
	std::ifstream file("input.txt");
	std::vector<std::string> result;
	std::string line;
	while (std::getline(file, line)) {
		result.push_back(line);
	}
	return result;
}

long long part1(std::vector<std::string> input) {
	long long sum = 0;

	for (auto& row : input) {
		auto row2 = parse_line2(row);
		std::string a = best_paths_doors[10][row2[0]];
		a += best_paths_doors[row2[0]][row2[1]];
		a += best_paths_doors[row2[1]][row2[2]];
		a += best_paths_doors[row2[2]][row2[3]];

		auto b = parse_line(a);

		for (int i = 0; i < 2; i++) {
			a = best_paths_keypads[1][b[0]];

			for (int ii = 0; ii < b.size() - 1; ii++) {
				a += best_paths_keypads[b[ii]][b[ii + 1]];
			}

			b = parse_line(a);
		}

		sum += b.size() * std::stoi(row);
	}

	return sum;
}

std::map<std::tuple<std::string, int>, long long> memo;

long long part2_recur(std::string str, int depth) {
	if (depth == 0) return str.size();

	if (memo.find({str, depth}) != memo.end()) return memo[{str, depth}];

	long long sum = 0;

	for (auto iter = str.begin(); iter != str.end();) {
		if (*iter == 'A') {
			iter++;
			sum++;
			continue;
		}
		auto Aloc = std::find(iter, str.end(), 'A');

		auto parsed = parse_line(std::string(iter, Aloc + 1));

		std::string a = best_paths_keypads[1][parsed[0]];
		for (int i = 0; i < parsed.size() - 1; i++) {
			a += best_paths_keypads[parsed[i]][parsed[i + 1]];
		}

		sum += part2_recur(a, depth - 1);

		iter = Aloc + 1;
	}

	memo[{str, depth}] = sum;
	return sum;
}

long long part2(std::vector<std::string> input) {
	long long sum = 0;

	for (auto& row : input) {
		auto row2 = parse_line2(row);
		std::string a = best_paths_doors[10][row2[0]];
		a += best_paths_doors[row2[0]][row2[1]];
		a += best_paths_doors[row2[1]][row2[2]];
		a += best_paths_doors[row2[2]][row2[3]];

		sum += part2_recur(a, 100000) * std::stol(row);
	}

	return sum;
}


int main() {
	auto input = parse_input();

	//std::cout << part1(input) << std::endl;
	std::cout << part2(input) << std::endl;

	return 0;
}
