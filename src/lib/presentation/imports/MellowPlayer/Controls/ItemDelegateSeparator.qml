import QtQuick 2.15
import QtQuick.Layouts 1.15

import MellowPlayer 3.0

Rectangle {
    color: ThemeViewModel.isDark(ThemeViewModel.background) ? Qt.lighter(ThemeViewModel.background) : Qt.darker(ThemeViewModel.background, 1.1)
    height: 1
}
