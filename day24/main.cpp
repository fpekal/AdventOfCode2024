#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <cstring>
#include <cmath>

enum GATE {
	AND, OR, XOR
};

GATE text_to_gate_type(std::string s) {
	if (s == "AND") {
		return AND;
	} else if (s == "OR") {
		return OR;
	} else if (s == "XOR") {
		return XOR;
	}

	return OR;
}

std::string gate_type_to_text(GATE g) {
	if (g == AND) {
		return "AND";
	} else if (g == OR) {
		return "OR";
	} else if (g == XOR) {
		return "XOR";
	}

	return "OR";
}

std::pair<std::map<std::string, bool>, std::map<std::string, std::tuple<std::string, std::string, GATE>>> parse_input() {
	std::ifstream fin("input.txt");
	std::regex r {"(.+): (\\d)"};
	std::map<std::string, bool> first;
	while(true) {
		std::string line;
		std::getline(fin, line);
		if (line.empty()) {
			break;
		}

		std::smatch m;
		if (!std::regex_search(line, m, r)) {
			throw std::runtime_error("Invalid input");
		}
		first[m[1]] = m[2].str() == "1";
	}

	std::regex r2 {"(.+) (.+) (.+) -> (.+)"};
	std::map<std::string, std::tuple<std::string, std::string, GATE>> second;
	while(true) {
		std::string line;
		std::getline(fin, line);
		if (line.empty()) {
			break;
		}

		std::smatch m;
		if (!std::regex_search(line, m, r2)) {
			throw std::runtime_error("Invalid input");
		}
		second[m[4]] = std::make_tuple(m[1], m[3], text_to_gate_type(m[2]));
	}

	return std::make_pair(first, second);
}

void evaluate(std::map<std::string, bool>& first, std::map<std::string, std::tuple<std::string, std::string, GATE>>& second, std::string input) {
	std::string left = std::get<0>(second[input]);
	std::string right = std::get<1>(second[input]);
	GATE gate = std::get<2>(second[input]);

	bool left_value = false;
	{
		auto it = first.find(left);
		if (it != first.end()) {
			left_value = it->second;
		} else {
			evaluate(first, second, left);
			it = first.find(left);
			left_value = it->second;
		}
	}

	bool right_value = false;
	{
		auto it = first.find(right);
		if (it != first.end()) {
			right_value = it->second;
		} else {
			evaluate(first, second, right);
			it = first.find(right);
			right_value = it->second;
		}
	}

	if (gate == AND) {
		first[input] = left_value && right_value;
	} else if (gate == OR) {
		first[input] = left_value || right_value;
	} else if (gate == XOR) {
		first[input] = left_value ^ right_value;
	}
}

long long part1(std::map<std::string, bool> first, std::map<std::string, std::tuple<std::string, std::string, GATE>>& second) {
	std::vector<bool> ret;

	for (int i = 0;; i++) {
		char buf[4];
		snprintf(buf, 4, "%02d", i);
		std::string output = "z";
		output += buf;

		if (second.find(output) == second.end()) {
			long long ret_value = 0;
			for (auto iter = ret.rbegin(); iter != ret.rend(); iter++) {
				ret_value <<= 1;
				ret_value += *iter;
			}

			return ret_value;
		}

		evaluate(first, second, output);
		ret.push_back(first[output]);
	}
}

std::map<std::string, bool> test1 {
	{"x00", true},
	{"x01", false},
	{"x02", true},
	{"x03", false},
	{"x04", true},
	{"x05", false},
	{"x06", true},
	{"x07", false},
	{"x08", true},
	{"x09", false},
	{"x10", true},
	{"x11", false},
	{"x12", true},
	{"x13", false},
	{"x14", true},
	{"x15", false},
	{"x16", true},
	{"x17", false},
	{"x18", true},
	{"x19", false},
	{"x20", true},
	{"x21", false},
	{"x22", true},
	{"x23", false},
	{"x24", true},
	{"x25", false},
	{"x26", true},
	{"x27", false},
	{"x28", true},
	{"x29", false},
	{"x30", true},
	{"x31", false},
	{"x32", true},
	{"x33", false},
	{"x34", true},
	{"x35", false},
	{"x36", true},
	{"x37", false},
	{"x38", true},
	{"x39", false},
	{"x40", true},
	{"x41", false},
	{"x42", true},
	{"x43", false},
	{"x44", true},
	{"y00", true},
	{"y01", false},
	{"y02", true},
	{"y03", false},
	{"y04", true},
	{"y05", false},
	{"y06", true},
	{"y07", false},
	{"y08", true},
	{"y09", false},
	{"y10", true},
	{"y11", false},
	{"y12", true},
	{"y13", false},
	{"y14", true},
	{"y15", false},
	{"y16", true},
	{"y17", false},
	{"y18", true},
	{"y19", false},
	{"y20", true},
	{"y21", false},
	{"y22", true},
	{"y23", false},
	{"y24", true},
	{"y25", false},
	{"y26", true},
	{"y27", false},
	{"y28", true},
	{"y29", false},
	{"y30", true},
	{"y31", false},
	{"y32", true},
	{"y33", false},
	{"y34", true},
	{"y35", false},
	{"y36", true},
	{"y37", false},
	{"y38", true},
	{"y39", false},
	{"y40", true},
	{"y41", false},
	{"y42", true},
	{"y43", false},
	{"y44", true}
};

