apng2mng
========

Convert APNG animations into MNG format





This is WIP, the tools are not ready yet.
=========================================
Pull requests appreciated!
==========================







Installation
------------

Requires `cmake`

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

It may be a good idea to link apng2mng to mng2apng in 
the destination directory on Unix systems.

