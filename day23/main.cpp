#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <map>
#include <vector>

std::map<std::string, std::set<std::string>> parse_input() {
	std::ifstream fin("input.txt");
	std::map<std::string, std::set<std::string>> result;
	std::regex r {"(..)-(..)"};
	std::string line;
	while (std::getline(fin, line)) {
		std::smatch m;
		std::regex_search(line, m, r);
		result[m[1]].insert(m[2]);
		result[m[2]].insert(m[1]);
	}
	return result;
}

long long part1(std::map<std::string, std::set<std::string>>& input) {
	std::set<std::set<std::string>> found;

	for (auto& [k, v] : input) {
		for (auto& i : v) {
			for (auto& ii : v) {
				if (i == ii) continue;
				if (input[i].find(ii) == input[i].end()) continue;

				found.insert({k, i, ii});
			}
		}
	}

	long long result = 0;
	for (auto& f : found) {
		bool cont = false;
		for (auto& i : f) {
			if (i[0] == 't') {
				cont = true;
				break;
			}
		}

		if (cont) {
			result += 1;
		}
	}

	return result;
}

std::string part2(std::map<std::string, std::set<std::string>>& input) {
	for (int i = input.size(); i >= 1; --i) {
		for (auto& [k, v] : input) {
			if (v.size()+1 < i) continue;

			std::string bitmask(i, 1); // K leading 1's
			bitmask.resize(v.size(), 0); // N-K trailing 0's
			
			do {
				std::vector<std::string> permutation;

				for (int i = 0; i < v.size(); ++i) // [0..N-1] integers
				{
					if (bitmask[i]) {
						auto iter = v.begin();
						std::advance(iter, i);
						permutation.push_back(*iter);
					}
				}

				bool all_connected = true;
				for (int ii = 0; ii < permutation.size()-1; ++ii) {
					for (int iii = ii+1; iii < permutation.size(); ++iii) {
						if (input[permutation[ii]].find(permutation[iii]) == input[permutation[ii]].end()) {
							all_connected = false;
							break;
						}
					}
				}

				if (all_connected) {
					std::set<std::string> ret {permutation.begin(), permutation.end()};
					ret.insert(k);

					std::string ret_str = "";
					for (auto& i : ret) {
						ret_str += i;
						ret_str += ",";
					}
					return ret_str;
				}
			} while (std::prev_permutation(bitmask.begin(), bitmask.end()));
		}
	}

	return "";
}

int main() {
	auto input = parse_input();

	std::cout << part1(input) << std::endl;
	std::cout << part2(input) << std::endl;
}
