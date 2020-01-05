#pragma once

#include <QString>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class ITextFile;

    class ITextFileFactory
    {
    public:
        virtual ~ITextFileFactory() = default;

        virtual std::shared_ptr<ITextFile> create(const QString& path) = 0;
    };
}