# DarkNpp

[![Build status](https://img.shields.io/github/actions/workflow/status/ozone10/Npp-DarkNpp/build.yml?branch=master&logo=Github)](https://github.com/ozone10/Npp-DarkNpp)
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
  <img src="https://i.imgur.com/UDTmTzj.png">
  <img src="https://i.imgur.com/fxBvFdi.png">
</p>

* * *

## Options

- **useDark** - Option to choose mode.

  - Value **0** - use light mode.
  - Value **1** - use dark mode, default value.

- **micaType** - Option to apply mica material or other effects on main window. It is recommended to use `useDark=1` for mica materials.

  - Value **0** - let system choose mica material and use it only on title bar, default value.
  - Value **1** - don't use mica material.
  - Value **2** - mica material.
  - Value **3** - mica acrylic material.
  - Value **4** - mica alternative material, found in tabbed applications.
  - Value **5** - acrylic effect, undocumented, works in Windows 10, but can cause lag while dragging or resizing window.

> [!IMPORTANT]  
> `micaType` with other value than `0` should not be used with HDR and ACM (Auto Color Management).
> Due to Windows bug using `micaType` with other value than `0` and/or with `useDark=0` can cause visual glitches, with HDR/ACM visual glitches are more severe (e.g. invisible controls).  
> It is also recommended when using with `micaType=1` to turn off Settings -> Personalization > Colors -> "Show accent color on title bars and window borders" setting.

* * *

## Configs

- **Default:**  Dark mode with no Mica

```ini
[DarkNpp]
useDark=1
micaType=0
```
