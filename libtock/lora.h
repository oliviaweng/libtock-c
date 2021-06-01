#pragma once

#include "tock.h"

#define DRIVER_NUM_LORA 0x30003

int lora_set_tx_data(const char* buf, size_t len);