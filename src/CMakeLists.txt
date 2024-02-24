# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(libxml2_flutter_plugin_library VERSION 0.0.1 LANGUAGES C)

add_library(libxml2_flutter_plugin SHARED
  "libxml2_flutter_plugin.c"
)

set_target_properties(libxml2_flutter_plugin PROPERTIES
  PUBLIC_HEADER libxml2_flutter_plugin.h
  OUTPUT_NAME "libxml2_flutter_plugin"
)

target_compile_definitions(libxml2_flutter_plugin PUBLIC DART_SHARED_LIB)
