#"Copyright (c) 2019-present Lenovo"

SUMMARY = "Hr630 FRU properties config for ipmi-fru-parser"
PR = "r1"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${LENOVOBASE}/COPYING.BSD;md5=efc72ac5d37ea632ccf0001f56126210"

inherit native
inherit phosphor-ipmi-fru

PROVIDES += "virtual/phosphor-ipmi-fru-properties"

SRC_URI += "file://extra-properties.yaml"
S = "${WORKDIR}"

do_install() {
    DEST=${D}${properties_datadir}
    install -d ${DEST}
    install extra-properties.yaml ${DEST}
}
