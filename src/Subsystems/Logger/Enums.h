#pragma once
#include <iostream>

namespace Tempus {
	namespace Log {
		enum class Level : uint8_t {
			Debug = 0,
			Warning = 1,
			Error = 2,
			None = 255
		};

		enum class Category : uint8_t {
			General = 0,
			System = 1,
			Core = 2,
			Rendering = 3,
			Engine = 4,
			None = 255
		};
#define TO_STR(x) #x
		inline std::ostream& operator<<(std::ostream& stream, const Level& logLevel) {
			switch (logLevel) {
				case Level::Debug: stream << TO_STR(DEBUG); break;
				case Level::Error: stream << TO_STR(ERROR); break;
				case Level::Warning: stream << TO_STR(WARNING); break;
				case Level::None: break;
			}
			return stream;
		}

		inline std::ostream& operator<<(std::ostream& stream, const Category& logCategory) {
			switch (logCategory) {
				case Category::General: stream << TO_STR(General); break;
				case Category::System: stream << TO_STR(System); break;
				case Category::Core: stream << TO_STR(Core); break;
				case Category::Rendering: stream << TO_STR(Rendering); break;
				case Category::Engine: stream << TO_STR(Engine); break;
				case Category::None: break;
			}
			return stream;
		}
#undef TO_STR
	}
}