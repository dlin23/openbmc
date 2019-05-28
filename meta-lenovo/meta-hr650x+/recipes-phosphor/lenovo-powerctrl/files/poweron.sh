#"Copyright ? 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."

#!/bin/bash

GPIO_BASE=$(cat /sys/devices/platform/ahb/ahb:apb/1e780000.gpio/gpio/*/base)
GPIO_NUM=$(($GPIO_BASE + 64 + 0))

echo 1 > /sys/class/gpio/gpio${GPIO_NUM}/value
sleep 1
echo 0 > /sys/class/gpio/gpio${GPIO_NUM}/value

exit 0;
