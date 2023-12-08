#include <iostream>
#include <mutex>
#include <thread>

class Data {
public:
    Data(int value) : scalarData(value) {}

    void printData() const {
        std::cout << "Scalar Data: " << scalarData << std::endl;
    }

    void swap(Data& first, Data& second) {
        std::swap(first.scalarData, second.scalarData);
    }

    
    // Функция swap с использованием std::lock
    void swapWithLock(Data& other) {
        std::lock(dataMutex, other.dataMutex);

        std::lock_guard<std::mutex> lockThis(dataMutex, std::adopt_lock); 
        std::lock_guard<std::mutex> lockOther(other.dataMutex, std::adopt_lock);

        swap(*this, other);
    }

    // Функция swap с использованием std::scoped_lock
    void swapWithScopedLock(Data& other) {
        std::scoped_lock lock(dataMutex, other.dataMutex);
        swap(*this, other);
    }

    // Функция swap с использованием std::unique_lock
    void swapWithUniqueLock(Data& other) {
        std::lock(dataMutex, other.dataMutex);

        std::unique_lock<std::mutex> lockThis(dataMutex, std::adopt_lock);
        std::unique_lock<std::mutex> lockOther(other.dataMutex, std::adopt_lock);

        swap(*this, other);
    }

private:
    int scalarData;
    std::mutex dataMutex;
};

int main() {
    Data data1(42);
    Data data2(99);

    std::cout << "Before swap:\n";
    data1.printData();
    data2.printData();

    data1.swapWithLock(data2);
    //data1.swapWithScopedLock(data2);
    //data1.swapWithUniqueLock(data2);

    std::cout << "\nAfter swap:\n";
    data1.printData();
    data2.printData();

    return 0;
}
