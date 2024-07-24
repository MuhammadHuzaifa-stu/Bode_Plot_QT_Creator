# Bode Plot Application

## Overview

This project is a Bode Plot Application built using C++ and Qt. It allows users to input the numerator and denominator of transfer functions and generate Bode plots for magnitude and phase. The application also includes functionality for checking the stability of the system based on the input coefficients.

## Features

- **Bode Plot Generation**: Plots magnitude and phase response based on user-defined transfer functions.
- **Stability Analysis**: Checks the stability of the system by analyzing the poles of the transfer function.
- **Interactive Plots**: Allows zooming and panning of plots for better visualization.

## Requirements

- **Qt Framework**: This project uses Qt for the graphical user interface.
- **Eigen Library**: Required for polynomial root-finding and stability analysis.

## Installation

1. **Clone the Repository**:

    ```bash
    git clone https://github.com/yourusername/your-repository-name.git
    cd your-repository-name
    ```

2. **Install Dependencies**:

    Make sure you have the Qt framework and Eigen library installed on your system. You can download Eigen from [Eigen's official site](https://eigen.tuxfamily.org/dox/GettingStarted.html).

3. **Configure the Project**:

    Open the `.pro` file in Qt Creator or any other Qt-compatible IDE and ensure that the path to the Eigen library is correctly set:

    ```pro
    INCLUDEPATH += D:/Softwares_Installed/QT_Creator/eigen-3.4.0
    ```

4. **Build the Project**:

    Use Qt Creator to build and run the project. Alternatively, you can use the command line:

    ```bash
    qmake
    make
    ```

## Usage

1. **Start the Application**:

    Launch the application from Qt Creator or the executable file generated during the build process.

2. **Input Data**:

    - **Numerator**: Enter the coefficients of the numerator polynomial separated by spaces.
    - **Denominator**: Enter the coefficients of the denominator polynomial separated by spaces.

3. **Generate Plots**:

    Click the "Plot" button to generate Bode plots for magnitude and phase. The plots will be displayed in the application window.

4. **Check Stability**:

    The stability of the system is analyzed and displayed based on the input coefficients.

## Functionality

- **Bode Plot**: Generates and displays magnitude and phase plots based on the transfer function.
- **Stability Check**: Analyzes the system's stability by examining the roots of the denominator polynomial.

## Example

To use the application, enter the coefficients of a transfer function in the numerator and denominator fields. For example:

- **Numerator**: `1 0 0`
- **Denominator**: `1 3 3 1`

Click "Plot" to see the Bode plots and stability status.
