#pragma once
#include "API.h"
#include <memory>

namespace Tempus {

	class TEMPUS_API Application {
	public:
		Application();
		~Application();

		void Run();

	};

	std::unique_ptr<Application> CreateApplication();
}