#pragma once

#include <zmk/events/layer_state_changed.h>

/* The pinned DYA processor only tracks its own layer transitions. An external
 * &to / &mo release can turn the layer off without clearing its active flag,
 * preventing the next pointer movement from activating it again.
 * Included after input_processor_runtime.c to access that private state.
 */
static int roba_temp_layer_state_changed_listener(const zmk_event_t *eh) {
    const struct zmk_layer_state_changed *ev = as_zmk_layer_state_changed(eh);
    if (ev == NULL || zmk_keymap_layer_active(ev->layer)) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    for (size_t i = 0; i < runtime_processors_count; i++) {
        struct runtime_processor_data *data = runtime_processors[i]->data;
        if (data->temp_layer_layer != ev->layer) {
            continue;
        }

        data->temp_layer_layer_active = false;
        k_work_cancel_delayable(&data->temp_layer_activation_work);
        k_work_cancel_delayable(&data->temp_layer_deactivation_work);
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(roba_temp_layer_state_sync, roba_temp_layer_state_changed_listener);
ZMK_SUBSCRIPTION(roba_temp_layer_state_sync, zmk_layer_state_changed);
