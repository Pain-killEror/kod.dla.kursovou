#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct Strou
{
	int index;
	char name[100];
	int section;
	bool availability;
	double quantity;
	double price;
};

void printArray(const string* arr, int size);
Strou* transferDataToArray(const string& filename, int& size);
void SortArrayByQuantity(const string& filename);
void LinearSearchByQuantity(FILE* file);
void Create(FILE* file);
void Read(FILE* file);
void Add(FILE* file);
void Infa(Strou* s);
void SortArrayBySelect(const string& filename);
vector<int> binarySearchByQuantity(const Strou* arr, int size, int targetQuantity);
void selectionSort(Strou* arr, int size);
void printConstructionMaterial(const Strou& material);
void sortAndWrite(Strou* constructionMaterials, int size);

void Menu() {
	bool k = true; // Объявление и инициализация переменной k типа bool со значением true.
	char str[20]; // Объявление массива символов str размером 20.
	int n; // Объявление переменной n типа int.
	int size; // Объявление переменной size типа int.
	Strou* constructionMaterials; // Объявление указателя constructionMaterials типа Strou.
	int targetQuantity; // Объявление переменной targetQuantity типа int.
	vector<int> indices; // Объявление вектора indices типа int.

	while (k == true) // Начало цикла while, который будет выполняться, пока k равно true.
	{
		FILE* file = fopen("Construction_materials.txt", "r"); // Открытие файла "Construction_materials.txt" в режиме чтения и присвоение указателя на файл переменной file.
		if (file != nullptr) { // Проверка, удалось ли успешно открыть файл. Если file не равен нулевому указателю, значит файл открылся успешно.	
			cout << "******" << endl; // Вывод строки "******" в консоль.
			fclose(file); // Закрытие файла.
			// Вывод меню на консоль.
			cout << "1.Очистить файл." << endl;
			cout << "2.Добавить новую запись." << endl;
			cout << "3.Просмотреть все строительные материалы." << endl;
			cout << "4.Линейный поиск по количеству." << endl;
			cout << "5.Быстрая сортировка." << endl;
			cout << "6.Сортировка методом прямого выбора." << endl;
			cout << "7.Бинарный поиск по количеству." << endl;
			cout << "8.Выйти." << endl;
			cout << "9.Индивидуальное." << endl;

			while (!(cin >> n)) { // Цикл while, который будет выполняться, пока пользователь не введет корректное значение для n.
				cin.clear(); // Очищает флаги ошибок ввода cin.
				cin.ignore(1000, '\n'); // Игнорирует оставшиеся символы во входном потоке до символа новой строки.
				system("cls");  // Очищает экран консоли.
				cout << "Ошибка! Введите цифру.\n"; // Вывод сообщения об ошибке.
				cout << "******" << endl;
				cout << "1.Очистить файл." << endl;
				cout << "2.Добавить новую запись." << endl;
				cout << "3.Просмотреть все строительные материалы." << endl;
				cout << "4.Линейный поиск по количеству." << endl;
				cout << "5.Быстрая сортировка." << endl;
				cout << "6.Сортировка методом прямого выбора." << endl;
				cout << "7.Бинарный поиск по количеству." << endl;
				cout << "8.Выйти." << endl;
				cout << "9.Индивидуальное." << endl;
			}
			system("cls"); // Очищает экран консоли.

			switch (n)
			{
			case 1:
				Create(file);
				cout << "Файл успешно очищен." << endl;
				break;
			case 2:
				Add(file);
				break;
			case 3:
				Read(file);
				break;
			case 4:
				LinearSearchByQuantity(file);
				break;
			case 5:
				SortArrayByQuantity("Construction_materials.txt");
				Read(file);
				break;
			case 6:
				SortArrayBySelect("Construction_materials.txt");
				Read(file);
				break;
			case 7:
				constructionMaterials = transferDataToArray("Construction_materials.txt", size);
				if (size > 1) {
					selectionSort(constructionMaterials, size);
				}
				cout << "Введите количество для поиска: ";
				while (!(cin >> targetQuantity)) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Ошибка! Введено некорректное значение. \nПопробуйте еще раз: ";
				}
				indices = binarySearchByQuantity(constructionMaterials, size, targetQuantity);
				if (indices.empty()) {
					cout << "Элементы не найдены." << endl;
				}
				else {
					cout << "Найдены элементы с заданным количеством:" << endl;
					for (int index : indices) {
						printConstructionMaterial(constructionMaterials[index]);
					}
				}
				delete[] constructionMaterials;
				break;
			case 8:
				k = 0;
				fclose(file);
				return ;
				break;
			case 9: {
				constructionMaterials = transferDataToArray("Construction_materials.txt", size);
				sortAndWrite(constructionMaterials, size);
				break;
			}
			default:

				cout << "Не существует такого пункта!" << endl;
				break;
			}
			fclose(file);

		}
		else
		{
			cout << "1.Создать файл." << endl;
			cout << "2.Выйти." << endl;
			int c;
			while (!(cin >> c)) {
				cin.clear();
				cin.ignore(1000, '\n');
				system("cls");
				cout << "Ошибка! Введите цифру.\n";
				cout << "1.Создать файл." << endl;
				cout << "2.Выйти." << endl;
			}
			system("cls");

			switch (c)
			{
			case 1:
				file = fopen("Construction_materials.txt", "w");
				if (file != nullptr)
				{
					cout << "Файл успешно создан." << endl;
				}
				else
				{
					cout << "Ошибка при создании файла." << endl;
					return;
				}
				break;
			case 2:
				k = 0;
				return;
				break;
			default:
				cout << "Такого пункта нет!\n";
				break;
			}

		}
		fclose(file);
	}

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu();
}

