# See
# https://www.xilinx.com/html_docs/xilinx2019_1/SDK_Doc/xsct/intro/xsct_introduction.html

setws .
if { $::argc == 1 } {
    set accname [lindex $::argv 0]
    createhw -name $accname\_platform -hwspec hdf/$accname\_design_wrapper.hdf
    createapp -name $accname\_standalone -app {Hello World} -proc microblaze_mcu -hwproject $accname\_platform -os standalone
    configapp -app $accname\_standalone build-config release
    configapp -app finn_cnv_w1a1_standalone -add linker-misc {-Wl,--defsym=_HEAP_SIZE=0x1000000}
    configapp -app finn_cnv_w1a1_standalone -add linker-misc {-Wl,--defsym=_STACK_SIZE=0x40000}
}
