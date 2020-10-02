.pragma library
.import QtQuick 2.15 as QtQuick
.import QtQuick.Controls 2.15 as QtQuickControls
.import QtQml 2.15 as QtQml

var mainWindow;

function initialize(mainWindowInstance) {
    mainWindow = mainWindowInstance;
}

function keepCenteredOnMainWindow(dialog) {
    dialog.x = Qt.binding(() => (mainWindow.width - dialog.width) / 2);
    dialog.y = Qt.binding(() => (mainWindow.height - dialog.height) / 2);
}

function create(qmlComponent, properties) {
    // load component
    var component = Qt.createComponent(Qt.resolvedUrl("Dialogs/" + qmlComponent));
    if (component.status !== QtQml.Component.Ready)
        throw "Error loading dialog component:" + component.errorString();

    // create object
    var dialog = component.createObject(mainWindow, properties);
    if (dialog == null)
        throw "Error creating dialog object";

    keepCenteredOnMainWindow(dialog);

    return dialog;
}

function open(qmlComponent, properties) {
    let dialog = create(qmlComponent, properties);
    dialog.open();
    return dialog;
}

function showMessage(title, message, callback=undefined) {
    var dialog = open("MessageBoxDialog.qml", {
        "title": title,
        "message": message,
        "standardButtons": QtQuickControls.Dialog.Ok
    });
    if (callback) {
        dialog.accepted.connect(() => callback(true));
        dialog.rejected.connect(() => callback(false));
    }
    return dialog;
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

function openServiceSettings(service) {
    return open("StreamingServiceSettingsDialog.qml", {"service": service})
}

function showAbout() {
    return open("AboutDialog.qml", {})
}

function showFileDialog(title, nameFilters, callback) {
    var dialog = open("NativeFileDialog.qml", {"nameFilters": nameFilters, "title": title});
    dialog.accepted.connect(() => callback(true, dialog.fileUrl));
    dialog.rejected.connect(() => callback(false, ""));
    return dialog;
}