
import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtWebEngine 1.10
import QtWebChannel 1.15

import MellowPlayer 3.0

Page {
    id: root

    property StreamingService service
    property Player player: service.player

    property bool hasProprietaryCodecs: true
    property var userAgentSetting: App.settings.get(SettingKey.PRIVACY_USER_AGENT)
    property alias url: webView.url

    function updateImage() {
        if (!mainWindow.visible)
            return;
        root.grabToImage(function(result) {
            var path = service.getPreviewImageUrlForSave();
            if (result.saveToFile(path))
                service.previewImageUrl = "file://" + path;
        }, Qt.size(root.width, root.height));
    }

    function exitFullScreen() {
        webView.triggerWebAction(WebEngineView.ExitFullScreen);
    }

    function zoomIn() {
        MainWindow.zoom.increment();
    }

    function zoomOut() {
        MainWindow.zoom.decrement()
    }

    function resetZoom() {
        MainWindow.zoom.reset();
    }
    
    function goBack() {
        webView.goBack();
    }

    function goHome() {
        webView.url = webView.service.url;
        webView.reload();
    }

    function goForward() {
        webView.goForward();
    }

    function reload() {
        webView.reload();
    }

    function getDefaultAcceptLanguage() {
        var langAndCountry = Qt.locale().name.split(".")[0].replace("_", "-");
        var lang = langAndCountry.split("-")[0];
        var header = langAndCountry + ", " + lang + ";q=0.9, en;q=0.8, *;q=0.5";
        return header;
    }


    WebEngineView {
        id: webView

        property bool loaded: false
        
        anchors.fill: parent

        url: service.url
        profile {
            httpUserAgent: root.userAgentSetting.value
            httpAcceptLanguage: getDefaultAcceptLanguage()
        }
        settings {
            pluginsEnabled : true
            fullScreenSupportEnabled: true
            autoLoadImages: true
            javascriptEnabled: true
            javascriptCanAccessClipboard: true
            javascriptCanPaste: true
            errorPageEnabled: true
            autoLoadIconsForPage: true
            showScrollBars: App.settings.get(SettingKey.APPEARANCE_SHOW_SCROLLBARS).value
            playbackRequiresUserGesture: App.settings.get(SettingKey.MAIN_PLAYBACK_REQUIRES_USER_GESTURE).value

            onShowScrollBarsChanged: reload()
            onPlaybackRequiresUserGestureChanged: reload()
        }
        userScripts: d.getUserScripts()
        zoomFactor: MainWindow.zoom.value
        webChannel: webChannel
        audioMuted: StreamingServices.currentService !== null && StreamingServices.currentService.name !== root.service.name

        onContextMenuRequested: {
            request.accepted = true;
            contextMenu.x = request.x;
            contextMenu.y = request.y;
            contextMenu.canCopy = request.selectedText !== "";
            contextMenu.canPaste = request.isContentEditable && ClipBoard.canPaste();
            contextMenu.canUnselect = request.selectedText !== "";
            contextMenu.canGoBack = webView.canGoBack;
            contextMenu.canGoForward = webView.canGoForward;
            contextMenu.hasLink = request.linkText !== "";
            contextMenu.show();
        }
        onAuthenticationDialogRequested: function(request) {
            request.accepted = true;
            Dialogs.open("Authentication.qml", mainWindow, {"request": request});
        }
        onJavaScriptDialogRequested: function(request){
            var component = "";
            switch (request.type) {
                case JavaScriptDialogRequest.DialogTypeAlert:
                    component = "Alert.qml"
                    break;
                case JavaScriptDialogRequest.DialogTypeConfirm:
                    component = "Confirmation.qml"
                    break;
                case JavaScriptDialogRequest.DialogTypePrompt:
                    component = "Prompt.qml"
                    break;
                case JavaScriptDialogRequest.DialogTypeUnload:
                default:
                    component = "Reload.qml"
                    break;
            }
            Dialogs.open(component, mainWindow, {"request": request});
            request.accepted = true;
        }
        onFormValidationMessageRequested: function(request) {
            switch (request.type) {
                case FormValidationMessageRequest.Show:
                    request.accepted = true;
                    validationMessage.text = request.text;
                    validationMessage.x = request.anchor.x
                    validationMessage.y = request.anchor.y + request.anchor.height;
                    validationMessage.visible = true;
                    break;
                case FormValidationMessageRequest.Move:
                    break;
                case FormValidationMessageRequest.Hide:
                    validationMessage.visible = false;
                    break;
            }
        }
        onLoadingChanged: {
            if (loadRequest.status === WebEngineLoadRequest.LoadSucceededStatus) {
                webView.loaded = true;
                updateImage();
            }
            else {
                webView.loaded = false;
            }
        }
        onFullScreenRequested: mainWindow.toggleFullScreen(request)
        onNewViewRequested: mainWindow.openWebPopup(request, profile)

        Component.onDestruction: {
            webView.url = "about:blank"
        }


        Shortcut {
            enabled: mainWindow.visibility === ApplicationWindow.FullScreen
            sequence: "Escape"
            onActivated: root.fullScreenCancelled()
        }

        ValidationMessage {
            id: validationMessage
        }

        QtObject {
            id: playerBridge

            property var updateResults
            property bool isRunning: root.visible
            property bool broken: root.service.broken
            property bool loaded: webView.loaded
            property var exception

            signal play()
            signal pause()
            signal next()
            signal previous()
            signal addToFavorites()
            signal removeFromFavorites()
            signal seekToPosition(var position)
            signal changeVolume(double newVolume)

            onUpdateResultsChanged: root.player.setUpdateResults(updateResults);
            onBrokenChanged: {
                if (playerBridge.broken) {
                    console.warn("Unhandled exception in plugin: " + playerBridge.exception)
                }
                root.service.broken = playerBridge.broken
            }

            WebChannel.id: "player"
        }

        WebChannel {
            id: webChannel
            registeredObjects: [playerBridge]
        }

        CustomUrlPane {
            customUrl: service.url
            x: root.width / 2 - width / 2; y: -2; z: 1
            width: 500
            state: service.url.match("(@.*@)") !== null ? "visible" : "hidden"

            onReloadRequested: root.reload()
            onCustomUrlChanged: {
                if (customUrl !== service.url) {
                    service.url = customUrl
                }
            }
        }

        WebViewContextMenu {
            id: contextMenu

            onCopyRequested: webView.triggerWebAction(WebEngineView.Copy)
            onPasteRequested: webView.triggerWebAction(WebEngineView.Paste)
            onUnselectRequested: webView.triggerWebAction(WebEngineView.Unselect)

            onCopyLinkRequested: webView.triggerWebAction(WebEngineView.CopyLinkToClipboard)
            onOpenLinkRequested: webView.triggerWebAction(WebEngineView.OpenLinkInNewTab)

            onGoBackRequested: root.goBack()
            onGoForwardRequested: root.goForward()
            onReloadRequested: root.reload()
            onViewPageSourceRequested: webView.triggerWebAction(WebEngineView.ViewSource)
        }

        Connections {
            target: root.userAgentSetting

            function onValueChanged() { console.log("new user agent: " + userAgentSetting.value); reload(); }
        }

        Connections {
            target: root.service.networkProxy

             function onChanged() { reload() }
        }

        Connections {
            target: root.service.userScripts.model

            function onCountChanged() { reload() }
        }

        Connections {
            target: root.player

            function onPlay() { playerBridge.play() }
            function onPause() { playerBridge.pause() }
            function onNext() { playerBridge.next() }
            function onPrevious() { playerBridge.previous() }
            function onAddToFavorites() { playerBridge.addToFavorites() }
            function onRemoveFromFavorites() { playerBridge.removeFromFavorites() }
            function onSeekToPositionRequest(newPosition) { playerBridge.seekToPosition(newPosition) }
            function onChangeVolumeRequest() { playerBridge.changeVolume(newVolume) }
        }

        QtObject {
            id: d

            function checkForProprietaryCodecs() {
                runJavaScript("var a = document.createElement('audio'); !!(a.canPlayType && a.canPlayType('audio/mpeg;').replace(/no/, ''));", function(result) {
                    hasProprietaryCodecs = result;
                })
            }

            function getUserScripts() {
                var scripts = [];

                var webChannelScript = createMellowPlayerScriptFromSourceUrl("WebChannelAPI", "qrc:///qtwebchannel/qwebchannel.js");
                webChannelScript.injectionPoint = WebEngineScript.DocumentCreation;
                scripts.push(webChannelScript);
                scripts.push(createMellowPlayerScriptFromSourceUrl("MellowPlayerAPI", "qrc:/MellowPlayer/Presentation/mellowplayer.js"));
                scripts.push(createMellowPlayerScriptFromSourceCode("IntegrationPlugin", root.service.sourceCode));

                for (var i = 0; i < service.userScripts.model.count; i++) {
                    var userScript = service.userScripts.model.get(i);
                    scripts.push(createUserScriptFromCode(userScript.name, userScript.code));
                }

                return scripts;
            }

            function createUserScriptFromCode(name, sourceCode) {
                var webEngineScript = Qt.createQmlObject("import QtWebEngine 1.10; WebEngineScript {}", root, "webEngineScript.js");
                webEngineScript.name = name;
                webEngineScript.sourceCode = sourceCode;
                webEngineScript.injectionPoint = WebEngineScript.DocumentReady;
                return webEngineScript;
            }

            function createMellowPlayerScript(name) {
                var webEngineScript = Qt.createQmlObject("import QtWebEngine 1.10; WebEngineScript {}", root, "webEngineScript.js");
                webEngineScript.name = name;
                webEngineScript.injectionPoint = WebEngineScript.DocumentReady;
                webEngineScript.worldId = WebEngineScript.MainWorld;
                return webEngineScript;
            }

            function createMellowPlayerScriptFromSourceUrl(name, sourceUrl) {
                var webEngineScript = createMellowPlayerScript(name)
                webEngineScript.sourceUrl = sourceUrl;
                return webEngineScript;
            }

            function createMellowPlayerScriptFromSourceCode(name, sourceCode) {
                var webEngineScript = createMellowPlayerScript(name)
                webEngineScript.sourceCode = sourceCode;
                return webEngineScript;
            }
        }
    }

    footer: Pane {
        Material.background: Material.color(Material.Orange, Material.Shade600)
        Material.foreground: "white"

        visible: root.service.broken
        rightPadding: 0


        RowLayout {
            anchors.fill: parent

            Label {
                text: MaterialIcons.icon_warning
                font { family: MaterialIcons.family; pixelSize: 32 }
            }

            Label {
                Layout.leftMargin: 12

                text: root.service.hasKnownIssues ? qsTr("This plugin is broken. We are aware of the issue, <b>your help is welcome</b>!") : qsTr("This plugin might be broken and it looks like we are not aware of it. <b>Please report the issue!</b>")
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                text: qsTr("See issue on gitlab")
                visible: root.service.hasKnownIssues

                onClicked: root.service.openKnownIssue()
            }

            ToolButton {
                text: qsTr("Report broken plugin")
                visible: !root.service.hasKnownIssues

                onClicked: reportIssueDialog.open()
            }

            ToolButton {
                Layout.leftMargin: 6

                flat: true
                text: MaterialIcons.icon_close
                font { family: MaterialIcons.family; pixelSize: 20 }

                onClicked: root.footer.visible = false
            }
        }
    }
}