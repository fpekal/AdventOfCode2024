#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <regex>
#include <thread>
#include <mutex>

std::pair<std::array<long long, 3>, std::vector<long long>> parse_input() {
	std::ifstream input("input.txt");

	std::array<long long, 3> registers;
	
	std::regex r {"Register .: (\\d+)"};
	std::string line;
	std::getline(input, line);

	std::smatch match;
	std::regex_match(line, match, r);
	registers[0] = std::stoi(match[1]);

	std::getline(input, line);
	std::regex_match(line, match, r);
	registers[1] = std::stoi(match[1]);

	std::getline(input, line);
	std::regex_match(line, match, r);
	registers[2] = std::stoi(match[1]);

	r = std::regex {"(\\d)"};

	std::vector<long long> instructions;
	std::getline(input, line);
	std::getline(input, line);

	std::sregex_iterator it(line.begin(), line.end(), r);
	std::sregex_iterator end;

	while (it != end) {
		instructions.push_back(std::stoi(it->str()));
		++it;
	}

	return std::make_pair(registers, instructions);
}

long long combo_operand(long long operand, std::array<long long, 3> registers) {
	switch (operand) {
	case 0: [[fallthrough]];
	case 1: [[fallthrough]];
	case 2: [[fallthrough]];
	case 3:
		return operand;
	
	case 4:
		return registers[0];
	case 5:
		return registers[1];
	case 6:
		return registers[2];
	
	default:
		return operand;
	}
}

std::vector<long long> interpret(std::array<long long, 3> registers, std::vector<long long> instructions) {
	std::vector<long long> out;

	for (auto iter = instructions.begin(); iter != instructions.end(); iter += 2) {
		long long opcode = *iter;
		long long operand = *(iter + 1);

		switch (opcode) {
		case 0:
			registers[0] >>= combo_operand(operand, registers);
			break;
		case 1:
			registers[1] ^= operand;
			break;
		case 2:
			registers[1] = combo_operand(operand, registers) & 0b00000111;
			break;
		case 3:
			if (registers[0] == 0) break;
			iter = instructions.begin() + operand - 2;
			break;
		case 4:
			registers[1] ^= registers[2];
			break;
		case 5:
			out.push_back(combo_operand(operand, registers) & 0b00000111);
			break;
		case 6:
			registers[1] = registers[0] >> combo_operand(operand, registers);
			break;
		case 7:
			registers[2] = registers[0] >> combo_operand(operand, registers);
			break;
		}
	}

	return out;
}

std::vector<long long> part1(std::array<long long, 3> registers, std::vector<long long> instructions) {
	return interpret(registers, instructions);
}


long long recursive(const std::vector<long long>& input, long long index, long long prev) {
	if (index == input.size()) {
		return prev;
	}

	long long now = prev << 3;

	for (long long i = 0; i < 8; ++i) {
		long long iteration = now + i;

		long long ii = i ^ 0b010;
		long long iii = (iteration >> ii) & 0b111;
		long long iv = ii ^ 0b111;
		long long v = iv ^ iii;

		if (v == input[index]) {
			long long ret = recursive(input, index + 1, iteration);
			if (ret != -1) {
				return ret;
			}
		}
	}

	return -1;
}


long long part2(std::array<long long, 3> registers, std::vector<long long> instructions) {
	//reverse instructions

	std::vector<long long> reversed = instructions;
	std::reverse(reversed.begin(), reversed.end());

	return recursive(reversed, 0, 0);
}


int main() {
	auto [registers, instructions] = parse_input();

	auto out = part1(registers, instructions);
	for (auto i : out) {
		std::cout << i << ",";
	}
	std::cout << std::endl;

	std::cout << part2(registers, instructions);
}
