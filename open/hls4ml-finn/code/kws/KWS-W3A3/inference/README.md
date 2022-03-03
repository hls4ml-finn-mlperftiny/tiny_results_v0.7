# Building the FINN bitfiles


## Setup

1. Run the `get-finn.sh` under this directory to clone FINN at the appropriate commit. Note that you may have
to do this again in the future when the `finn-examples` repo gets updated and requires FINN at a newer commit.

2. Ensure you have the [requirements](https://finn.readthedocs.io/en/latest/getting_started.html#requirements) for FINN installed, which includes
Docker community edition `docker-ce`.

3. Set up the environment variables to point to your Vivado/Vitis installation, depending on your target platform(s):
    *  For Zynq platforms you'll need to set `VIVADO_PATH`, e.g. `VIVADO_PATH=/opt/xilinx/Vivado/2019.1/`
    * For Alveo platforms you'll need to set `VITIS_PATH`, `PLATFORM_REPO_PATHS` and `XILINX_XRT`

## Build bitfiles

Please see the READMEs under the respective subfolders here for instructions on how to rebuild the bitfiles.
