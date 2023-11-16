#include <iostream>
#include <thread>
#include <chrono>

void client(int& count, int& count_max) {
    while (count <= count_max)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count++;
        std::cout << "Client: " << count << std::endl;
    }
}

void teller(int& count) {
    while (count >= 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        count--;
        std::cout << "Teller: " << count << std::endl;
    }
}

int main()
{
    int count = 0;
    int count_max = 16;
    
    std::thread t1(client, std::ref(count), std::ref(count_max));
    std::thread t2(teller, std::ref(count));

    t1.join();
    t2.join();

    return 0;
}