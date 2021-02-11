// SPDX-License-Identifier: GPL-2.0-only
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/slab.h>

MODULE_AUTHOR("Hassan Shahbazi");
MODULE_DESCRIPTION("Linux Kernel Mentorship task 06");
MODULE_LICENSE("GPL v2");

#define DEVICE_NAME	"eudyptula"

static char *id = "19aa2fa32708";

static ssize_t
f_read(struct file *f, char __user *buff, size_t size, loff_t *loff)
{
	return simple_read_from_buffer(buff, size, loff, id, strlen(id));
}

static ssize_t
f_write(struct file *f, const char *buff, size_t size, loff_t *loff)
{
	char *input = kmalloc(size+1, GFP_KERNEL);
	int ret = 0;

	if (size-1 != strlen(id)) {
		ret = -EINVAL;
		goto exit;
	}

	ret = simple_write_to_buffer(input, size, loff, buff, size);
	if (ret != size)
		goto exit;

	if (strncmp(input, id, strlen(id)) != 0) {
		ret = -EINVAL;
		goto exit;
	}

exit:
	kfree(input);
	return ret;
}

static const struct file_operations fops = {
	.owner		= THIS_MODULE,
	.write		= f_write,
	.read		= f_read,
	.llseek		= no_llseek,
};

struct miscdevice device = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= DEVICE_NAME,
	.fops	= &fops,
};

static int __init task_init(void)
{
	return misc_register(&device);
}
module_init(task_init);

static void __exit task_exit(void)
{
	misc_deregister(&device);
}
module_exit(task_exit);
