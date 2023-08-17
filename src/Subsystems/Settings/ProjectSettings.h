#pragma once
#include "Common.h"

namespace Tempus {
    namespace Settings {
        struct TEMPUS_API ProjectSettings {
#pragma warning (push)
#pragma warning (disable : 4251)
            std::wstring ProjectName{L"DefaultProjectName"};
            std::string ProjectVersion{"1.0.0"};
            std::string Company{"DefaultCompany"};

            std::array<int, 2> WindowSize{800, 600};
#pragma warning (pop)

            ProjectSettings(std::wstring name, const int& width, const int& height, std::string version = "1.0.0", std::string company = "DefaultCompany")
                : ProjectName(std::move(name)), ProjectVersion(std::move(version)), Company(std::move(company)), WindowSize({width, height}) {}

            ProjectSettings() = default;
        };
    }
}