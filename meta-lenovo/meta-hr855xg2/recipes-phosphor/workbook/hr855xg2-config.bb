SUMMARY = "hr855xg2 board wiring"
DESCRIPTION = "Board wiring information for the hr855xg2 system."
PR = "r1"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${LENOVOBASE}/COPYING.BSD;md5=efc72ac5d37ea632ccf0001f56126210"

inherit allarch
inherit setuptools
inherit pythonnative

PROVIDES += "virtual/obmc-inventory-data"
RPROVIDES_${PN} += "virtual-obmc-inventory-data"

DEPENDS += "python"

S = "${WORKDIR}"
SRC_URI += "file://Hr855xg2.py"

# the following is unnecessary.
python() {
        machine = d.getVar('MACHINE', True).capitalize() + '.py'
        d.setVar('_config_in_skeleton', machine)
}

do_make_setup() {
        cp ${S}/${_config_in_skeleton} \
                ${S}/obmc_system_config.py
        cat <<EOF > ${S}/setup.py
from distutils.core import setup

setup(name='${BPN}',
    version='${PR}',
    py_modules=['obmc_system_config'],
    )
EOF
}

addtask make_setup after do_patch before do_configure

