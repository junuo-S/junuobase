set(sources
    src/global.h
    src/utils/winfunc.h
    src/utils/winfunc.cpp
    src/utils/stringconvert.h
    src/utils/stringconvert.cpp
)

set(target_name junuobase)

junuo_add_library(${target_name} SHARED ${sources})
junuo_include_directories(${target_name} . ../include)
junuo_compile_definitions(${target_name} JUNUO_BASE_MODULE)
