junuo_package(junuobase SHARED)
junuo_sources(
    src/global.h
    src/utils/winfunc.h
    src/utils/winfunc.cpp
    src/utils/stringconvert.h
    src/utils/stringconvert.cpp
)
junuo_include_directories(. ../include)
junuo_compile_definitions(JUNUO_BASE_MODULE)
