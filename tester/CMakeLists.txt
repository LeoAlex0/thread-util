aux_source_directory(. SRC_LIST)

foreach(source_file ${SRC_LIST})
    string (REGEX REPLACE "./" "" source_file "${source_file}")
    string (REGEX REPLACE "_test.cpp" "" bin_name "${source_file}")
    string (REGEX REPLACE "_test.c" "_c" bin_name "${bin_name}")
    add_executable ("${bin_name}" "${source_file}")
    target_link_libraries ("${bin_name}" thread)
endforeach()