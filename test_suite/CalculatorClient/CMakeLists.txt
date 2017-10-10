include_directories(
    inc
    ../../src-gen
    ../../src-gen/v1/SimpleCalculator/CalculatorInterface
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
    CalculatorClient
    src/CalculatorClient.cpp
    ../../src-gen/v1/SimpleCalculator/CalculatorInterface/CalculatorDBusProxy.cpp
    ../../src-gen/v1/SimpleCalculator/CalculatorInterface/CalculatorDBusDeployment.cpp
)


target_link_libraries(
    CalculatorClient
    PocoFoundation
    PocoUtil
    dlt
    CommonAPI
    CommonAPI-DBus
    dbus-1
)


install(
    TARGETS CalculatorClient
    DESTINATION bin
)
