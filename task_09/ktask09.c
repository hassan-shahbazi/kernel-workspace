// SPDX-License-Identifier: GPL-2.0-only
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/jiffies.h>
#include <linux/semaphore.h>

MODULE_AUTHOR("Hassan Shahbazi");
MODULE_DESCRIPTION("Linux Kernel Mentorship task 09");
MODULE_LICENSE("GPL v2");

#define DIRECTORY	"eudyptula"

static DEFINE_MUTEX(foo_busy);
static struct kobject *eudyptula;
static char *id = "19aa2fa32708";
static char foo[PAGE_SIZE];

static ssize_t
id_show(struct device *dev, struct device_attribute *attr, char *buff)
{
	return sysfs_emit(buff, "%s", id);
}
static ssize_t
jiffies_show(struct device *dev, struct device_attribute *attr, char *buff)
{
	return sysfs_emit(buff, "%lu", jiffies);
}

static ssize_t
foo_show(struct device *dev, struct device_attribute *attr, char *buff)
{
	mutex_lock(&foo_busy);
	sysfs_emit(buff, "%s", foo);
	mutex_unlock(&foo_busy);

	return strlen(buff);
}

static ssize_t
id_store(struct device *dev, struct device_attribute *attr,
		const char *buff, size_t size)
{
	if (size-1 != strlen(id))
		return -EINVAL;
	if (strncmp(buff, id, strlen(id)) != 0)
		return -EINVAL;
	return strlen(buff);
}

static ssize_t
foo_store(struct device *dev, struct device_attribute *attr,
		const char *buff, size_t size)
{
	mutex_lock(&foo_busy);
	strncpy(foo, buff, size);
	mutex_unlock(&foo_busy);

	return strlen(foo);
}

static struct device_attribute id_device_attr = __ATTR_RW(id);
static struct device_attribute jiffies_device_attr = __ATTR_RO(jiffies);
static struct device_attribute foo_device_attr = __ATTR_RW(foo);

static struct attribute *attrs[] = {
	&id_device_attr.attr,
	&jiffies_device_attr.attr,
	&foo_device_attr.attr,
	NULL,
};
static struct attribute_group attr_group = {
	.attrs = attrs,
};

static int __init task_init(void)
{
	int ret;

	eudyptula = kobject_create_and_add(DIRECTORY, kernel_kobj);
	if (!eudyptula)
		return -EINVAL;

	ret = sysfs_create_group(eudyptula, &attr_group);
	if (ret)
		kobject_put(eudyptula);

	return ret;
}
module_init(task_init);

static void __exit task_exit(void)
{
	kobject_put(eudyptula);
}
module_exit(task_exit);
