#include <iostream>
#include <algorithm>
#include <vector>

template <class T>
class Numbers_divisible_by_3 {
public:
    Numbers_divisible_by_3() : sum(0), count(0) {}

    void operator()(int value) {
        if (value % 3 == 0) {
            sum += value;
            count++;
        }
    }

    int get_sum() const {
        return sum;
    }

    int get_count() const {
        return count;
    }

private:
    int sum;
    int count;
};

int main() {
    
    std::vector<int> A = { 4, 1, 3, 6, 25, 54 };

    Numbers_divisible_by_3<int> counter;
    counter = std::for_each(A.begin(), A.end(), Numbers_divisible_by_3<int>());

    std::cout << "[IN]: ";
    for (auto& i : A)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::cout << "[OUT]: get_sum() = " << counter.get_sum() << std::endl;
    std::cout << "[OUT]: get_count() = " << counter.get_count() << std::endl;

    return 0;
}
