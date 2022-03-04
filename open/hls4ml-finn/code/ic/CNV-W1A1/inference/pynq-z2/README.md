## Build stitched-IP for MLPerf tiny and bitfile for PYNQ

The build is currently configured for the PYNQ-Z2 board at a clock frequency of 100 MHz.

1. Copy the trained `conv-w1a1.onnx` model from the training folder to the model folder. The command is: `cp ../../training/cnv-w1a1.onnx models`
2. Launch the build as follows:
```shell
# cd to where the FINN compiler was cloned to
cd ../finn
# launch the build on the build foler
bash run-docker.sh build_custom ../pynq-z2
```

## Creating the bare metal application for MLPerf tiny
The following steps are adapted from original instructions by Giuseppe:

1. Make sure the shell has access to the Vivado 2019.1 tools and SDK, by setting the PATH environment variable to include them.
2. Run the Vivado project script: 

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
