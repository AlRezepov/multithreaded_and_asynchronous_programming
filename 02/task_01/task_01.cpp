#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>

void client(std::atomic<int>& count, int& count_max) {
    while (count.load(std::memory_order_relaxed) <= count_max)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count.fetch_add(1, std::memory_order_relaxed);
        std::cout << "Client: " << count << std::endl;
    }
}

void teller(std::atomic<int>& count) {

    while (count.load(std::memory_order_relaxed) >= 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        count.fetch_sub(1, std::memory_order_relaxed);
        std::cout << "Teller: " << count << std::endl;
    }

}

int main() {

    std::atomic<int> count = 0;
    int count_max = 16;

    std::thread t1(client, std::ref(count), std::ref(count_max));
    std::thread t2(teller, std::ref(count));

    t1.join();
    t2.join();

    return 0;
}
