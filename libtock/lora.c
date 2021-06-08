#include "lora.h"

// TODO: If we are using I2C, len needs to be of type uint8_t
int lora_set_tx_data(const char* buf, size_t len) {
    // TODO: Add callback subscribe stuff
    allow_ro_return_t aval = allow_readonly(DRIVER_NUM_LORA, 0, buf, len);

    if (aval.success == 0) {
        return tock_status_to_returncode(aval.status);
    }
    
    syscall_return_t cval = command(DRIVER_NUM_LORA, 1, len, 0);
    return tock_command_return_novalue_to_returncode(cval);
}
