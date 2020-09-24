#pragma once

#include <MellowPlayer/Domain/UserScripts/UserScriptBase.hpp>

namespace MellowPlayer::Infrastructure
{
    class UserScriptDirectory
    {
    public:
        QString path() const;
        bool create() const;
        QString generateFileName() const;
    };

    class UserScript : public Domain::UserScriptBase
    {
    public:
        using Domain::UserScriptBase::UserScriptBase;

        bool import(const QString& sourcePath) override;
        bool load(const QString& path) override;
        void removeFile() override;
    };
}
