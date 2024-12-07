#include <iostream>
#include <fstream>
#include <regex>
#include <bitset>
#include <cmath>

std::vector<long long> parseNumbers(const std::string& line) {
	std::vector<long long> ret;

	long long begin = 0;

	while(true) {
		long long end = line.find(" ", begin);
		
		long long number = std::stol(line.substr(begin, end - begin));
		ret.push_back(number);
		if (end == std::string::npos) {
			break;
		}
		begin = end + 1;
	}

	return ret;
}

std::string toStr(long long n, long long base) {
		std::string convertString = "0123456789ABCDEF";
    if (n < base) {
        return std::string(1, convertString[n]); // converts char to string, and returns it
    } else {
        return toStr(n/base, base) + convertString[n%base]; // function makes a recursive call to itself.
    }
}

std::string leading_zeros(const std::string& s, long long length) {
	long long diff = length - s.length();

	std::string ret = "";
	for (long long i = 0; i < diff; i++) {
		ret += '0';
	}

	ret += s;
	return ret;
}

int main() {
	std::ifstream file("input.txt");
	std::string line;

	long long part1 = 0;
	long long part2 = 0;

	while (std::getline(file, line)) {
		std::regex r { "(\\d+): (.+)" };

		std::smatch m;
		if (std::regex_match(line, m, r)) {
			long long result = std::stol(m.str(1));

			std::vector<long long> numbers = parseNumbers(m.str(2));

			for (long long i = 0; i < std::pow(2, numbers.size()-1); i++) {
				std::bitset<16> bs(i);

				long long sum = numbers[0];
				for (long long j = 1; j < numbers.size(); j++) {
					if (bs[j-1]) {
						sum += numbers[j];
					}
					else {
						sum *= numbers[j];
					}
				}

				if (sum == result) {
					part1 += result;
					break;
				}
			}


			for (long long i = 0; i < std::pow(3, numbers.size()-1); i++) {
				std::string based = leading_zeros(toStr(i, 3), numbers.size() - 1);

				long long sum = numbers[0];
				for (long long j = 1; j < numbers.size(); j++) {
					if (based[j-1] == '0') {
						sum += numbers[j];
					}
					else if (based[j-1] == '1') {
						sum *= std::pow(10, std::ceil(std::log10(numbers[j]+1)));
						sum += numbers[j];
					}
					else {
						sum *= numbers[j];
					}
				}

				if (sum == result) {
					part2 += result;
					break;
				}
			}
		}
	}

	std::cout << part1 << '\n';
	std::cout << part2;
	return 0;
}
