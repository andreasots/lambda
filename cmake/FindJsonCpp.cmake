cmake_minimum_required(VERSION 2.8.2)

find_path(JSONCPP_INCLUDE_DIRS
  NAMES
    json/json.h
  PATHS
    ${JSONCPP_PREFIX}/include
    /usr/include
    /usr/include/jsoncpp
    /usr/local/include
    /opt/local/include
  NO_DEFAULT_PATH
)

find_library(JSONCPP_LIBRARIES
  NAMES
    jsoncpp
  PATHS
    ${JSONCPP_INCLUDE_DIRS}/..
    ${JSONCPP_INCLUDE_DIRS}/../lib
    ${JSONCPP_INCLUDE_DIRS}/../../lib
  NO_DEFAULT_PATH
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JSONCPP DEFAULT_MSG JSONCPP_LIBRARIES
  JSONCPP_INCLUDE_DIRS)
