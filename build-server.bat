
pushd %~dp0\..
set PARENT=%CD%
popd

echo %PARENT%
%PARENT%\UnrealEngine\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PARENT%\GameLiftMultiplayer\GameLiftMultiplayer.uproject" -noP4 -serverconfig=Development -cook -iterate -server -serverplatform=win64 -noclient -build -stage -archive -archivedirectory="%PARENT%\Server"