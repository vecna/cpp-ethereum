cmake_policy(SET CMP0015 NEW)

aux_source_directory(. SRC_LIST)

include_directories(..)

set(EXECUTABLE sc)

add_executable(${EXECUTABLE} ${SRC_LIST})

if (${TARGET_PLATFORM} STREQUAL "w64")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
	target_link_libraries(${EXECUTABLE} gcc)
	target_link_libraries(${EXECUTABLE} gdi32)
	target_link_libraries(${EXECUTABLE} ws2_32)
	target_link_libraries(${EXECUTABLE} mswsock)
	target_link_libraries(${EXECUTABLE} shlwapi)
	target_link_libraries(${EXECUTABLE} iphlpapi)
	target_link_libraries(${EXECUTABLE} boost_thread_win32-mt-s)
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
elseif (UNIX)
else ()
	find_package(Threads REQUIRED)
	target_link_libraries(${EXECUTABLE} ${CMAKE_THREAD_LIBS_INIT})
endif ()

target_link_libraries(${EXECUTABLE} serpent)
target_link_libraries(${EXECUTABLE} lll)
target_link_libraries(${EXECUTABLE} evmface)
target_link_libraries(${EXECUTABLE} ethential)
target_link_libraries(${EXECUTABLE} gmp)

install( TARGETS ${EXECUTABLE} DESTINATION bin )

cmake_policy(SET CMP0015 NEW)
