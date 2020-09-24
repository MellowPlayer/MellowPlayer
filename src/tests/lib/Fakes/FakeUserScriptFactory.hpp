#pragma once

#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <Fakes/FakeUserScript.hpp>

namespace MellowPlayer::Domain::Tests
{
    class FakeUserScriptFactory : public IUserScriptFactory
    {
    public:
        FakeUserScriptFactory(const QString& code = "",
                              const QString& path = "",
                              const QString& name = "") : _code(code), _path(path), _name(name)
        {
        }

        IUserScript* create() override
        {
            _lastCreated = new FakeUserScript(_code, _path, _name);
            return _lastCreated;
        }

        FakeUserScript* lastCreated()
        {
            return _lastCreated;
        }

    private:
        QString _code, _path, _name;
        FakeUserScript* _lastCreated;
    };
}