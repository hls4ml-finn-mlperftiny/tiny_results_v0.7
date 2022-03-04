## Build stitched-IP for MLPerf tiny and bitfile for Arty A7-100T

The build is currently configured for the Arty A7-100T board at a clock frequency of 100 MHz.

1. Copy the trained `conv-w1a1.onnx` model from the training folder to the model folder. The command is: `cp ../../training/cnv-w1a1.onnx models`
2. Launch the build as follows:
```shell
# cd to where the FINN compiler was cloned to
cd ../finn
# launch the build on the build foler
bash run-docker.sh build_custom ../arty-a7-100
```

## Creating the bare metal application for MLPerf tiny
The following steps are adapted from original instructions by Giuseppe:

1. Make sure the shell has access to the Vivado 2019.1 tools and SDK, by setting the PATH environment variable to include them.
2. For the Arty additionally make sure that the board definitions are installed to your Vivado installation.
   1. The board definition can be found here: https://github.com/Digilent/vivado-boards
   2. Instructions for the installation are here: https://digilent.com/reference/programmable-logic/guides/installing-vivado-and-sdk?redirect=1#installing_digilent_board_files
   3. Be sure to install the board definitoins from the mater branch of the mentioned github repository.
3. Run the Vivado project script: 

```shell
cd vivado_project/sys
make sys-hlsmover
```

3. The Vivado script essentially opens the FINN project and exports the HDF file for the SDK in the directory `vivado_project/sdk/hdf/`. Note that when we use HLS datamovers we don't have to create our own Vivado project (as with the AXI DMA IP).
4. Finally, let's create the SDK project + running it:
```shell
cd vivado_project/sdk
make hlsmover-sdk
make gui
```
5. This will pop up the SDK, close the "welcome" tab and you should have the baremetal app.
6. The SDK project now contains all harness files to build the harness and run the accelerator + harness on the FPGA.
7. Note: For accuracy/timing measurements the UART baud rate needs to be set to `115200`, while for power measurements the baud rate needs to be `9600`.
8. Program the FPGA with the bit file in SDK
   * <img width="600" alt="Screen Shot 2021-06-06 at 10 20 14 PM" src="https://user-images.githubusercontent.com/4932543/120962896-78ceee00-c715-11eb-8888-540dcf3bed39.png"/>
9. Run test harness software in SDK
   * <img width="600" alt="Screen Shot 2021-06-06 at 10 22 07 PM" src="https://user-images.githubusercontent.com/4932543/120963020-b6337b80-c715-11eb-93c7-e0de1fa2c070.png"/>
10. Download EEMBC runner GUI and for the dataset the KWS bin files have been re-quantized for this network, they can be found in the following folder, relative to here: `../../training/kws_bin_files`
11. Open EEMBC runner GUI and and perform measurements, follow the instructions on the eembc README 
   * <img width="400" alt="Screen Shot 2021-06-06 at 10 18 51 PM" src="https://user-images.githubusercontent.com/4932543/120962751-32798f00-c715-11eb-816a-c1ab4f11da47.png"/>
