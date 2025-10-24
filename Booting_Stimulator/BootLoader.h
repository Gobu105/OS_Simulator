#include<stdio.h>
#include<unistd.h>
#ifndef BOOTLOADER_H
#define BOOTLOADER_H
#include"../utils.h"

void bootloader(){
	yellow("🚀 Bootloader: Loading kernel into memory...\n");
    	sleep(1);
   	green("📦 Kernel loaded successfully.\n");
	sleep(1);
	yellow("🧭 Transferring control to kernel...\n\n");
}

#endif
