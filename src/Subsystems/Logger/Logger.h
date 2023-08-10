#pragma once
#include "Enums.h"
#include "API.h"
#include <iostream>

namespace Tempus
{
	namespace Log
	{
		class TEMPUS_API Logger;
	}
}

using TLogger = Tempus::Log::Logger;

namespace Tempus {
	namespace Log {
#define T_STREAM_BRACKETS(x) "[" << (x) << "]"
#define T_LOGGER Tempus::Log::Logger
#define T_ENABLE_LOG(category) T_LOGGER::EnableCategory(category)
#define T_DISABLE_LOG(category) T_LOGGER::DisableCategory(category)
// #define LOG_DEBUG(message, suffix) Tempus::Log::Logger::Debug(message, suffix)
// #define LOG_WARNING(message, suffix) Tempus::Log::Logger::Debug(message, suffix)
// #define LOG_ERROR(message, suffix) Tempus::Log::Logger::Debug(message, suffix)

		class Logger {
		private:
			static std::vector<Category> enabledCategories;\
			std::string prefix;
			Category category;

			static bool ContainsCategory(const Category& category);

			void Log(Level level, const std::string& message, const std::string& suffix) const;

		public:
			void Debug(const std::string& message, const std::string& suffix = "") const;

			void Warning(const std::string& message, const std::string& suffix = "") const;

			void Error(const std::string& message, const std::string& suffix = "") const;

			static void EnableCategory(const Category& category);

			static void DisableCategory(const Category& category);

		public:
			Logger() = delete;

			explicit Logger(Category category, std::string prefix);
			Logger(const Logger& other);

			~Logger();
		};
	}
}