#"Copyright (c) 2019-present Lenovo

SUMMARY = "hr855xg2 FRU properties config for ipmi-fru-parser"
PR = "r1"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${LENOVOBASE}/COPYING.BSD;md5=efc72ac5d37ea632ccf0001f56126210"

inherit native
inherit phosphor-ipmi-fru

SRC_URI += "file://extra-properties.yaml"

PROVIDES += "virtual/phosphor-ipmi-fru-properties"

S = "${WORKDIR}"

do_install() {
        # This recipe is supposed to create an output yaml file with
        # FRU property values extracted from the MRW. This example recipe
        # provides a sample output file.

        DEST=${D}${properties_datadir}
        install -d ${DEST}
        install extra-properties.yaml ${DEST}
}
