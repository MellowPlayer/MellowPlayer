#pragma once

#include <MellowPlayer/Domain/UserScripts/UserScriptBase.hpp>
#include <QString>

#define FAKE_USER_SCRIPT_CODE "foo"

namespace MellowPlayer::Domain::Tests
{
    class FakeUserScript : public UserScriptBase
    {
    public:
        using UserScriptBase::UserScriptBase;

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

        void removeFile() override
        {
            _removed = true;
        }

        bool removed() const { return _removed; }


    private:
        bool _removed = false;
    };
}