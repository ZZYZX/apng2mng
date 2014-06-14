apng2mng
========

Tool to convert between APNG and MNG image file formats

_________________________________________

This is WIP, the tools are not ready yet.
=========================================
Pull requests appreciated!
==========================

_________________________________________

Requirements
------------


Relies upon `apngasm` and `libmng` libraries.
They should be installed on your system.

https://github.com/apngasm/apngasm

http://sourceforge.net/projects/libmng

Installation
------------

Requires `cmake` to build.

# mkdir build && cd build
# cmake ..
# make

If all went well, you should have apng2mng binary in the ./build/out folder.

Usage
-----

# apng2mng penguins.apng penguins.mng
# apng2mng penguins.mng penguins_again.apng

Notes
-----

It may be a good idea to link apng2mng to mng2apng
in the destination directory on Unix systems.

