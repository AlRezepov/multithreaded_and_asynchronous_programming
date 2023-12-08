#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

template <typename It, typename Function>
void parallel_for_each(It begin, It end, Function&& func, std::size_t threshold) {
    std::size_t size = std::distance(begin, end);

    if (size <= threshold) {
        // Если размер диапазона меньше или равен пороговому значению, обрабатываем стандартным for_each
        std::for_each(begin, end, func);
    }
    else {
        It mid = begin + size / 2;

        auto first_half = std::async(parallel_for_each<It, Function>, begin, mid, func, threshold);
        auto second_half = std::async(parallel_for_each<It, Function>, mid, end, func, threshold);

        // Ожидаем завершения задач
        first_half.get();
        second_half.get();
    }
}

int main() {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Устанавливаем пороговое значение
    std::size_t threshold = 2;

    // Пример использования параллельного for_each, где каждый элемент вектора умножается на 2
    parallel_for_each(numbers.begin(), numbers.end(), [](int& num) {
        num *= 2;
        }, threshold);

    std::cout << "Modified array: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
