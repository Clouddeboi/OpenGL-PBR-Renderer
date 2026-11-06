option(PBR_WARNINGS_AS_ERRORS "Treat compiler warnings as errors in project targets" ON)

# Applies the project's warning policy to a single target.
# Only call this on our own targets, never on third-party code.
function(enable_project_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W4
            /permissive-        # strict standards conformance
            /Zc:__cplusplus     # make __cplusplus report the real standard
            /utf-8              # UTF-8 source and execution charset
            /w14263             # member function does not override base virtual
            /w14265             # class has virtual functions but non-virtual destructor
            /w14287             # unsigned/negative constant mismatch
            /w14640             # thread-unsafe static member initialisation
            /w14826             # sign-extended conversion
            /w14905 /w14906     # wide string literal casts
            /w14928             # illegal copy-initialisation
        )
        if(PBR_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE /WX)
        endif()
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic
            -Wshadow -Wconversion -Wsign-conversion
            -Wnon-virtual-dtor -Woverloaded-virtual
        )
        if(PBR_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE -Werror)
        endif()
    endif()
endfunction()