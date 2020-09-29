#include "RunningServicesViewModel.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

RunningServicesViewModel::RunningServicesViewModel(StreamingServicesViewModel& streamingServicesViewModel)
        : _streamingServicesViewModel(streamingServicesViewModel), _logger(Loggers::logger("RunningServices"))
{
    connect(&_streamingServicesViewModel, &IStreamingServicesViewModel::currentServiceChanged, this, &RunningServicesViewModel::onCurrentServiceChanged);
}

int RunningServicesViewModel::count() const
{
    return _model.count();
}

int RunningServicesViewModel::currentIndex() const
{
    return _currentIndex;
}
StreamingServiceListModel* RunningServicesViewModel::model()
{
    return &_model;
}

void RunningServicesViewModel::onCurrentServiceChanged()
{
    StreamingServiceViewModel* item = _streamingServicesViewModel.currentService();
    if (item == nullptr)
    {
        return;
    }

    LOG_DEBUG(_logger, "Current Service changed: " << item->name());

    if (_model.contains(item))
    {
        LOG_DEBUG(_logger, "Service already added:" << item->name());
        setCurrentIndex(_model.indexOf(item));
    }
    else
    {
        LOG_DEBUG(_logger, "Adding service:" << item->name());

        if (_model.isEmpty())
        {
            setCurrentIndex(-1);
        }

        item->setActive(true);
        _model.append(item);
        setCurrentIndex(_model.count() - 1);
    }
}

void RunningServicesViewModel::remove(StreamingServiceViewModel* item)
{
    item->setActive(false);
    _model.remove(item);
}

void RunningServicesViewModel::setCurrentIndex(int index)
{
    if (index != _currentIndex)
    {
        _currentIndex = index;
        emit currentIndexChanged();
        LOG_DEBUG(_logger, "Current index changed:" << index);
    }
}
