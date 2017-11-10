
pushd %~dp0\..
set PARENT=%CD%
popd

echo %PARENT%
%PARENT%\UnrealEngine\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PARENT%\GameLiftMultiplayer\GameLiftMultiplayer.uproject" -installed -nop4 -cook -iterate -targetplatform=Win64 -utf8output -config=Development -archive -archivedirectory="%PARENT%\Client"
