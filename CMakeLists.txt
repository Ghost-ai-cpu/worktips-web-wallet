cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME
        worktips-web-wallet)

project(${PROJECT_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fsanitize=address")
set(CMAKE_CXX_STANDARD 14)

if(CMAKE_SIZEOF_VOID_P EQUAL "4")
  add_definitions(-DMDB_VL32)
endif()

if (NOT WORKTIPS_DIR)
    set(WORKTIPS_DIR ~/worktips)
endif()

option(BUILD_TEST "Build tests for the project" OFF)

message(STATUS WORKTIPS_DIR ": ${WORKTIPS_DIR}")

set(WORKTIPS_SOURCE_DIR ${WORKTIPS_DIR}
        CACHE PATH "Path to the root directory for Worktips")

# set location of worktips build tree
set(WORKTIPS_BUILD_DIR ${WORKTIPS_SOURCE_DIR}/build/release/
        CACHE PATH "Path to the build directory for Worktips")

set(MY_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake"
        CACHE PATH "The path to the cmake directory of the current project")

list(APPEND CMAKE_MODULE_PATH "${MY_CMAKE_DIR}")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${WORKTIPS_BUILD_DIR}"
        CACHE PATH "Add Worktips directory for library searching")

include(MyUtils)


if (${BUILD_TEST})
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_EXCLUDES
            '${CMAKE_SOURCE_DIR}/ext/*'
            'asio/*'
            '${WORKTIPS_SOURCE_DIR}/*'
            '${CMAKE_SOURCE_DIR}/tests/*')
endif()

find_package(Worktips)

find_package(MySQL++)


include_directories(${MYSQL_INCLUDE_DIR})

# include boost headers
include_directories(${Boost_INCLUDE_DIRS})

# include worktips headers
include_directories("ext/restbed/source")

include_directories(
	${WORKTIPS_SOURCE_DIR}/external/worktips-mq
    ${WORKTIPS_SOURCE_DIR}/build
    /usr/local/include
    /usr/local/include/mysql
    /usr/include/mysql++
    /usr/include/mysql
    /usr/local/opt/openssl/include

    )

link_directories(
    ${WORKTIPS_BUILD_DIR}/src/crypto
    /usr/local/lib
    /usr/include/mysql++
    /usr/lib/mysql
    /usr/local/opt/openssl/lib
)

create_git_version()

configure_files(${CMAKE_CURRENT_SOURCE_DIR}/config ${CMAKE_CURRENT_BINARY_DIR}/config)


# find boost
find_package(Boost COMPONENTS
        system
        filesystem
        thread
        date_time
        chrono
        regex
        serialization
        program_options
        date_time
        REQUIRED)


# add src/ subfolder
add_subdirectory(src/)


# add ext/ subfolder
add_subdirectory(ext/)


set(SOURCE_FILES
        main.cpp)

add_executable(${PROJECT_NAME}
        ${SOURCE_FILES})

set(LIBRARIES
        myxrm
        myext
        restbed
        wallet
        cryptonote_core
        blockchain_db       
        cryptonote_protocol
        cryptonote_basic
        daemonizer
        cncrypto
        blocks
        lmdb
        ringct
	ringct_basic
	common
	mnemonics
        epee
        easylogging
        mysqlpp
        mysqlclient
        device
        epee
        checkpoints
        version       
        ${Boost_LIBRARIES}
        pthread
        sodium
	unbound
        curl
        cncrypto
        ssl
        crypto)

if(APPLE)
    set(LIBRARIES ${LIBRARIES} "-framework IOKit -framework Foundation")
else()
    set(LIBRARIES ${LIBRARIES} atomic)
endif()

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND NOT WIN32)
    set(LIBRARIES ${LIBRARIES} unwind)
endif()


if (WIN32)
    set(LIBRARIES ${LIBRARIES}
            wsock32
            ntdll
            ws2_32
            Iphlpapi)
else()
    set(LIBRARIES ${LIBRARIES} dl)
endif()

find_package(HIDAPI)
set(LIBRARIES ${LIBRARIES} ${HIDAPI_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})


if (${BUILD_TEST})
    include_directories(
        ${CMAKE_SOURCE_DIR}/ext/googletest/googletest/include
        ${CMAKE_SOURCE_DIR}/ext/googletest/googlemock/include)
endif()

configure_files(${CMAKE_CURRENT_SOURCE_DIR}/sql ${CMAKE_CURRENT_BINARY_DIR}/sql)

if (${BUILD_TEST})
    enable_testing()
    add_subdirectory(ext/googletest)
    add_subdirectory(tests)
endif()
