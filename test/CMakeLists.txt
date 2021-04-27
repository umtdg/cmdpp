add_subdirectory("${cmdpp_SOURCE_DIR}/extern/googletest" "extern/googletest")

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

include("../cmake/utils.cmake")

set(TEST_INCLUDE_DIRS
	"${CMDPP_BUILD_INCLUDE_DIRS}"
	"${cmdpp_SOURCE_DIR}/extern/googletest/googletest/include")
include_directories("${TEST_INCLUDE_DIRS}")

set(LIBS gtest_main cmdpp)
cmdpp_cxx_test(cmdpp_utils_test "${LIBS}")
