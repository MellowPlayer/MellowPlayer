#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServiceListModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>

namespace MellowPlayer::Presentation
{
    class RunningServicesViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
        Q_PROPERTY(StreamingServiceListModel* model READ model CONSTANT)
    public:
        explicit RunningServicesViewModel(IStreamingServicesViewModel& streamingServicesViewModel);

        Q_INVOKABLE void remove(IStreamingServiceViewModel* item);

        void clear();

        int count() const;
        int currentIndex() const;
        StreamingServiceListModel* model();

    signals:
        void currentIndexChanged();

    private:
        void setCurrentIndex(int index);
        void onCurrentServiceChanged();

        int _currentIndex = -1;
        IStreamingServicesViewModel& _streamingServicesViewModel;
        StreamingServiceListModel _model;
        Domain::ILogger& _logger;
    };
}