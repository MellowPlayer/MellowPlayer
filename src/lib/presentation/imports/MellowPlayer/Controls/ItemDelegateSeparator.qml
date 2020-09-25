import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle {
    color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
    height: 1
}
