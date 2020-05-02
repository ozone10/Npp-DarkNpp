@echo off
@echo Choose Visual Studio 2019 Edition (after 5s will default to (2) Enterprise):
::https://help.github.com/en/actions/automating-your-workflow-with-github-actions/software-installed-on-github-hosted-runners#visual-studio-2019-enterprise
::This is because I am poor.
:Reset
@echo (1) Community
@echo (2) Enterprise
@echo (3) Reset Timer
@choice /c:123 /t:5 /d:2
if errorlevel 3 goto Reset
if errorlevel 2 goto Enterprise
if errorlevel 1 goto Community
:Enterprise
set Edition=Enterprise
goto Continue
:Community
set Edition=Community
goto Continue
:Continue
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\%Edition%\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
set solutionsFile=".\PluginDarkNpp.sln"
msbuild -m /t:build /p:Configuration=Release;Platform=x64 %solutionsFile%
msbuild -m /t:build /p:Configuration=Release;Platform=Win32 %solutionsFile%