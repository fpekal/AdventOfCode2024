#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <regex>

typedef std::pair<int,int> rule;
typedef std::vector<rule> rules;

typedef std::vector<int> update;
typedef std::vector<update> updates;

std::pair<rules, updates> parse_input() {
	std::ifstream input("input.txt");
	std::string line;
	rules rules;
	updates updates;

	std::regex rule_regex("(\\d+)\\|(\\d+)");

	while (std::getline(input, line)) {
		if (line == "")
			break;

		std::smatch match;
		std::regex_match(line, match, rule_regex);
		rules.push_back(std::make_pair(std::stoi(match[1].str()), std::stoi(match[2].str())));
	}

	std::regex update_regex("(\\d+),?");

	while (std::getline(input, line)) {
		std::sregex_iterator it(line.begin(), line.end(), update_regex);
		std::sregex_iterator end;

		std::vector<int> update;
		for (; it != end; ++it) {
			std::smatch m = *it;
			update.push_back(std::stoi(m[1].str()));
		}
		updates.push_back(update);
	}

	return std::make_pair(rules, updates);
}

int main() {
	auto input = parse_input();

	int sum_part1 = 0;
	int sum_part2 = 0;

	for (update& u : input.second) {
		bool update_good = true;
		for (int i = 0; i < u.size()-1; i++) {
			for (int j = i+1; j < u.size(); j++) {
				bool rule_exist = false;
				for (rule& r : input.first) {
					if (u[i] == r.first && u[j] == r.second) {
						rule_exist = true;
						break;
					}
				}
				if (!rule_exist) {
					update_good = false;
					break;
				}
			}
		}

		if (update_good) {
			sum_part1 += u.at(u.size()/2);
		}
		else {
			while(true) {
				bool changed_now = false;
				
				for (int i = 0; i < u.size()-1; i++) {
					for (int j = i+1; j < u.size(); j++) {
						bool rule_exist = false;
						for (rule& r : input.first) {
							if (u[i] == r.first && u[j] == r.second) {
								rule_exist = true;
								break;
							}
						}

						if (!rule_exist) {
							std::swap(u[i], u[j]);
							changed_now = true;
						}
					}
				}

				if (!changed_now) {
					break;
				}
			}
				
			sum_part2 += u.at(u.size()/2);
		}
	}

	std::cout << sum_part1 << std::endl;
	std::cout << sum_part2 << std::endl;
}
