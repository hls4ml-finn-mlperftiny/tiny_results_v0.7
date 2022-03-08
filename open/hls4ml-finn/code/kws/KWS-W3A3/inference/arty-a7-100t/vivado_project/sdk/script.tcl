# See
# https://www.xilinx.com/html_docs/xilinx2019_1/SDK_Doc/xsct/intro/xsct_introduction.html

setws .
if { $::argc == 1 } {
    set accname [lindex $::argv 0]
    createhw -name $accname\_platform -hwspec hdf/$accname\_design_wrapper.hdf
    createapp -name $accname\_standalone -lang c++ -app {Empty Application} -proc microblaze_mcu -hwproject $accname\_platform -os standalone
    configapp -app $accname\_standalone build-config release
    configapp -app finn_kws_mlp_w3a3_standalone -add linker-misc {-Wl,--defsym=_HEAP_SIZE=0x1000000}
    configapp -app finn_kws_mlp_w3a3_standalone -add linker-misc {-Wl,--defsym=_STACK_SIZE=0x40000}
}
