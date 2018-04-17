// Лихачев Максим 61 II
// Исследовать зависимость числа коллизий от коэффициента заполненности хеш-таблицы 

#include "stdafx.h"
#include <iostream>
using namespace std;

int collisions = 0;		//	Счетчик коллизий

struct Node				//	Связный список для разрешения коллизий
{
	int data;
	Node *next;
};

struct Hash				//	Хеш-таблица
{
	int key[10];
	Node *value[10];
};

void Push(Node *& head, int newsymbol)	//	Добавление в список
{
	Node * temp = new Node;
	temp->data = newsymbol;
	temp->next = head;
	head = temp;
}

void PopAll(Node *& head)				//	Вывод и удалени списка
{
	for (Node *temp = head, *backup = head; backup != NULL; delete temp)
	{
		if (backup->data != 0) cout << backup->data << " ";
		temp = backup;
		backup = temp->next;
	}

	cout << endl;
}

long GenerateValue()	//	Генератор случайных значений
{
	int value = 1;

	for (int i = rand() % 9 + 1; i > 0; i--)
	{
		value += rand() % 9 + 1;
		value *= 10;
	}
	
	if (value < 0) value *= -1;

	return value;
}

int GenerateKey(int element)	//	Генератор хеш-ключа
{
	int temp = element;
	int key = 0;
	
	while (temp > 0)
	{
		temp /= 10;
		key++;
	}

	if (key >= 0 && key <= 9) return key;
	else return -1;
}

void AddHash(Hash *hash, long element)		//	Добавление элемента в хеш-таблицу
{

	int key = GenerateKey(element);

	if (key != -1)
	{
		if (hash->value[key]->data != 0) collisions++;

			Push(hash->value[key], element);
	}
}

void ShowHash(Hash *hash)		//	Вывод хеш-таблицы
{
	for (int i = 0; i < 10; i++)
	{
		cout << "( " << hash->key[i] << " ) ";
		if (hash->value[i] != NULL)	PopAll(hash->value[i]);
		
		cout << endl;
	}
}

void InitHash(Hash *&hash)		//	Инициализация хеш-таблицы
{
	for (int i = 0; i < 10; i++)
	{
		hash->key[i] = i;
		hash->value[i] = NULL;
		Push(hash->value[i], 0);
	}

}

int main()
{
	Hash *hash = new Hash;
	InitHash(hash);

	int count;
	cout << "Enter count of elements:\n";
	cin >> count;

	for (int i = 1; i <= count; i++)
	{
		long symbol = GenerateValue();
		AddHash(hash, symbol);

		if (i % 10 == 5 || i == count)		//	Вывод исследуемых значений каждые 5 проходов
		{
			cout << "Collisions: " << collisions << endl;
			cout << "Occupancy factor: " << static_cast<float>(i)/10 << endl << endl;
		}
		
	}

	ShowHash(hash);

	delete hash;
	hash = NULL;

	system("pause");
    return 0;
}

