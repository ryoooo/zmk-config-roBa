# The pinned DYA settings RPC writes both idle and sleep timeouts, even when
# only idle changed. ZMK rejects all sleep writes when deep sleep is disabled.
if(CONFIG_ZMK_SETTINGS_RPC AND NOT CONFIG_ZMK_SLEEP)
  target_sources(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/activity_sleep_compat.c)
  target_link_options(app PUBLIC -Wl,--wrap=zmk_activity_set_sleep_ms)
endif()
