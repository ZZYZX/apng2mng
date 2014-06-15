apng2mng
========

Tool to convert between APNG and MNG image file formats

_________________________________________

This is WIP, the tool is not ready yet.
=======================================
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

> make

Usage
-----

> apng2mng penguins.apng

> apng2mng penguins.mng penguins_again.apng

Notes
-----

It may be a good idea to link apng2mng to mng2apng
in the destination directory on Unix systems.

