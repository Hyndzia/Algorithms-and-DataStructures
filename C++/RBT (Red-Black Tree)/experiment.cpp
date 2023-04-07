#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include "RBT.h"


uint64_t int_gen(uint64_t first, uint64_t last) {
    std::random_device seed;
    std::mt19937_64 gen(seed());
    std::uniform_int_distribution<uint64_t> d(first, last);
    return d(gen);
}

std::string string_gen() {
    static std::string arr[] = { "Gauss", "Maxwell", "Bohr", "Einstein", "Newton", "Leibniz", "Ohm", "Faraday", "Pascal" };
    return arr[int_gen(0, 8)];

}

struct so {
    uint64_t key;
    std::string name;
};

std::ostream& operator<<(std::ostream& st, so some) {
    st << "" << some.key;
    st << ",  " << some.name << "))\n";
    return st;
}
bool operator >(so a, so b) {
    if (a.key > b.key) return true;
    else return false;
}
bool operator ==(so a, so b) {
    if (a.key == b.key) return true;
    else return false;
}

so init_so() {
    return { int_gen(1, 9999), string_gen() };
}

int main() {
    const int MAX_ORDER = 7;
    RBT<so>* tree = new RBT<so>;

    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);

        auto t1 = std::chrono::steady_clock::now();
        for (int i = 0; i < n; i++)
        {
            auto so = init_so();
            tree->insert(rand() % 1000, so);
        }
        auto t2 = std::chrono::steady_clock::now();

        std::cout << tree->display();
        long long timer = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "\nInsertion time: " << timer / 1000.0 << "s\n\n";


        const int m = pow(10, 4);
        int hits = 0;
        t1 = std::chrono::steady_clock::now();
        for (int i = 0; i < m; i++)
        {
            auto some = init_so();
            auto result = tree->search(some);
            if (result != nullptr) hits++;

        }
        t2 = std::chrono::steady_clock::now();
        timer = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "\n\nhits: " << hits << "\n";
        std::cout << "Search time: " << timer / 1000.0 << "s\n\n";

        std::cout << tree->display();
        std::cout << "\nRed-black Size: " << tree->getSize();
        std::cout << "\nRed-black Height: " << tree->getHeight();
        std::cout << "\nApprox. maximal height: " << std::log2(tree->getSize() + 1) * 2 << std::endl;

    }
    tree->clearALL();
    delete tree;
    return 0;
}


