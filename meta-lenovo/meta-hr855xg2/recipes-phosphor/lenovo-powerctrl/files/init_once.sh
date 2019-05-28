#"Copyright ? 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."


#!/bin/bash

# Set all output GPIOs as such and drive them with reasonable values.
function set_gpio_active_low() {
  if [ $# -ne 2 ]; then
    echo "set_gpio_active_low: need both GPIO# and initial level";
    return;
  fi

  echo $1 > /sys/class/gpio/export
  echo 1 > /sys/class/gpio/gpio$1/active_low
  echo $2 > /sys/class/gpio/gpio$1/direction
}

GPIO_BASE=$(cat /sys/devices/platform/ahb/ahb:apb/1e780000.gpio/gpio/*/base)

# FP_PWR_BTN_PASS_R_N, GPIO I0, active low
set_gpio_active_low $((${GPIO_BASE} + 64 + 0)) high

exit 0;
