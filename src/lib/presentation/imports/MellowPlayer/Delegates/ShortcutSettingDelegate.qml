import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

ItemDelegate {
    id: root

    bottomPadding: 3; topPadding: 3
    enabled: root.enabled
    hoverEnabled: true
    
    required property bool isEnabled
    required property string name
    required property string toolTip
    required property string type
    required property string qmlComponent
    required property Setting qtObject

    onClicked: keySequenceEdit.forceActiveFocus()

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: parent.leftPadding
        anchors.rightMargin: parent.rightPadding
        anchors.topMargin: parent.topPadding
        anchors.bottomMargin: parent.bottomPadding

        Label {
            text: SettingsTranslator.translateName(root.name)

            Layout.fillWidth: true
        }

        TextField {
            id: keySequenceEdit
            hoverEnabled: false

            property int nbKeyPressed: 0
            property int newKey: 0
            property int newMofifiers: 0
            property string memText: text

            onTextChanged: root.qtObject.value = text
            text: root.qtObject.value

            Keys.onPressed: {
                if (event.key === Qt.Key_Backspace|| event.key === Qt.Key_Delete) {
                    timerRecording.stop();
                    placeholderText = ""
                    text = "";
                    return
                }

                nbKeyPressed += 1

                if (nbKeyPressed > 3) {
                    nbKeyPressed = 3
                }

                if( nbKeyPressed == 1) {
                    startRecording()
                }
                placeholderText = root.qtObject.keySequenceToString(event.key, event.modifiers);
                newKey = event.key;
                newMofifiers = event.modifiers
                event.accepted = true;
                timerRecording.restart();
            }
            Keys.onReleased: {
                nbKeyPressed -= 1;
                if (event.key === Qt.Key_Escape)
                    cancelRecording();
                else if( nbKeyPressed == 0)
                    finishRecording();
                event.accepted = true;
            }

            function startRecording() {
                memText = text;
                text = ""
                placeholderText = ""
            }

            function cancelRecording() {
                placeholderText = ""
                text = memText;
                nbKeyPressed = 0;
                timerRecording.stop();
            }

            function finishRecording() {
                if (root.qtObject.isValidKeySequence(newKey, newMofifiers))
                    text = placeholderText
                else
                    text = memText;
                placeholderText = ""
                nbKeyPressed = 0;
                timerRecording.stop();
            }

            Tooltip {
                text: SettingsTranslator.translateToolTip(root.toolTip)
            }


            Timer {
                id: timerRecording
                running: true
                interval: 2000
            }
        }
    }

}
