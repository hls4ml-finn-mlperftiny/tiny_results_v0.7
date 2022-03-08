## Build stitched-IP for MLPerf tiny and bitfile for Arty A7-100T

The build is currently configured for the Arty A7-100T board and a throughput of about 200k FPS at a clock frequency of 100 MHz.

1. Copy the trained `QONNX_model.onnx` model from the training folder. The command is: `cp ../../training/training_checkpoint/QONNX_model.onnx .`
2. (Optional) Download the pre-processed validation data using the `get-kws-data.sh` script.
3. Launch the build as follows:
```shell
# cd to where the FINN compiler was cloned to
cd ../finn
# launch the build on the build folder
bash run-docker.sh build_custom ../arty-a7-100t
```

4. The generated outputs will be exported to a folder called `<timestamp>_output_<onnx_file_name>_<platform>`. 
You can find a description of the generated files [here](https://finn-dev.readthedocs.io/en/latest/command_line.html#simple-dataflow-build-mode).
The folder will additionally include the quantized inputs for verification (`all_validation_KWS_data_inputs_len_10102.npy`) and the expected outputs (`all_validation_KWS_data_outputs_len_10102.npy`).
When running the network on hardware the validation should achieve an accuracy of about 84.6 %. Note that this accuracy is NOT the test accuracy, but the validation accuracy. Verifying the test accuracy can be done with the the bare metal application and the re-quantized bin files described in the next section.

## Creating the bare metal application for MLPerf tiny
The following steps are adapted from original instructions by Giuseppe:

1. Make sure the shell has access to the Vivado 2019.1 tools and SDK, by setting the PATH environment variable to include them.
2. For the Arty additionally make sure that the board definitions are installed to your Vivado installation.
   1. The board definition can be found here: https://github.com/Digilent/vivado-boards
   2. Instructions for the installation are here: https://digilent.com/reference/programmable-logic/guides/installing-vivado-and-sdk?redirect=1#installing_digilent_board_files
   3. Be sure to install the board definitions from the mater branch of the mentioned GitHub repository.
3. Two separate builds for accuracy/timing and for power measurements can be synthesised. To select which one is built line 6 in the file `vivado_project/sys/tcl/script_axidma.tcl` must be changed.
   1. Accuracy/timing measurements: Set the line to: `set eembc_power 0`
   2. Power measurements: Set the line to: `set eembc_power 1`
4. Run the Vivado project script: 

```shell
cd vivado_project/sys
make sys
```

4. The Vivado script essentially opens the FINN project and exports the HDF file for the SDK in the directory `vivado_project/sdk/hdf/`. Note that when we use HLS datamovers we don't have to create our own Vivado project (as with the AXI DMA IP).
5. Finally, let's create the SDK project + running it:
```shell
cd vivado_project/sdk
make sdk
make gui
```
6. This will pop up the SDK, close the "welcome" tab and you should have the bare metal app.
7. The SDK project now contains all harness files to build the harness and run the accelerator + harness on the FPGA.
8. Program the FPGA with the bit file in the SDK. The screenshot below highlights the corresponding context menu and button to press.
 * <img width="600" alt="Screen Shot 2021-06-06 at 10 20 14 PM" src="https://user-images.githubusercontent.com/4932543/120962896-78ceee00-c715-11eb-8888-540dcf3bed39.png"/>
9. Build the software project, **then** run test harness software in the SDK. The screenshot below highlights the button for running the harness. The button for building the software project can be found in the same context menu, further above the "Run as" filed.
 * <img width="600" alt="Screen Shot 2021-06-06 at 10 22 07 PM" src="https://user-images.githubusercontent.com/4932543/120963020-b6337b80-c715-11eb-93c7-e0de1fa2c070.png"/>
11. Download EEMBC runner GUI and for the dataset the KWS bin files have been re-quantized for this network, they can be found in the following folder, relative to here: `../../training/kws_bin_files`
12. Open EEMBC runner GUI and and perform measurements, follow the instructions in the eembc README.
