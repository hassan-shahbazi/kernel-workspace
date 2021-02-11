// SPDX-License-Identifier: GPL-2.0-only
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int fd, r_ret, w_ret, ret;
	char id[256] = {0};
	char invalid_input[] = "abcd";
	char *valid_input = "19aa2fa32708";

	printf("starting the caller...\n");

	fd = open("/dev/eudyptula", O_RDWR);
	if (fd < 0) {
		printf("error in openning the module: %d\n", fd);
		ret = fd;
		goto exit;
	}

	r_ret = read(fd, id, strlen(valid_input));
	if (r_ret < 0) {
		printf("error in reading the id\n");
		ret = r_ret;
		goto exit;
	}
	printf("the id:%s was read from the device\n", id);

	printf("trying to write an invalid input\n");
	w_ret = write(fd, invalid_input, strlen(invalid));
	if (w_ret >= 0) {
		printf("the input should not be accepted\n");
		ret = w_ret;
		goto exit;
	}

	printf("trying to write the valid input\n");
	w_ret = write(fd, valid_input, 13);
	if (w_ret < 0) {
		printf("the input should be accepted\n");
		ret = w_ret;
		goto exit;
	}

exit:
	close(fd);
	return ret;
}
