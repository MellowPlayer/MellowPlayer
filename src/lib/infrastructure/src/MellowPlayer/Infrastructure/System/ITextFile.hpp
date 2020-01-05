#pragma once

#include <QString>
#include <QStringList>

namespace MellowPlayer::Infrastructure
{
    class ITextFile
    {
    public:
        virtual ~ITextFile() = default;

        virtual bool exists() const = 0;
        virtual QString read() const = 0;
        virtual void write(const QString& content) = 0;
    };
}