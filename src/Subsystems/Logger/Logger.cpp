#include "Logger.h"

namespace Tempus {
	namespace Log {

		static std::vector<Category> enabledCategories;
		std::string prefix;
		Category category;

		bool Logger::ContainsCategory(const Category& category) {
			if (std::find(enabledCategories.begin(), enabledCategories.end(), category) != enabledCategories.end())
				return true;

			return false;
		}

		void Logger::Log(const Level& level, const std::string& message, const std::string& suffix) const {
			if (category != Category::None && !ContainsCategory(category))
				return;

			if (category != Category::None) {
				if (!suffix.empty()) {
					std::cout << T_STREAM_BRACKETS(level) << T_STREAM_BRACKETS(category) << T_STREAM_BRACKETS(prefix << ":" << suffix) << message << std::endl;
					return;
				}
				std::cout << T_STREAM_BRACKETS(level) << T_STREAM_BRACKETS(category) << T_STREAM_BRACKETS(prefix) << message << std::endl;
				return;
			}

			std::cout << T_STREAM_BRACKETS(level) << T_STREAM_BRACKETS(prefix) << message << std::endl;
		}

		void Logger::Debug(const std::string& message, const std::string& suffix) const {
			Log(Level::Debug, message, suffix);
		}

		void Logger::Warning(const std::string& message, const std::string& suffix) const {
			Log(Level::Warning, message, suffix);
		}

		void Logger::Error(const std::string& message, const std::string& suffix) const {
			Log(Level::Error, message, suffix);
		}


		void Logger::EnableCategory(const Category& category) {
			if (ContainsCategory(category))
				return;

			enabledCategories.emplace_back(category);
		}

		void Logger::DisableCategory(const Category& category) {
			if (!ContainsCategory(category))
				return;

			enabledCategories.erase(std::find(enabledCategories.begin(), enabledCategories.end(), category));
		}

		Logger::Logger(Category category, std::string prefix)
			: prefix(std::move(prefix)), category(category) {
			EnableCategory(this->category);
		}

		Logger::Logger(const Logger& other) {
			this->prefix = other.prefix;
			this->category = other.category;
		}

		Logger::~Logger() {
			DisableCategory(this->category);
		}

		std::vector<Category> Logger::enabledCategories;
		std::unique_ptr<Logger> Logger::SharedLogger = std::make_unique<Logger>(Category::None, "Shared");
	};
}