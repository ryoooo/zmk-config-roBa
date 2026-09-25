#include <stdbool.h>
#include <stdint.h>

#include <zmk/activity.h>

/* Only linked when CONFIG_ZMK_SLEEP=n. Accept an unchanged sleep timeout so
 * DYA can update idle and relay it to the peripheral. This also handles a
 * retained timeout from older firmware; deep sleep remains disabled.
 * Reject actual sleep changes instead of pretending to enable deep sleep.
 */
bool __wrap_zmk_activity_set_sleep_ms(uint32_t sleep_ms) {
    return sleep_ms == zmk_activity_get_sleep_ms();
}
