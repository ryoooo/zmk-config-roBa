# The pinned threshold processor predates main+dya's layer-locking argument.
# Scope the adapter to that source; other modules already use the new API.
if(CONFIG_ZMK_INPUT_PROCESSOR_TEMP_LAYER_THRESHOLD)
  set_property(
    SOURCE "${ZEPHYR_ZMK_INPUT_PROCESSOR_TEMP_LAYER_THRESHOLD_MODULE_DIR}/src/input_processor_temp_layer_threshold.c"
    TARGET_DIRECTORY app
    APPEND PROPERTY COMPILE_OPTIONS
    "-include" "${CMAKE_CURRENT_LIST_DIR}/compat/temp_layer_threshold.h"
  )
endif()
