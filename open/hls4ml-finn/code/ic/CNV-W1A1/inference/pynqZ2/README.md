## Build stitched-IP for MLPerf tiny and bitfile for PYNQ

The build is currently configured for the PYNQ-Z2 board at a clock frequency of 100 MHz.

1. Copy the trained `conv-w1a1.onnx` model from the training folder to the model folder. The command is: `cp ../../training/cnv-w1a1.onnx models`
2. Launch the build as follows:
```shell
# cd to where the FINN compiler was cloned to
cd ../finn
# launch the build on the build foler
bash run-docker.sh build_custom ../pynqZ2
```

## Creating the bare metal application for MLPerf tiny
The following steps are adapted from original instructions by Giuseppe:

1. Make sure the shell has access to the Vivado 2019.1 tools and SDK.
2. Run the Vivado project script: 

```shell
cd vivado_project
make run
```
3. This will pop up the SDK, close the "welcome" tab and you should have the baremetal app.

