#pragma once

#include <MellowPlayer/Infrastructure/System/IProcessFactory.hpp>

namespace MellowPlayer::Infrastructure
{
    class ProcessFactory : public IProcessFactory
    {
    public:
        std::shared_ptr<IProcess> create(const QString& name) override;
    };
}
