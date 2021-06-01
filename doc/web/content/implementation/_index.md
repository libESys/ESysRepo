---
title: Implementation
weight: 20
pre: "<b>2. </b>"
chapter: false
---

Based on the requirements set, the decision was to implement ESysRepo in C++ and the main libraries
used are:

* Boost

* POCO

* libgit2

* spdlog

* several other ESys libraries

Apart from the command line parser, all the functionality is in a dynamic library: a shared library
libesysrepo under Linux; a DLL esysrepo-*.dll under Windows. The esysrepo executable implements
only the command line parser, which will soon be moved to the dynamic library.

To avoid using an external git executable and parse its output, we use the libgit2 library, a
platform-independent C library implementing git from scratch based on its specification. 


