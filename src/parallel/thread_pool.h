/*  
 * Copyright (c) 2012 Jakob Progsch, Václav Zeman
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 */

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <memory>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class thread_pool
{
    
public:
    
    thread_pool(size_t _threads);
    ~thread_pool();
    
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
    ->std::future<typename std::result_of<F(Args...)>::type>;
    
    void shutdown();
    
private:
    
    std::vector<std::thread> workers;
    
    std::queue<std::function<void()>> tasks;
    
    std::mutex queue_mutex;
    std::condition_variable condition;
    
    bool is_shutdown;
    
};

inline thread_pool::thread_pool(size_t _threads) : is_shutdown(false)
{
    for (size_t i = 0; i < _threads; ++i)
    {
        workers.emplace_back(
            [&]
            {
                for (;;)
                {
                    std::function<void()> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(
                            lock,
                            [this]
                            {
                               return is_shutdown || !tasks.empty(); 
                            });
                        
                            if (is_shutdown && tasks.empty())
                                return;
                            
                            task = std::move(tasks.front());
                            tasks.pop();
                    }
                    
                    task();
                }
            } 
        );
    }
}

inline thread_pool::~thread_pool() 
{
    shutdown();
}

template<class F, class... Args>
auto thread_pool::enqueue(F&& f, Args&&... args)
->std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(is_shutdown)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });
    }
    
    condition.notify_one();
    return res;
}

inline void thread_pool::shutdown() 
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (!is_shutdown) is_shutdown = true;
    }
    
    condition.notify_all();
    
    for (auto& worker : workers)
        if (worker.joinable())
            worker.join();
}

#endif /* THREAD_POOL_H */

