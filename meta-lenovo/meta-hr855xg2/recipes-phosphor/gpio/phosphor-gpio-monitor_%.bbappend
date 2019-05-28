#"Copyright ? 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."


SUMMARY = "Phosphor IPMI Inventory Plugin"
DESCRIPTION = "A Phosphor IPMI plugin that updates inventory."
PR = "r1"
PV = "1.0+git${SRCPV}"

inherit autotools pkgconfig
inherit obmc-phosphor-systemd
inherit obmc-phosphor-ipmiprovider-symlink
inherit phosphor-ipmi-fru
inherit pythonnative
