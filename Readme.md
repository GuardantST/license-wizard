# Info

This is _Guardant License Wizard_ repository.

Note that this code is not at all compatible with the _License Wizard_ executable from the _Guardant Software Licensing Kit_ distro (see e.g. settings path domains).

# Prerequisites

This code is designed for:
* language: C++17,
* build system: Qbs 1.11.0,
* dependencies:
  * Qt 5.6.3;
* toolchains:
  * MSVC 2017 (14.16.*),
  * GCC 8.4,
  * Xcode 7.*.

_Qt_ is the only direct third-party dependency. Do not forget to link with _Guardant Licensing API_ as well.

# Build

_Qbs_ build (meta-build) system is used. There are numerous project generators supported, including (but not limited to) _CMake_ and _Microsoft Visual Studio_ (see [here](https://doc.qt.io/qbs/generators.html) for details).
