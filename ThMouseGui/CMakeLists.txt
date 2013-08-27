cmake_minimum_required(VERSION 2.8)

include_directories($(PROJECT_SOURCE_DIR)/ThDxHook)

set(SRC_LIST
ReadConfig.h     resource.h       stdafx.h         targetver.h
ThMouse.h        ReadConfig.cpp   stdafx.cpp       ThMouse.cpp
ThMouse.rc
)

add_executable(ThMouse WIN32 ${SRC_LIST})
target_link_libraries(ThMouse ThDxHook)

add_custom_command(
    TARGET ThMouse POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Data
    $<TARGET_FILE_DIR:ThMouse>
)

