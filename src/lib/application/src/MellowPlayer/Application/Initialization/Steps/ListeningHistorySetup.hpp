#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class ListeningHistoryViewModel;
}

namespace MellowPlayer::Application
{
    class ListeningHistorySetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit ListeningHistorySetup(Presentation::ListeningHistoryViewModel& listeningHistory);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::ListeningHistoryViewModel& _listeningHistory;
    };
}
