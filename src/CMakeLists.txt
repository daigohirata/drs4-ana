# List all the source files in this directory
set(SOURCES
    drsDatDecoder.cpp
)

# Compile them as a dynamic library
add_library(libdrs4ana SHARED ${SOURCES})

# Set the library name (dont use the wrong "liblibwagasci" name)
set_target_properties(libdrs4ana PROPERTIES OUTPUT_NAME "drs4ana")

# Link with libraries
target_link_libraries(libdrs4ana ${Boost_LIBRARIES} ${ROOT_LIBRARIES})

# make the library discoverable from all the programs
target_include_directories(libdrs4ana PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# list all target headers
set_target_properties(libdrs4ana PROPERTIES PUBLIC_HEADER "${DRS4_ANA_INCLUDES}")

# install the library in the lib folder
install(TARGETS libdrs4ana
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
