#pragma once

#include <QObject>

namespace MellowPlayer::Infrastructure
{
    enum class UpdateChannel
    {
        Stable,
        Continuous,
    };
}

class UpdateChannelStringer : public QObject
{
    Q_OBJECT
public:
    QString stable() const
    {
        return tr("Stable");
    }
    QString beta() const
    {
        return tr("Beta");
    }

    QString continuous() const
    {
        return tr("Continuous");
    }

    QString toString(MellowPlayer::Infrastructure::UpdateChannel channelType) const
    {
        switch (channelType)
        {
        case MellowPlayer::Infrastructure::UpdateChannel::Continuous:
            return "Continuous";
        case MellowPlayer::Infrastructure::UpdateChannel::Stable:
        default:
            return "Stable";
        }
    }

    QString toTranslatedString(MellowPlayer::Infrastructure::UpdateChannel channelType) const
    {
        QString string;

        switch (channelType)
        {
        case MellowPlayer::Infrastructure::UpdateChannel::Stable:
            string = stable();
            break;
        case MellowPlayer::Infrastructure::UpdateChannel::Continuous:
            string = continuous();
            break;
        }

        return string;
    }

    MellowPlayer::Infrastructure::UpdateChannel fromString(const QString& channelName) const
    {
        MellowPlayer::Infrastructure::UpdateChannel channel;

        if (channelName == continuous())
            channel = MellowPlayer::Infrastructure::UpdateChannel::Continuous;
        else
            channel = MellowPlayer::Infrastructure::UpdateChannel::Stable;

        return channel;
    }
};
