include_directories(
    inc
)

add_executable(
    LifecycleTest
    src/LifecycleTest.cpp
    ${CMAKE_SYSROOT}/usr/src/debug/node-state-manager/2.0.0-r1/git/NodeStateAccess/generated/NodeStateLifecycleControl.c
)


target_link_libraries(
    LifecycleTest
    PocoFoundation
    PocoUtil
    dlt
    gio-2.0
    glib-2.0
    dbus-glib-1
    gobject-2.0    
)


install(
    TARGETS LifecycleTest 
    DESTINATION bin
)
