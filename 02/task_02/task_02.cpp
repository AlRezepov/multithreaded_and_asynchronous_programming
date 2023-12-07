#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <mutex>

std::mutex my_mutex;

// Функция отрисовки прогресс бара
void draw_progress_bar(int thread_number){

    auto start = std::chrono::steady_clock::now();

    std::cout << thread_number << ": \t";
    std::cout << std::this_thread::get_id() << "\t";

    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::unique_lock<std::mutex> lock(my_mutex);
        std::cout << "|";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "\t" << elapsed_seconds.count() << std::endl;
}


int main()
{
    std::vector<std::thread> t;
    int numThreads = 5;

    std::cout << "#\t" << "id\t" << "Progress Bar\t" << "Time" << std::endl;

    for (int i = 0; i < numThreads; i++)
    {
        t.push_back(std::thread(draw_progress_bar, i));
    }

    for (auto& i : t)
    {
        i.join();
    }
    t.clear();
}
