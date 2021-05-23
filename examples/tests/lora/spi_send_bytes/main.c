#include <led.h>
#include <spi.h>
#include <timer.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <console.h>

static void nop(
  int a __attribute__((unused)),
  int b __attribute__((unused)),
  int c __attribute__((unused)),
  void* d __attribute__((unused))) {}

// This callback occurs when a read_write call completed.
// Note that we do not start another transfer here.
static void write_cb(__attribute__ ((unused)) int arg0,
                     __attribute__ ((unused)) int arg2,
                     __attribute__ ((unused)) int arg3,
                     __attribute__ ((unused)) void* userdata) {
  printf("Transfer complete.\n");
}


// char digits[] = "012345\r\n";
char buf[] = "A\r\n";
char read_write[] = "read_write return code\r\n";


#define BUF_SIZE 16
char rbuf[BUF_SIZE];
char wbuf[BUF_SIZE];

int main(void) {
  int i;
  int return_code;

  for (i = 0; i < BUF_SIZE; i++) {
    wbuf[i] = 0xA5;
    rbuf[i] = 0;
  }

  // NOTE: No need to chip select since it just relies on the hardcoded chip select
  // return_code = spi_set_chip_select(1);

  for (i = 0; ; i++) {
    led_off(0);
    return_code = spi_read_write(wbuf, rbuf, BUF_SIZE, write_cb, NULL);
    // return_code = spi_write_byte((unsigned char)i & 0xff); // NOTE: NOT supported by Tock capsules/src/spi_controller.rs
    putnstr_async(read_write, strlen(read_write), nop, NULL);
    buf[0] = return_code + '1';
    putnstr_async(buf, strlen(buf), nop, NULL);
    delay_ms(25);

    led_on(0);

    delay_ms(25);
  }

  return 0;
}
