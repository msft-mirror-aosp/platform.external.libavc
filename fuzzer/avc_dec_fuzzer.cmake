if(NOT "${SYSTEM_NAME}" STREQUAL "Darwin")
    libavc_add_fuzzer(avc_dec_fuzzer libavcdec SOURCES
                  ${AVC_ROOT}/fuzzer/avc_dec_fuzzer.cpp)
endif()