#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

// Функция для для складывания двух векторов
void progress_bar(int threadID){

    std::cout << std::this_thread::get_id() << "\t";

    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "|";
    }
}

int main()
{
    std::vector<std::thread> t;
    int numThreads = 5;

    std::cout << "#\t" << "id\t" << "Progress Bar\t" << "Time" << std::endl;

    for (int i = 0; i < numThreads; i++)
    {

        std::cout << i << ": \t";

        auto start = std::chrono::steady_clock::now();
        t.push_back(std::thread(progress_bar, i));
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "\t" << elapsed_seconds.count() << std::endl;
    }

    for (auto& i : t)
    {
        i.join();
    }

    t.clear();
    std::cout << std::endl;
}
