---
title: Requirements
weight: 10
pre: "<b>1. </b>"
chapter: false
---

The main requirements for a tool to help the handling of muti-repos are:

* Platform independent: it must support Linux, Windows, and macOS

* Solve the issue of commit dependencies across git repositories, especially in the context of CI

* Efficient: the tool should minimize the time needed for getting the source since it can be a
sizeable percentage of the time spent by a CI engine

* Fast execution: the time spent to run a CI is precious

* Have a certain level of compatibility with existing tools solving similar issues, i.e., Google
repo tool

* Has own manifest format for supporting new functionalities but supports conversion from and
towards other manifest formats

* Built as a library to allow scripting extension, easy inclusion in other tools

* Built as a modular SW, not created as a single executable

* Decent amount of unit tests

* Self-contained: not relying on and using other command-line tools, i.e., git

