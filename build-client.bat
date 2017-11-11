
pushd %~dp0\..
set PARENT=%CD%
popd

echo %PARENT%
%PARENT%\UnrealEngine\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PARENT%\GameLiftMultiplayer\GameLiftMultiplayer.uproject" -prereqs -noP4 -platform=Win64 -clientconfig=Development -serverconfig=Development -cook -iterate -build -stage -archive -archivedirectory="%PARENT%\Client"
