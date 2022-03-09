# CIFAR-10 image classification with hls4ml

## Setup

Use provided conda environment

```bash
conda create -f environment.yml
conda activate tiny-mlperf-env
```

## Training

To retrain the model from scratch, do
```
cd training
python train.py -c RN07.yml
```
or simply take the pretrained model from the `training/trained_model` subfodler.

## Inference and Synthesis

To convert the trained model into FPGA firmware do
```bash
cd inference/<device>
python ../convert.py -c <accuracy/power/accuracy_power>.py
```
For all, the same model is used, but minor changes are made to enable the power measurement on the Arty.