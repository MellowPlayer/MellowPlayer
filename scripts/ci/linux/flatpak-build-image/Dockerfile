FROM ubuntu:20.04

RUN apt update
RUN apt -y install software-properties-common
RUN add-apt-repository -y universe
RUN apt -y install keyboard-configuration
RUN apt install -y flatpak flatpak-builder
RUN flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
RUN flatpak install -y flathub org.kde.Sdk/x86_64/5.15
RUN flatpak install -y flathub org.kde.Platform/x86_64/5.15
RUN flatpak install -y flathub io.qt.qtwebengine.BaseApp/x86_64/5.15