qt_add_library(Gui STATIC
    mainwindow.ui
    mainwindow.cpp

    document.ui
    document.cpp
    document.h

    documentline.ui
    documentline.cpp
    documentline.h

    documentsegment.cpp
    documentsegment.h
    textsegment.cpp
    mathsegment.cpp
    
    obtabwidget.h
    obtabwidget.cpp
)

target_link_libraries(Gui PRIVATE Qt6::Widgets)
target_include_directories(Gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
