.pragma library
.import QtQuick 2.15 as QtQuick
.import QtQuick.Controls 2.15 as QtQuickControls
.import QtQml 2.15 as QtQml

var mainWindow;

function open(qmlComponent, parent, properties) {
    // load component
    var component = Qt.createComponent(Qt.resolvedUrl("Dialogs/" + qmlComponent));
    if (component.status !== QtQml.Component.Ready)
        throw "Error loading dialog component:" + component.errorString();

    // create object
    var dialog = component.createObject(parent, properties);
    if (dialog == null)
        throw "Error creating dialog object";

    dialog.x = parent.width / 2 - dialog.width / 2;
    dialog.y = parent.height / 2 - dialog.height / 2 - 48;
    dialog.open();
    return dialog;
}

function showError(title, message) {
    console.log("MainWindow in dialogs", mainWindow)
    open("MessageBoxDialog.qml", mainWindow, {
        "title": title,
        "message": message,
        "standardButtons": QtQuickControls.Dialog.Ok
    });
}

function askConfirmation(title, message, callback) {
    var dialog = open("MessageBoxDialog.qml", mainWindow, {
        "title": title,
        "message": message,
        "standardButtons": QtQuickControls.Dialog.Yes | QtQuickControls.Dialog.No
    });
    dialog.accepted.connect(() => callback(true));
    dialog.rejected.connect(() => callback(false));
}