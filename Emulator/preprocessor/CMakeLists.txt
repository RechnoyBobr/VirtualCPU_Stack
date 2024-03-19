add_library(preproc preprocessor.cxx)
target_include_directories(preproc PRIVATE include)
include_directories(include)
target_link_libraries(preproc PRIVATE serializer parser)
