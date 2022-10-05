#pragma once
#include <iostream>
using namespace std;

template <class T>
class list
{
public:
	int Size() { return size; }
	void push_front(T data); // Добавление в начало списка
	void push_back(T data);   // Добавление в конец списка
	
	void pop_front(); // Удаление первого элемента
	void pop_back(); // Удаление последнего элемента

	void resize(int n); // Изменение размерности списка
	void resize(int n, T data); // Изменение размерности списка

	void insert(T data, int index); // Вставка эл-та по индексу
	void insert(T data, int n, int index); // Вставка эл-тов

	T front(); // Первый элемент списка
	T back(); // Последний элемент списка

	void Clear(); // Удаление всех элементов списка
	bool Empty(); // Проверка списка на пустоту

	T& operator [](const int index); // Перегрузка оператора []

	list<T>(); // Конструктор по умолчанию
	~list(); // Деструктор

	

private:
	int size;
	template <class T>
	class object
	{
	private:
		T data;
		object* next;
		object* prev;
		object(T data = T(), object* next = nullptr, object* prev = nullptr)
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
		friend class  list;
	};
	object<T>* head;
	object<T>* tail;
public:

	class iterator
	{
		object<T>* cur;
	public:
		iterator(object<T>* head) { this->cur = head; }
		T& operator*(){ return cur->data; }
		object<T>* operator++(int)
		{ 
			object<T>* temp = this->cur;
			cur = cur->next;
			return temp;
		}
		object<T>* operator-- (int)
		{
			object<T>* temp = this->cur;
			cur = cur->prev;
			return temp;
		}

		object<T>* operator++ ()
		{
			cur = cur->next;
			return cur;
		}

		object<T>* operator-- ()
		{
			cur = cur->prev;
			return cur;
		}

		bool operator!= (const iterator& temp )
		{
			return cur->data != temp.cur->data;
		}
		bool operator == (const iterator& temp)
		{
			return cur->data == temp.cur->data;
		}
		object<T>* operator+= (int a)
		{
			for (int i = 0; i < a; i++)
			cur = cur->next;
			return cur;
		}
		object<T>* operator-= (int a)
		{
			for (int i = 0; i < a; i++)
				cur = cur->prev;
			return cur;
		}

		object<T>* operator+ (int a)
		{
			object<T>* temp = this->cur;
			for (int i = 0; i < a; i++)
				temp = temp->next;
			return temp;
		}

		object<T>* operator- (int a)
		{
			object<T>* temp = this->cur;
			for (int i = 0; i < a; i++)
				temp = temp->prev;
			return temp;
		}
	};
	iterator begin() const { return iterator(head); }
	iterator end() const { return iterator(tail->next); }
};

template <class T>
void list<T>::push_back(T data) // Добавление в конец списка
{
	if (head == nullptr)
	{
		head = new object<T>(data);
		this->tail = head;
	}
	else
	{
		object<T>* temp = this->tail;
		this->tail = new object<T>(data);
		temp->next = this->tail;
		this->tail->prev = temp;
	}
	size++;
}

template <class T>
void list<T>::push_front(T data) // Добавление в начало списка
{
	if (head == nullptr)
	{
		head = new object<T>(data);
	}
	else
	{
		object<T>* temp = this->head;
		this->head = new object<T>(data, temp);
		temp->prev = this->head;
	}
	size++;
}

template<class T>
void list<T> ::resize(int n) // Изменение размерности списка
{

	if (n == 0) Clear();
	else if (n < size)
	{
		int k = size;
		for (int i = 0; i < k - n; i++)
		{
			pop_back();
		}
	}
	else if (n == size) return;
	else if (n > size)
	{
		int k = size;
		for (int i = 0; i < n - k; i++)
		{
			push_back(0);
		}
	}
}

template<class T>
void list<T>::resize(int n, T data) // Изменение размерности списка
{

	if (n == 0) Clear();
	else if (n < size)
	{
		int k = size;
		for (int i = 0; i < k - n; i++)
		{
			pop_back();
		}
	}
	else if (n == size) return;
	else if (n > size)
	{
		int k = size;
		for (int i = 0; i < n - k; i++)
		{
			push_back(data);
		}
	}
}

template<class T>
T list<T> ::front() // Первый элемент списка
{
	return head->data;
}

template<class T>
void list<T>::insert(T data, int index) // Вставка эл-та по индексу
{
	if (index == 0) push_front(data);
	else
	{
		object<T>* temp = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			temp = temp->next;
		}
		object<T>* Node = new object<T>(data, temp->next, temp);
		temp->next = Node;
		Node->next->prev = Node;
		size++;
	}
}

template<class T>
void list<T>::insert(T data, int n, int index) // Вставка эл-тов
{
	for (int i = 0; i < n; i++)
	{
		insert(data, index);
	}
}

template<class T>
T list<T>::back() // Последний элемент списка
{
	return this->tail->data;
}

template<class T>
void list<T>::pop_front() // Удаление первого элемента
{
	object<T>* temp = this->head;
	this->head = this->head->next;
	delete temp;
	size--;
}

template<class T>
void list<T>::pop_back() // Удаление последнего элемента
{
	object<T>* temp = this->tail;
	this->tail = this->tail->prev;
	delete temp;
	size--;
}

template<class T>
list<T>::list() // Конструктор по умолчанию
{
	head = nullptr;
	tail = head;
	size = 0;
}

template<class T>
void list<T>::Clear() // Удаление всех элементов списка
{
	while (size)
	{
		pop_front();
	}
}

template<class T>
bool list<T>::Empty() // Проверка списка на пустоту
{
	if (head == nullptr)
		return true; else return false;
}

template<class T>
T& list<T>:: operator [](const int index) // Перегрузка оператора []
{
	int count = 0;
	object<T>* temp = this->head;
	while (temp != nullptr)
	{
		if (count == index)
		{
			return temp->data;
		}
		count++;
		temp = temp->next;
	}
}

template<class T>
list<T>:: ~list() // Деструктор
{
	Clear();
}