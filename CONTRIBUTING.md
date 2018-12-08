Contributing to MellowPlayer
============================

Reporting bugs or Wishes
------------------------

Report any bugs you encountered or any wishes on our [issue tracker](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues).

If you're reporting a bug, make sure that the bug has not already been reported (search in the issue tracker for similar issue) and that the answer to your issue is not already in the [FAQ section of the user documentation](https://mellowplayer.readthedocs.io/en/latest/users/faq.html)

If you haven't found an answer to your issue, feel free to report the bug on our issue tracker. If you do so, make sure to include the following information:

- Information about your **Operating system**. If you're on Linux, you'll need to specify the name of the distribution and the desktop environment you're using and whether you're using a native package or the AppImage.
- The **music streaming service** that you were using when you encountered the bug if it is related to a specific streaming service.
- A **clear description** of the bug with **steps to reproduce**.
- You should use **English** to describe your issue.
- Paste the application log between triple backquotes ```(About > Show Logs)```.


Setting up a development environment
------------------------------------

Read the how to setup page of the [wiki](https://gitlab.com/ColinDuquesnoy/MellowPlayer/wikis/%5BTutorial%5D-Setting-up-a-development-environment)

We also recommend you read the [architecture](https://gitlab.com/ColinDuquesnoy/MellowPlayer/wikis/architecture) and the [coding guidelines](https://gitlab.com/ColinDuquesnoy/MellowPlayer/wikis/coding-guidelines) pages before hacking on MellowPlayer.

Submitting a pull request
-------------------------

Here are the steps you need to follow to start working on MellowPlayer and submit your work
for evaluation or integration into the main project:

1. Fork the Repo on gitlab.
2. Create a feature or a bugfix branch before you start coding.
3. Add your name to AUTHORS.md
4. Format the code using ``scripts/beautify.py`` (run it from the root source directory).  
5. Push to your fork and submit a pull request to **the master branch**.


Adding support for a new service
--------------------------------

Web streaming service integration plugins are now written in pure javascript.

1. Create a new plugin using the wizard (see http://mellowplayer.readthedocs.io/en/latest/developers/plugins.html#create-a-new-plugin)
2. Edit ``metadata.ini`` (add correct url, name, version,...)
3. Edit ``description.html`` to describe the streaming service
4. Customise logo.svg
5. Implement the needed functions in ``integration.js``
6. Once your plugin works, submit a pull request to **the develop branch**.


Adding/Updating a new translation
---------------------------------

MellowPlayer translations are hosted on [transifex](https://www.transifex.com/colinduquesnoy/mellowplayer)

- Create an account at transifex
- Go to the project's homepage and click on the "Join the team" button
- If the language you want to work on does not exists yet, send us a language request. Once the request has been accepted, a new translation file for the requested language will be created automatically by transifex.
- To actually start translating, go to the project's home page on transifex and click on the translate button. This will open the translator tool where you can choose the resource and the language you want to work on.
