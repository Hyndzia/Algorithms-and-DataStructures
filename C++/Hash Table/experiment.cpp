
#include "hashtab.h"

#include <iostream>
#include <sstream>
#include <random>
#include <chrono>

uint64_t int_gen(uint64_t first, uint64_t last) {
    std::random_device seed;
    std::mt19937_64 gen(seed());
    std::uniform_int_distribution<uint64_t> d(first, last);
    return d(gen);
}

std::string string_gen(const unsigned int length)
{
    std::string str;
    char tab[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y', 'z' };
    for (int i = 0; i < length; i++)
        str = str + tab[int_gen(0, 25)];
    return str;
}

int main() {
    const int MAX_ORDER = 7;
    auto hash = new Hash_table<int>;
    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);
        auto t1 = std::chrono::steady_clock::now();
        for (int i = 0; i < n; i++)
            hash->put(string_gen(6), i);
        auto t2 = std::chrono::steady_clock::now();
        long long time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << hash->disp();
        std::cout << "\n\nInsertion time: " << time/1000.0;

        const int m = pow(10, 4);
        int hits = 0;
        t1 = std::chrono::steady_clock::now();
        for (int i = 0; i < m; i++)
        {
            Entry<int>* entry = hash->get(string_gen(6));
            if (entry != nullptr)
                hits++;
        }
        t2 = std::chrono::steady_clock::now();
         time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "\n\nHits count: " << hits;
        std::cout << "\nSearch time: " << time / 1000.0;
        hash->clear();
    }
    delete hash;
    return 0;
}