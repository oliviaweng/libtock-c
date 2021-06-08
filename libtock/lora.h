#pragma once

#include "tock.h"

#define DRIVER_NUM_LORA 0x30003

// TODO: If we are using I2C, len needs to be of time uint8_t
int lora_set_tx_data(const char* buf, size_t len);