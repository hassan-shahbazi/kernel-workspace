obj-m += ktask05.o

ifndef $(build_dir)
	kernel_version = $(shell uname -r)
	build_dir = /lib/modules/$(kernel_version)/build
endif
kernel_module = ktask05.ko

all:
	make -C $(build_dir) M=$(PWD) modules

clean:
	make -C $(build_dir) M=$(PWD) clean
