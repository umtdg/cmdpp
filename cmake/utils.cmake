macro(config_compiler_and_linker)
	set(cxx_base_flags "-Wall -Wshadow -Werror")
	set(cxx_strict_flags "-Wextra -Wunused-parameter")
	set(cxx_exception "-fexceptions")

	set(cxx_exception "${cxx_base_flags} ${cxx_exception_flags}")
	set(cxx_default "${cxx_exception}")
	set(cxx_strict "${cxx_default} ${cxx_strict_flags}")
endmacro()

function(cxx_library_with_type name type cxx_flags)
    add_library(${name} ${type} ${ARGN})
    set_target_properties(${name}
            PROPERTIES
            COMPILE_FLAGS "${cxx_flags}")
    set_target_properties(${name}
            PROPERTIES
            DEBUG_POSTFIX "d")
    set_target_properties(${name}
            PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    get_target_property(pdb_debug_postfix ${name} DEBUG_POSTFIX)
    set_target_properties(${name}
            PROPERTIES
            PDB_NAME "${name}"
            PDB_NAME_DEBUG "${name}${pdb_debug_postfix}"
            COMPILE_PDB_NAME "${name}"
            COMPILE_PDB_NAME_DEBUG "${name}${pdb_debug_postfix}")

    if (BUILD_SHARED_LIBS OR type STREQUAL "SHARED")
        set_target_properties(${name}
                PROPERTIES
                COMPILE_DEFINITIONS "CREATE_SHARED_LIBRARY=1")
    endif()

    target_compile_features(${name} PUBLIC cxx_std_17)
endfunction()

function(cxx_shared_library name cxx_flags)
    cxx_library_with_type(${name} SHARED "${cxx_flags}" ${ARGN})
endfunction()

function(cxx_library name cxx_flags)
    cxx_library_with_type(${name} "" "${cxx_flags}" ${ARGN})
endfunction()

function(cxx_executable_with_flags name cxx_flags libs)
    add_executable(${name} ${ARGN})
    set_target_properties(${name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

    if (cxx_flags)
        set_target_properties(${name}
                PROPERTIES
                COMPILE_FLAGS "${cxx_flags}")
    endif()

    if (BUILD_SHARED_LIBS)
        set_target_properties(${name}
                PROPERTIES
                COMPILE_DEFINITIONS "LINKED_AS_SHARED_LIBRARY=1")
    endif()

    foreach (lib "${libs}")
        target_link_libraries(${name} ${lib})
    endforeach()
endfunction()

function(cxx_executable name dir libs)
    cxx_executable_with_flags(
            ${name} "${cxx_default}" "${libs}" "${dir}/${name}.cpp" ${ARGN})
endfunction()
