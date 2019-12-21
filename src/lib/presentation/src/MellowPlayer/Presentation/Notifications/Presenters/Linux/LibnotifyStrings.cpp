#include <MellowPlayer/Presentation/Notifications/Presenters/Linux/LibnotifyStrings.hpp>
#include <QtCore/QObject>

using namespace std;

string LibnotifyStrings::open() const
{
    return QObject::tr("Open").toStdString().c_str();
}
