import QtQuick 2.15
import QtQuick.Layouts 1.15

import MellowPlayer 3.0

Rectangle {
    color: ActiveTheme.isDark(ActiveTheme.background) ? Qt.lighter(ActiveTheme.background) : Qt.darker(ActiveTheme.background, 1.1)
    height: 1
}
