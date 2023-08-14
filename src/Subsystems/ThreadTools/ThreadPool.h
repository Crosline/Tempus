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
            std::queue<std::function<void()>> _jobs;
            std::mutex _jobPoolMutex;
            std::condition_variable _mutexCondition;
            std::vector<std::thread> _threads;
#pragma warning (pop)
            bool _isRunning = false;
            bool _isBusy = false;

            ThreadPool();
            ~ThreadPool();
        };
    }
}