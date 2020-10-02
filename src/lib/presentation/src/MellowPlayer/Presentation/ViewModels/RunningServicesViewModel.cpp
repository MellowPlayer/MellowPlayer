#include "RunningServicesViewModel.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

RunningServicesViewModel::RunningServicesViewModel(IStreamingServicesViewModel& streamingServicesViewModel)
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
    IStreamingServiceViewModel* item = _streamingServicesViewModel.currentService();
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
        item->setActive(true);
        _model.append(item);
        setCurrentIndex(_model.count() - 1);
    }
}

void RunningServicesViewModel::remove(IStreamingServiceViewModel* item)
{
    item->setActive(false);
    _model.remove(item);
    setCurrentIndex(_model.count() - 1);
    _streamingServicesViewModel.setCurrentService(_currentIndex == -1 ? nullptr : _model.at(_currentIndex));
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

void RunningServicesViewModel::clear()
{
    for (auto* service : _model)
    {
        service->setActive(false);
    }
    _model.clear();
    setCurrentIndex(-1);
}
