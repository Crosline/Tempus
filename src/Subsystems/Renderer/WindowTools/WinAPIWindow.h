#pragma once
#include "BaseWindow.h"
#include <Windows.h>

namespace Tempus {
    namespace Renderer {
        class TEMPUS_API WinApiWindow final : public BaseWindow {
        public:
            explicit WinApiWindow(const Settings::ProjectSettings& settings);
            WinApiWindow() = delete;

            ~WinApiWindow();

        protected:
            void PrepareWindow() override;
            void Update() override;
            void ShowWindow() override;
        };
    }
}