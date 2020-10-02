.pragma library
.import QtQuick 2.15 as QtQuick
.import QtWebEngine 1.10 as WebEngine


function isLoaded(loadRequest) {
    return loadRequest.status === WebEngine.WebEngineLoadRequest.LoadSucceededStatus;
}
