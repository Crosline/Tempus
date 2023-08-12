#pragma once
#include <condition_variable>
#include <functional>
#include <queue>

#include "Common.h"
#include "API.h"

namespace Tempus {
    namespace Thread {
        class TEMPUS_API ThreadPool {
        public:
            static ThreadPool SharedPool;
            void EnqueueJob(const std::function<void()>& job);
            bool IsBusy();

        private:
            void Loop();

#pragma warning (push)
#pragma warning (disable : 4251)
            std::queue<std::function<void()>> jobs;
            std::mutex jobPoolMutex;
            std::condition_variable mutexCondition;
            std::vector<std::thread> threads;
#pragma warning (pop)
            bool isRunning = false;
            bool isBusy = false;

            ThreadPool();
            ~ThreadPool();
        };
    }
}