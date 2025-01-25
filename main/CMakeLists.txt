
set(SOURCES "main.cpp"
            "devices/spi.cpp"
            "boards/common/board.cpp"
            "application.cpp"
    )


file(GLOB BOARD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/boards/${CONFIG_BOARD_NAME}/*.cpp)
list(APPEND SOURCES ${BOARD_SOURCES})

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS "." "./include")
