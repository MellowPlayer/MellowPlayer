#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <QtCore/QElapsedTimer>
#include <QtCore/QList>
#include <QtCore/QString>
#include <memory>
#include <vector>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Application
{
    class InitializationSequence : public Domain::Initializable
    {
    public:
        explicit InitializationSequence(const std::vector<std::shared_ptr<Domain::Initializable>>& items);

        void append(const std::shared_ptr<Domain::Initializable>& item);
        std::shared_ptr<Domain::Initializable> currentItem() const;

        int currentIndex() const;
        int count() const;
        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;

        QString errorMessage() const override;

    private:
        void onFinished(bool result);
        void initializeNext();
        void onItemInitialized(bool result);

        Domain::ILogger& _logger;
        QList<std::shared_ptr<Domain::Initializable>> _itemsToInitialize;
        QList<std::shared_ptr<Domain::Initializable>> _initializedItems;
        Domain::Initializable::ResultCallback _resultCallback;
        QString _exceptionMessage;
        QElapsedTimer _elapsedTimer;
        int _count = 0;
        int _currentIndex = 0;
    };
}