# DarkNpp

[![Build status](https://img.shields.io/github/workflow/status/ozone10/Npp-DarkNpp/Build/master?logo=Github)](https://github.com/ozone10/Npp-DarkNpp)
[![Latest release](https://img.shields.io/github/v/release/ozone10/Npp-DarkNpp?include_prereleases)](https://github.com/ozone10/Npp-DarkNpp/releases/latest)
[![Total downloads](https://img.shields.io/github/downloads/ozone10/Npp-DarkNpp/total.svg)](https://github.com/ozone10/Npp-DarkNpp/releases)
[![Licence](https://img.shields.io/github/license/ozone10/Npp-DarkNpp?color=9cf)](https://www.gnu.org/licenses/gpl-3.0.en.html)

## NOTICE: Notepad++ 8.0 comes with support for the dark mode

Currently plugin is mainly used for testing mica effects.

* * *

[Notepad++](https://github.com/notepad-plus-plus/notepad-plus-plus) plugin that allows to use partially dark mode on Notepad++.  
Currently support: main title bar, some tooltips, some scroll bars and context menus.  
  
On Windows 11 allow to use mica effect on main window.

This is mainly for testing purposes.

* * *

<p align="center">
  <img src="https://i.imgur.com/sJm0Kke.png">
</p>

* * *

## Options

- **useDark** - Option to choose mode.

  - Value **0** - use light mode.
  - Value **1** - use dark mode, default value.

- **micaType** - Option to apply mica on main window. It is recommended to use `useDark=1`.

  - Value **0** - don't use mica, default value.
  - Value **1** - let system choose mica type, currently do nothing, secret value.
  - Value **2** - mica background.
  - Value **3** - acrylic background.
  - Value **4** - tabbed mica background.

* * *

## Configs

- **Default:**  Dark mode with no Mica

```ini
[DarkNpp]
useDark=1
micaType=0
```
