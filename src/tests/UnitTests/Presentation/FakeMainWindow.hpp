#pragma once

#include <MellowPlayer/Presentation/IMainWindow.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeMainWindow : public IMainWindow
    {
    public:
        void show() override
        {
            isShown = true;
        }

        void raise() override
        {
            isShown = true;
        }

        void hide() override
        {
            isHidden = true;
        }

        void requestQuit() override
        {
            quitRequested = true;
        }

        bool isLoaded = false;
        bool isShown = false;
        bool isHidden = false;
        bool quitRequested = false;
    };
}
