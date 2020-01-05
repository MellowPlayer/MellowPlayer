#pragma once

#include <MellowPlayer/Infrastructure/System/ITextFile.hpp>
#include <QString>
#include <QStringList>

namespace MellowPlayer::Infrastructure
{
    class TextFile : public ITextFile
    {
    public:
        TextFile(const QString& path);

        bool exists() const override;
        QString read() const;
        void write(const QString& content) override;

    private:
        QString _path;
    };

}