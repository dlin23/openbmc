#"Copyright (c) 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
EXTRA_OECONF += " --enable-static-layout --enable-lpc-bridge --enable-aspeed-lpc MAPPED_ADDRESS=0x98000000"
