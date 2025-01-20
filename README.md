# Linux Kernel Module: mkloubert.ko

This repository contains a simple Linux kernel module named **mkloubert**. The module creates a proc entry in the Linux virtual filesystem, allowing users to read a simple message ("Hail to The GitFather!\n") from `/proc/mkloubert`.

## Features

- demonstrates basic Linux kernel module development
- creates a proc entry in `/proc`
- responds with a predefined message when the proc entry is read by `cat` e.g.

## Tested Environment

This kernel module was tested in a virtual machine created using [Multipass](https://multipass.run/).

## Prerequisites

To build and install the module, ensure the following software is installed on your Ubuntu system:

1. **Linux headers**:
   ```bash
   sudo apt update
   sudo apt install linux-headers-$(uname -r)
   ```

2. **Build-essential tools**:
   ```bash
   sudo apt install build-essential
   ```

3. **Make utility**:
   Make is included with the `build-essential` package, but you can verify its presence:
   ```bash
   make --version
   ```

## Build Instructions

Follow these steps to build the kernel module:

1. Clone this repository and switch to new sub-directory `mkloubert_kernel_module`.

2. Use the included Makefile to build the module:
   ```bash
   make
   ```
   The `mkloubert.ko` file (kernel object file) will be created in the current directory.

## Installation Instructions

To load and test the module:

1. **Insert the module into the kernel**:
   ```bash
   sudo insmod mkloubert.ko
   ```

2. **Verify that the module is loaded**:
   ```bash
   lsmod | grep mkloubert
   ```

4. **Check kernel logs**:
   ```bash
   sudo dmesg
   ```

4. **Read from the proc entry**:
   ```bash
   cat /proc/mkloubert
   ```
   You should see the output:
   ```
   Hail to The GitFather!
   ```

5. **Remove the module from the kernel**:
   ```bash
   sudo rmmod mkloubert
   ```

6. **Clean up build files**:
   ```bash
   make clean
   ```

## File Descriptions

- [mkloubert.c](./mkloubert.c): the source code of the kernel module
- [Makefile](./Makefile): automates the building and cleaning of the kernel module

## Notes

- modifying kernel space can be dangerous!!!: always test in a virtual environment or non-critical system!!!
- ensure you are using the correct kernel headers for your current kernel version!!!

## License

This project is licensed under the [GPL License](https://www.gnu.org/licenses/gpl-3.0.en.html).

## Credits

This repository is inspired by [How to Create Linux Device Drivers @ FreeCodeCamp](https://www.freecodecamp.org/news/how-to-create-linux-device-drivers/).
