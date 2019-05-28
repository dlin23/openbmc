#"Copyright (c) 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."

#!/bin/bash
GPIO_BASE=$(cat /sys/class/gpio/gpio*/base)
GPIO_NUM=$(($GPIO_BASE + 64))
PWR_GOOD=$(($GPIO_BASE + 201))

st=$(cat /sys/class/gpio/gpio${PWR_GOOD}/value)

if [ "$st" != "0" ]; then
echo 1 > /sys/class/gpio/gpio${GPIO_NUM}/value
    sleep 6
echo 0 > /sys/class/gpio/gpio${GPIO_NUM}/value
fi

exit 0;
