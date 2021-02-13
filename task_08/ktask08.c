// SPDX-License-Identifier: GPL-2.0-only
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/fs.h>
#include <linux/slab.h>

MODULE_AUTHOR("Hassan Shahbazi");
MODULE_DESCRIPTION("Linux Kernel Mentorship task 08");
MODULE_LICENSE("GPL v2");

#define DIRECTORY	"eudyptula"

static struct dentry *eudyptula;
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

static int __init task_init(void)
{
	eudyptula = debugfs_create_dir(DIRECTORY, NULL);
	debugfs_create_file("id", 0755, eudyptula, NULL, &fops);
	return 0;
}
module_init(task_init);

static void __exit task_exit(void)
{
	debugfs_remove_recursive(eudyptula);
}
module_exit(task_exit);
