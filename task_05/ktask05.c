// SPDX-License-Identifier: GPL-2.0-only
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/hid.h>

MODULE_AUTHOR("Hassan Shahbazi");
MODULE_DESCRIPTION("Linux Kernel Mentorship task 05");
MODULE_LICENSE("GPL v2");

static int skel_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	pr_debug("USB is connected!\n");
	return 0;
}

static void skel_disconnect(struct usb_interface *intf)
{
	pr_debug("USB is disconnected\n");
}

static struct usb_device_id skel_table[] = {
	{ USB_INTERFACE_INFO(
		USB_INTERFACE_CLASS_HID,
		USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_KEYBOARD) },
	{},
};
MODULE_DEVICE_TABLE(usb, skel_table);

