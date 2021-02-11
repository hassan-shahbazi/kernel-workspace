obj-m += ktask06.o

ifndef $(build_dir)
	kernel_version = $(shell uname -r)
	build_dir = /lib/modules/$(kernel_version)/build
endif
kernel_module = ktask06.ko

all:
	make -C $(build_dir) M=$(PWD) modules

clean:
	make -C $(build_dir) M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod $(kernel_module)
	sudo ./script.sh
	sudo rmmod $(kernel_module)
	dmesg
