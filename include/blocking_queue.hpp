//
// Created by Cedric Ai on 10/20/2022.
//

#ifndef GADGETS_BLOCKING_QUEUE_HPP
#define GADGETS_BLOCKING_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

template<typename T>
class BlockingQueue {
public:
    void push_back(const T &data) {
        {
#if __cplusplus >= 201703L
            std::lock_guard lock{guard_};
#else
            std::lock_guard<std::mutex> lock{guard_};
#endif
            queue_.push(data);
        }
        signal_.notify_one();
    }

    bool empty() const {
#if __cplusplus >= 201703L
        std::lock_guard lock{guard_};
#else
        std::lock_guard<std::mutex> lock{guard_};
#endif
        return queue_.empty();
    }

    bool tryPop(T &value) {
#if __cplusplus >= 201703L
        std::lock_guard lock{guard_};
#else
        std::lock_guard<std::mutex> lock{guard_};
#endif
        if (queue_.empty()) {
            return false;
        }
        value = queue_.front();
        queue_.pop();
        return true;
    }

    void pop(T &value) {
#if __cplusplus >= 201703L
        std::unique_lock lock{guard_};
#else
        std::unique_lock<std::mutex> lock{guard_};
#endif
        signal_.wait(lock, [this] { return !queue_.empty(); });
        value = queue_.front();
        queue_.pop();
    }

    bool pop(T &value, int milli) {
#if __cplusplus >= 201703L
        std::unique_lock lock{guard_};
#else
        std::unique_lock<std::mutex> lock{guard_};
#endif
        if (queue_.empty()) {
            signal_.wait_for(lock, std::chrono::milliseconds(milli));
            if (queue_.empty()) {
                return false;
            }
        }
        value = queue_.front();
        queue_.pop();
        return true;
    }

private:
    std::queue<T> queue_;
    mutable std::mutex guard_;
    std::condition_variable signal_;
};

#endif  // GADGETS_BLOCKING_QUEUE_HPP