std::map<std::string, bool> test2 {
	{"x00", false},
	{"x01", true},
	{"x02", false},
	{"x03", true},
	{"x04", false},
	{"x05", true},
	{"x06", false},
	{"x07", true},
	{"x08", false},
	{"x09", true},
	{"x10", false},
	{"x11", true},
	{"x12", false},
	{"x13", true},
	{"x14", false},
	{"x15", true},
	{"x16", false},
	{"x17", true},
	{"x18", false},
	{"x19", true},
	{"x20", false},
	{"x21", true},
	{"x22", false},
	{"x23", true},
	{"x24", false},
	{"x25", true},
	{"x26", false},
	{"x27", true},
	{"x28", false},
	{"x29", true},
	{"x30", false},
	{"x31", true},
	{"x32", false},
	{"x33", true},
	{"x34", false},
	{"x35", true},
	{"x36", false},
	{"x37", true},
	{"x38", false},
	{"x39", true},
	{"x40", false},
	{"x41", true},
	{"x42", false},
	{"x43", true},
	{"x44", false},
	{"y00", false},
	{"y01", true},
	{"y02", false},
	{"y03", true},
	{"y04", false},
	{"y05", true},
	{"y06", false},
	{"y07", true},
	{"y08", false},
	{"y09", true},
	{"y10", false},
	{"y11", true},
	{"y12", false},
	{"y13", true},
	{"y14", false},
	{"y15", true},
	{"y16", false},
	{"y17", true},
	{"y18", false},
	{"y19", true},
	{"y20", false},
	{"y21", true},
	{"y22", false},
	{"y23", true},
	{"y24", false},
	{"y25", true},
	{"y26", false},
	{"y27", true},
	{"y28", false},
	{"y29", true},
	{"y30", false},
	{"y31", true},
	{"y32", false},
	{"y33", true},
	{"y34", false},
	{"y35", true},
	{"y36", false},
	{"y37", true},
	{"y38", false},
	{"y39", true},
	{"y40", false},
	{"y41", true},
	{"y42", false},
	{"y43", true},
	{"y44", false}
};

std::map<std::string, bool> test3 {
	{"x00", true},
	{"x01", true},
	{"x02", true},
	{"x03", true},
	{"x04", true},
	{"x05", true},
	{"x06", true},
	{"x07", true},
	{"x08", true},
	{"x09", true},
	{"x10", true},
	{"x11", true},
	{"x12", true},
	{"x13", true},
	{"x14", true},
	{"x15", true},
	{"x16", true},
	{"x17", true},
	{"x18", true},
	{"x19", true},
	{"x20", true},
	{"x21", true},
	{"x22", true},
	{"x23", true},
	{"x24", true},
	{"x25", true},
	{"x26", true},
	{"x27", true},
	{"x28", true},
	{"x29", true},
	{"x30", true},
	{"x31", true},
	{"x32", true},
	{"x33", true},
	{"x34", true},
	{"x35", true},
	{"x36", true},
	{"x37", true},
	{"x38", true},
	{"x39", true},
	{"x40", true},
	{"x41", true},
	{"x42", true},
	{"x43", true},
	{"x44", true},
	{"y00", true},
	{"y01", true},
	{"y02", true},
	{"y03", true},
	{"y04", true},
	{"y05", true},
	{"y06", true},
	{"y07", true},
	{"y08", true},
	{"y09", true},
	{"y10", true},
	{"y11", true},
	{"y12", true},
	{"y13", true},
	{"y14", true},
	{"y15", true},
	{"y16", true},
	{"y17", true},
	{"y18", true},
	{"y19", true},
	{"y20", true},
	{"y21", true},
	{"y22", true},
	{"y23", true},
	{"y24", true},
	{"y25", true},
	{"y26", true},
	{"y27", true},
	{"y28", true},
	{"y29", true},
	{"y30", true},
	{"y31", true},
	{"y32", true},
	{"y33", true},
	{"y34", true},
	{"y35", true},
	{"y36", true},
	{"y37", true},
	{"y38", true},
	{"y39", true},
	{"y40", true},
	{"y41", true},
	{"y42", true},
	{"y43", true},
	{"y44", true}
};