void sortAndWrite(Strou* constructionMaterials, int size) {
	// Сортировка по имени
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (strcmp(constructionMaterials[j].name, constructionMaterials[j + 1].name) > 0) {
				Strou temp = constructionMaterials[j];
				constructionMaterials[j] = constructionMaterials[j + 1];
				constructionMaterials[j + 1] = temp;
			}
		}
	}

	int currentIndex = 1;
	for (int i = 0; i < size; i++) {
		constructionMaterials[i].index = currentIndex;
		currentIndex++;
	}

	// Запись в файл
	FILE* file = fopen("MaterialsGreaterThan100.txt", "w");
	if (file != nullptr) {
		for (int i = 0; i < size; i++) {
			if (constructionMaterials[i].quantity >= 100) {
				fwrite(&constructionMaterials[i], sizeof(Strou), 1, file);
			}
		}
		fclose(file);
	}
	else {
		cout << "Ошибка при открытии файла." << endl;
	}



	file = fopen("MaterialsGreaterThan100.txt", "r");
	if (file == nullptr) {
		cout << "Ошибка в открытии файла." << endl;
		return;
	}
	Strou s;
	int kolvo = _filelength(_fileno(file)) / sizeof(Strou);
	for (int i = 0; i < kolvo; i++) {
		fread(&s, sizeof(Strou), 1, file);
		Infa(&s);
	}

	fclose(file);
}


void printConstructionMaterial(const Strou& material) {
	cout << "Индекс: " << material.index << endl;
	cout << "Название материалов: " << material.name << endl;
	cout << "Номер секции: " << material.section << endl;
	if (material.availability == 1)
		cout << "Есть в наличии." << endl;
	else
		cout << "Нет в наличии." << endl;
	cout << "Количество стройматериалов: " << material.quantity << endl;
	cout << "Стоимость стройматериалов: " << material.price << endl;
	cout << endl;
}

vector<int> binarySearchByQuantity(const Strou* arr, int size, int targetQuantity) {
	vector<int> indices;

	int low = 0;
	int high = size - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;

		if (arr[mid].quantity == targetQuantity) {
			indices.push_back(mid);
			// Поиск влево и вправо от найденного индекса для поиска дополнительных элементов
			int left = mid - 1;
			int right = mid + 1;

			while (left >= 0 && arr[left].quantity == targetQuantity) {
				indices.push_back(left);
				left--;
			}

			while (right < size && arr[right].quantity == targetQuantity) {
				indices.push_back(right);
				right++;
			}

			return indices;
		}


		else if (arr[mid].quantity < targetQuantity) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}

	}

	return indices; // Возвращаем пустой вектор, если элементы не найдены
}

