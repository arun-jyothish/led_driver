CONFIG_MODULE_SIG=n
CROSS_COMPILE= /home/arun/new/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
EXTRA_CFLAGS += $(CFLAGS_EXTRA) -fno-pie

ARCH=arm

obj-m += gpio.o

# arm_dir = /home/arun/new/linux
arm_dir = /home/arun/Technexion/tech/linux

final:
	@echo ${ARCH}
	@echo ${CROSS_COMPILE}
	@echo
	@echo	${PWD}
	@echo
	make -C ${arm_dir} M=${PWD} modules
clean:
	make -C ${arm_dir} M=${PWD} clean

