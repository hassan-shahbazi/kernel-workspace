#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Hassan Shahbazi");
MODULE_DESCRIPTION("Linux Kernel Mentorship task 01");
MODULE_LICENSE("GPL");

static int __init task_init(void) {
    printk(KERN_INFO "Hello World!\n");
    return 0;
}

static void __exit task_exit(void) {
    printk(KERN_INFO "Goodby!\n");
}

module_init(task_init);
module_exit(task_exit);
