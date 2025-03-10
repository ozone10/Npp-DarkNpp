/*
  Copyright (C) 2020-2025 oZone10
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "StdAfx.h"

constexpr DWORD VER_1809 = 17763; // Windows 10 1809 (October 2018 Update)
constexpr DWORD VER_1903 = 18362; // Windows 10 1903 (May 2019 Update)

constexpr DWORD WIN10_22H2 = 19045; // Windows 10 22H2 (Last)

constexpr DWORD BUILD_WIN11 = 22000; // Windows 11 first "stable" build
constexpr DWORD BUILD_22H2 = 22621; // Windows 11 22H2 first to support mica properly

constexpr uint32_t DWMWA_MICA_EFFECT = 1029; // Windows 11 Mica undocumented for build 22000

enum class PreferredAppMode {
    Default,
    AllowDark,
    ForceDark,
    ForceLight,
    Max
};

enum WINDOWCOMPOSITIONATTRIB
{
    WCA_UNDEFINED = 0,
    WCA_NCRENDERING_ENABLED = 1,
    WCA_NCRENDERING_POLICY = 2,
    WCA_TRANSITIONS_FORCEDISABLED = 3,
    WCA_ALLOW_NCPAINT = 4,
    WCA_CAPTION_BUTTON_BOUNDS = 5,
    WCA_NONCLIENT_RTL_LAYOUT = 6,
    WCA_FORCE_ICONIC_REPRESENTATION = 7,
    WCA_EXTENDED_FRAME_BOUNDS = 8,
    WCA_HAS_ICONIC_BITMAP = 9,
    WCA_THEME_ATTRIBUTES = 10,
    WCA_NCRENDERING_EXILED = 11,
    WCA_NCADORNMENTINFO = 12,
    WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
    WCA_VIDEO_OVERLAY_ACTIVE = 14,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
    WCA_DISALLOW_PEEK = 16,
    WCA_CLOAK = 17,
    WCA_CLOAKED = 18,
    WCA_ACCENT_POLICY = 19,
    WCA_FREEZE_REPRESENTATION = 20,
    WCA_EVER_UNCLOAKED = 21,
    WCA_VISUAL_OWNER = 22,
    WCA_HOLOGRAPHIC = 23,
    WCA_EXCLUDED_FROM_DDA = 24,
    WCA_PASSIVEUPDATEMODE = 25,
    WCA_USEDARKMODECOLORS = 26,
    WCA_LAST = 27
};

struct WINDOWCOMPOSITIONATTRIBDATA
{
    WINDOWCOMPOSITIONATTRIB Attrib;
    PVOID pvData;
    SIZE_T cbData;
};

enum AccentTypes : int {
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,
    ACCENT_ENABLE_HOSTBACKDROP = 5,
    ACCENT_ENABLE_TRANSPARENT = 6
};

struct ACCENTPOLICY {
    AccentTypes nAccentState = AccentTypes::ACCENT_DISABLED;
    int32_t nFlags = 0;
    uint32_t nColor = 0;
    int32_t nAnimationId = 0;
};

using SWCA = bool (WINAPI*)(HWND hWnd, WINDOWCOMPOSITIONATTRIBDATA* wcaData);

const wchar_t NPP_PLUGIN_NAME[] = L"DarkNpp";
constexpr int nbFunc = 11;

void PluginInit();
void CommandMenuInit();

void LoadSettings();
void SavePluginParams();
void DarkCheckTag();
void SetMicaTagAuto();
void SetMicaTagNone();
void SetMicaTagMica();
void SetMicaTagAcrylic();
void SetMicaTagTabbed();
void SetTagAcrylic();
void MicaCheckTag();
void About();

bool IsAtLeastWin10Build(DWORD buildNumber);

void SetMode(HMODULE hUxtheme);
void SetTheme(HWND hWnd);
void SetTitleBar(HWND hWnd);
void SetTooltips(HWND hWnd);
BOOL CALLBACK ScrollBarChildProc(HWND hWnd, LPARAM lparam);

void SetMica(HWND hWnd);

void SetDarkNpp();
void SetMicaNpp();
