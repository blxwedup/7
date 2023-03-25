#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>
using namespace std;

void outvector(vector<int>& s, int& n) //Вывод вектора
{
	for (int i = 0; i < n; ++i)
	{
		cout << s[i] << endl;
	}
}

void mergesort(vector<int>& s, size_t start, size_t end) //Сортировка слиянием
{
	if (end - start < 2)
	{
		return;
	}
	if (end - start == 2)
	{
		if (s[start] > s[start + 1])
		{
			swap(s[start], s[start + 1]);
		}
		return;
	}
	mergesort(s, start, start + (end - start) / 2);
	mergesort(s, start + (end - start) / 2, end);
	vector<int> b;
	size_t bl = start;
	size_t el = start + (end - start) / 2;
	size_t b2 = el;
	while (b.size() < end - start) {
		if (bl >= el || (b2 < end && s[b2] <= s[bl]))
		{
			b.push_back(s[b2]);
			++b2;
		}
		else
		{
			b.push_back(s[bl]);
			++bl;
		}
	}
	for (size_t i = start; i < end; ++i)
	{
		s[i] = b[i - start];
	}
}

void heapify(vector <int>& s, int n, int i) // функция для пирамидальной
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && s[l] > s[largest])
		largest = l;
	if (r < n && s[r] > s[largest])
		largest = r;
	if (largest != i)
	{
		swap(s[i], s[largest]);
		heapify(s, n, largest);
	}
}

void heapsort(vector <int>& s, int& n) //Пирамидальная
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(s, n, i);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		swap(s[0], s[i]);
		heapify(s, i, 0);
	}
}

void vstavka(vector<int>& s, int& n) // сортировка вставками
{
	int indexlast, element, j, i;
	for (i = 1; i < n; ++i)
	{
		element = s[i];
		indexlast = i - 1;
		for (j = indexlast; j >= 0 && element < s[j]; j--)
		{
			s[j + 1] = s[j];
		}
		s[j + 1] = element;
	}
}

void shell(vector <int>& arr, int& n)  // сортировка Шелла
{
	for (int d = n / 2; d > 0; d /= 2)
	{
		for (int i = d; i < n; ++i)
		{
			int el = arr[i];
			int j;
			for (j = i; j >= d && arr[j - d] > el; j -= d)
			{
				arr[j] = arr[j - d];
			}
			arr[j] = el;
		}
	}
}

void qsort(vector<int>& s, int n) //быстрая сортировка
{
	int i = 0;
	int j = n - 1;
	int mid = s[n / 2];
	do
	{
		while (s[i] < mid)
		{
			++i;
		}
		while (s[j] > mid)
		{
			--j;
		}
		if (i <= j)
		{
			int tmp = s[i]; s[i] = s[j]; s[j] = tmp;
			++i;
			--j;
		}
	} while (i <= j);
	if (j > 0)
	{
		qsort(s, j + 1);
	}
	if (i < n)
	{
		qsort(s, n - i);
	}
}

int main()
{
	int t = 1000; // Количество тестов
	cout << "MergeSort   HeapSort   InsertionSort   ShellSort   QuickSort" << endl;
	while (--t)
	{
		srand(time(0));

		int n = 1000000; // Количество элементов для всех сортировок
		int k = 10000; // кол-во элементов для сортировки вставками

		vector<int> s(n);
		for (int i = 0; i < n; ++i) //Заполнение вектора
		{
			s[i] = rand();
		}

		auto start = chrono::steady_clock::now();
		mergesort(s, 0, s.size()); //Сортировка слиянием
		auto end = chrono::steady_clock::now();

		cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << "      ";

		//outVector(s, n); //Вывод вектора

		for (int i = 0; i < n; ++i)
		{
			s[i] = rand(); //Переопределение вектора рандомными числами
		}

		start = chrono::steady_clock::now();
		heapsort(s, n); //Пирамидальная
		end = chrono::steady_clock::now();

		cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << "      ";

		vector<int> v(k); //Вектор для сортировки вставками
		for (int i = 0; i < k; ++i)
		{
			v[i] = rand();
		}

		start = chrono::steady_clock::now();
		vstavka(v, k); // Вызов сортировки вставками
		end = chrono::steady_clock::now();

		cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << "      ";

		for (int i = 0; i < n; ++i)
		{
			s[i] = rand(); //Переопределение вектора рандомными числами
		}

		start = chrono::steady_clock::now();
		shell(s, n); // сортировка Шелла
		end = chrono::steady_clock::now();

		cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << "      ";

		for (int i = 0; i < n; ++i)
		{
			s[i] = rand(); //Переопределение вектора рандомными числами
		}

		start = chrono::steady_clock::now();
		qsort(s, n); // Быстрая сортировка
		end = chrono::steady_clock::now();

		cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << "      " << endl;
	}
}