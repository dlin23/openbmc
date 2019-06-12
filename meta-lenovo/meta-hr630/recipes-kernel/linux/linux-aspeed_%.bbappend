#"Copyright (c) 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."


FILESEXTRAPATHS_prepend_hr630 := "${THISDIR}/${PN}:"
SRC_URI += "file://aspeed-bmc-lenovo-hr630.dts \
            file://hr630.cfg \
            "
     
#SRC_URI += "file://0001-Add_hr630_dts_file.patch"             
			

do_configure_append() {

	myfile="../aspeed-bmc-lenovo-hr630.dts"
	
	if [ ! -f $myfile ]; then
		echo $myfile" is not exist"	
	else
		cp ../aspeed-bmc-lenovo-hr630.dts  ./source/arch/arm/boot/dts/
	fi	
}



