#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 4037
// Hash 2518
// Hash 9148
// Hash 2792
// Hash 8354
// Hash 8679
// Hash 1200
// Hash 2257
// Hash 3758
// Hash 5045
// Hash 5719
// Hash 6310
// Hash 7007
// Hash 8386
// Hash 6505
// Hash 4839
// Hash 5377
// Hash 4622
// Hash 3050
// Hash 7884
// Hash 7603
// Hash 3343
// Hash 1489
// Hash 8926
// Hash 7816
// Hash 1414
// Hash 1519
// Hash 1420
// Hash 2303
// Hash 6608
// Hash 8106
// Hash 3296
// Hash 4778
// Hash 5671
// Hash 4951
// Hash 5807
// Hash 8594
// Hash 6200
// Hash 3836
// Hash 7578
// Hash 2173
// Hash 8384
// Hash 7072
// Hash 8072
// Hash 9642
// Hash 5285
// Hash 3666
// Hash 6919
// Hash 4546
// Hash 3206
// Hash 4334
// Hash 4109
// Hash 4591
// Hash 9366
// Hash 5694
// Hash 4787
// Hash 7375
// Hash 2777
// Hash 2236
// Hash 7932
// Hash 7948
// Hash 2179
// Hash 6486
// Hash 5246
// Hash 7906
// Hash 3570
// Hash 1080
// Hash 1328
// Hash 4316
// Hash 2978
// Hash 2392
// Hash 3118
// Hash 1867
// Hash 6346
// Hash 6376
// Hash 8335
// Hash 7337
// Hash 9511