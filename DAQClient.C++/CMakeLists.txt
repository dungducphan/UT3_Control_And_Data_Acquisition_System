link_directories(${TANGO_LIB_HOME})

add_executable(testClient testClient.cpp)

target_include_directories(testClient PRIVATE ${TANGO_INCLUDES})
target_link_libraries(testClient ${TANGO_LIBS})

