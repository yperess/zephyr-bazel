# Pigweed: minimal Bazel example

This repository contains a minimal example of a Bazel-based Pigweed project.
It's an echo application for the STM32F429 Discovery Board.

## Cloning

```
git clone --recursive https://pigweed.googlesource.com/example/echo
```

If you already cloned but forgot to include `--recursive`, run `git submodule
update --init` to pull all submodules.

TODO: b/300695111 - Don't require submodules for this example.

## Building

To build for the host, run

```
bazel build //...
```

To build for the STM32 Discovery Board:

```
bazel build --platforms=//target:stm32 //...
```

## Flashing

TODO: b/299994234 - Add tools and instructions for flashing.

## Running

TODO: b/299994234 - Add tools and instructions for talking to the device after
flashing.
