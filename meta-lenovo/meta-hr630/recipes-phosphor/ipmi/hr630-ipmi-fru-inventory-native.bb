#"Copyright (c) 2019-present Lenovo"

SUMMARY = "Hr630 IPMI to DBus Inventory mapping."
PR = "r1"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${LENOVOBASE}/COPYING.BSD;md5=efc72ac5d37ea632ccf0001f56126210"

inherit native
inherit phosphor-ipmi-fru

PROVIDES += "virtual/phosphor-ipmi-fru-inventory"

SRC_URI += "file://config.yaml"
S = "${WORKDIR}"

do_install() {
    DEST=${D}${config_datadir}
    install -d ${DEST}
    install config.yaml ${DEST}
}
