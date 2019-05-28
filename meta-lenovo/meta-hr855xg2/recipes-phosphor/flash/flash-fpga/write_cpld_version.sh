#"Copyright ? 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."

#!/bin/bash

#set cpld version to file /run/cpld{id}.version


version=`i2cget -y 1 0x44 1`
version=${version:2:3}
echo $version >/run/cpld0.version

