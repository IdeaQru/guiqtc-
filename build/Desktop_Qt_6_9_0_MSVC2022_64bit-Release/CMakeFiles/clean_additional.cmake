# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\GuiSensor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GuiSensor_autogen.dir\\ParseCache.txt"
  "GuiSensor_autogen"
  )
endif()
