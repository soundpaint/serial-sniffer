Additionally required packages on Raspian Wheezy
================================================

* Install log4cxx (required for compiling and running):

```
  $ sudo apt-get install liblog4cxx-dev
  $ sudo apt-get install liblog4cxx10v5
```

* Install qt5 (required for compiling):

```
  $ sudo apt-get install qt5-default
```

* Install `icu-devtools`, `libicu-dev`, `libxerces-c-dev`,
  `libxerces-c3.1` (required for compiling):

```
  $ sudo apt-get install libxerces-c-dev
```

* Install `libasound2-dev` (required for compiling):

```
  $ sudo apt-get install libasound2-dev
```

* Install `libusb-dev` (required for compiling):

```
  $ sudo apt-get install libusb-dev
```

* Install `GIMP` (required for art-work and icons creation):

```
  $ sudo apt-get install gimp
```

* Install `Dia` (required for icons creation):

```
  $ sudo apt-get install dia
```

* Install `InkScape` (required for icons creation):

```
  $ sudo apt-get install inkscape
```

Compile serial-sniffer application
=============================

* Change to home directory:

```
  $ cd
```

* Clone Git repository of serial-sniffer application:

```
  $ git clone https://github.com/soundpaint/serial-sniffer.git
```

* Compile serial-sniffer application:

```
  $ cd serial-sniffer
  $ make
```

Application Configuration [optional]
====================================

There are lots of configuration variables in the file
`~/serial-sniffer/build/bin/config.xml`.  For a documentation of all
of these variables, just have a look into the corresponding comments
in the `config.xml` file.
