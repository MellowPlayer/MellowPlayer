#pragma once

#include "ApplicationDecorator.hpp"
#include <MellowPlayer/Domain/Logging/ILoggerFactory.hpp>

namespace MellowPlayer::Domain
{
    class ILoggerFactory;
}

namespace MellowPlayer::Infrastructure
{
    class ICommandLineArguments;

    class WithLogging : public ApplicationDecorator
    {
    public:
        WithLogging(const std::shared_ptr<IApplication>& application, ICommandLineArguments& commandLineArguments);

        void initialize() override;

    private:
        ;
        ICommandLineArguments& commandLineArguments_;
    };
}
