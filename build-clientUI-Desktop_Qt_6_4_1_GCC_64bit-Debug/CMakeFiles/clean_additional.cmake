# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/clientUI_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/clientUI_autogen.dir/ParseCache.txt"
  "clientUI_autogen"
  )
endif()
