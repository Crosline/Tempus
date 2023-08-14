#pragma once
#include <mutex>

#include "Enums.h"
#include "API.h"
#include "Common.h"

namespace Tempus {
    namespace Log {
        class TEMPUS_API Logger;
    }
}

using TLogger = Tempus::Log::Logger;

namespace Tempus {
    namespace Log {
#define T_STREAM_BRACKETS(x) "[" << x << "]"
#define T_LOGGER Tempus::Log::Logger
#define T_ENABLE_LOG(category) T_LOGGER::EnableCategory(category)
#define T_DISABLE_LOG(category) T_LOGGER::DisableCategory(category)
// #define LOG_DEBUG(message, suffix) Tempus::Log::Logger::Debug(message, suffix)
// #define LOG_WARNING(message, suffix) Tempus::Log::Logger::Debug(message, suffix)
// #define LOG_ERROR(message, suffix) Tempus::Log::Logger::Debug(message, suffix)

        class Logger {
        protected:
#pragma warning (push)
#pragma warning (disable : 4251)
            static std::vector<Category> _enabledCategories;
            static std::mutex _categoryMutex;
            std::string _prefix;
#pragma warning (pop)
            Category _category;

            static bool ContainsCategory(const Category& category);

            std::string PrepareLogMessage(const Level& level, const std::string& message, const std::string& suffix) const;
            void virtual Log(const Level& level, const std::string& message, const std::string& suffix = "") const = 0;

        public:
#pragma warning (push)
#pragma warning (disable : 4251)
            static std::shared_ptr<Logger> SharedLogger;
#pragma warning (pop)

            void virtual Debug(const std::string& message, const std::string& suffix = "") const;

            void virtual Warning(const std::string& message, const std::string& suffix = "") const;

            void virtual Error(const std::string& message, const std::string& suffix = "") const;

            static void EnableCategory(const Category& category);

            static void DisableCategory(const Category& category);

        public:
            Logger() = delete;

            explicit Logger(Category category, std::string prefix = "");
            explicit Logger(const Logger& other);

            virtual ~Logger();
        };
    }
}