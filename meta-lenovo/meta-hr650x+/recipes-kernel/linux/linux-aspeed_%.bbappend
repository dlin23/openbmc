#"Copyright ? 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."


FILESEXTRAPATHS_prepend_hr650x+ := "${THISDIR}/${PN}:"
SRC_URI += "file://aspeed-bmc-lenovo-hr650x+.dts \
            file://hr650x+.cfg \
            "
     
			

do_configure_append() {

	myfile="../aspeed-bmc-lenovo-hr650x+.dts"
	
	if [ ! -f $myfile ]; then
		echo $myfile" is not exist"	
	else
		cp ../aspeed-bmc-lenovo-hr650x+.dts  ./source/arch/arm/boot/dts/
	fi	
}


FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

