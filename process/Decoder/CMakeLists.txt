set(process Decoder)

#####################################################################
#                                                                   #
#                            Library                                #
#                                                                   #
#####################################################################

##### Decoder

add_library(lib${process} SHARED libdaDatDecoder.cpp libdaDirProcessor.cpp)
set_target_properties(lib${process} PROPERTIES OUTPUT_NAME "${process}")

# Link with ...
target_link_libraries(lib${process}
    ${ROOT_LIBRARIES}               # ROOT のライブラリ（Tree, RIO など）
    ${Boost_PROGRAM_OPTIONS_LIBRARY} # Boost のライブラリ（program_options）
)

# make the library discoverable from all the programs
target_include_directories(lib${process} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# install the library in the lib folder
install(TARGETS lib${process} DESTINATION "${CMAKE_INSTALL_LIBDIR}")

#####################################################################
#                                                                   #
#                          Executables                              #
#                                                                   #
#####################################################################

##### wgDecoder
add_executable(${process} ${process}.cpp)

# Link with ...
target_link_libraries(${process} lib${process})

# install the executable in the bin folder
install(TARGETS ${process} DESTINATION "${CMAKE_INSTALL_BINDIR}")
