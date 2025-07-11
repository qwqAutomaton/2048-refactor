cmake_minimum_required(VERSION 3.10)

project(2048)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
endif()

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories(
    ${SRC}/game
    ${SRC}/ui
)

set(SOURCES
    ${SRC}/main.cpp
    ${SRC}/game/board.cpp
    ${SRC}/game/logic.cpp
    ${SRC}/ui/display.cpp
    ${SRC}/game/AI.cpp
)

set(HEADERS
    ${SRC}/game/AI.h
    ${SRC}/game/board.h
    ${SRC}/game/logic.h
    ${SRC}/game/AI_TMP.h
    ${SRC}/ui/display.h
    ${SRC}/ui/console.h
)

if(WIN32)
    list(APPEND SOURCES
        ${SRC}/ui/console_windows.cpp
    )
else()
    list(APPEND SOURCES
        ${SRC}/ui/console_unix.cpp
    )
endif()

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)
