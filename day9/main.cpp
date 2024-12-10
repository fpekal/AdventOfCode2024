#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> parse_input() {
	std::ifstream file("input.txt");
	std::string line;
	std::getline(file, line);

	std::vector<int> input;
	bool is_file = true;
	int file_id = 0;
	for (char c : line) {
		int num = c - '0';

		for (int i = 0; i < num; i++) {
			if (is_file) {
				input.push_back(file_id);
			} else {
				input.push_back(-1);
			}
		}
		if (is_file) {
			is_file = false;
		} else {
			is_file = true;
			file_id++;
		}
	}

	return input;
}

long long part1(std::vector<int> input) {
	int next_free_space = 0;
	int next_number_to_move = input.size() - 1;

	while(true) {
		if (next_free_space >= next_number_to_move) break;

		if (input[next_free_space] != -1) {
			next_free_space++;
			continue;
		}

		if (input[next_number_to_move] == -1) {
			next_number_to_move--;
			continue;
		}

		input[next_free_space] = input[next_number_to_move];
		input[next_number_to_move] = -1;
		next_free_space++;
		next_number_to_move--;
	}

	long long sum = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == -1) break;
		sum += (long long)input[i] * i;
	}

	return sum;
}

long long part2(std::vector<int> input) {
	int next_id = input[input.size() - 1];

	while(true) {
		int begin_index = std::find(input.begin(), input.end(), next_id) - input.begin();
		int end_index = std::find(input.rbegin(), input.rend(), next_id).base() - input.begin();

		int size = end_index - begin_index;

		int dest_begin = 0;
		int dest_end = 0;

		while(true) {
			dest_begin = std::find(input.begin()+dest_end, input.end(), -1) - input.begin();
			if (dest_begin >= begin_index) {
				dest_end = -1;
				break;
			}

			dest_end = std::find_if(input.begin() + dest_begin, input.end(), [](int x) { return x != -1; }) - input.begin();
			int dest_size = dest_end - dest_begin;

			if (dest_size >= size) break;
		}
		next_id--;

		if (dest_end != -1) {
			for (int i = 0; i < size; i++) {
				input[dest_begin + i] = input[begin_index + i];
				input[begin_index + i] = -1;
			}
		}

		if (next_id == -1) break;

	}

	long long sum = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == -1) continue;
		sum += (long long)input[i] * i;
	}

	return sum;
}

int main() {
	auto input = parse_input();

	std::cout << part1(input) << '\n';
	std::cout << part2(input) << '\n';

}
