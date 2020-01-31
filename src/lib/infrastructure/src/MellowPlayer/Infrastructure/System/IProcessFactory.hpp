#pragma once

#include <memory>
#include <QString>

namespace MellowPlayer::Infrastructure
{
    class IProcess;

    class IProcessFactory
    {
    public:
        virtual ~IProcessFactory() = default;

        virtual std::shared_ptr<IProcess> create(const QString& name) = 0;
    };
}
