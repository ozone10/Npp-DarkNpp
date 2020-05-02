/*
  Copyright (C) 2020 oZone
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

#include "PluginDefinition.h"

FuncItem funcItem[nbFunc];
NppData nppData;

wchar_t pluginConfigPath[MAX_PATH] = { '\0' };
wchar_t iniFilePath[MAX_PATH] = { '\0' };
const wchar_t sectionName[] = L"DarkNpp";

bool enableDark = false;

const int menuItemEnableDark = 0;

//void pluginInit(HANDLE /*hModule*/)
//{
//}

//void pluginCleanUp()
//{
//}

void commandMenuInit()
{
    funcItem[menuItemEnableDark] = { L"Enable Dark Mode", DarkCheckTag, 0, enableDark, nullptr };
    funcItem[1] = { L"Refresh", SetDarkNpp, 0, false, nullptr };
    funcItem[2] = { L"&About...", About, 0, false, nullptr };
}

//void commandMenuCleanUp()
//{
//}

void LoadSettings()
{
    ::SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, reinterpret_cast<LPARAM>(pluginConfigPath));
    wcscpy_s(iniFilePath, pluginConfigPath);
    ::PathAppend(iniFilePath, TEXT("\\DarkNpp.ini"));

    enableDark = ::GetPrivateProfileInt(sectionName, L"useDark", 1, iniFilePath) != 0;
}

void SavePluginParams()
{
    funcItem[menuItemEnableDark]._init2Check = enableDark;
    ::WritePrivateProfileString(sectionName, L"useDark", enableDark ? L"1" : L"0", iniFilePath);
}

void DarkCheckTag()
{
    enableDark = !enableDark;
    ::CheckMenuItem(::GetMenu(nppData._nppHandle), funcItem[menuItemEnableDark]._cmdID, MF_BYCOMMAND | (enableDark ? MF_CHECKED : MF_UNCHECKED));
    SetDarkNpp();
    SavePluginParams();
}

void About()
{
    ::MessageBox(
        NULL,
        L"This is Dark Theme Notepad++ test.\n"
        "Plugin is using undocumented WINAPI.\n"
        "@2020 � oZone",
        L"About",
        MB_OK);
}

inline bool IsAtLeastWin10Build(DWORD buildNumber)
{
    if (!IsWindows10OrGreater())
    {
        return false;
    }

    auto mask = VerSetConditionMask(0, VER_BUILDNUMBER, VER_GREATER_EQUAL);

    OSVERSIONINFOEXW osvi;
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    osvi.dwBuildNumber = buildNumber;
    return VerifyVersionInfo(&osvi, VER_BUILDNUMBER, mask) != FALSE;
}

void SetMode(HMODULE hUxtheme, bool useDark)
{
    const auto ord135 = GetProcAddress(hUxtheme, MAKEINTRESOURCEA(135));

    if (IsAtLeastWin10Build(VER_1903))
    {
        using SPAM = PreferredAppMode(WINAPI*)(PreferredAppMode appMode);
        const auto _SetPreferredAppMode = reinterpret_cast<SPAM>(ord135);

        auto appMode = useDark ? PreferredAppMode::ForceDark : PreferredAppMode::ForceLight;

        if (_SetPreferredAppMode != nullptr)
        {
            _SetPreferredAppMode(appMode);
        }
    }
    else
    {
        using ADMFA = bool (WINAPI*)(bool allow);
        const auto _AllowDarkModeForApp = reinterpret_cast<ADMFA>(ord135);

        if (_AllowDarkModeForApp != nullptr)
        {
            _AllowDarkModeForApp(true);
        }
    }
}

void SetTheme(HWND hWnd, bool useDark)
{
    const auto hUxtheme = LoadLibraryEx(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_USER_DIRS | LOAD_LIBRARY_SEARCH_SYSTEM32);

    if (hUxtheme == nullptr)
    {
        return;
    }

    using ADMFW = bool (WINAPI*)(HWND, bool);
    using FMT = void (WINAPI*)();

    const auto _AllowDarkModeForWindow = reinterpret_cast<ADMFW>(GetProcAddress(hUxtheme, MAKEINTRESOURCEA(133)));
    const auto _FlushMenuThemes = reinterpret_cast<FMT>(GetProcAddress(hUxtheme, MAKEINTRESOURCEA(136)));

    if (_AllowDarkModeForWindow != nullptr && _FlushMenuThemes != nullptr)
    {
        _AllowDarkModeForWindow(hWnd, useDark);
        SetMode(hUxtheme, useDark);
        _FlushMenuThemes();
    }

    FreeLibrary(hUxtheme);
}

