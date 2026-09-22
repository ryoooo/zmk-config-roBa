#pragma once

#include <zmk/keymap.h>

/* Temporary layers must not lock themselves on activation or deactivation. */
#define zmk_keymap_layer_activate(layer) zmk_keymap_layer_activate((layer), false)
#define zmk_keymap_layer_deactivate(layer) zmk_keymap_layer_deactivate((layer), false)
