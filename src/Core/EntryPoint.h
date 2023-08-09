#pragma once
#include <memory>

#include "Application.h"

extern std::unique_ptr<Tempus::Application> Tempus::CreateApplication();


int main(int argc, char** argv) {

	auto gameApplication = Tempus::CreateApplication();

	gameApplication->Run();

	return 0;
}