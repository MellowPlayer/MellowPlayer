#pragma once

#include <QString>

namespace MellowPlayer::Infrastructure
{
    class Asset
    {
    public:
        Asset();
        Asset(const QString& name, const QString& url);

        QString name() const;
        QString url() const;

        bool isWindowsInstaller() const;
        bool isDmg() const;

        bool isValid() const;

    private:
        QString _name;
        QString _url;
    };
}
