# Change log

## [3.6.1](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.6.0) (2020-4-25)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.6.0...3.6.1)

**Fixed bugs:**

- Fix typo in Accept-Language patch.

## [3.6.0](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.6.0) (2020-4-25)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.10...3.6.0)

**Implemented enhancements:**

- Change to logging rules & related command line arguments [\#392](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/392)
- `Accept-Language` header support [\#372](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/372)
- Detection of broken plugins [\#340](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/340)
- Add ability to filter by favorite services [\#336](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/336)
- Remote control MellowPlayer instance from any other device [\#332](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/332)
- Pandora support [\#331](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/331)
- Add a filter bar to service selection screen [\#327](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/327)
- Show hidden player bar from contextual menu [\#314](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/314)

**Fixed bugs:**

- "origin" is a non-standard property emitted with PropertiesChanged [\#413](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/413)
- QtWebEngine (chromium) exposes useless MPRIS interface [\#407](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/407)
- Mixcloud integration plugin is broken [\#405](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/405)
- 2 config files are created: MellowPlayer.conf & MellowPlayer3.conf [\#381](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/381)
- org.mpris.MediaPlayer2.Player.Stop dbus method make toggle play/pause instead of stop [\#380](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/380)
- Restore window does not work in all cases [\#376](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/376)


**Merged merge requests:**

- MPRIS: Do not expose broken chromium mpris implementation [\#319](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/319) ([t.clastres](https://gitlab.com/t.clastres))
- Add Pandora integration [\#317](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/317) ([cautionoid](https://gitlab.com/cautionoid))

## [3.5.9](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.9) (2020-1-18)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.8...3.5.9)

**Fixed bugs:**

- Escape does not work to exit fullscreen (e.g. on Youtube) [\#398](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/398)
- Main tool bar don't close after making window fullscreen [\#393](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/393)
- Blank popup windows with Qt 5.14 [\#390](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/390)


## [3.5.8](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.8) (2019-12-27)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.7...3.5.8)

**Fixed bugs:**

- Logs are place in the wrong folder [\#389](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/389)


## [3.5.7](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.7) (2019-12-27)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.6...3.5.7)


**Fixed bugs:**

- Compilation issues with Qt 5.14 [\#385](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/385)

**Merged merge requests:**

- [Google Play Music] Parse times in both MM:SS and HH:MM:SS formats [\#316](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/316) ([cspiegel](https://gitlab.com/cspiegel))

## [3.5.6](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.6) (2019-11-24)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.5...3.5.6)

**Implemented enhancements:**

- Allow Multi-user single instances [\#333](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/333)

**Fixed bugs:**

- Keyboard shortcut not working in Quit dialog [\#377](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/377)
- Restore window does not work in all cases [\#376](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/376)
- TuneIn play/pause buttons in MellowPlayer interface not working [\#363](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/363)
- api url `https://api.bintray.com/packages/colinduquesnoy/MellowPlayer/Стабильный/files` is translated to current language [\#359](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/359)
- MellowPlayer not starting without output stream [\#358](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/358)
- Service order in services list page not saved after drag'n'drop [\#356](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/356)


**Closed issues:**

- [Windows 10] Google Play Music, Youtube prompts that the browser is not supported [\#360](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/360)


**Merged merge requests:**

- Add Apple Music [\#315](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/315) ([vanyasem](https://gitlab.com/vanyasem))

## [3.5.5](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.5) (2019-7-12)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.4...3.5.5)

**Fixed bugs:**

- Mpris: user rating is not updated when user toggle favorite song [\#352](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/352)
- Build failure with Qt 5.13 [\#351](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/351)
- Typo in French translation [\#350](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/350)
- Libnotify: unable to filter MellowPlayer notifications on KDE Plasma [\#345](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/345)

**Merged merge requests:**

- Update Tidal plugin [\#307](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/307) ([lapinskim](https://gitlab.com/lapinskim))
- Add Brain.fm [\#306](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/306) ([Schnouki](https://gitlab.com/Schnouki))

## [3.5.4](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.4) (2019-5-19)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.3...3.5.4)

**Implemented enhancements:**

- Update deezer theme to match their new UI design [\#305](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/305)

**Fixed bugs:**

- Deezer: love button does not work as expected when in a playlist, artist or album page [\#343](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/343)
- Listening History: Application is very slow to start when the history contains a lots of tracks. [\#342](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/342)
- Listening History: the same song keeps being added to the history [\#341](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/341)

**Merged merge requests:**

- fix(spotify): update UI element selectors [\#303](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/303) ([b0o](https://gitlab.com/b0o))

## [3.5.3](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.3) (2019-3-10)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.2...3.5.3)


**Fixed bugs:**

- [Deezer] Love button does not always work [\#326](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/326)
- [Youtube Music] Mute and skip ads options don't work [\#322](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/322)


**Closed issues:**

- [Amazon Music] Wrong icon format [\#324](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/324)


**Merged merge requests:**

- [Youtube] fix ads mute/skip and add popup auto close [\#302](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/302) ([NicolasGuilloux](https://gitlab.com/NicolasGuilloux))
- Add flatpak manifest [\#301](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/301) ([Cogitri](https://gitlab.com/Cogitri))

## [3.5.2](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.2) (2019-2-10)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.1...3.5.2)

**Closed issues:**

- compilation fails with GCC 9: redundant move in return statement [-Werror=redundant-move] [\#321](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/321)


## [3.5.1](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.1) (2019-2-5)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.5.0...3.5.1)


**Fixed bugs:**

- MPRIS: Invalid types used for Rate & Shuffle properties [\#320](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/320)
- Broken Spotify integration plugin [\#319](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/319)
- Window is not maximized anymore after exit from full-screen [\#318](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/318)
- Tooltip for "Next song" button is "true" [\#312](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/312)
- HiDPI scaling [\#271](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/271)

**Merged merge requests:**

- Add amazon music player [\#296](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/296) ([tibocat](https://gitlab.com/tibocat))

## [3.5.0](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/3.5.0) (2018-12-26)
[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/3.4.0...3.5.0)

**Implemented enhancements:**

- Add option to disable shortcuts [\#310](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/310) ([gombosg](https://github.com/gombosg))
- Make use of the gitlab service desk feature [\#304](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/304)
- Customize main toolbar content [\#302](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/302)
- Add shortcut to hide player bar [\#298](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/298)
- Option to hide scrollbar. [\#285](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/285) ([Ixoos](https://github.com/Ixoos))
- Add a start-minimized option [\#283](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/283)
- Show zoom widget in main menu [\#281](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/281)
- HiDPI scaling [\#271](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/271)
- Possibility to redefine tray icon [\#234](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/234)

**Fixed bugs:**

- Listening history section line separator is misplaced with Qt > 5.9.3 [\#305](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/305)
- MPRIS doesn't work with Spotify on Plasma [\#297](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/297)
- Unable to login to Yandex Music with Google account [\#287](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/287)


**Closed issues:**

- Use bintray rest API for the auto-update mechanism [\#303](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/303)
- QBS is deprecated: swich back to CMake [\#291](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/291)


**Merged merge requests:**

- Fix Spotify integration: update query selectors [\#292](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/292)
- Fixing TIDAL and Listening History [\#289](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/289) ([t-bond](https://github.com/t-bond))
- Netflix addon [\#270](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/270) ([NicolasGuilloux](https://github.com/NicolasGuilloux))
- YouTube Music Addon [\#268](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/268) ([NicolasGuilloux](https://github.com/NicolasGuilloux))

## [3.4.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.4.0) (2018-07-08)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.3.5...3.4.0)

**Implemented enhancements:**

- Add brazilian translations [\#256](https://github.com/ColinDuquesnoy/MellowPlayer/issues/256)
- Settings page for each plugin. [\#236](https://github.com/ColinDuquesnoy/MellowPlayer/issues/236)
- Youtube: automatically mute and skip ads [\#218](https://github.com/ColinDuquesnoy/MellowPlayer/issues/218)
- Stop automatically playing videos in MellowPlayer [\#130](https://github.com/ColinDuquesnoy/MellowPlayer/issues/130)
- Youtube plugin improvements [\#229](https://github.com/ColinDuquesnoy/MellowPlayer/pull/229) ([NicolasGuilloux](https://github.com/NicolasGuilloux))
- Add Yandex Music support [\#223](https://github.com/ColinDuquesnoy/MellowPlayer/pull/223) ([rustamzh](https://github.com/rustamzh))
- Google Play Music: handle cases when we can't go to next/previous [\#222](https://github.com/ColinDuquesnoy/MellowPlayer/pull/222) ([DmMlhch](https://github.com/DmMlhch))
- Google Play Music: add favorites support [\#220](https://github.com/ColinDuquesnoy/MellowPlayer/pull/220) ([DmMlhch](https://github.com/DmMlhch))

**Fixed bugs:**

- MPRIS2 Pause should only pause, not be a toggle and play if already paused [\#250](https://github.com/ColinDuquesnoy/MellowPlayer/issues/250)
- Unable to add user scripts on Windows 10 [\#249](https://github.com/ColinDuquesnoy/MellowPlayer/issues/249)
- Fix Qt 5.11 qml warnings [\#244](https://github.com/ColinDuquesnoy/MellowPlayer/issues/244)
- Listening history broken with Qt 5.11 [\#243](https://github.com/ColinDuquesnoy/MellowPlayer/issues/243)
- Mixcloud mixtape art sometimes missing or blurry in KDE Mpris Client [\#240](https://github.com/ColinDuquesnoy/MellowPlayer/issues/240)
- Open Dev Tools from right-click menu does not work. [\#239](https://github.com/ColinDuquesnoy/MellowPlayer/issues/239)
- Quit action from KDE's MPRIS player tray icon does not work [\#226](https://github.com/ColinDuquesnoy/MellowPlayer/issues/226)
- Web view scrollbar does not always work and is hard to use [\#225](https://github.com/ColinDuquesnoy/MellowPlayer/issues/225)
- Unable to maximize window on 1280x720 screens [\#221](https://github.com/ColinDuquesnoy/MellowPlayer/issues/221)
- Fix Spotify integration script [\#258](https://github.com/ColinDuquesnoy/MellowPlayer/pull/258) ([b0o](https://github.com/b0o))
- Youtube plugin improvements [\#229](https://github.com/ColinDuquesnoy/MellowPlayer/pull/229) ([NicolasGuilloux](https://github.com/NicolasGuilloux))
- Youtube: fix the art URL and the position [\#227](https://github.com/ColinDuquesnoy/MellowPlayer/pull/227) ([NicolasGuilloux](https://github.com/NicolasGuilloux))

**Closed issues:**

- Debian package for Ubuntu 18.04 [\#238](https://github.com/ColinDuquesnoy/MellowPlayer/issues/238)
- Improve README instructions for installing with qbs [\#230](https://github.com/ColinDuquesnoy/MellowPlayer/issues/230)

**Merged pull requests:**

- Google Play Music : add seeking support [\#219](https://github.com/ColinDuquesnoy/MellowPlayer/pull/219) ([DmMlhch](https://github.com/DmMlhch))
- Minor docs updates [\#215](https://github.com/ColinDuquesnoy/MellowPlayer/pull/215) ([axxx007xxxz](https://github.com/axxx007xxxz))

## [3.3.5](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.3.5) (2018-03-03)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.3.4...3.3.5)

**Fixed bugs:**

- MainWindow does not show up with Qt 5.10.1 [\#211](https://github.com/ColinDuquesnoy/MellowPlayer/issues/211)
- Service setting url not updated when clicking on another service [\#210](https://github.com/ColinDuquesnoy/MellowPlayer/issues/210)
- No notification if the song has no album art [\#209](https://github.com/ColinDuquesnoy/MellowPlayer/issues/209)

**Closed issues:**

- Add Greek translations [\#212](https://github.com/ColinDuquesnoy/MellowPlayer/issues/212)

**Merged pull requests:**

- Add Hypemachine support [\#208](https://github.com/ColinDuquesnoy/MellowPlayer/pull/208) ([bayang](https://github.com/bayang))

## [3.3.4](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.3.4) (2018-02-18)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.3.3...3.3.4)

**Implemented enhancements:**

- add bandcamp plugin [\#200](https://github.com/ColinDuquesnoy/MellowPlayer/pull/200) ([bayang](https://github.com/bayang))

**Fixed bugs:**

- JS errors in ympd [\#207](https://github.com/ColinDuquesnoy/MellowPlayer/issues/207)
- JS errors in Google Play Music [\#206](https://github.com/ColinDuquesnoy/MellowPlayer/issues/206)
- JS Error on Deezer login page [\#205](https://github.com/ColinDuquesnoy/MellowPlayer/issues/205)
- mellowplayer-3.3.3 compilation fails on Fedora 27 [\#196](https://github.com/ColinDuquesnoy/MellowPlayer/issues/196)

**Closed issues:**

- \[Documentation\] Broken links to ReadTheDocs in some files [\#201](https://github.com/ColinDuquesnoy/MellowPlayer/issues/201)
- error message when generating man/html page with sphinx [\#199](https://github.com/ColinDuquesnoy/MellowPlayer/issues/199)

**Merged pull requests:**

- Fix broken links to ReadTheDocs in some files [\#202](https://github.com/ColinDuquesnoy/MellowPlayer/pull/202) ([andrewjmetzger](https://github.com/andrewjmetzger))

## [3.3.3](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.3.3) (2018-02-10)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.3.2...3.3.3)

**Fixed bugs:**

- AppImage startup fails on 3.3.3  [\#195](https://github.com/ColinDuquesnoy/MellowPlayer/issues/195)
- Compilation issues with GCC8 [\#193](https://github.com/ColinDuquesnoy/MellowPlayer/issues/193)

## [3.3.2](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.3.2) (2018-01-28)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.3.1...3.3.2)

**Fixed bugs:**

- openSUSE package is broken [\#192](https://github.com/ColinDuquesnoy/MellowPlayer/issues/192)

## [3.3.1](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.3.1) (2018-01-14)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.3.0...3.3.1)

**Fixed bugs:**

- Missing QtWebChannel dependency on Ubuntu \(version 3.3.1\) [\#190](https://github.com/ColinDuquesnoy/MellowPlayer/issues/190)
- Build issues when packaging version 3.3.0 [\#188](https://github.com/ColinDuquesnoy/MellowPlayer/issues/188)

## [3.3.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.3.0) (2018-01-14)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.2.0...3.3.0)

**Implemented enhancements:**

- Add Russian localization [\#186](https://github.com/ColinDuquesnoy/MellowPlayer/issues/186)
- \[New Service\] Add support for player.fm [\#182](https://github.com/ColinDuquesnoy/MellowPlayer/issues/182)
- Use custom dialogs for WebEngine dialogs [\#180](https://github.com/ColinDuquesnoy/MellowPlayer/issues/180)
- Improve centering of services overview grid [\#178](https://github.com/ColinDuquesnoy/MellowPlayer/issues/178)
- Improve web views management [\#177](https://github.com/ColinDuquesnoy/MellowPlayer/issues/177)
- Redesign service settings [\#176](https://github.com/ColinDuquesnoy/MellowPlayer/issues/176)
- Use QtWebChannel to interact with streaming service web page [\#172](https://github.com/ColinDuquesnoy/MellowPlayer/issues/172)
- Add Network Proxy Support [\#170](https://github.com/ColinDuquesnoy/MellowPlayer/issues/170)

**Fixed bugs:**

- Broken Wynk integration plugin [\#181](https://github.com/ColinDuquesnoy/MellowPlayer/issues/181)
- Scrolling in the service settings page is slow and emits lots of QML warnings [\#175](https://github.com/ColinDuquesnoy/MellowPlayer/issues/175)
- Quit shortcut doesn't work anymore [\#174](https://github.com/ColinDuquesnoy/MellowPlayer/issues/174)
- CMake developper warning [\#173](https://github.com/ColinDuquesnoy/MellowPlayer/issues/173)
- Fail to build when Qt was linked using GNU Gold Linker [\#171](https://github.com/ColinDuquesnoy/MellowPlayer/issues/171)

**Closed issues:**

- Update copyright year [\#185](https://github.com/ColinDuquesnoy/MellowPlayer/issues/185)

## [3.2.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.2.0) (2017-12-18)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.1.0...3.2.0)

**Implemented enhancements:**

- Allow to customize notifications per service [\#158](https://github.com/ColinDuquesnoy/MellowPlayer/issues/158)
- Add support for compiling on FreeBSD [\#157](https://github.com/ColinDuquesnoy/MellowPlayer/issues/157)
- Add a way to easily open the logs folder [\#156](https://github.com/ColinDuquesnoy/MellowPlayer/issues/156)
- Use system qxtglobalshortcut library if available [\#151](https://github.com/ColinDuquesnoy/MellowPlayer/issues/151)
- Add missing QtWebEngine command line arguments [\#150](https://github.com/ColinDuquesnoy/MellowPlayer/issues/150)
-  Appdata.xml file for Gnome Software Center  [\#149](https://github.com/ColinDuquesnoy/MellowPlayer/issues/149)
- Improve state restoration [\#141](https://github.com/ColinDuquesnoy/MellowPlayer/issues/141)

**Fixed bugs:**

- Cannot change settings on Windows 7 [\#168](https://github.com/ColinDuquesnoy/MellowPlayer/issues/168)
- MellowPlayer does not start anymore with Qt 5.10 [\#167](https://github.com/ColinDuquesnoy/MellowPlayer/issues/167)
- Single application instance sometimes does not work [\#161](https://github.com/ColinDuquesnoy/MellowPlayer/issues/161)
- Broken Tidal integration plugin [\#160](https://github.com/ColinDuquesnoy/MellowPlayer/issues/160)
- "You are now in fullscreen" message shown when quitting fullscreen mode [\#159](https://github.com/ColinDuquesnoy/MellowPlayer/issues/159)
- Notifications on Ubuntu are not showing properly [\#153](https://github.com/ColinDuquesnoy/MellowPlayer/issues/153)
- \[Windows\] Blank screen on Deezer [\#152](https://github.com/ColinDuquesnoy/MellowPlayer/issues/152)
- \[UI Regression\] Service grid is not centered anymore [\#147](https://github.com/ColinDuquesnoy/MellowPlayer/issues/147)
- Deezer love button broken [\#146](https://github.com/ColinDuquesnoy/MellowPlayer/issues/146)
- Player window does not show on macOs High Sierra [\#144](https://github.com/ColinDuquesnoy/MellowPlayer/issues/144)
- Logout cancelled by MellowPlayer [\#143](https://github.com/ColinDuquesnoy/MellowPlayer/issues/143)

**Closed issues:**

- Debian package for Ubuntu 17.10 [\#137](https://github.com/ColinDuquesnoy/MellowPlayer/issues/137)
- Broken AppImage [\#166](https://github.com/ColinDuquesnoy/MellowPlayer/issues/166)

**Merged pull requests:**

- Plex plugin: initial bring up [\#135](https://github.com/ColinDuquesnoy/MellowPlayer/pull/135) ([Cogitri](https://github.com/Cogitri))

## [3.1.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.1.0) (2017-10-21)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/3.0.0...3.1.0)

**Implemented enhancements:**

- Add ambiance theme for ubuntu [\#138](https://github.com/ColinDuquesnoy/MellowPlayer/issues/138)
- Add support for ympd [\#118](https://github.com/ColinDuquesnoy/MellowPlayer/issues/118)
- Add a dustbin icon where users can drag a service icon to disable the service [\#116](https://github.com/ColinDuquesnoy/MellowPlayer/issues/116)
- Add ability to specify list of supported platforms for a plugin [\#115](https://github.com/ColinDuquesnoy/MellowPlayer/issues/115)
- \[Feature request\] Zoom [\#114](https://github.com/ColinDuquesnoy/MellowPlayer/issues/114)
- Integrate Catalan translation [\#111](https://github.com/ColinDuquesnoy/MellowPlayer/issues/111)
- Integrate Spanish translation [\#110](https://github.com/ColinDuquesnoy/MellowPlayer/issues/110)
- Add a function to change the user agent in the settings [\#102](https://github.com/ColinDuquesnoy/MellowPlayer/issues/102)
- Add Radionomy [\#100](https://github.com/ColinDuquesnoy/MellowPlayer/issues/100)
- Add JAMENDO MUSIC [\#83](https://github.com/ColinDuquesnoy/MellowPlayer/issues/83)
- Add shortcut to open web developer tools [\#80](https://github.com/ColinDuquesnoy/MellowPlayer/issues/80)
- MPRIS: Use favorite song info [\#79](https://github.com/ColinDuquesnoy/MellowPlayer/issues/79)
- Add hearthis.at [\#75](https://github.com/ColinDuquesnoy/MellowPlayer/issues/75)
- Add support for user scripts [\#69](https://github.com/ColinDuquesnoy/MellowPlayer/issues/69)

**Fixed bugs:**

- Drag & Drop to trash icon does not always work [\#136](https://github.com/ColinDuquesnoy/MellowPlayer/issues/136)
- TuneIn integration broken [\#133](https://github.com/ColinDuquesnoy/MellowPlayer/issues/133)
- Mixcloud integration plugin broken [\#108](https://github.com/ColinDuquesnoy/MellowPlayer/issues/108)

**Closed issues:**

- mellowplayer.desktop does not pass desktop-file-validate [\#104](https://github.com/ColinDuquesnoy/MellowPlayer/issues/104)
- Buttons not translatable [\#101](https://github.com/ColinDuquesnoy/MellowPlayer/issues/101)

**Merged pull requests:**

- Add favorites support to soundcloud plugin [\#134](https://github.com/ColinDuquesnoy/MellowPlayer/pull/134) ([Cogitri](https://github.com/Cogitri))
- GPM: improve playback status detection [\#129](https://github.com/ColinDuquesnoy/MellowPlayer/pull/129) ([terinjokes](https://github.com/terinjokes))
- Add Wynk Music plugin [\#125](https://github.com/ColinDuquesnoy/MellowPlayer/pull/125) ([shreyanshk](https://github.com/shreyanshk))
- Update Readme.md [\#123](https://github.com/ColinDuquesnoy/MellowPlayer/pull/123) ([ZeroDot1](https://github.com/ZeroDot1))
- README.md updated [\#122](https://github.com/ColinDuquesnoy/MellowPlayer/pull/122) ([ZeroDot1](https://github.com/ZeroDot1))
- Anghami [\#120](https://github.com/ColinDuquesnoy/MellowPlayer/pull/120) ([mahmoudhossam](https://github.com/mahmoudhossam))
- Add a Gitter chat badge to README.md [\#119](https://github.com/ColinDuquesnoy/MellowPlayer/pull/119) ([gitter-badger](https://github.com/gitter-badger))
- Feature pocketcasts plugin [\#117](https://github.com/ColinDuquesnoy/MellowPlayer/pull/117) ([kolletzki](https://github.com/kolletzki))
- Fix Buttons not translatable / archlinux-env-setup.sh [\#103](https://github.com/ColinDuquesnoy/MellowPlayer/pull/103) ([ZeroDot1](https://github.com/ZeroDot1))

## [3.0.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/3.0.0) (2017-08-13)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/2.99.0...3.0.0)

**Fixed bugs:**

- Last page of plugin wizard is not translatable [\#97](https://github.com/ColinDuquesnoy/MellowPlayer/issues/97)

## [2.99.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/2.99.0) (2017-08-06)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/2.95.0...2.99.0)

**Implemented enhancements:**

- Check audio codecs support [\#82](https://github.com/ColinDuquesnoy/MellowPlayer/issues/82)
- Command-Line flags to toggle/get song favorite status [\#77](https://github.com/ColinDuquesnoy/MellowPlayer/issues/77)
- Add copy and paste for the context menu [\#73](https://github.com/ColinDuquesnoy/MellowPlayer/issues/73)
- Add a menu entry to report issue on github [\#65](https://github.com/ColinDuquesnoy/MellowPlayer/issues/65)
- Limit ListeningHistory [\#64](https://github.com/ColinDuquesnoy/MellowPlayer/issues/64)
- Add Tidal support [\#59](https://github.com/ColinDuquesnoy/MellowPlayer/issues/59)
- Add youtube support [\#58](https://github.com/ColinDuquesnoy/MellowPlayer/issues/58)
- ListeningHistory: smarter song tracking [\#55](https://github.com/ColinDuquesnoy/MellowPlayer/issues/55)
- Call cache cleaner when closing MellowPlayer [\#54](https://github.com/ColinDuquesnoy/MellowPlayer/issues/54)
- Add global menu on OSX [\#53](https://github.com/ColinDuquesnoy/MellowPlayer/issues/53)
- Internationalisation [\#52](https://github.com/ColinDuquesnoy/MellowPlayer/issues/52)
- Add ability to disable a service [\#51](https://github.com/ColinDuquesnoy/MellowPlayer/issues/51)
- Add hotkey to restore window [\#50](https://github.com/ColinDuquesnoy/MellowPlayer/issues/50)
- Add theme setting [\#49](https://github.com/ColinDuquesnoy/MellowPlayer/issues/49)
- Check for update mechanism [\#48](https://github.com/ColinDuquesnoy/MellowPlayer/issues/48)
- Add command line options [\#43](https://github.com/ColinDuquesnoy/MellowPlayer/issues/43)
- Allow to reorder services via drag & drop [\#42](https://github.com/ColinDuquesnoy/MellowPlayer/issues/42)
- Plugin wizard [\#38](https://github.com/ColinDuquesnoy/MellowPlayer/issues/38)

**Fixed bugs:**

- Youtube fullscreen does not work [\#87](https://github.com/ColinDuquesnoy/MellowPlayer/issues/87)
- High DPI issue [\#71](https://github.com/ColinDuquesnoy/MellowPlayer/issues/71)
- Soundcloud integration broken [\#60](https://github.com/ColinDuquesnoy/MellowPlayer/issues/60)

**Closed issues:**

- Windows Packaging [\#44](https://github.com/ColinDuquesnoy/MellowPlayer/issues/44)
- Use QtQuickControls2 dialog set for QtWebengine [\#67](https://github.com/ColinDuquesnoy/MellowPlayer/issues/67)

**Merged pull requests:**

- German translation finished. [\#89](https://github.com/ColinDuquesnoy/MellowPlayer/pull/89) ([ZeroDot1](https://github.com/ZeroDot1))

## [2.95.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/2.95.0) (2017-06-24)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/2.2.5...2.95.0)

**Closed issues:**

- OSX Packaging [\#45](https://github.com/ColinDuquesnoy/MellowPlayer/issues/45)



\* *This Change Log was automatically generated by [github_changelog_generator](https://github.com/skywinder/Github-Changelog-Generator)*