
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS --std=c++11)

include_directories(
    inc
    src-gen
    src-gen/v1/SimpleCalculator/CalculatorInterface
    /home/ashok/work_dir/capi_someIP_study/capicxx-core-runtime/include
    /home/ashok/work_dir/capi_someIP_study/capicxx-someip-runtime/include
    /home/ashok/work_dir/capi_someIP_study/vSomeIP/interface
    /home/ashok/work_dir/capi_someIP_study/capicxx-dbus-runtime/include
    /home/ashok/work_dir/capi_someIP_study/dbus-1.10.6
)

link_directories(
    /home/ashok/work_dir/capi_someIP_study/capicxx-core-runtime/build
    /home/ashok/work_dir/capi_someIP_study/capicxx-someip-runtime/build
    /home/ashok/work_dir/capi_someIP_study/vSomeIP/build
    /home/ashok/work_dir/capi_someIP_study/capicxx-dbus-runtime/build
    /home/ashok/work_dir/capi_someIP_study/dbus-1.10.6/dbus/.libs
)

add_executable(
    CalculatorServer
    src/CalculatorServer.cpp
    src/CalculatorStubImpl.cpp
    src-gen/v1/SimpleCalculator/CalculatorInterface/CalculatorStubDefault.cpp
    src-gen/v1/SimpleCalculator/CalculatorInterface/CalculatorDBusStubAdapter.cpp
    src-gen/v1/SimpleCalculator/CalculatorInterface/CalculatorDBusDeployment.cpp
)


target_link_libraries(
    CalculatorServer
    PocoFoundation
    PocoUtil
    CommonAPI
    CommonAPI-DBus
    dbus-1
    dlt
)

install(
    TARGETS CalculatorServer
    DESTINATION bin
)

add_subdirectory(
    test_suite/CalculatorClient
)


