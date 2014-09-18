apng2mng
====

Tool to convert between APNG and MNG (JNG) image file formats

_________________________________________

This is WIP, the code is not ready yet.
====
Pull requests are appreciated!
====

_________________________________________

Requirements
----

Relies on [apngasm](https://github.com/apngasm/apngasm) 
and [libmng](http://sourceforge.net/projects/libmng) libraries.

Installation
----

> make clean all

> sudo make install

Usage
----

> apng2mng penguins.apng

> apng2mng penguins.mng penguins_again.apng

> apng2mng penguins.jng penguins_again.apng

Notes
----

It may be a good idea to link apng2mng to mng2apng
in the destination directory on Unix systems.

TODO
----
- Implement the pipe support (both | and > )
