FROM fedora:latest

RUN dnf install -y flatpak flatpak-builder
RUN flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
RUN flatpak install -y flathub org.kde.Sdk/x86_64/5.12
RUN flatpak install -y flathub org.kde.Platform/x86_64/5.12
