cmake_minimum_required(VERSION 3.3)
project(metal-test LANGUAGES C)

file(GLOB metal_files ../../shaders/metal/*.metal)
set_source_files_properties(${metal_files} PROPERTIES LANGUAGE METAL)
add_executable(metal-test ${metal_files})
