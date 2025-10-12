#include<stdio.h>
#include<unistd.h>
#ifndef BIOS_H
#define BIOS_H

void bios() {
    printf("🧠 BIOS: Power-On Self Test (POST)...\n");
    sleep(2);
    printf("✅ CPU OK\n");
    printf("✅ RAM OK\n");
    printf("✅ Keyboard Detected\n");
    sleep(2);
    printf("🔍 Searching for bootable device...\n");
    sleep(2);
    printf("💾 Bootable disk found! Loading bootloader...\n\n");
}

#endif
