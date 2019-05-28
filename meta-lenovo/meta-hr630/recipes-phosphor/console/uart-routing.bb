#"Copyright (c) 2019-present Lenovo"

FILESEXTRAPATHS_append := "${THISDIR}/uart-routing:"
SUMMARY = "Hr630 Uart Routing"
PR = "r1"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${LENOVOBASE}/COPYING.BSD;md5=efc72ac5d37ea632ccf0001f56126210"

inherit obmc-phosphor-systemd
inherit systemd

S = "${WORKDIR}/"
SRC_URI = "file://cross-link.sh \
           file://uart-cross-link.service"

DEPENDS = "systemd"
RDEPENDS_${PN} = "bash"

SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE_${PN} = "uart-cross-link.service"

do_install() {
    install -d ${D}/usr/sbin
    install -m 0755 ${S}cross-link.sh ${D}/${sbindir}/
}
