set(CRYPTO_SOURCES http.cpp utils.cpp)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(crypto crypto.cpp)

target_compile_features(crypto PUBLIC cxx_std_20)
set_target_properties(crypto PROPERTIES CXX_EXTENSIONS 0)
target_link_libraries(crypto PRIVATE
    ${FUSE_LIBRARIES}
    fmt::fmt
    CURL::libcurl
    nlohmann_json::nlohmann_json
)
target_compile_definitions(crypto PRIVATE
    ${FUSE_DEFINITIONS}
    ${KQ_DEFINES}
)
target_include_directories(crypto PRIVATE ${FUSE_INCLUDES})
target_sources(crypto PRIVATE ${CRYPTO_SOURCES})
