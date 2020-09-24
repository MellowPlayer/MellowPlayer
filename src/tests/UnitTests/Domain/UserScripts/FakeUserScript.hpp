#pragma once

#include <MellowPlayer/Domain/UserScripts/UserScriptBase.hpp>
#include <QString>

#define FAKE_USER_SCRIPT_CODE "foo"

namespace MellowPlayer::Domain::Tests
{
    class FakeUserScript : public UserScriptBase
    {
    public:
        bool import(const QString& path) override
        {
            return load(path);
        }

        bool load(const QString& path) override
        {
            UserScriptBase::_path = path;
            Domain::UserScriptBase::_code = FAKE_USER_SCRIPT_CODE;
            return true;
        }

        void removeFile() const override
        {
        }
    };
}