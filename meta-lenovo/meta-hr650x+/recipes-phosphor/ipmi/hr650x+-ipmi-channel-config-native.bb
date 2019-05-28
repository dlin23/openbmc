SUMMARY = "Hr650x+ IPMI Channel to if_name mapping."
PR = "r1"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${LENOVOBASE}/COPYING.BSD;md5=efc72ac5d37ea632ccf0001f56126210"

inherit native
inherit phosphor-ipmi-host

PROVIDES += "virtual/phosphor-ipmi-channel-config"

SRC_URI += "file://channel.yaml"

S = "${WORKDIR}"

do_install() {
	DEST=${D}${sensor_datadir}
        install -d ${DEST}
	install channel.yaml ${DEST}/channel.yaml
}
