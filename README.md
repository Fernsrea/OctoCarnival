# Bilinear Interpolation Image Rescaling

This C++ program demonstrates the use of bilinear interpolation to resize an input image by a specified scale factor. Bilinear interpolation is a technique for estimating pixel values at non-integer coordinates, resulting in smoother image resizing compared to traditional methods.

## Table of Contents
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Compilation](#compilation)
- [Example](#example)

## Prerequisites

- CMake (version 3.10 or higher)
- OpenCV (Open Source Computer Vision Library)

Make sure you have these prerequisites installed on your system before proceeding with the compilation and usage of the program.

## Usage

To use this program, follow these steps:

1. Clone or download this repository to your local machine.
2. Open a terminal and navigate to the project directory.

## Compilation

Before compiling the program, make sure you have CMake and OpenCV installed. To compile the program, follow these steps:

1. Open a terminal and navigate to the project directory.
2. Run the following commands:

```sh
mkdir build
cd build
cmake ..
make
```

This will generate an executable named `MyProject` in the `build` directory.

## Example

To run the program, use the following syntax:

```sh
./MyProject <input_image> <output_image> <scale>
```

- `<input_image>`: Absolute Path to the input image file.
- `<output_image>`: Absolute Path to save the resized output image.
- `<scale>`: Scaling factor (float) to resize the image.

For example:

```sh
./MyProject input.jpg output.jpg 1.3
```

This command will resize the `input.jpg` image by a scale factor of 1.3 and save the result as `output.jpg`.

The program waits for user to enter a key to close the images and end the program.

---

**CMakeLists.txt**

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)
find_package(OpenCV REQUIRED)
add_executable(MyProject BilinearInterpolation.cpp)
target_link_libraries(MyProject ${OpenCV_LIBS})
```

This `CMakeLists.txt` file sets up the CMake configuration for building the project. It specifies the minimum required CMake version, identifies the project name, finds the OpenCV package, compiles the `BilinearInterpolation.cpp` source file, and links the project with the necessary OpenCV libraries.

---

Enjoy experimenting with bilinear interpolation for image resizing!
