#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include"Booting_Stimulator/BIOS.h"
#include"Booting_Stimulator/BootLoader.h"
#include"Booting_Stimulator/Kernel.h"
#include"Booting_Stimulator/Shell.h"

int main() {
    printf("💡 Powering ON system...\n\n");
    bios();
    bootloader();
    kernel();
    shell();
    printf("\n💤 System powered off.\n");
    return 0;
}
