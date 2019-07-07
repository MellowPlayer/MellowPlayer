#!/usr/bin/env bash
flatpak-builder --repo=repo --force-clean _build com.gitlab.ColinDuquesnoy.MellowPlayer.yml
flatpak build-bundle repo MellowPlayer.flatpak com.gitlab.ColinDuquesnoy.MellowPlayer
