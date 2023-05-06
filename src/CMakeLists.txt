
# build main of application
add_executable(${PROJECT_NAME} main.cpp 
    ARX.cpp 
    PI.cpp
    PD.cpp
    PID.cpp
    helper.cpp
    )
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )
