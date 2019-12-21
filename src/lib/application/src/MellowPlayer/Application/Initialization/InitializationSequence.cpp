#include "InitializationSequence.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Application;

InitializationSequence::InitializationSequence(const std::vector<std::shared_ptr<IInitializable>>& items) : _logger(Loggers::logger("InitializationSequence"))
{
    for (const auto& item : items)
        append(item);
}

void InitializationSequence::append(const std::shared_ptr<IInitializable>& item)
{
    _itemsToInitialize.append(item);
    _count = _itemsToInitialize.count();
}

std::shared_ptr<IInitializable> InitializationSequence::currentItem() const
{
    return _itemsToInitialize.isEmpty() ? nullptr : _itemsToInitialize.first();
}

int InitializationSequence::currentIndex() const
{
    return _currentIndex;
}

int InitializationSequence::count() const
{
    return _count;
}

void InitializationSequence::initialize(const IInitializable::ResultCallback& resultCallback)
{
    LOG_DEBUG(_logger, "Starting Initialization sequence");

    _resultCallback = resultCallback;
    _currentIndex = 0;

    if (_itemsToInitialize.isEmpty())
        onFinished(true);
    else
        initializeNext();
}

void InitializationSequence::onFinished(bool result)
{
    LOG_DEBUG(_logger, "Finished Initialization sequence, status: " << (result ? "SUCCESS" : "FAILED"));
    _resultCallback(result);
}

void InitializationSequence::initializeNext()
{
    try
    {
        // clang-format off
        auto msg = QString("Starting Initialization step (%1/%2) [%3]")
                           .arg(_currentIndex + 1)
                           .arg(_count)
                           .arg(currentItem()->toString());
        // clang-format on
        LOG_DEBUG(_logger, msg);
        currentItem()->initialize([=](bool result) { onItemInitialized(result); });
    }
    catch (const std::exception& exception)
    {
        // clang-format off
        auto msg = QString("Unhandled exception while Initialization step (%1/%2) [%3]: %4")
                           .arg(_currentIndex + 1)
                           .arg(_count)
                           .arg(currentItem()->toString())
                           .arg(exception.what());
        // clang-format on
        _exceptionMessage = msg;
        LOG_ERROR(_logger, msg);
    }
}

void InitializationSequence::onItemInitialized(bool initialized)
{
    auto item = currentItem();

    if (!initialized)
    {
        // clang-format off
        auto msg = QString("Initialization step (%1/%2) [%3] failed: %4")
                           .arg(_currentIndex + 1)
                           .arg(_count)
                           .arg(item->toString())
                           .arg(item->errorMessage());
        // clang-format on
        LOG_ERROR(_logger, msg);
        onFinished(false);
    }
    else
    {
        // clang-format off
        auto msg = QString("Finished Initialization step (%1/%2) [%3]")
                .arg(_currentIndex + 1)
                .arg(_count)
                .arg(item->toString());
        // clang-format on
        LOG_DEBUG(_logger, msg);

        _currentIndex++;
        _initializedItems.append(_itemsToInitialize.takeFirst());
        if (_itemsToInitialize.isEmpty())
        {
            onFinished(true);
        }
        else
            initializeNext();
    }
}

void InitializationSequence::cleanUp()
{
    LOG_DEBUG(_logger, "Cleanup Initialization sequence");
    int i = 0;
    for (auto& item : _initializedItems)
    {
        // clang-format off
        auto msg = QString("Cleaning Initialization step (%1/%2) [%3]")
                           .arg(i + 1)
                           .arg(_initializedItems.count())
                           .arg(item->toString());
        // clang-format on
        LOG_DEBUG(_logger, msg);
        item->cleanUp();
        ++i;
    }
}

QString InitializationSequence::errorMessage() const
{
    if (_itemsToInitialize.isEmpty())
        return "";

    auto errorMessage = _itemsToInitialize.first()->errorMessage();
    return errorMessage.isEmpty() ? _exceptionMessage : errorMessage;
}
