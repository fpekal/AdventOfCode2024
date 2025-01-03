#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> parse_input() {
	std::ifstream file("input.txt");
	std::vector<int> result;

	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			result.push_back(std::stoi(line));
		}
	}

	return result;
}


static long long sequence(long long secret) {
	secret = (secret ^ secret * 64) % 16777216;
	secret = (secret ^ secret / 32) % 16777216;
	secret = (secret ^ secret * 2048) % 16777216;

	return secret;
}

static long long part1(std::vector<int> input) {
	long long sum = 0;

	for (auto i : input) {
		for (int ii = 0; ii < 2000; ++ii) {
			i = sequence(i);
		}

		sum += i;
	}

	return sum;
}

static long long sell_spot(int secret, std::vector<int> trigger) {
	int prev_num = secret % 10;

	std::vector<int> saved_changes;

	for (int i = 0; i < 2000; ++i) {
		secret = sequence(secret);
		int num = secret % 10;

		saved_changes.push_back(num - prev_num);
		if (std::equal(saved_changes.end() - trigger.size(), saved_changes.end(), trigger.begin(), trigger.end())) {
			return num;
		}
		prev_num = num;
	}

	return 0;
}

long long part2(std::vector<int> input) {
	long long best = 0;
	std::vector<int> best_trigger;

	for (int i = -9; i <= 9; ++i) {
		std::vector v_i = { i };
		for (int ii = -9; ii <= 9; ++ii) {
			std::vector<int> v_ii = v_i;
			v_ii.push_back(ii);
			for (int iii = -9; iii <= 9; ++iii) {
				std::vector<int> v_iii = v_ii;
				v_iii.push_back(iii);
				for (int iv = -9; iv <= 9; ++iv) {
					std::vector<int> v_iv = v_iii;
					v_iv.push_back(iv);

					long long sum = 0;
					int num = 0;
					for (auto i : input) {
						if (9*(4-num)+sum < best) break; 
						sum += sell_spot(i, v_iv);
						++num;
					}
					if (sum > best) {
						best_trigger = v_iv;
						best = sum;
					}
				}
			}
		}
	}

	return best;
}

int main() {
	auto input = parse_input();

	std::cout << part1(input) << std::endl;
	std::cout << part2(input) << std::endl;
}
