#!/bin/bash

echo -e "Change flash map area"

sed -i  '/FLASH (rx)      : ORIGIN = /c\FLASH (rx)      : ORIGIN = 0x08004000, LENGTH = 48K' ldscripts/AT32F421x8_FLASH.ld

sed -i  '/.*\/\/ nvic_vector_table/c\  nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x4000);' user/main.c

echo -e "Done"