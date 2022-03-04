# See
# https://www.xilinx.com/html_docs/xilinx2019_1/SDK_Doc/xsct/intro/xsct_introduction.html

setws .
if { $::argc == 1 } {
    set accname [lindex $::argv 0]
    createhw -name $accname\_hlsmover_platform -hwspec hdf/$accname\_hlsmover_design_wrapper.hdf
    createapp -name $accname\_hlsmover_standalone -app {Hello World} -proc ps7_cortexa9_0 -hwproject $accname\_hlsmover_platform -os standalone
    configapp -app $accname\_hlsmover_standalone -add linker-misc {-Wl,--defsym=_HEAP_SIZE=0x1000000}
    configapp -app $accname\_hlsmover_standalone -add linker-misc {-Wl,--defsym=_STACK_SIZE=0x40000}
}
