// Question 3 - implementation
// 
//	without using STL containers implement the following:
//	A class for a dynamic int array, let's call it "CVectorInt" that -
//  1. doubles its size automatically when its full (allocates twice the size and moves the data),
//	2. halves its size when it is half empty (allocates half of the size and moves the data)
//  3. can be told the initial capacity (num of ints) in a constructor
//  4. have a method called "reserve" - that Requests that the vector capacity be at least enough to contain n elements.
//     If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n
//  5. have a method called "capacity" - that returns the number of int elements allocated
//  6. have a method called "size" - that returns the number of elements actually inserted
//  7. have a method called "empty" - that returns true/false according to amount of actual elements in the data
//  8. have a method called "clear" - that frees all the data and resets the size
//  9. have a method called "push_back" - that adds an int elements at the end
// 10. have a method called "pop_back" - that removes an int elements at the end and return it
// 11. have a method called "remove"  - that removes an int elements at specific index
// 12. have an interface to access the data at a specific index using subscript "[]"
//
// make sure to handle edge cases such as memory issues, size issues etc.



#include <iostream>
#include <stdexcept>


class CVectorInt
{
	// TODO: your code here

public:
	CVectorInt(int capacity = 0)
	{
		if (capacity <= 0)
		{
			throw std::invalid_argument("capacity must be greater than 0");
		}

		this->data = new int[capacity];
		this->data_size = 0;
		this->data_capacity = capacity;
	}
	~CVectorInt()
	{
		delete[] data;
	}
	void push_back(int value) {
		if (data_size == data_capacity)
		{
			int new_capacity = data_capacity * 2;
			int* new_data = new int[new_capacity];
			memcpy(new_data, data, data_size * sizeof(int));
			delete[] data;
			data = new_data;
			data_capacity = new_capacity;
		}
		data[data_size] = value;
		data_size++;
	}
	int pop_back()
	{
		if (data_size == 0)
		{
			throw std::out_of_range("vector is empty");
		}

		int value = data[data_size - 1];
		data[data_size - 1] = 0; //not must
		data_size--;

		if (data_size < data_capacity / 2)
		{
			int new_capacity = data_capacity / 2;
			int* new_data = new int[new_capacity];
			memcpy(new_data, data, data_size * sizeof(int));
			delete[] data;
			data = new_data;
			data_capacity = new_capacity;
		}

		return value;
	}
	int& operator[](int index)
	{
		if (index < 0 || index >= data_size)
		{
			throw std::out_of_range("index is out of range");
		}

		return data[index];
	}
	void reserve(int n) {
		if (n <= data_capacity)
		{
			return;
		}

		int* new_data = new int[n];
		memcpy(new_data, data, data_size * sizeof(int));
		delete[] data;
		data = new_data;
		data_capacity = n;
	}
	void remove(int index) {
		if (index < 0 || index >= data_size)
		{
			throw std::out_of_range("index is out of range");
		}

		for (int i = index; i < data_size - 1; i++)
		{
			data[i] = data[i + 1];
		}

		data_size--;

		if (data_size < data_capacity / 2)
		{
			int new_capacity = data_capacity / 2;
			int* new_data = new int[new_capacity];
			memcpy(new_data, data, data_size * sizeof(int));
			delete[] data;
			data = new_data;
			data_capacity = new_capacity;
		}
	}
	int size() {
		return data_size;
	}
	int capacity() {
		return data_capacity;
	}
	bool empty() {
		return (data_size == 0);
	}
	void clear()
	{
		data_size = 0;
		data_capacity = 0;
		delete[] data;
		data = nullptr;
	}
private:
	int* data;
	int data_size;
	int data_capacity;
protected:
};

int main(int argc, char* argv[])
{
	// some code to use the class
	try
	{
		CVectorInt v(5);

		for (int i = 0; i < 5; i++)
		{
			v.push_back(i);
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.push_back(1);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		while (!v.empty())
		{
			v.pop_back();
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.reserve(15);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		for (int i = 0; i < 15; i++)
		{
			v.push_back(i);
		}
		v[5] = 3;
		for (int i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
		v.clear();
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

