#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>

#pragma warning( disable: 4018 4244)

void fillRandom(int list[], int length, int min, int max)
{
	for (int i = 0; i < length; i++)
	{
		list[i] = rand() % (max - min + 1) + min;
	}
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// ============= Sortowanie bąbelkowe ==============
// =================================================
void bubbleSort(int list[], int length)
{
	bool swapped;
	do
	{
		swapped = false;
		for (int i = 0; i < length - 1; i++)
		{
			if (list[i] > list[i + 1])
			{
				swap(list[i], list[i + 1]);
				swapped = true;
			}
		}
	} while (swapped);
}
// =================================================



// ========== Sortowanie przez wybieranie ==========
// =================================================
void selectionSort(int list[], int length)
{
	// Basically szukamy najmniejszej wartości i wrzucamy ją na miejsce 0, potem szukamy drugiej najmniejszej wartości i wrzucamy ją na miejsce 1 i tak dalej
	for (int sorted = 0; sorted < length;)
	{
		int minindex = sorted;
		for (int i = sorted; i < length; i++)
		{
			if (list[i] < list[minindex])
			{
				minindex = i;
			}
		}
		swap(list[sorted], list[minindex]);
		sorted += 1;
	}
}


// Rekurencyjnie: 
void selectionSortR(int list[], int length, int start)
{
	if (length == 1) return;
	int minindex = start;
	for (int i = start; i < length; i++)
	{
		if (list[i] < list[minindex])
		{
			minindex = i;
		}
	}
	swap(list[start], list[minindex]);
	selectionSortR(list, length, start + 1);
}
// =================================================



// ======== Sortowanie przez wstawianie ============
// =================================================
void insertionSort(int list[], int length)
{
	// Część tablicy jest posortowana, bierzemy pierwszy nieposortowany element i szukamy gdzie go "wcisnąć" do posortowanej części
	for (int i = 1; i < length; i++)
	{
		int value = list[i];
		int j = i - 1;
		while (j >= 0 and list[j] > value)
		{
			// Dopóki elementy posortowanej części są większe to przesuwamy je w prawo
			list[j + 1] = list[j];
			j -= 1;
		}
		list[j + 1] = value;
	}
}
// =================================================



// ======== Sortowanie przez scalanie ==============
// =================================================
void mergeSort(int list[], int start, int end)
{
	if (start >= end) return;
	int q = (int)((start + end) / 2); // Znajdujemy środek
	// Sortujemy osobno lewą i prawą połowę
	mergeSort(list, start, q);
	mergeSort(list, q + 1, end);

	// Scalanie:
	int* L = new int[q - start + 1]; // tymczasowa tablica na lewą połowę
	int* R = new int[end - q]; // tymczasowa tablica na prawą połowę
	memcpy(L, list + start, (q - start + 1) * sizeof(int)); // kopiowanie lewej połowy do L
	memcpy(R, list + q + 1, (end - q) * sizeof(int)); // kopiowanie prawej połowy do R
	int l = 0; // indeks lewej tablicy
	int r = 0; // indeks prawej tablicy
	for (int i = start; i <= end; i++)
	{
		// Sprawdzamy która połowa ma mniejszą wartość i dodajemy ją do tablicy. 
		// Jeśli wyczerpiemy którąś z połówek to przepisujemy resztę drugiej połowy
		if (l >= q - start + 1)
		{
			// Dodajemy wartość z prawej połwy
			list[i] = R[r];
			r += 1;
			continue;
		}
		else if (r >= end - q)
		{
			// Dodajemy do tablicy wartość z lewej połowy
			list[i] = L[l];
			l += 1;
			continue;
		}
		if (L[l] <= R[r])
		{
			// Dodajemy do tablicy wartość z lewej połowy
			list[i] = L[l];
			l += 1;
		}
		else
		{
			// Dodajemy wartość z prawej połwy
			list[i] = R[r];
			r += 1;
		}
	}
	delete[] L;
	delete[] R;
}
// =================================================



// ================= Quicksort =====================
// =================================================
void quickSort(int list[], int start, int end)
{
	if (start >= end)return;

	// Reorganizujemy listę tak żeby ostatni element miał indeks q i wszystkie elementy po jego lewej były mniejsze lub równe, a po prawej - większe
	int q = start;
	for (int i = start; i < end; i++)
	{
		if (list[i] <= list[end])
		{
			swap(list[i], list[q]);
			q += 1;
		}
	}

	swap(list[q], list[end]);
	quickSort(list, start, q - 1);
	quickSort(list, q + 1, end);
}
// =================================================


// ================ Radix sort =====================
// =================================================

// =================================================



// =================================================================================================================================================
// =================================================================================================================================================

void selectionSort_demo(int list[], int length)
{
	for (int sorted = 0; sorted < length;)
	{
		int minindex = sorted;
		for (int i = sorted; i < length; i++)
		{
			if (list[i] < list[minindex])
			{
				minindex = i;
			}
		}
		for (int k = 0; k < length; k++)
		{
			std::cout << (k <= sorted ? "\x1b[30;102m" : k == minindex ? "\x1b[30;103m" : "\x1b[37;100m") << list[k] << "\x1b[0m ";
		}
		std::cout << "\x1b[0m \n";
		swap(list[sorted], list[minindex]);
		for (int k = 0; k < length; k++)
		{
			std::cout << (k < sorted ? "\x1b[30;102m" : k == minindex or k == sorted ? "\x1b[30;103m" : "\x1b[37;100m") << list[k] << "\x1b[0m ";
		}
		std::cout << "\x1b[0m \n";

		sorted += 1;
	}

	for (int k = 0; k < length; k++)
	{
		std::cout << "\x1b[30;102m" << list[k] << "\x1b[0m ";
	}
	std::cout << "\x1b[0m \n";

}

void quickSort_demo(int list[], int start, int end, int level, int gend, std::vector<std::string*>& qsort_vector, bool mode)
{
	if (level >= qsort_vector.size())
		qsort_vector.push_back(new std::string[gend + 1]);
	if (start >= end)
	{
		if (start > end) return;
		std::stringstream ss;
		std::string value;
		ss << list[start];
		ss >> value;
		qsort_vector[level][start] = "\x1b[97;41m";
		qsort_vector[level][start] += value;
		qsort_vector[level][start] += "\x1b[0m ";
		return;
	}

	int q = start;
	for (int i = start; i < end; i++)
	{
		if (list[i] <= list[end])
		{
			swap(list[i], list[q]);
			q += 1;
		}
	}
	swap(list[q], list[end]);


	for (int k = start; k <= end; k++)
	{
		std::stringstream ss;
		std::string value;
		ss << list[k];
		ss >> value;
		qsort_vector[level][k] = (k < q ? "\x1b[97;42m" : k == q ? "\x1b[97;41m" : "\x1b[97;43m");
		qsort_vector[level][k] += value;
		qsort_vector[level][k] += "\x1b[0m ";
	}

	quickSort_demo(list, start, q - 1, level + 1, gend, qsort_vector, mode);
	quickSort_demo(list, q + 1, end, level + 1, gend, qsort_vector, mode);

	if (start == 0 and end == gend)
	{
		for (int l = 0; l < qsort_vector.size(); l++)
		{
			for (int k = 0; k <= gend; k++)
			{
				if (qsort_vector[l][k] == "") {
					qsort_vector[l][k] = mode ? "\x1b[0m   " : qsort_vector[l - 1][k];
				}
				std::cout << qsort_vector[l][k];
			}
			std::cout << "\x1b[0m \n";
		}
	}
}

// =================================================================================================================================================
// =================================================================================================================================================
#define SIZE 30
int main()
{
	srand(time(NULL));
	int list[SIZE];

	fillRandom(list, SIZE, 10, 99);
	selectionSort_demo(list, SIZE);
	system("pause");
	system("cls");

	fillRandom(list, SIZE, 10, 99);
	std::vector<std::string*> qsort_vector;
	quickSort_demo(list, 0, SIZE - 1, 0, SIZE - 1, qsort_vector, 1);
	system("pause");
	return 0;
}
