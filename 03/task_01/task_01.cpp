#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

// Асинхронная функция для поиска минимального элемента
template <typename T>
std::future<T> min_element(std::vector<T>& vec, std::size_t start, std::size_t end) {
    std::promise<T> result_promise;
    std::future<T> result_future = result_promise.get_future();

    std::async([&]() {
        auto min_it = std::min_element(vec.begin() + start, vec.begin() + end);
        result_promise.set_value(*min_it);
        });

    return result_future;
}

// Сортировка выбором
template <typename T>
std::vector<T> selection_sort(std::vector<T> vec) {
    std::size_t n = vec.size();

    for (std::size_t i = 0; i < n - 1; ++i) {
        
        auto future_min = min_element(vec, i, n);
        auto min_val = future_min.get();

        // Находим индекс минимального элемента
        auto min_it = std::find(vec.begin() + i, vec.end(), min_val);

        // Обмениваем местами текущий элемент и минимальный элемент
        std::iter_swap(vec.begin() + i, min_it);
    }

    return vec;
}

int main() {
    std::vector<int> arr = { 150, 1, 40, 22, 5 };

    // Вызываем сортировку выбором
    auto sorted_future = std::async(std::launch::async, selection_sort<int>, arr);
    auto sorted = sorted_future.get();

    // Выводим результат
    std::cout << "Sorted array: ";
    for (auto& i : sorted) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
