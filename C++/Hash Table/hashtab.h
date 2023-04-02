#include "linkedlist.h"
#include <sstream>

template <typename T>
struct Entry {
    std::string key;
    T data;
    Entry(const std::string key, const T& data) {
        this->key = key;
        this->data = data;
    }
    bool operator==(const Entry& a) const {
        if (this->key == a.key) return true;
        else return false;
    }
};

template <typename T> std::ostream& operator<< (std::ostream& output, const Entry<T>& a) {
    output << " " << a.key << " -> " << a.data;
    return output;
}

template <typename T>
class Hash_table {
    lista<Entry<T>>* h_tab;
public:
    Hash_table() {
        capacity = 1;
        h_tab = new lista<Entry<T>>[capacity];
        size = 0;
        maxpairs_count = 0;
        notnull = 0;
        average = 0;
    }
    ~Hash_table() {
        delete[] h_tab;
    }
    void put(const std::string key, const T& data) {
        Entry<T>* tmp = get(key);
        Entry<T> entry(key, data);
        if (tmp != nullptr) {
            tmp->data = data;
        }
        else {

            if (static_cast<double>(size)/static_cast<double>(capacity) >= 0.75) {
                rehash();
            }
            unsigned int ind = hash_f(key);
            h_tab[ind].push_bot(entry);
            size++;
        }
    }
    Entry<T>* get(const std::string key) {
        unsigned int ind = hash_f(key);
        auto tmp = h_tab[ind].search_dl({ key, {} });
        if (tmp != nullptr) return &tmp->data;
        else return nullptr;
    }
    bool remove(const std::string key) {
        unsigned int ind = hash_f(key);
        auto tmp = h_tab[ind].search_del({ key, {} });
        --size;
        return tmp;
    }
    void clear() {
        auto tmp = new lista<Entry<T>>[capacity];
        delete[] h_tab;
        h_tab = nullptr;
        h_tab = tmp;
        size = 0;
    }
    std::string stats() {
        unsigned int cnt = 0;
        float avg = 0;
        for (int i = 0; i < capacity; ++i) {
            unsigned int dlugosc = h_tab[i].getLength();
            if (maxpairs_count < dlugosc) {
                maxpairs_count = dlugosc;
            }
            if (h_tab[i].getLength() != 0) {
                ++cnt;
                avg += h_tab[i].getLength();
            }
        }
        notnull = cnt;
        average = avg / cnt;
        std::ostringstream str;
        str << "stats:\n";
        str << " list max size: " << maxpairs_count;
        str << "\n non-null lists: " << notnull;
        str << "\n average list size: " << average;
        return str.str();
    }
    std::string disp() {
        std::ostringstream str;
        str << "\n\nhash table:\n";
        str << " current_size: " << size << "\n";
        str << " max_size: " << capacity << "\n";
        str << " table:\n";
        str << "{\n";
        for (int i = 0; i < 15; i++) {
            if (h_tab[i].getLength() != 0) {
                str << "   " << i << ": ";
                str << h_tab[i].disp() << "\n";
            }
        }
        str << "   ...\n";
        str << "}\n";
        str << stats();
        return str.str();
    }
    unsigned int get_notnull() {
        return notnull;
    }
    unsigned int get_max() {
        return maxpairs_count;
    }
    unsigned int getSize() {
        return size;
    }
    unsigned int getCapacity() {
        return capacity;
    }
private:
    unsigned int size;
    unsigned int capacity;
    unsigned int maxpairs_count;
    unsigned int notnull;
    float average;
    uint64_t hash_f(const std::string key) {
        unsigned char ch = key[0];
        unsigned int s = ch;
        for (int i = 1; i < key.length(); i++) {
            s = s * 31 + key[i];
        }
        unsigned int hash = s % capacity;
        return hash;
    }
    void rehash() {
        auto tmp = new lista<Entry<T>>[capacity * 2];
        capacity = capacity * 2;
        for (int i = 0; i < capacity / 2; i++) {
            while (h_tab[i].getHead() != nullptr) {
                auto obj = h_tab[i].getHead();
                std::string klucz = obj->data.key;
                unsigned int ind = hash_f(klucz);
                tmp[ind].push_bot(obj->data);
                h_tab[i].clear_top();
            }
        }
        delete[] h_tab;
        h_tab = nullptr;
        h_tab = tmp;
    }
};
