#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include <time.h>
template<typename T>
class dyArray {
public:
	dyArray()
	{
		arr = new T[1];
		size = 0;
		capacity = 1;
	}
	~dyArray() {
		if (arr) {
			delete[]arr;
		}
	}

	void bubbleSort() {
		T tmp;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 1 - i; j++) {
				if (arr[j] > arr[j + 1]) {
					tmp = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = tmp;
				}
			}
		}
	}
	void swap(unsigned a, const T& dane) {
		if (a >= size) throw std::out_of_range("");
		else arr[a] = dane;
	}
	void clear_all() {
		for (int cnt = 0; cnt < size; cnt++) {
			arr[cnt].~T();
		}
		size = 0;
	}

	T index(unsigned a) {
		if (a >= size) throw std::out_of_range("");
		else return arr[a];
	}

	void push_back(const T& data) {
		if (size == capacity) {
			add_capacity();
			arr[size] = data;
			size++;
		}
		else {
			arr[size] = data;
			size++;
		}
	}

	std::string getSize() {
		std::ostringstream st;
		st << "Array size: " << size;
		return st.str();
	}

	std::string disp() {
		std::ostringstream st;
		for (int i = 0; i < size; i++) {
			st << "  " << arr[i];
		}
		st << "\n";
		st << getSize() << "\n";
		st << "Array capacity: " << capacity << "\n";
		return st.str();
	}

	

private:
	void add_capacity() {
		T* tmp = new T[capacity * 2];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = arr[i];
		}
		delete[] arr;
		arr = tmp;
		capacity = capacity * 2;
	}
	T* arr;
	int size;
	int capacity;
};