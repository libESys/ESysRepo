---
title: Implementation
weight: 20
pre: "<b>2. </b>"
chapter: false
---

Based on the requirements set, it was decided to implement ESysRepo in C++ and the main librairies
used are:

* Boost

* POCO

* libgit2

* spdlog

* several other ESys libraries

Apart from the command line parser, all the functionality is in a dynamic library: a shared library
libesysrepo under Linux; a DLL esysrepo-*.dll under Windows. The esyrepo executable implements only
the command line parser, which will soon be moved to the dynamic library as well.

To avoid having to use an external git executable and parse its output, the libgit2 libraries is used, which is a platform independent C library implementing git from scratch based on its specification. 