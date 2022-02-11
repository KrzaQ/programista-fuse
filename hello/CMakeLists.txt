add_executable(hello hello.cpp)

target_compile_features(hello PUBLIC cxx_std_20)
set_target_properties(hello PROPERTIES CXX_EXTENSIONS 0)
target_link_libraries(hello PRIVATE
    ${FUSE_LIBRARIES}
    fmt::fmt
)
target_compile_definitions(hello PRIVATE
    ${FUSE_DEFINITIONS}
    ${KQ_DEFINES}
)
target_include_directories(hello PRIVATE ${FUSE_INCLUDES})
