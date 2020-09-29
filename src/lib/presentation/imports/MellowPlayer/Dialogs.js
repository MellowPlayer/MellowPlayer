.pragma library
.import QtQuick 2.15 as QtQuick
.import QtQuick.Controls 2.15 as QtQuickControls
.import QtQml 2.15 as QtQml

var mainWindow;

function create(qmlComponent, properties) {
    // load component
    var component = Qt.createComponent(Qt.resolvedUrl("Dialogs/" + qmlComponent));
    if (component.status !== QtQml.Component.Ready)
        throw "Error loading dialog component:" + component.errorString();

    // create object
    var dialog = component.createObject(mainWindow, properties);
    if (dialog == null)
        throw "Error creating dialog object";

    dialog.x = mainWindow.width / 2 - dialog.width / 2;
    dialog.y = mainWindow.height / 2 - dialog.height / 2 - 48;

    return dialog;
}

function open(qmlComponent, properties) {
    let dialog = create(qmlComponent, properties);
    dialog.open();
    return dialog;
}

function showError(title, message) {
    return open("MessageBoxDialog.qml", {
        "title": title,
        "message": message,
        "standardButtons": QtQuickControls.Dialog.Ok
    });
}

function askConfirmation(title, message, callback) {
    let dialog = open("MessageBoxDialog.qml", {
        "title": title,
        "message": message,
        "standardButtons": QtQuickControls.Dialog.Yes | QtQuickControls.Dialog.No
    });
    dialog.accepted.connect(() => callback(true));
    dialog.rejected.connect(() => callback(false));

    return dialog;
}

function reportIssue() {
    return open("ReportIssueDialog.qml", {});
}

function openWebPopup(request, profile) {
    let popup = create("BrowserDialog.qml", {});
    popup.open(request, profile);
    return popup;
}