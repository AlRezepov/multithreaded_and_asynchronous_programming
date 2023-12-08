#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

std::mutex mutex;

// Функция отрисовки прогресс бара
void draw_progress_bar(int thread_number, int progress_bar_size) {
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i <= progress_bar_size; i++) {
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lk(mutex);

            // Перемещаем курсор к началу нужной строки
            std::cout << "\033[" << thread_number + 2 << ";0H"; // +2 потому что заголовок таблицы занимает две строки
           
            std::cout << thread_number <<"\t" << std::this_thread::get_id() << "\t";
            for (int j = 0; j < progress_bar_size; j++) {
                if (j < i) {
                    std::cout << "|";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << "\t";
            if (i == progress_bar_size) {
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << elapsed_seconds.count();
            }
            std::cout << std::flush; // Сбрасываем буфер вывода
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << std::endl;
}

int main() {
    
    std::vector<std::thread> th;
    int numThreads = 8;
    int progress_bar_size = 10;

    std::cout << "#\t" << "id\t" << "Progress Bar\t" << "Time" << std::endl;

    for (int i = 0; i < numThreads; i++)
    {
        th.push_back(std::thread(draw_progress_bar, i, progress_bar_size));
    }

    for (auto& t : th) {
        t.join();
    }
    th.clear();
}

