/* Host regression test for the listener; no Zephyr SDK required. */
#include <assert.h>
#include <zmk/events/layer_state_changed.h>

struct k_work_delayable {
    bool pending;
};
struct runtime_processor_data {
    uint8_t temp_layer_layer;
    bool temp_layer_layer_active;
    struct k_work_delayable temp_layer_activation_work;
    struct k_work_delayable temp_layer_deactivation_work;
};
struct device {
    struct runtime_processor_data *data;
};

static bool active_layers[8];
static bool zmk_keymap_layer_active(uint8_t layer) { return active_layers[layer]; }
static int k_work_cancel_delayable(struct k_work_delayable *work) {
    work->pending = false;
    return 0;
}

static struct runtime_processor_data mouse = {.temp_layer_layer = 4};
static struct runtime_processor_data scroll = {.temp_layer_layer = 5};
static const struct device devices[] = {{&mouse}, {&scroll}};
static const struct device *runtime_processors[] = {&devices[0], &devices[1]};
static const size_t runtime_processors_count = 2;

#include "../temp_layer_state_sync.h"

int main(void) {
    const zmk_event_t mouse_event = {.layer = 4};
    const zmk_event_t other_event = {.layer = 2};

    /* Repeat entry -> external &to 0 -> entry, including unrelated processors. */
    for (int i = 0; i < 3; i++) {
        assert(!mouse.temp_layer_layer_active);
        active_layers[4] = true;
        mouse.temp_layer_layer_active = true;
        mouse.temp_layer_deactivation_work.pending = true;
        scroll.temp_layer_layer_active = true;
        scroll.temp_layer_deactivation_work.pending = true;
        roba_temp_layer_state_changed_listener(&mouse_event);
        assert(mouse.temp_layer_layer_active);
        assert(mouse.temp_layer_deactivation_work.pending);

        roba_temp_layer_state_changed_listener(NULL);
        roba_temp_layer_state_changed_listener(&other_event);
        assert(mouse.temp_layer_layer_active);

        /* &to 0 clears the keymap layer, but upstream retains its active flag. */
        active_layers[4] = false;
        assert(mouse.temp_layer_layer_active);
        roba_temp_layer_state_changed_listener(&mouse_event);
        assert(!mouse.temp_layer_layer_active);
        assert(!mouse.temp_layer_deactivation_work.pending);
        assert(scroll.temp_layer_layer_active);
        assert(scroll.temp_layer_deactivation_work.pending);
    }

    /* External exit must also cancel activation queued by pointer movement. */
    mouse.temp_layer_activation_work.pending = true;
    roba_temp_layer_state_changed_listener(&mouse_event);
    assert(!mouse.temp_layer_activation_work.pending);
    return 0;
}
