#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class safe_queue {
public:
    void push(T value) {
        std::unique_lock<std::mutex> lock(m);
        q.push(std::move(value));
        lock.unlock();
        condition_variable.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m);
        condition_variable.wait(lock, [this] { return !q.empty(); });
        T value = std::move(q.front());
        q.pop();
        return value;
    }

    bool empty() const {
        std::unique_lock<std::mutex> lock(m);
        return q.empty();
    }

private:
    std::queue<T> q;
    mutable std::mutex m;
    std::condition_variable condition_variable;
};

class thread_pool {
public:
    thread_pool() {
        const auto cores = std::thread::hardware_concurrency();

        for (size_t i = 0; i < cores; i++) {
            threads.emplace_back([this] { work(); });
        }
    }

    ~thread_pool() {

        std::unique_lock<std::mutex> lock(m);
        stop = true;
        lock.unlock();

        condition_variable.notify_all();

        for (auto& thread : threads) {
            thread.join();
        }
    }

    void work() {
        while (true) {
            std::unique_lock<std::mutex> lock(m);
            condition_variable.wait(lock, [this] { return stop || !queue.empty(); });

            if (stop && queue.empty()) {
                return;
            }

            auto task = std::move(queue.pop());
            lock.unlock();
            task();
        }
    }

    template<typename T>
    void submit(T&& t) {
        queue.push(std::forward<T>(t));
        condition_variable.notify_one();
    }

private:
    std::vector<std::thread> threads;
    safe_queue<std::function<void()>> queue;
    std::mutex m;
    std::condition_variable condition_variable;
    bool stop = false;
};

void test_function_01() {
    std::cout << std::this_thread::get_id() << ": " << "Function 1\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void test_function_02() {
    std::cout << std::this_thread::get_id() << ": " << "Function 2\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    thread_pool pool;

    while (true) {
        pool.submit(test_function_01);
        pool.submit(test_function_02);

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
