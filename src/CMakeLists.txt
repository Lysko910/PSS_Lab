set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# build main of application
add_executable(${PROJECT_NAME} main.cpp 
    struktury.cpp
    SISO.cpp        
    ARX.cpp 
    PI.cpp
    PD.cpp
    PID.cpp
    generator.cpp
    helper.cpp  
    )
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )
