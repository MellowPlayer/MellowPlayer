#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <QtCore/QTranslator>

namespace MellowPlayer::Infrastructure
{
    class IQtApplication;
}

namespace MellowPlayer::Application
{
    class TranslationsSetup : public Domain::Initializable
    {
    Q_OBJECT
    public:
        explicit TranslationsSetup(Infrastructure::IQtApplication& qtApplication);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        QTranslator _translator;
        Infrastructure::IQtApplication& _qtApplication;
    };
}
