#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <unordered_map>

std::pair<std::vector<std::string>, std::vector<std::string>> parse_input() {
	std::ifstream file("input.txt");

	std::string line;
	std::vector<std::string> rules;
	std::vector<std::string> messages;

	std::getline(file, line);
	std::regex r{ "[a-z]+" };

	std::sregex_iterator it{ line.begin(), line.end(), r, std::regex_constants::match_default };
	std::sregex_iterator end;

	while (it != end) {
		rules.push_back(it->str());
		++it;
	}

	std::getline(file, line);

	while(std::getline(file, line)) {
		messages.push_back(line);
	}

	return { rules, messages };
}

// This solution WILL eat your cpu like it was a fish
// I could implement it like part 2, but I'm too proud of this solution
long long part1(std::vector<std::string> rules, std::vector<std::string> messages) {
	std::string reg_str = "^(";
	bool first = true;
	for (auto& rule : rules) {
		reg_str += std::string{"("} + rule + ")*";
	}

	reg_str += ")+$";
	std::cout << reg_str << std::endl;

	std::regex r{ reg_str, std::regex::optimize };

	long long ret = 0;
	for (auto message : messages) {
		std::cerr << message << ": ";
		std::condition_variable cv;
		std::mutex m;
		std::unique_lock<std::mutex> l{ m };
		bool done = false;
		std::jthread t{ [message, r, &ret, &done, &cv, &m]() {
			if (std::regex_match(message, r)) {
				std::unique_lock<std::mutex> l{ m };
				ret++;
				done = true;
				cv.notify_one();
				std::cerr << "true" << std::endl;
			}
			else {
				std::unique_lock<std::mutex> l{ m };
				std::cerr << "false" << std::endl;
			}
		} };

		auto start_time = std::chrono::steady_clock::now();

		while (!done) {
			cv.wait_for(l, std::chrono::milliseconds(200));

			if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() > 100) {
				break;
			}
		}

		if (!done) {
			t.detach();
			std::cerr << "timeout" << std::endl;
			l.unlock();
			continue;
		}
		l.unlock();

		t.join();
	}

	return ret;
}

std::unordered_map<std::string, long long> cache;

long long part2recur(const std::vector<std::string>& rules, std::string_view message) {
	if (message.length() == 0) {
		return 1;
	}

	if (cache.contains(std::string{message})) {
		return cache.at(std::string{message});
	}

	long long sum = 0;
	for (const auto& rule : rules) {
		if (message.starts_with(rule)) {
			sum += part2recur(rules, message.substr(rule.length()));
		}
	}

	cache.emplace(message, sum);

	return sum;
}

long long part2(const std::vector<std::string>& rules, const std::vector<std::string>& messages) {
	long long sum = 0;
	for (const auto& message : messages) {
		sum += part2recur(rules, message);
	}

	return sum;
}

int main() {
	auto [rules, messages] = parse_input();

	std::cout << part1(rules, messages) << std::endl;
	long long p2 = part2(rules, messages);
	std::cout << p2 << std::endl;
}
