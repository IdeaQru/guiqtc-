@echo off
cd /d %~dp0
copy Qt5Core_conda.dll Qt5Core.dll
copy Qt5Gui_conda.dll Qt5Gui.dll
copy Qt5Network_conda.dll Qt5Network.dll
copy Qt5SerialPort_conda.dll Qt5SerialPort.dll
copy Qt5Svg_conda.dll Qt5Svg.dll
copy Qt5Widgets_conda.dll Qt5Widgets.dll
GuiSensor.exe
