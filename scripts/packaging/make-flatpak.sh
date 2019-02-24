#!/usr/bin/env bash
flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
flatpak install -y flathub org.kde.Sdk/x86_64/5.12
flatpak install -y flathub org.kde.Platform/x86_64/5.12

flatpak-builder --repo=repo --force-clean _build com.gitlab.ColinDuquesnoy.MellowPlayer.yml

flatpak build-bundle repo MellowPlayer.flatpak com.gitlab.ColinDuquesnoy.MellowPlayer
