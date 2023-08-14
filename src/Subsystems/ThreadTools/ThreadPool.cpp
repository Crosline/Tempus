#include "ThreadPool.h"

namespace Tempus {
    namespace Thread {
        ThreadPool ThreadPool::SharedPool = {};

        void ThreadPool::Loop() {
            while (true) {
                std::function<void()> job;
                {
                    std::unique_lock<std::mutex> lock(_jobPoolMutex);
                    _mutexCondition.wait(lock, [this] {
                        return !_isRunning || !_jobs.empty();
                    });

                    if (!_isRunning && _jobs.empty())
                        return;

                    job = std::move(_jobs.front());
                    _jobs.pop();
                }

                job();
            }
        }

        ThreadPool::ThreadPool() {
            _isRunning = true;
            for (uint32_t i = 0; i < std::thread::hardware_concurrency(); i++)
                _threads.emplace_back(&ThreadPool::Loop, this);
        }

        ThreadPool::~ThreadPool() {
            {
                std::unique_lock<std::mutex> lock(_jobPoolMutex);
                _isRunning = false;
            }
            _mutexCondition.notify_all();

            for (auto& thread : _threads)
                thread.join();
        }

        void ThreadPool::EnqueueJob(const std::function<void()>& job) {
            {
                std::unique_lock<std::mutex> lock(_jobPoolMutex);
                _jobs.emplace(job);
            }
            _mutexCondition.notify_one();
        }

        bool ThreadPool::IsBusy() {
            {
                std::unique_lock<std::mutex> lock(_jobPoolMutex);
                _isBusy = !_jobs.empty();
            }
            return _isBusy;
        }
    }
}