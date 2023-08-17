qt_add_library(BirchCAS STATIC
  BirchCAS.cpp
  polynomial.h
)

target_link_libraries(BirchCAS PRIVATE Qt6::Core)
target_include_directories(BirchCAS INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})