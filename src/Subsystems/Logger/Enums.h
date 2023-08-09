#pragma once
#include <unordered_map>

namespace Tempus {
	namespace Log {
		enum Level : char {
			Debug,
			Warning,
			Error
		};

		enum Category : char {
			General,
			System,
			Core,
			Rendering
		};

		static const std::unordered_map<Category, std::string> categoryMap = {
			{General, "General"},
			{System, "System"},
			{Core, "Core"},
			{Rendering, "Rendering"}
		};

		static const std::unordered_map<Level, std::string> levelMap = {
			{Debug, "Debug"},
			{Warning, "Warning"},
			{Error, "Error"}
		};

		inline std::ostream& operator<<(std::ostream& stream, const Category& logCategory) {
			const auto it = categoryMap.find(logCategory);
			if (it != categoryMap.end())
			{
				stream << it->second;
			}

			return stream;
		}

		inline std::ostream& operator<<(std::ostream& stream, const Level& logLevel) {
			const auto it = levelMap.find(logLevel);
			if (it != levelMap.end())
			{
				stream << it->second;
			}

			return stream;
		}
	}
}