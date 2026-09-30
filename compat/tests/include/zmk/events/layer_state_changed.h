#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct zmk_layer_state_changed {
    uint8_t layer;
};
typedef struct zmk_layer_state_changed zmk_event_t;

static inline const struct zmk_layer_state_changed *
as_zmk_layer_state_changed(const zmk_event_t *event) {
    return event;
}

#define ZMK_EV_EVENT_BUBBLE 0
#define ZMK_LISTENER(...)
#define ZMK_SUBSCRIPTION(...)