std::map<std::string, bool> test4 {
	{"x00", true},
	{"x01", true},
	{"x02", true},
	{"x03", true},
	{"x04", true},
	{"x05", true},
	{"x06", true},
	{"x07", true},
	{"x08", true},
	{"x09", true},
	{"x10", true},
	{"x11", true},
	{"x12", true},
	{"x13", true},
	{"x14", true},
	{"x15", true},
	{"x16", true},
	{"x17", true},
	{"x18", true},
	{"x19", true},
	{"x20", true},
	{"x21", true},
	{"x22", true},
	{"x23", true},
	{"x24", false},
	{"x25", false},
	{"x26", false},
	{"x27", false},
	{"x28", false},
	{"x29", false},
	{"x30", false},
	{"x31", false},
	{"x32", false},
	{"x33", false},
	{"x34", false},
	{"x35", false},
	{"x36", false},
	{"x37", false},
	{"x38", false},
	{"x39", false},
	{"x40", false},
	{"x41", false},
	{"x42", false},
	{"x43", false},
	{"x44", false},
	{"y00", false},
	{"y01", false},
	{"y02", false},
	{"y03", false},
	{"y04", false},
	{"y05", false},
	{"y06", false},
	{"y07", false},
	{"y08", false},
	{"y09", false},
	{"y10", false},
	{"y11", false},
	{"y12", false},
	{"y13", false},
	{"y14", false},
	{"y15", false},
	{"y16", false},
	{"y17", false},
	{"y18", false},
	{"y19", false},
	{"y20", false},
	{"y21", false},
	{"y22", false},
	{"y23", false},
	{"y24", false},
	{"y25", false},
	{"y26", false},
	{"y27", false},
	{"y28", false},
	{"y29", false},
	{"y30", false},
	{"y31", false},
	{"y32", false},
	{"y33", false},
	{"y34", false},
	{"y35", false},
	{"y36", false},
	{"y37", false},
	{"y38", false},
	{"y39", false},
	{"y40", false},
	{"y41", false},
	{"y42", false},
	{"y43", false},
	{"y44", false}
};

std::map<std::string, bool> test5 {
	{"x00", false},
	{"x01", false},
	{"x02", false},
	{"x03", false},
	{"x04", false},
	{"x05", false},
	{"x06", false},
	{"x07", false},
	{"x08", false},
	{"x09", false},
	{"x10", false},
	{"x11", false},
	{"x12", false},
	{"x13", false},
	{"x14", false},
	{"x15", false},
	{"x16", false},
	{"x17", false},
	{"x18", false},
	{"x19", false},
	{"x20", false},
	{"x21", false},
	{"x22", false},
	{"x23", false},
	{"x24", true},
	{"x25", true},
	{"x26", true},
	{"x27", true},
	{"x28", true},
	{"x29", true},
	{"x30", true},
	{"x31", true},
	{"x32", true},
	{"x33", true},
	{"x34", true},
	{"x35", true},
	{"x36", true},
	{"x37", true},
	{"x38", true},
	{"x39", true},
	{"x40", true},
	{"x41", true},
	{"x42", true},
	{"x43", true},
	{"x44", true},
	{"y00", false},
	{"y01", false},
	{"y02", false},
	{"y03", false},
	{"y04", false},
	{"y05", false},
	{"y06", false},
	{"y07", false},
	{"y08", false},
	{"y09", false},
	{"y10", false},
	{"y11", false},
	{"y12", false},
	{"y13", false},
	{"y14", false},
	{"y15", false},
	{"y16", false},
	{"y17", false},
	{"y18", false},
	{"y19", false},
	{"y20", false},
	{"y21", false},
	{"y22", false},
	{"y23", false},
	{"y24", false},
	{"y25", false},
	{"y26", false},
	{"y27", false},
	{"y28", false},
	{"y29", false},
	{"y30", false},
	{"y31", false},
	{"y32", false},
	{"y33", false},
	{"y34", false},
	{"y35", false},
	{"y36", false},
	{"y37", false},
	{"y38", false},
	{"y39", false},
	{"y40", false},
	{"y41", false},
	{"y42", false},
	{"y43", false},
	{"y44", false}
};

void evaluate_whole(std::map<std::string, bool>& first, std::map<std::string, std::tuple<std::string, std::string, GATE>>& second) {
	long long num = 0;
	for (int i = 45 ; i >= 0; i--) {
		char buf[4];
		snprintf(buf, 4, "%02d", i);
		std::string output = "z";
		output += buf;
		evaluate(first, second, output);
		num <<= 1;
		num += first[output];
	}

	std::cout << std::bitset<46>(num) << std::endl;
}

void test(std::map<std::string, std::tuple<std::string, std::string, GATE>>& second) {
	{
		auto test_tmp = test1;
		evaluate_whole(test_tmp, second);
	}

	{
		auto test_tmp = test2;
		evaluate_whole(test_tmp, second);
	}

	{
		auto test_tmp = test3;
		evaluate_whole(test_tmp, second);
	}

	{
		auto test_tmp = test4;
		evaluate_whole(test_tmp, second);
	}

	{
		auto test_tmp = test5;
		evaluate_whole(test_tmp, second);
	}
}

