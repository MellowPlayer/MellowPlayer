
import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtWebEngine 1.10
import QtWebChannel 1.15

import MellowPlayer 3.0

import "../Dialogs.js" as Dialogs

Page {
    id: root

    required property StreamingService service

    property bool hasProprietaryCodecs: true
    property var userAgentSetting: App.settings.get(SettingKey.PRIVACY_USER_AGENT)
    property alias url: webView.url

    function updateImage() {
        console.debug("grabbing image")
        webView.grabToImage(function(result) {
            var path = root.service.getPreviewImageUrlForSave();
            if (result.saveToFile(path)) {
                console.debug("image grabbed: ", path)
                root.service.previewImageUrl = "file://" + path;
            }
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
        webView.url = root.service.url;
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

    Shortcut {
        enabled: MainWindow.fullScreen
        sequence: "Escape"

        onActivated: webView.fullScreenCancelled()
    }

    WebEngineView {
        id: webView

        property bool loaded: false
        property var networkProxy: root.service.networkProxy
        property var allUserScripts: d.getUserScripts()

        anchors.fill: parent

        url: root.service.url
        profile {
            httpUserAgent: root.userAgentSetting.value
            httpAcceptLanguage: getDefaultAcceptLanguage()

            onHttpUserAgentChanged: {
                console.log("new user agent: " + root.userAgentSetting.value);
                reload();
            }
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
        userScripts: allUserScripts
        zoomFactor: MainWindow.zoom.value
        webChannel: webChannel
        audioMuted: StreamingServices.currentService !== root.service

        onContextMenuRequested: (request) => {
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
        onAuthenticationDialogRequested: (request) => {
            request.accepted = true;
            Dialogs.open("Authentication.qml", {"request": request});
        }

        onJavaScriptDialogRequested: (request) => {
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
                default:
                    component = "Reload.qml"
                    break;
            }
            Dialogs.open(component, {"request": request});
            request.accepted = true;
        }
        onFormValidationMessageRequested: (request) => {
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
        onLoadingChanged: (loadRequest) => {
            webView.loaded = loadRequest.status === WebEngineLoadRequest.LoadSucceededStatus;
        }
        onFullScreenRequested: (request) => {
            MainWindow.fullScreen = request.toggleOn
            request.accept()

        }
        onNewViewRequested: (request) => {
            if (request.userInitiated) {
                console.log("opening web popup", request.requestedUrl)
                Dialogs.openWebPopup(request, webView.profile)
            }
        }
        onNetworkProxyChanged: reload()
        onAllUserScriptsChanged: reload()

        Component.onCompleted: {
           root.service.player.play.connect(() => { playerBridge.play() });
           root.service.player.pause.connect(() => { playerBridge.pause() });
           root.service.player.next.connect(() => { playerBridge.next() });
           root.service.player.previous.connect(() => { playerBridge.previous() });
           root.service.player.addToFavorites.connect(() => { playerBridge.addToFavorites() });
           root.service.player.removeFromFavorites.connect(() => { playerBridge.removeFromFavorites() });
           root.service.player.seekToPositionRequest.connect((newPosition) => { playerBridge.seekToPosition(newPosition) });
           root.service.player.changeVolumeRequest.connect((newVolume) => { playerBridge.changeVolume(newVolume) });
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

            onUpdateResultsChanged: root.service.player.setUpdateResults(updateResults);
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
            customUrl: root.service.url
            x: root.width / 2 - width / 2; y: -2; z: 1
            width: 500
            state: root.service.url.match("(@.*@)") !== null ? "visible" : "hidden"

            onReloadRequested: root.reload()
            onCustomUrlChanged: {
                if (customUrl !== root.service.url) {
                    root.service.url = customUrl
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

        QtObject {
            id: d
            property bool hasProprietaryCodecs: false

            function checkForProprietaryCodecs() {
                webView.runJavaScript("var a = document.createElement('audio'); !!(a.canPlayType && a.canPlayType('audio/mpeg;').replace(/no/, ''));", function(result) {
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

                for (var i = 0; i < root.service.userScripts.model.count; i++) {
                    var userScript = root.service.userScripts.model.get(i);
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

                onClicked: Dialogs.reportIssue()
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
