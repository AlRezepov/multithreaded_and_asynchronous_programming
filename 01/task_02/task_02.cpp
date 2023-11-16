#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

// Функция для генерации случайных чисел в диапазоне [min, max]
int getRandomNumber(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Функция для для складывания двух векторов
std::vector<int> vector_sum(int threadID, std::vector<int>& a, std::vector<int>& b, int size) {
	std::vector<int> c(size);
	for (int i = 0; i < size; ++i)
	{
		c[i] = a[i] + b[i];
	}
	return c;
}

// Функция для заполнения вектора
void full_vector(std::vector<int>& vector, int size) {
	for (int i = 0; i < size; i++)
	{
		vector.push_back(getRandomNumber(0, 100));
	}
}

int main()
{
	std::vector<std::thread> t;
	
	// Вывод количества доступных аппаратных ядер
	int num_cores = std::thread::hardware_concurrency();
	std::cout << "Number of hardware cores: " << num_cores << std::endl;
	std::cout << std::endl;

	// Установка размеров векторов
	std::vector<int> vector_sizes = { 1000, 10000, 100000, 1000000 };

	// Установка количества потоков
	std::vector<int> numThreads = { 2, 4, 8, 16 };

	// Создание векторов
	std::vector<int> a;
	std::vector<int> b;

	for (int i = 0; i < vector_sizes.size(); i++)
	{
		std::cout << "\t" << vector_sizes[i] << "\t";
	}

	std::cout << std::endl;

	for (int i = 0; i < 4; i++)
	{
		std::cout << numThreads[i] << ": ";

		for (int j = 0; j < 4; j++)
		{
			// Заполнение первого вектора
			full_vector(a, vector_sizes[j]);

			// Заполнение второго вектора
			full_vector(b, vector_sizes[j]);

			auto start = std::chrono::steady_clock::now();
			t.push_back(std::thread(vector_sum, numThreads[i], std::ref(a), std::ref(b), vector_sizes[j]));
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;

			std::cout << "\t" << elapsed_seconds.count();

		}

		for (auto& i : t)
		{
			i.join();
		}

		t.clear();
		std::cout << std::endl;
	}

}