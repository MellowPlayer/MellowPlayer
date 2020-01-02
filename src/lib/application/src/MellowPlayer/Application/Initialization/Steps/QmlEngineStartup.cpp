#include "QmlEngineStartup.hpp"
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

QmlEngineStartup::QmlEngineStartup(IQmlApplicationEngine& qmlApplicationEngine)
        : _qmlApplicationEngine(qmlApplicationEngine)
{

}

void QmlEngineStartup::initialize(const ResultCallback& resultCallback)
{
    _qmlApplicationEngine.addImportPath("qrc:/MellowPlayer/imports");
    bool success = _qmlApplicationEngine.load(QUrl("qrc:/MellowPlayer/main.qml"));

    resultCallback(success);
}
