require ofono.inc

SRC_URI  = "\
  ${KERNELORG_MIRROR}/linux/network/${BPN}/${BP}.tar.xz \
  file://ofono \
  file://0001-build-Fix-a-race-condition.patch \
  file://0001-build-Add-check-for-explicit_bzero-support.patch \
"
SRC_URI[md5sum] = "4fa0372630ff03f223452e4d05efa8f8"
SRC_URI[sha256sum] = "67f0f8e5740dea5b46309e40667d1e560be39c90ef08dd01ff9e9ce8e61f0679"
