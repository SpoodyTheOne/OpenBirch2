qt_add_executable(${PROJECT_NAME}
    application.qrc
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Gui CAS BirchCAS Qt6::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
