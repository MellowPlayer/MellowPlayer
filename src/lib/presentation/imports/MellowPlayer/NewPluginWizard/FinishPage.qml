import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

WizardPage {
    id: root

    property string directory

    title: qsTr("Finished")
    description: qsTr("Plugin succesfully created!")
    goBackVisible: false
    goNextVisible: false
    finishVisible: true
    openPluginDirectoryVisible: true

    Label {
        anchors.fill: parent
        textFormat: "RichText"
        wrapMode: "WordWrap"
        text: qsTr("
<html>
    <head>
        <body>
            <p>Your plugin has been created to: <b>") + root.directory + qsTr("</b></p>
            <p>Your plugin should now appear in the list of available services, just select it and start working in it!</p>
            <p><span style=\" font-style:italic;\">Your code will be reloaded automatically whenever you save it using your preferred editor...</span></p>
        </body>
    </head>
</html>")
    }
}
