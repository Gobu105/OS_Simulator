#include<stdio.h>
#include<unistd.h>
#ifndef BOOTLOADER_H
#define BOOTLOADER_H


void bootloader(){
	printf("🚀 Bootloader: Loading kernel into memory...\n");
    	sleep(2);
   	printf("📦 Kernel loaded successfully.\n");
	sleep(2);
	printf("🧭 Transferring control to kernel...\n\n");
}

#endif
