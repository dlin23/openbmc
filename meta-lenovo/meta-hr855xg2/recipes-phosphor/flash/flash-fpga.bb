#"Copyright (c) 2019-present Lenovo

FILESEXTRAPATHS_append := "${THISDIR}/flash-fpga:"
SUMMARY = "Phosphor OpenBMC fpga test."
DESCRIPTION = "Phosphor OpenBMC fpga test."
PR = "r1"
#FILESEXTRAPATHS_append := "${THISDIR}/files:"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${LENOVOBASE}/COPYING.BSD;md5=efc72ac5d37ea632ccf0001f56126210"

inherit pkgconfig
inherit obmc-phosphor-sdbus-service
inherit obmc-phosphor-c-daemon

PROVIDES += "virtual/flash-fpga"
RPROVIDES_${PN} += "virtual-flash-fpga"
RDEPENDS_${PN} = "bash"

S = "${WORKDIR}/"
SRC_URI += "file://Makefile \
	file://main.c \
	file://fpga.c \
	file://fpga.h \
        file://write_cpld_version.sh \
           "


do_install() {
    install -d ${D}/usr/sbin
    install -m 0755 ${S}write_cpld_version.sh ${D}/${sbindir}/

}
