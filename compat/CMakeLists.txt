# The pinned DYA settings RPC writes both idle and sleep timeouts, even when
# only idle changed. ZMK rejects all sleep writes when deep sleep is disabled.
if(CONFIG_ZMK_SETTINGS_RPC AND NOT CONFIG_ZMK_SLEEP)
  target_sources(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/activity_sleep_compat.c)
  target_link_options(app PUBLIC -Wl,--wrap=zmk_activity_set_sleep_ms)
endif()

# Compile the pinned processor in the same translation unit as the state-sync
# listener so it can reconcile the processor's private temp-layer state.
if(CONFIG_ZMK_RUNTIME_INPUT_PROCESSOR)
  set(roba_runtime_source
    "${ZEPHYR_ZMK_MODULE_RUNTIME_INPUT_PROCESSOR_MODULE_DIR}/src/pointing/input_processor_runtime.c")
  set_source_files_properties("${roba_runtime_source}"
    TARGET_DIRECTORY app PROPERTIES HEADER_FILE_ONLY TRUE)
  set(roba_runtime_wrapper "${CMAKE_CURRENT_BINARY_DIR}/runtime_input_processor_compat.c")
  file(WRITE "${roba_runtime_wrapper}"
    "#include \"${roba_runtime_source}\"\n"
    "#include \"${CMAKE_CURRENT_LIST_DIR}/temp_layer_state_sync.h\"\n")
  target_sources(app PRIVATE "${roba_runtime_wrapper}")
endif()