void part2(std::map<std::string, std::tuple<std::string, std::string, GATE>> second) {
	while(true) {
		int option = 0;
		std::cin >> option;

		if (option == 1) {
			test(second);
		}
		else if (option == 2) {
			std::string input;
			std::cin >> input;

			auto gate = second[input];
			std::cout << std::get<0>(gate) << " " << std::get<1>(gate) << " " << gate_type_to_text(std::get<2>(gate)) << std::endl;
		}
		else if (option == 3) {
			std::string input1;
			std::cin >> input1;
			std::string input2;
			std::cin >> input2;

			auto gate = second[input1];
			second[input1] = second[input2];
			second[input2] = gate;
		}
	}
}

std::map<std::string, bool> blank_test {
	{"x00", false},
	{"x01", false},
	{"x02", false},
	{"x03", false},
	{"x04", false},
	{"x05", false},
	{"x06", false},
	{"x07", false},
	{"x08", false},
	{"x09", false},
	{"x10", false},
	{"x11", false},
	{"x12", false},
	{"x13", false},
	{"x14", false},
	{"x15", false},
	{"x16", false},
	{"x17", false},
	{"x18", false},
	{"x19", false},
	{"x20", false},
	{"x21", false},
	{"x22", false},
	{"x23", false},
	{"x24", false},
	{"x25", false},
	{"x26", false},
	{"x27", false},
	{"x28", false},
	{"x29", false},
	{"x30", false},
	{"x31", false},
	{"x32", false},
	{"x33", false},
	{"x34", false},
	{"x35", false},
	{"x36", false},
	{"x37", false},
	{"x38", false},
	{"x39", false},
	{"x40", false},
	{"x41", false},
	{"x42", false},
	{"x43", false},
	{"x44", false},
	{"y00", false},
	{"y01", false},
	{"y02", false},
	{"y03", false},
	{"y04", false},
	{"y05", false},
	{"y06", false},
	{"y07", false},
	{"y08", false},
	{"y09", false},
	{"y10", false},
	{"y11", false},
	{"y12", false},
	{"y13", false},
	{"y14", false},
	{"y15", false},
	{"y16", false},
	{"y17", false},
	{"y18", false},
	{"y19", false},
	{"y20", false},
	{"y21", false},
	{"y22", false},
	{"y23", false},
	{"y24", false},
	{"y25", false},
	{"y26", false},
	{"y27", false},
	{"y28", false},
	{"y29", false},
	{"y30", false},
	{"y31", false},
	{"y32", false},
	{"y33", false},
	{"y34", false},
	{"y35", false},
	{"y36", false},
	{"y37", false},
	{"y38", false},
	{"y39", false},
	{"y40", false},
	{"y41", false},
	{"y42", false},
	{"y43", false},
	{"y44", false}
};

void tester2000(std::map<std::string, std::tuple<std::string, std::string, GATE>> second) {
	{
		auto gate = second["vjv"];
		second["vjv"] = second["cqm"];
		second["cqm"] = gate;
	}
	{
		auto gate = second["vcv"];
		second["vcv"] = second["z13"];
		second["z13"] = gate;
	}
	{
		auto gate = second["z19"];
		second["z19"] = second["vwp"];
		second["vwp"] = gate;
	}
	{
		auto gate = second["mps"];
		second["mps"] = second["z25"];
		second["z25"] = gate;
	}

	while(true) {
		long long x = (((long long)rand() << 32) ^ (long long)rand()) % (long long)std::pow(2, 45);
		long long y = (((long long)rand() << 32) ^ (long long)rand()) % (long long)std::pow(2, 45);

		std::map<std::string, bool> first = blank_test;
		int i = 0;
		for (long long xx = x; xx > 0; xx /= 2) {
			char buf[5];
			snprintf(buf, 5, "x%02d", i);
			first[buf] = xx % 2;
			++i;
		}
		i = 0;
		for (long long yy = y; yy > 0; yy /= 2) {
			char buf[5];
			snprintf(buf, 5, "y%02d", i);
			first[buf] = yy % 2;
			++i;
		}

		evaluate_whole(first, second);

		long long result = 0;
		for (int i = 46; i >= 0; i--) {
			char buf[5];
			snprintf(buf, 5, "z%02d", i);
			result <<= 1;
			result += first[buf];
		}

		if (result != x + y) {
			std::cout << x << " " << y << " " << result << std::endl;
		}
	}
}

int main() {
	auto [first, second] = parse_input();

	std::cout << part1(first, second) << '\n';

	//tester2000(second);
	part2(second);
}
