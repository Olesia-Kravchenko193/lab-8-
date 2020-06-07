#include <iostream>
#include <windows.h>
#include <iterator>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

template<typename T>
class forward_list
{
public:
	forward_list();
	~forward_list();

	T& operator[](const int index);
	int getSize() { return Size; }
	void pop_front();
	void clear();
	void push_front(T data);
	void insert(T data, int index);
	void erase(int index);

private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T data; //поле обобщённого типа
		Node(T data = T(), Node* pNext = nullptr) //по умолчанию указатель на следующий элемент указывает на NULL
		{
			this->data = data; //присваиваем входящие параметры полям класса Node
			this->pNext = pNext;
		}
	};
	//поля класса forward_list
	int Size;
	Node<T>* head;
};


template<typename T>
forward_list<T>::forward_list()
{
	Size = 0;
	head = nullptr;
}

template<typename T>
forward_list<T>::~forward_list()
{
	clear();
}

template<typename T>
void forward_list<T>::pop_front()
{
	Node<T>* temp = head; //создаем временный объект, содержащий адрес начала списка
	head = head->pNext; //присваиваем элементу из начала списка элемент, идущий следом за ним
	delete temp; //удаляем временный объект
	Size--; //уменьшаем размер списка на единицу

}

template<typename T>
void forward_list<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
void forward_list<T>::push_front(T data)
{
	head = new Node<T>(data, head); //помещаем в начало новый элемент и увеличиваем на единицу размер списка
	Size++;
}

template<typename T>
void forward_list<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;
		Size++;
	}
}

template<typename T>
void forward_list<T>::erase(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		delete toDelete;
		Size--;
	}

}

template<typename T>
T& forward_list<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head; //current указывает на начало списка
	while (current != nullptr) //пока current не будет указывать на последний элемент
	{
		if (counter == index)
		{
			return current->data; //если значение счетчика совпадает с индексом требуемого элемента, то возвращаем этот элемент
		}
		current = current->pNext; //текущему элементу присваиваем адрес следующего элемента
		counter++; //переход к следующей итерации цикла
	}
}
struct Node
{
	double data = 0;
	Node* next = nullptr;
};

struct Queue
{
	Node* head = nullptr, *tail = nullptr;

	void add(double value)
	{
		if (!head)
		{
			head = new Node();
			head->data = value;
		}
		else if (!tail)
		{
			tail = new Node();
			tail->data = value;
			head->next = tail;
		}
		else
		{
			tail->next = new Node();
			tail->next->data = value;
			tail = tail->next;
		}
	}

	void insert_by_num(double by_num, double value)
	{
		Node* insertance;
		for (Node* next = head; next; next = next->next)
		{
			if (next->data < by_num)
			{
				insertance = new Node();
				insertance->data = value;
				insertance->next = next->next;
				next->next = insertance;
				next = next->next;
			}
		}
	}

	void remove_at_range(double minVal, double maxVal)
	{
		if (head)
		{
			Node* save;
			while (head && head->data >= minVal && head->data <= maxVal)
			{
				save = head->next;
				delete head;
				head = save;
				if (head == tail)
					tail = nullptr;
			}
			for (Node* next = head; next; next = next->next)
			{
				while (next->next && next->next->data >= minVal && next->next->data <= maxVal)
				{
					save = next->next->next;
					delete next->next;
					next->next = save;
				}
			}
		}
	}

	void integrate(Queue queue)
	{
		if (queue.head)
		{
			if (!head)
			{
				head = queue.head;
			}
			else
			{
				Node* next;
				if (head->data <= queue.head->data)
					next = head;
				else next = queue.head;
			}
		}
	}

	void show()
	{
		if (head)
		{
			for (Node* next = head; next; next = next->next)
			{
				std::cout << std::setw(5) << next->data << " ";
			}
			std::cout << std::endl;
		}
		else std::cout << "NULL" << std::endl;
	}
};


void Task1()

{

	forward_list<short> numbers;
	short amount;
	do
	{
		cout << endl << "Введите количество элементов в списке: ";
		cin >> amount;
		if (amount <= 0)
			cout << "Количество элементов должно быть больше 0.";
	} while (amount <= 0);
	vector<short> temp_array(amount);
	for (int i = 0; i < amount; i++)
	{
		short temp;
		temp = -20 + rand() % 40;
		numbers.push_front(temp);
		temp_array[i] = temp;
	}
	if (temp_array.size() < 5)
	{
		cout << "| | |" << 0 << "| | |";
	}
	else
	{
		float sum = 0;
		for (int i = 5; i < temp_array.size(); i++)
		{
			sum += temp_array[i];
		}
		numbers.clear();
		for (int i = 0; i < temp_array.size(); i++)
			numbers.push_front(temp_array[temp_array.size() - i - 1]);
		cout << endl << "Элементы в списке :" << endl;
		for (int i = 0; i < amount; i++)
		{
			cout << temp_array[i] << " ";
		}
		cout << "Сумма элементов - " << sum << endl << "Их среднее арифметическое - " << sum / (temp_array.size() - 5) << endl;
	}

}

void Task2()
{
	Queue list;
	list.add(0);
	list.add(4);
	list.add(-1);
	list.add(3);
	list.add(-2);
	list.add(0.1);
	std::cout << std::setw(20) << "оригинальный список: ";
	list.show();
	list.insert_by_num(0, 1.5);
	std::cout << std::setw(20) << "после вставки: ";
	list.show();
	list.remove_at_range(2, 5);
	std::cout << std::setw(20) << "после удаления: ";
	list.show();
}


int main()
{
	int numTask;
	cout << "Enter num of task: ";
	cin >> numTask;
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");

	switch (numTask)
	{
	case 1:
		Task1();
		break;
	case 2:
		Task2();
		break;
	}
}

