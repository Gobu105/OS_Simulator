#include<stdio.h>
#include<unistd.h>
#ifndef BIOS_H
#define BIOS_H
#include"../utils.h"

void bios() {
    yellow("🧠 BIOS: Power-On Self Test (POST)...\n");
    sleep(1);
    printf("✅ CPU OK\n");
    printf("✅ RAM OK\n");
    printf("✅ Keyboard Detected\n");
    sleep(1);
    yellow("🔍 Searching for bootable device...\n");
    sleep(1);
    green("💾 Bootable disk found! Loading bootloader...\n\n");
}

#endif
