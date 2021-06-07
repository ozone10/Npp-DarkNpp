# Notice

## Notepad++ 8.0 comes with support for the dark mode, so this plugin is not needed anymore.

# DarkNpp

[![Build status](https://img.shields.io/github/workflow/status/ozone10/Npp-DarkNpp/Build/master?logo=Github)](https://github.com/ozone10/Npp-DarkNpp)
[![Codacy Badge](https://img.shields.io/codacy/grade/3f6fef8152004cb990a3a9de4fc3ee10?logo=Codacy)](https://www.codacy.com/manual/ozone10/Npp-DarkNpp?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=ozone10/Npp-DarkNpp&amp;utm_campaign=Badge_Grade)
[![Latest release](https://img.shields.io/github/v/release/ozone10/Npp-DarkNpp?include_prereleases)](https://github.com/ozone10/Npp-DarkNpp/releases/latest)
[![Total downloads](https://img.shields.io/github/downloads/ozone10/Npp-DarkNpp/total.svg)](https://github.com/ozone10/Npp-DarkNpp/releases)
[![Licence](https://img.shields.io/github/license/ozone10/Npp-DarkNpp?color=9cf)](https://www.gnu.org/licenses/gpl-3.0.en.html)

[Notepad++](https://github.com/notepad-plus-plus/notepad-plus-plus) plugin that allows to use partially dark mode (theme) on Notepad++.  
Currently support: main title bar, some tooltips, some scroll bars, main tab background and context menus.

This is mainly for testing purposes.

* * *

<p align="center">
  <img src="https://i.imgur.com/sJm0Kke.png">
</p>

* * *

## Options

-   **useDark** - Option to choose mode.

    -   Value **0** - use light mode.
    -   Value **1** - use dark mode, default value.

-   **enableTabBG** - This is 'secret' setting, you can change it only via editing config file. 
This setting affect main tab background.

    -   Value **0** - disable tab background.
    -   Value **1** - enable tab background, default value.

* * *

## Configs

-   **Default:**  Dark mode

```ini
[DarkNpp]
useDark=1
enableTabBG=1
```
