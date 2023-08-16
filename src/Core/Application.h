#pragma once
#include "API.h"
#include <memory>

namespace Tempus {

	class TEMPUS_API Application {  // NOLINT(cppcoreguidelines-special-member-functions)
	public:
		Application();
		virtual ~Application();

		virtual void Run() = 0;
	};

	std::unique_ptr<Application> CreateApplication();
}