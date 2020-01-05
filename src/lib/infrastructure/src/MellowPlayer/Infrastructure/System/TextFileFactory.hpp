#pragma once

#include <MellowPlayer/Infrastructure/System/ITextFileFactory.hpp>
#include <QString>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class TextFileFactory : public ITextFileFactory
    {
    public:
        TextFileFactory() = default;

        std::shared_ptr<ITextFile> create(const QString& path);
    };
}