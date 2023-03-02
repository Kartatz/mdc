cmake_minimum_required(VERSION 3.13)

project(
	SparkleC
	VERSION 0.4
	DESCRIPTION "Tiny CLI tool to download courses from Hotmart"
	HOMEPAGE_URL "https://github.com/Kartatz/SparkleC"
	LANGUAGES C
)

option(SPARKLEC_ENABLE_LTO "Turn on compiler Link Time Optimizations" OFF)

option(SPARKLEC_DISABLE_HOTMART "Disable support for Hotmart" OFF)
option(SPARKLEC_DISABLE_ESTRATEGIA "Disable support for Estratégia websites" OFF)

if (NOT SPARKLEC_DISABLE_ESTRATEGIA)
	option(SPARKLEC_DISABLE_ESTRATEGIA_CONCURSOS "Disable support for Estratégia Concursos" OFF)
	option(SPARKLEC_DISABLE_ESTRATEGIA_VESTIBULARES "Disable support for Estratégia Vestibulares" OFF)
	option(SPARKLEC_DISABLE_ESTRATEGIA_MILITARES "Disable support for Estratégia Militares" OFF)
endif()

option(SPARKLEC_DISABLE_IAEXPERT "Disable support for IA Expert Academy" OFF)
option(SPARKLEC_DISABLE_CERTIFICATE_VALIDATION "Disable SSL certificate validation in libcurl" OFF)

set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

# curl
set(PICKY_COMPILER OFF)
set(BUILD_CURL_EXE OFF)
set(HTTP_ONLY ON)
set(ENABLE_THREADED_RESOLVER OFF)
set(CURL_USE_OPENSSL ON)
set(CURL_USE_LIBPSL OFF)
set(CURL_DISABLE_ALTSVC ON)
set(CURL_DISABLE_CRYPTO_AUTH ON)
set(CURL_DISABLE_COOKIES OFF)
set(CURL_DISABLE_HSTS ON)
set(CURL_DISABLE_HTTP_AUTH ON)
set(CURL_DISABLE_NETRC ON)
set(USE_LIBIDN2 OFF)
set(ENABLE_UNIX_SOCKETS OFF)
set(CURL_USE_LIBSSH2 OFF)
set(CURL_CA_BUNDLE "none")
set(CURL_CA_PATH "none")
set(CURL_WERROR OFF)
set(CURL_DISABLE_DOH ON)

if (WIN32)
	set(ENABLE_UNICODE ON)
endif()

# jansson
set(JANSSON_BUILD_DOCS OFF CACHE BOOL "")
set(JANSSON_BUILD_SHARED_LIBS ON CACHE BOOL "")
set(SYMVER_WORKS OFF CACHE BOOL "")
set(VSCRIPT_WORKS OFF CACHE BOOL "")

if (NOT APPLE)
	if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
		add_link_options(-s)
	endif()
endif()

if (CMAKE_C_COMPILER_ID STREQUAL "Clang" AND CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	add_compile_options(-Oz)
endif()


include_directories(
	src
)

set(OPENSSL_INCLUDE_DIRS /home/kartz/.local/include)
set(OPENSSL_LIBRARY /home/kartz/.local/lib/libssl.so)

add_subdirectory(submodules/curl EXCLUDE_FROM_ALL)

set_target_properties(
	libcurl
	PROPERTIES
	IMPORTED_LOCATION ${OPENSSL_LIBRARY}
)

# Disable SO versioning for all third-party packages
foreach(target libcurl)
	set_target_properties(
		${target}
		PROPERTIES
		NO_SONAME 1
	)
endforeach()

add_executable(
	main
	src/main.c
)

target_link_libraries(
	main
	libcurl
)
