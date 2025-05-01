cmake_minimum_required(VERSION 3.8)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Search_Engine")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(Search_Engine 
    "src/Search_Engine.cpp"
    "src/Converter.cpp"
    "src/InvertedIndex.cpp"
    "src/SearchServer.cpp")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)
target_link_libraries(Search_Engine PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Search_Engine PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(Search_Engine) 

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/JsonFile) 

configure_file(${CMAKE_SOURCE_DIR}/JsonFile/config.json ${CMAKE_BINARY_DIR}/JsonFile/config.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/JsonFile/request.json ${CMAKE_BINARY_DIR}/JsonFile/request.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/JsonFile/answers.json ${CMAKE_BINARY_DIR}/JsonFile/answers.json COPYONLY)

configure_file(${CMAKE_SOURCE_DIR}/resources/file1.txt ${CMAKE_BINARY_DIR}/resources/file1.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/resources/file2.txt ${CMAKE_BINARY_DIR}/resources/file2.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/resources/file3.txt ${CMAKE_BINARY_DIR}/resources/file3.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/resources/file4.txt ${CMAKE_BINARY_DIR}/resources/file4.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/resources/file5.txt ${CMAKE_BINARY_DIR}/resources/file5.txt COPYONLY)

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Search_Engine PROPERTY CXX_STANDARD 20)
endif()