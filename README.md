# EOOS Automotive FreeRTOS
---

**EOOS copyrights reserved in [Rospatent Federal Service for Intellectual Property]( https://www1.fips.ru/registers-doc-view/fips_servlet?DB=EVM&DocNumber=2017664105&TypeFile=html), Russian Federation**

EOOS Automotive for FreeRTOS operating system is a **C++ library for cross-platform development** of 
applications in automotive sphere. The library is developed in **C++98** programming language and supports 
features of **C++11** programming language depending on compiler options that 
**allows to consider wide criteria when selecting a suitable programming language** on initiation step 
of product development.

EOOS Automotive FreeRTOS is developed within **ISO C++ standards**, complied with **MISRA C++:2008** and 
**AUTOSAR C++14 Coding Guidelines**, and relies on **ISO 26262** that means applications based on EOOS 
**can be used in critical and safety-related systems**.

---

## 1. About The Project

The FreeRTOS operating system has wide number of ports for wide number of MCUs. 
This project provides exactly one MCU port for exactly one PCB board, 
which is the EOOS deep elaborated approach.

- Architecture: ARMv7-M
- Processor: Cortex-M3
- Vendor: Hangshun Chip HK32F103VET6 (STM32F103xx compatible)
- Board: Hangshun Chip HK32F103VET6 Development Board v1.00 2022.01.20



## 2. How-to Build Project

EOOS is a static library for linkage with other applications. This EOOS project based on Keil project that 
builds the static library within application source code and links all the object files to a binary file 
to burn the target MCU.

This build procedure mostly is given as an example, because all the source code can be built with any C++ 
cross compilers for the appropriate processor architecture on any host operating systems under 
any projects not only Keil.


#### 2.1. Prerequisites on Windows

The process described below is passed on 

- Windows 11 (64-bit)

and requires the next tool to be installed on it:

###### 2.1.1. Install [Git for Windows](https://git-scm.com/downloads)

The installer automatically sets the *Path* system environment variable.
But you have to set manually *C:\Program Files\Git\binpath* to the *Path* user environment variable to execute Bash if it needs. 
After the installation, check in CMD that tool is executed properly by executing the following commands.

```
C:\> git --version
git version 2.26.0.windows.1
 
C:\> bash --version
GNU bash, version 4.4.23(1)-release (x86_64-pc-msys)
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
 
This is free software; you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

###### 2.1.2. Install [IDE Keil uVision v5.37.0.0 or higher](https://www.keil.com/download/)

The IDE must be licensed for the MDK-ARM Plus product. Check it in the program menu *File -> License Management*.

###### 2.1.3. Install ARM GNU Toolchain [GCC arm-none-eabi v11.2 2022.02 or higher](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

EOOS is developed within ISO C++ standards and can be compiled with any cross compilers, 
which support ISO/IEC 14882:1998 standard and ISO/IEC 14882:2011 standard for new
features of C++ programming language.

For now, the project is developed in assembly directives and linker script of GCC GNU Toolchain.
Therefore, we recommend to use gcc-arm-none-eabi-11.2-2022.02 which is shall to be installed 
to its default directory *C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\11.2 2022.02\*

###### 2.1.4. Install [Segger J-Link/J-Trace driver](https://www.segger.com/downloads/jlink/)

The board can be debugged through the JTAG debugging interface on port CN1. 
You can use any suitable JTAG debugger, but we have used the most popular one - J-Link.

###### 2.1.3. Install [PuTTY Client](https://www.putty.org/)

To use terminal on serial UART interface through USB port for debugging, install PuTTY Client for example.


#### 2.2. Obtain Git Repository

###### 2.2.1. Create an empty directory somewhere on your disk

For instance we will create *C:\REPOSITORY*.

```
C:\> mkdir REPOSITORY
C:\> cd REPOSITORY
C:\REPOSITORY>
```

###### 2.2.2. Clone this repository

For instance we will clone it to *EOOS* directory by SSH.

```
C:\REPOSITORY\> git clone --branch master git@gitflic.ru:baigudin-software/eoos-project-if-freertos-cm3-hk32f103vet6-evk.git EOOS
```

###### 2.2.3. Go the EOOS directory

```
C:\REPOSITORY\> cd EOOS
```

###### 2.2.4. Initialize and update all submodules of the repository

```
C:\REPOSITORY\EOOS> git submodule update --init
```


#### 2.3. Source Code Build and Run

This EOOS project is developed for fast start developing of target customer boards
and is based on the evaluation kit of the target MCU.

###### 2.3.1. Connect the board to your host PC by JTAG and UART

Connect JTAG debugger to CN1 port and to USB port of your host PC, and connect USB cable 
to CN3 port and to USB port of the host PC for UART interface connection.

###### 2.3.2. Run PyTTY terminal for serial UART connection

Check COM port number for this press Windows + R keyboard shortcut to launch the Windows Run box, 
type *devmgmt.msc* and click the *OK* button. The Device Manager window appears, go to ports (COM and LPT)
and check your COM port number for USB-SERIAL CH340 device.

Run PyTTY, go *Session* and check *Serial*. Go to *Connection -> Serial* and enter the configuration:

- Serial line to connction to: COM port you got in Device Manager
- Speed (baud): 115200
- Data bits: 8
- Stop bits: 1
- Parity: None
- Flow control: None

Press *Open* button to run the PyTTY terminal.

###### 2.3.3. Run and setup the project

Go to *C:\REPOSITORY\EOOS\ide\eoos-exe-tests-keil\* and run the *eoos-tests-if-freertos.uvprojx* project.

Go to *Project -> Options for target 'eoos-tests'...*, go to *Debug* and chose your JTAG debugger. 
For our example, we select *J-Link / J-Trace Cortex* Press *OK*.

###### 2.3.4. Build and run the project

Go to *Project -> Build Target*, and after that do *Debug -> Start/Stop Debug Session*, so that 
the built program will be upload on the board and execution of it stopped on the `main` funtion.

Go to *Debug -> Run* so that you will run the program.

###### 2.3.4. Check the project run

Go to the opened PyTTY terminal and check the output of the program.

```
WELCOME TO EOOS FreeRTOS TESTS
LANGUAGE: C++17
DATA MODEL: C++ Standard Library types
DISABLE: Dynamic heap memory allocation
MEMORY MODE: Mutex in pool memory of 5.
MEMORY MODE: Semaphore in pool memory of 5.
MEMORY MODE: Thread in pool memory of 5.
MEMORY MODE: Interrupts in pool memory of 5.
MEMORY MODE: System timer in pool memory of 1.
MEMORY MODE: USART driver in pool memory of 1.
EOOS: Size of system 13168 Bytes
```