void SetTitleBar(HWND hWnd, bool useDark)
{
    BOOL dark = useDark ? TRUE : FALSE;

    if (IsAtLeastWin10Build(VER_1903))
    {
        const auto hUser32 = LoadLibraryEx(L"user32.dll", nullptr, LOAD_LIBRARY_SEARCH_USER_DIRS | LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (hUser32)
        {
            using SWCA = bool (WINAPI*)(HWND hWnd, WINDOWCOMPOSITIONATTRIBDATA* wcaData);
            const auto _SetWindowCompositionAttribute = reinterpret_cast<SWCA>(GetProcAddress(hUser32, "SetWindowCompositionAttribute"));

            if (_SetWindowCompositionAttribute != nullptr)
            {
                WINDOWCOMPOSITIONATTRIBDATA data = { WCA_USEDARKMODECOLORS, &dark, sizeof(dark) };

                if (_SetWindowCompositionAttribute(hWnd, &data))
                {
                    FreeLibrary(hUser32);
                    return;
                }
            }

            FreeLibrary(hUser32);
        }
    }

    SetProp(hWnd, L"UseImmersiveDarkModeColors", reinterpret_cast<HANDLE>(static_cast<INT_PTR>(dark)));
}

//BOOL CALLBACK TooltipsChildProc(HWND hWnd, LPARAM lparam)
//{
//    const auto useDark = static_cast<BOOL>(lparam) == TRUE;
//
//    WCHAR className[64] = { 0 };
//
//    if (GetClassName(hWnd, className, _countof(className)) > 0)
//    {
//        if (wcscmp(className, TOOLTIPS_CLASS) == 0)
//        {
//            SetWindowTheme(hWnd, useDark ? L"DarkMode_Explorer" : nullptr, nullptr);
//        }
//        else if (wcscmp(className, TOOLBARCLASSNAME) == 0)
//        {
//            const auto hTip = reinterpret_cast<HWND>(SendMessage(hWnd, TB_GETTOOLTIPS, NULL, NULL));
//            if (hTip != nullptr)
//            {
//                SetWindowTheme(hTip, useDark ? L"DarkMode_Explorer" : nullptr, nullptr);
//            }
//        }
//    }
//
//    return TRUE;
//}

//void SetTooltips(HWND hWnd, bool useDark)
//{
//     EnumChildWindows(hWnd, &TooltipsChildProc, MAKELPARAM(useDark ? TRUE : FALSE, 0));
//}

void SetTooltips(HWND hWnd, bool useDark)
{
    DWORD ProcessID = 0;
    GetWindowThreadProcessId(hWnd, &ProcessID);
    HWND hTooltip = nullptr;
    do {
        hTooltip = FindWindowEx(nullptr, hTooltip, nullptr, nullptr);
        DWORD checkProcessID = 0;
        GetWindowThreadProcessId(hTooltip, &checkProcessID);

        if (checkProcessID == ProcessID)
        {
            WCHAR className[64] = { 0 };

            if (GetClassName(hTooltip, className, _countof(className)) > 0)
            {
                if (wcscmp(className, TOOLTIPS_CLASS) == 0)
                {
                    SetWindowTheme(hTooltip, useDark ? L"DarkMode_Explorer" : nullptr, nullptr);
                }
                else if (wcscmp(className, TOOLBARCLASSNAME) == 0)
                {
                    const auto hTip = reinterpret_cast<HWND>(SendMessage(hTooltip, TB_GETTOOLTIPS, NULL, NULL));
                    if (hTip != nullptr)
                    {
                        SetWindowTheme(hTip, useDark ? L"DarkMode_Explorer" : nullptr, nullptr);
                    }
                }
            }
        }
    } while (hTooltip != nullptr);
}

void SetDarkNpp()
{
    if (IsAtLeastWin10Build(VER_1809))
    {
        HWND hNppWwd = FindWindow(L"Notepad++", nullptr);
        if (hNppWwd != nullptr)
        {
            SetTheme(hNppWwd, enableDark);
            SetTitleBar(hNppWwd, enableDark);
            SetTooltips(hNppWwd, enableDark);
        }
    }
}