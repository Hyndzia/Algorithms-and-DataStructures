#include "dyArray.h"

#include<chrono>
#include<iostream>
#include <random>

struct Scientist
{
	uint64_t nr_id;
	std::string name;
	char char_id;
};

uint64_t int_gen(uint64_t first, uint64_t last) {
	std::random_device seed;
	std::mt19937_64 gen(seed());
	std::uniform_int_distribution<size_t> d(first, last);
	return d(gen);
}

std::string string_gen() {
	static std::string arr[] = { "Gauss", "Maxwell", "Bohr", "Einstein", "Newton", "Leibniz", "Ohm", "Faraday", "Pascal" };
	return arr[int_gen(0, 8)];

}

char char_gen() {
	static char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm', 'n', 'o', 'p', 'q','r', 's', 't', 'w', 'u','v', 'x', 'y', 'z' };
	return arr[int_gen(0, 25)];
}



bool operator>(Scientist a, Scientist b)
{
	if (a.nr_id > b.nr_id) return true;
	else return false;
}

std::ostream& operator<<(std::ostream& st, Scientist so) {
	st << "\n"<< "NUMBER ID: " << so.nr_id << "\n";
	st << "NAME: " << so.name << "\n\n";
	return st;
}

Scientist init_so() {
	Scientist so;
	so.nr_id = int_gen(0, 99999);
	so.name = string_gen();
	so.char_id = char_gen();
	return so;
}


int main() {
	dyArray<Scientist>* sot = new dyArray<Scientist>();
	const int MAX_ORDER = 7;
	std::cout << "-----------------------------\n";
	std::cout << "Adding into the array \n";
	std::cout << "-----------------------------\n";
	{
		const int n = static_cast<const int>(pow(10, MAX_ORDER));
		long long eps = static_cast<long long>(0.0001);
		auto t1 = std::chrono::steady_clock::now();
		long long max_time_per_element = static_cast<long long>(0.0000);
		for (int j = 0; j < n; j++) {
			auto t1 = std::chrono::steady_clock::now();
			Scientist so = init_so();
			sot->push_back(so);
			auto t2 = std::chrono::steady_clock::now();
			long long time_per_element = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
			if (time_per_element - max_time_per_element > eps) {
				max_time_per_element = time_per_element;
				int ind = j;
				std::cout << "At index: " << ind << " New worst time: " << max_time_per_element/1000.0 << "s\n";
			}
		}

		auto t2 = std::chrono::steady_clock::now();
		std::cout << "Time overall: " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << "s\n";

	}
	sot->clear_all();
	std::cout << sot->disp();


	return 0;
}