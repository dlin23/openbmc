//¡°Copyright ? 2019-present Lenovo
//Licensed under BSD-3, see COPYING.BSD file for details.¡±

#ifndef _FGPA_H
#define _FGPA_H

#include <linux/types.h>
#include <linux/ioctl.h>

#define UPDATE_RETRY_MAX 5

/* ioctl interface */
#define __JTAG_IOCTL_MAGIC	0xb2


#define JTAG_GIOCFREQ	          _IOR(__JTAG_IOCTL_MAGIC, 2, unsigned int)
#define JTAG_UPDATE_CPLD          _IOW(__JTAG_IOCTL_MAGIC, 5, struct _io_access_data)


typedef struct _io_access_data {
	unsigned char	type;
	unsigned long	address;
	unsigned long	data;
	unsigned long	value;
	unsigned long	i2cvalue;
	int		kernel_socket;
	unsigned long	input_buffer_base;
}io_access_data;

typedef io_access_data jtag_ioaccess_data;

int get_freq(unsigned int *value);
int update_cpld_start(int argvcnt,char **argv);

#endif /* _FGPA_H */