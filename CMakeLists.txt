junuo_package(junuobase SHARED)
junuo_sources(
    src/utils/processutils.h
    src/utils/processutils.cpp
    src/utils/stringutils.h
    src/utils/stringutils.cpp
    src/async/junuoasynccall.hpp
)
junuo_include_directories(./src ../include)
junuo_compile_definitions(JUNUO_BASE_MODULE)
