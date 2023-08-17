qt_add_library(CAS STATIC
  CAS.h
)

target_link_libraries(CAS PRIVATE Qt6::Core)
target_include_directories(CAS INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})