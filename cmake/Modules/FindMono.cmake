find_program(MONO_EXECUTABLE mono)
find_program(MCS_EXECUTABLE mcs)
find_program(GACUTIL_EXECUTABLE gacutil)
find_program(MSBUILD_EXECUTABLE msbuild)

set(MONO_FOUND FALSE CACHE INTERNAL "")

if(MONO_EXECUTABLE AND MCS_EXECUTABLE AND GACUTIL_EXECUTABLE AND MSBUILD_EXECUTABLE)
    set(MONO_FOUND TRUE CACHE INTERNAL "")

    # default GAC is located in <prefix>/lib/mono/gac
    find_path(MONO_ROOT
            NAMES Mono/mono-2.0/mono/metadata/appdomain.h
            PATHS "/usr;/usr/local;")

    set(MONO_INCLUDE_DIR "${MONO_ROOT}/Headers/mono-2.0" CACHE PATH "Mono include directory")
    set(MONO_LIBRARIES "${MONO_ROOT}/Libraries/libmonosgen-2.0.dylib" CACHE PATH "Mono library")
    # TODO: win and linux

    execute_process(COMMAND ${MCS_EXECUTABLE} --version OUTPUT_VARIABLE MONO_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX REPLACE ".*version ([^ ]+)" "\\1" MONO_VERSION "${MONO_VERSION}")
endif()

mark_as_advanced(MONO_EXECUTABLE MCS_EXECUTABLE GACUTIL_EXECUTABLE MSBUILD_EXECUTABLE MONO_VERSION)
