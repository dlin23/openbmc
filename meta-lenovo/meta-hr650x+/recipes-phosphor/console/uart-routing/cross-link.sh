#"Copyright ? 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."

#!/bin/sh

# BMC use one UART3 controller to cross link with Host System COM port (UART 1) to function as SOL
mknod -m 660 /dev/mem c 1 1
devmem 0x1E78909C 32 0x01450000
devmem 0x1E789098 32 0x00000A30
devmem 0x1E78909C
devmem 0x1E789098

devmem 0x1E6E2000 32 0x1688A8A8
devmem 0x1E6E2084 32 0xFFFFF000
devmem 0x1E6E2090 32 0x07FF0004
devmem 0x1E6E2000 32 0x00000000
unlink /dev/mem
