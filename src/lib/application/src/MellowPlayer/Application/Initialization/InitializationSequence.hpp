#pragma once

#include <MellowPlayer/Domain/IInitializable.hpp>
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
    class InitializationSequence : public Domain::IInitializable
    {
    public:
        explicit InitializationSequence(const std::vector<std::shared_ptr<Domain::IInitializable>>& items);

        void append(const std::shared_ptr<Domain::IInitializable>& item);
        std::shared_ptr<Domain::IInitializable> currentItem() const;

        int currentIndex() const;
        int count() const;
        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;

        QString errorMessage() const override;
        QString toString() const override { return "InitializationSequence"; };

    private:
        void onFinished(bool result);
        void initializeNext();
        void onItemInitialized(bool result);

        Domain::ILogger& _logger;
        QList<std::shared_ptr<Domain::IInitializable>> _itemsToInitialize;
        QList<std::shared_ptr<Domain::IInitializable>> _initializedItems;
        Domain::IInitializable::ResultCallback _resultCallback;
        QString _exceptionMessage;
        int _count = 0;
        int _currentIndex = 0;
    };
}