void selectionSort(Strou* arr, int size) {
	for (int i = 0; i < size - 1; ++i) {
		int minIndex = i;

		for (int j = i + 1; j < size; ++j) {
			if (arr[j].quantity < arr[minIndex].quantity) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			// Обмен значениями элементов массива
			Strou temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
}

void SortArrayBySelect(const string& filename) {
	int size;
	Strou* constructionMaterials = transferDataToArray(filename, size);

	// Сортировка массива методом прямого выбора по количеству
	if (size > 1) {
		selectionSort(constructionMaterials, size);
	}

	// Перенумерация индексов
	int currentIndex = 1;
	for (int i = 0; i < size; i++) {
		constructionMaterials[i].index = currentIndex;
		currentIndex++;
	}

	// Очистка файла и запись отсортированного массива
	FILE* file = fopen(filename.c_str(), "wb");
	if (!file) {
		cout << "Ошибка открытия файла для записи." << endl;
		return;
	}

	fwrite(constructionMaterials, sizeof(Strou), size, file);

	fclose(file);

	delete[] constructionMaterials;
}


Strou* transferDataToArray(const string& filename, int& size) {
	FILE* file = fopen(filename.c_str(), "r");
	if (file == nullptr) {
		cout << "Ошибка в открытии файла." << endl;
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	size = fileSize / sizeof(Strou);

	Strou* arr = new Strou[size];
	fread(arr, sizeof(Strou), size, file);

	fclose(file);

	return arr;
}


int partition(Strou* arr, int low, int high) {
	int pivot = arr[high].quantity;
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (arr[j].quantity < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(Strou* arr, int low, int high) {
	if (low < high) {
		int pivotIndex = partition(arr, low, high);

		quickSort(arr, low, pivotIndex - 1);
		quickSort(arr, pivotIndex + 1, high);
	}
}

void SortArrayByQuantity(const string& filename) {
	int size;
	Strou* constructionMaterials = transferDataToArray(filename, size);

	// Быстрая сортировка массива по количеству
	if (size > 1) {
		quickSort(constructionMaterials, 0, size - 1);
	}

	// Перенумерация индексов
	int currentIndex = 1;
	for (int i = 0; i < size; i++) {
		constructionMaterials[i].index = currentIndex;
		currentIndex++;
	}

	// Очистка файла и запись отсортированного массива
	FILE* file = fopen(filename.c_str(), "wb");
	if (!file) {
		cout << "Ошибка открытия файла для записи." << endl;
		return;
	}

	fwrite(constructionMaterials, sizeof(Strou), size, file);

	fclose(file);

	delete[] constructionMaterials;
}



void Swap(Strou& a, Strou& b) {
	Strou temp = a;
	a = b;
	b = temp;
}


void Create(FILE* file) {
	file = fopen("Construction_materials.txt", "w");
	fclose(file);
}

void Add(FILE* file)
{
	ofstream fout("Construction_materials.txt", ios_base::app);
	Strou s;

	fseek(file, 0, SEEK_END);
	int index = ftell(file) / sizeof(Strou) + 1;
	s.index = index;

	system("cls");

	cout << "Введите название материала: ";
	cin.ignore();

	cin.getline(s.name, 100);

	cout << "Введите номер секции: ";
	cin >> s.section;

	cout << "Введите наличие материала (1 - есть (по умолчанию), 0 - нет): ";
	int answ2;
	cin >> answ2;

	if (answ2 == 0) {
		s.availability = false;
	}
	else {
		s.availability = true;
	}

	cout << "Введите количество строительного материала: ";
	cin >> s.quantity;

	cout << "Введите стоимость строительного материала: ";
	cin >> s.price;
	fwrite(&s, sizeof(Strou), 1, file);

	fclose(file);

	cout << "1.Добавить еще. \n2.В меню." << endl;
	int answ;
	cin >> answ;
	switch (answ)
	{
	case 1:
		system("cls");
		fclose(file);
		Add(file);
		break;
	case 2:
		system("cls");
		fclose(file);
		Menu();
		break;
	default:
		system("cls");
		fclose(file);
		Menu();
		break;
	}

}

void LinearSearchByQuantity(FILE* file)
{
	double quantityToSearch;
	cout << "Введите количество материалов для поиска: ";
	while (!(cin >> quantityToSearch)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ошибка! Введено некорректное значение. \nПопробуйте еще раз: ";
	}
	file = fopen("Construction_materials.txt", "r");
	if (file == nullptr) {
		cout << "Ошибка в открытии файла." << endl;
		return;
	}
	cout << "Найдены элементы с заданным количеством:" << endl;
	Strou s;
	while (fread(&s, sizeof(Strou), 1, file) != 0) {
		if (s.quantity == quantityToSearch) {
			Infa(&s);
		}
	}
	fclose(file);
}

void Read(FILE* file) {

	system("cls");

	file = fopen("Construction_materials.txt", "r");
	if (file == nullptr) {
		cout << "Ошибка в открытии файла." << endl;
		return;
	}
	Strou s;
	int kolvo = _filelength(_fileno(file)) / sizeof(Strou);
	for (int i = 0; i < kolvo; i++) {
		fread(&s, sizeof(Strou), 1, file);
		Infa(&s);
	}

	fclose(file);
}


void Infa(Strou* s) {
	printf("Индекс: %d\n", s->index);
	printf("Наименование: %s\n", s->name);
	printf("Раздел: %d\n", s->section);
	printf("Наличие: %s\n", s->availability ? "Да" : "Нет");
	printf("Количество: %.2f\n", s->quantity);
	printf("Цена: %.2f\n", s->price);
	cout << endl;
}