cmake_policy(SET CMP0015 NEW)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTATICLIB")

aux_source_directory(. SRC_LIST)

set(EXECUTABLE lll)

if(APPLE)
	# set(CMAKE_INSTALL_PREFIX ../lib)
	add_library(${EXECUTABLE} SHARED ${SRC_LIST})
else()
	add_library(${EXECUTABLE} ${SRC_LIST})
endif()
if (UNIX)
    FIND_PACKAGE(Boost 1.53 REQUIRED COMPONENTS thread date_time system filesystem program_options signals serialization chrono unit_test_framework locale)
endif()
file(GLOB HEADERS "*.h") 

include_directories(..)
include_directories(${MINIUPNPC_ID})
include_directories(${LEVELDB_ID})

target_link_libraries(${EXECUTABLE} ethcore)
target_link_libraries(${EXECUTABLE} ethsupport)
target_link_libraries(${EXECUTABLE} secp256k1)
target_link_libraries(${EXECUTABLE} ${MINIUPNPC_LS})
target_link_libraries(${EXECUTABLE} ${LEVELDB_LS})
target_link_libraries(${EXECUTABLE} gmp)


if(${TARGET_PLATFORM} STREQUAL "w64")
	include_directories(/usr/x86_64-w64-mingw32/include/cryptopp)
	target_link_libraries(${EXECUTABLE} cryptopp)
	target_link_libraries(${EXECUTABLE} boost_system-mt-s)
	target_link_libraries(${EXECUTABLE} boost_filesystem-mt-s)
	target_link_libraries(${EXECUTABLE} boost_thread_win32-mt-s)
	target_link_libraries(${EXECUTABLE} iphlpapi)
	target_link_libraries(${EXECUTABLE} ws2_32)
	target_link_libraries(${EXECUTABLE} mswsock)
	target_link_libraries(${EXECUTABLE} shlwapi)
elseif (APPLE)
	# Latest mavericks boost libraries only come with -mt
	target_link_libraries(${EXECUTABLE} ${CRYPTOPP_LIBRARIES})
	target_link_libraries(${EXECUTABLE} boost_system-mt)
	target_link_libraries(${EXECUTABLE} boost_filesystem-mt)
	target_link_libraries(${EXECUTABLE} boost_thread-mt)
	find_package(Threads REQUIRED)
	target_link_libraries(${EXECUTABLE} ${CMAKE_THREAD_LIBS_INIT})
elseif (UNIX)
	target_link_libraries(${EXECUTABLE} ${CRYPTOPP_LIBRARIES})
	target_link_libraries(${EXECUTABLE} ${Boost_SYSTEM_LIBRARY})
	target_link_libraries(${EXECUTABLE} ${Boost_FILESYSTEM_LIBRARY})
	target_link_libraries(${EXECUTABLE} ${Boost_THREAD_LIBRARY})
	target_link_libraries(${EXECUTABLE} ${Boost_DATE_TIME_LIBRARY})
	target_link_libraries(${EXECUTABLE} ${CMAKE_THREAD_LIBS_INIT})
else ()
	target_link_libraries(${EXECUTABLE} ${CRYPTOPP_LIBRARIES})
	target_link_libraries(${EXECUTABLE} boost_system)
	target_link_libraries(${EXECUTABLE} boost_filesystem)
	target_link_libraries(${EXECUTABLE} boost_thread)
	find_package(Threads REQUIRED)
	target_link_libraries(${EXECUTABLE} ${CMAKE_THREAD_LIBS_INIT})
endif ()

message("Installation path: ${CMAKE_INSTALL_PREFIX}")

install( TARGETS ${EXECUTABLE} ARCHIVE DESTINATION lib LIBRARY DESTINATION lib )
install( FILES ${HEADERS} DESTINATION include/${EXECUTABLE} )
