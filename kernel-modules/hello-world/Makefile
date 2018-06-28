modname := hello-world
obj-m += $(modname).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load:
	-rmmod $(modname)
	insmod $(modname).ko

unload:
	-rmmod $(modname)