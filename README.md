# apng2mng

CLI tool capable of converting between APNG and MNG image file formats.

MNG can be integrated into GUI applications built with Qt framework, providing UIs with beautiful, lossless, fully-transparent (24-bit) animated icons and other UI elements.
There’s a [code example](examples/mng-in-qt/) available that demonstrates usage of MNG graphics in Qt/C++ projects.


## Requirements

Relies on [apngasm](https://github.com/apngasm/apngasm/)
and [libmng](https://libmng.com/) libraries.


## Installation

    make clean all

    sudo make install


## Usage

    apng2mng penguins.apng

    apng2mng penguins.mng penguins_again.apng

    apng2mng penguins.jng penguins_again.apng


## Notes

It may be a good idea to link apng2mng to mng2apng
in the destination directory on Unix systems.


## TODO
- Implement support for pipes (both | and > )
