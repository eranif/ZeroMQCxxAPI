# run the wx-config program to get cxxflags

set(wxWidgets_CONFIG_EXECUTABLE wx-config)

if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set( wxWidgets_SELECT_OPTIONS --unicode --debug=yes)
else ()
    set( wxWidgets_SELECT_OPTIONS --unicode --debug=no)
endif()

execute_process(
    COMMAND "${wxWidgets_CONFIG_EXECUTABLE}" ${wxWidgets_SELECT_OPTIONS} --cxxflags
    OUTPUT_VARIABLE wxWidgets_CXX_FLAGS
    RESULT_VARIABLE RET
    ERROR_QUIET
    )

if(RET EQUAL 0)
    string(STRIP "${wxWidgets_CXX_FLAGS}" wxWidgets_CXX_FLAGS)
    separate_arguments(wxWidgets_CXX_FLAGS)

    # parse definitions from cxxflags;
    #   drop -D* from CXXFLAGS and the -D prefix
    string(REGEX MATCHALL "-D[^;]+"
      wxWidgets_DEFINITIONS  "${wxWidgets_CXX_FLAGS}")
      
    string(REGEX REPLACE "-D[^;]+(;|$)" ""
      wxWidgets_CXX_FLAGS "${wxWidgets_CXX_FLAGS}")
      
    string(REGEX REPLACE ";$" ""
      wxWidgets_CXX_FLAGS "${wxWidgets_CXX_FLAGS}")
    
    #string(REPLACE "-D" ""
    #  wxWidgets_DEFINITIONS "${wxWidgets_DEFINITIONS}")

    # parse include dirs from cxxflags; drop -I prefix
    string(REGEX MATCHALL "-I[^;]+"
      wxWidgets_INCLUDE_DIRS "${wxWidgets_CXX_FLAGS}")
      
    string(REGEX REPLACE "-I[^;]+;" ""
      wxWidgets_CXX_FLAGS "${wxWidgets_CXX_FLAGS}")
      
    string(REPLACE "-I" ""
      wxWidgets_INCLUDE_DIRS "${wxWidgets_INCLUDE_DIRS}")
    
    string(REPLACE ";" " "
          wxWidgets_CXX_FLAGS "${wxWidgets_CXX_FLAGS}")
    
    string(REPLACE ";" " "
          wxWidgets_DEFINITIONS "${wxWidgets_DEFINITIONS}")
    
    set( wxWidgets_FOUND 1 )
    # message("wxWidgets_INCLUDE_DIRS=${wxWidgets_INCLUDE_DIRS}")
    # message("wxWidgets_CXX_FLAGS=${wxWidgets_CXX_FLAGS}")
    # message("wxWidgets_DEFINITIONS=${wxWidgets_DEFINITIONS}")
else()
    set(wxWidgets_FOUND 0)
    message(FATAL "${wxWidgets_CONFIG_EXECUTABLE} --cxxflags FAILED with RET=${RET}")
endif()

set( wxWidgets_FIND_COMPONENTS std )
# run the wx-config program to get the libs
# - NOTE: wx-config doesn't verify that the libs requested exist
#         it just produces the names. Maybe a TRY_COMPILE would
#         be useful here...
string(REPLACE ";" ","
    wxWidgets_FIND_COMPONENTS "${wxWidgets_FIND_COMPONENTS}")
execute_process(
    COMMAND "${wxWidgets_CONFIG_EXECUTABLE}" ${wxWidgets_SELECT_OPTIONS} --libs ${wxWidgets_FIND_COMPONENTS}
        OUTPUT_VARIABLE wxWidgets_LIBRARIES
        RESULT_VARIABLE RET
        ERROR_QUIET
    )
    
if(RET EQUAL 0)
    string(STRIP "${wxWidgets_LIBRARIES}" wxWidgets_LIBRARIES)
    separate_arguments(wxWidgets_LIBRARIES)
    string(REPLACE "-framework;" "-framework "
      wxWidgets_LIBRARIES "${wxWidgets_LIBRARIES}")
    string(REPLACE "-arch;" "-arch "
      wxWidgets_LIBRARIES "${wxWidgets_LIBRARIES}")
    string(REPLACE "-isysroot;" "-isysroot "
      wxWidgets_LIBRARIES "${wxWidgets_LIBRARIES}")

    # extract linkdirs (-L) for rpath (i.e., LINK_DIRECTORIES)
    string(REGEX MATCHALL "-L[^;]+"
      wxWidgets_LIBRARY_DIRS "${wxWidgets_LIBRARIES}")
    string(REPLACE "-L" ""
      wxWidgets_LIBRARY_DIRS "${wxWidgets_LIBRARY_DIRS}")
    
    set( wxWidgets_FOUND 1 )
    #message("wxWidgets_LIBRARIES=${wxWidgets_LIBRARIES}")
    #message("wxWidgets_LIBRARY_DIRS=${wxWidgets_LIBRARY_DIRS}")

else()
    set(wxWidgets_FOUND 0)
    message(FATAL_ERROR "${wxWidgets_CONFIG_EXECUTABLE} --libs ${wxWidgets_FIND_COMPONENTS} FAILED with RET=${RET}")
endif()

