#include "ThreadPool.h"

namespace Tempus {
    namespace Thread {
        ThreadPool ThreadPool::SharedPool = {};

        void ThreadPool::Loop() {
            while (true) {
                std::function<void()> job;
                {
                    std::unique_lock<std::mutex> lock(jobPoolMutex);
                    mutexCondition.wait(lock, [this] {
                        return !isRunning || !jobs.empty();
                    });

                    if (!isRunning && jobs.empty())
                        return;

                    job = std::move(jobs.front());
                    jobs.pop();
                }

                job();
            }
        }

        ThreadPool::ThreadPool() {
            isRunning = true;
            for (uint32_t i = 0; i < std::thread::hardware_concurrency(); i++)
                threads.emplace_back(&ThreadPool::Loop, this);
        }

        ThreadPool::~ThreadPool() {
            {
                std::unique_lock<std::mutex> lock(jobPoolMutex);
                isRunning = false;
            }
            mutexCondition.notify_all();

            for (auto& thread : threads)
                thread.join();
        }

        void ThreadPool::EnqueueJob(const std::function<void()>& job) {
            {
                std::unique_lock<std::mutex> lock(jobPoolMutex);
                jobs.emplace(job);
            }
            mutexCondition.notify_one();
        }

        bool ThreadPool::IsBusy() {
            {
                std::unique_lock<std::mutex> lock(jobPoolMutex);
                isBusy = !jobs.empty();
            }
            return isBusy;
        }
    }
}