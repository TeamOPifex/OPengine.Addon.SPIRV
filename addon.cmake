
message(STATUS "Prep for addon: SPIRV")

SET(SPIRV_PATH ${CMAKE_CURRENT_LIST_DIR})

macro(ADDON_SPIRV_PROJECT ADDON_BUILD)
    message(STATUS "Adding project with build folder of ${ADDON_BUILD}")
    add_subdirectory (${SPIRV_PATH} "${ADDON_BUILD}/SPIRV_build")
endmacro(ADDON_SPIRV_PROJECT)

macro(ADDON_SPIRV_INCLUDES)
    include_directories(${SPIRV_PATH}/include/)
    include_directories(${SPIRV_PATH}/repo/)
endmacro(ADDON_SPIRV_INCLUDES)

macro(ADDON_SPIRV APPLICATION_TARGET FOLDER)

endmacro(ADDON_SPIRV)

macro(ADDON_SPIRV_LINK TEMP_RESULT)    
    SET(TEMP_RESULT "spirv")
endmacro(ADDON_SPIRV_LINK)

macro(ADDON_SPIRV_DEFINES TEMP_RESULT)
    SET(TEMP_RESULT "")
endmacro(ADDON_SPIRV_DEFINES)

macro(ADDON_SPIRV_ASSETS TEMP_RESULT)
	SET(TEMP_RESULT "")
endmacro(ADDON_SPIRV_ASSETS)
