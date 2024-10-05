#include <cstring>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

template<typename T>
class Node {
	T * _data = nullptr;
	int* _amount_of_data = nullptr;

	void delete_data()
	{
		if (_amount_of_data == nullptr)
		{
			if(_data!= nullptr)
				delete _data;
		}
		else
		{
			if(_data != nullptr)
				delete[] _data;
			delete _amount_of_data;
		}
	}

	friend ostream& operator<<(ostream& os, const Node<T>& node)
	{
		if (node._amount_of_data == nullptr)
		{
			os << *node._data;
		}
		else
		{
			for (int i = 0; i < *node._amount_of_data; i++)
			{
				os << node._data[i] << " ";
			}
		}
		return os;
	}
public:
	Node() = default;
	Node(T data)
	{
		_data = new T{ data };
	}
	Node(T* data, int size)
	{
		_amount_of_data = new int{ size };
		_data = new T[*_amount_of_data];
		for (size_t i = 0; i < *_amount_of_data; i++)
		{
			_data[i] = data[i];
		}
	}
	Node(const Node& other)
	{
		if (other._amount_of_data != nullptr)
		{
			_amount_of_data = new int{ *other._amount_of_data };
			_data = new T[*_amount_of_data];
			for (int i = 0; i < *_amount_of_data; i++)
			{
				_data[i] = other._data[i];
			}
		}
		else
		{
			_data = new T{ *other._data };
		}
	}

	void change_data(T new_value)
	{
		delete_data();
		_data = new T{ new_value };
	}

	void change_data(T * new_value, int size)
	{
		delete_data();

		_amount_of_data = new int{ size };
		_data = new T[size];

		for (int i = 0; i < size; i++)
		{
			_data[i] = new_value[i];
		}
	}

	T* get_data()
	{
		return _data;
	}

	int get_amount_of_data()
	{
		return *_amount_of_data;
	}



	~Node()
	{
		delete_data();
	}
};



template<typename T>
class Stack
{
	Node<T>** _items = nullptr;
	const int _step = 10;
	int _size;
	int _fact_size = 0;

	void check_resize()
	{
		if (_fact_size == _size - 1)
		{
			resize();
		}
	}

	void resize()
	{
		Node<T>** new_items = new Node<T>*[_size + _step];
		for (int i = 0; i < _size; i++)
		{
			new_items[i] = _items[i];
		}
		delete[] _items;
		_items = new_items;
		_size += _step;
	}
public:
	Stack()
	{
		_size = _step;
		_items = new Node<T>*[_size];
	}

	void push(T value)
	{
		check_resize();
		Node<T> * new_node = new Node<T>(value);
		_items[_fact_size] = new_node;
		_fact_size++;
	}

	void push(T* value, int size)
	{
		check_resize();
		Node<T>* new_node = new Node<T>(value, size);
		_items[_fact_size] = new_node;
		_fact_size++;
	}

	Node<T> pop()
	{
		if (_fact_size == 0)
		{
			throw std::out_of_range("Stack is empty");
		}
		Node<T>* item = _items[_fact_size - 1];
		Node<T> result(*item);
		delete item;
		_fact_size--;
		return result;
	}

	Node<T> top()
	{
		if (_fact_size == 0)
		{
			throw std::out_of_range("Stack is empty");
		}
		Node<T>* item = _items[_fact_size - 1];
		Node<T> result = *item;
		return result;
	}


	~Stack()
	{
		delete[] _items;
	}
};

int main() {
	const int maxLSize = 250;
	string line;
	getline(cin, line);
	char* erLine = new char[line.size()];

	stack<char> stack1;
	stack<char> stack2;
	int index = 0;
	while(line[index] != ';') {
		if(line[index] == '{' || line[index] == '[' || line[index] == '(') {
			stack1.push(line[index]);
		}
		if(line[index] == '}' || line[index] == ']' || line[index] == ')') {
			if(stack1.top() == '(') {
				if(stack1.top() + 1 == line[index]) {
					stack1.pop();
				} else {
					cout << "line isn't correct" << endl;
					cout << erLine << endl;
					delete[] erLine;
					return 0;
				}
			} else {
				if(stack1.top() + 2 == line[index]) {
					stack1.pop();
				} else {
					cout << "line isn't correct" << endl;
					cout << erLine << endl;
					delete[] erLine;
					return 0;
				}
			}
		}
		erLine[index] += line[index];
		index++;
	}
	cout << "line is correct" << endl;
	cout << erLine << endl;
	delete[] erLine;
	//		({12 + 34} - 8);

	return 0;
}

/*
	while(line[index] != '}' || line[index] != ']' || line[index] != ')') {
		if(line[index] == '{' || line[index] == '[' || line[index] == '(') {
			stack1.push(line[index]);
		}
		index++;
	}

	index++;
*/