# ESysRepo

Note that this document is automatically generated from the file "readme.xml" by the tool msword2md
0.0.1. So don't modify this file directly because all changes will be lost. Modify the source file
instead

With any sizeable SW project, working with several git repositories is usually inevitable.
Typically, this leads to the debate about the mono-repo vs. multi-repo pattern. ESysRepo is a tool
to simplify handling a multi-repo, including the issues related to their CI. It takes inspiration
from the [Google repo](https://gerrit.googlesource.com/git-repo/) tool, [git
superproject](https://git-scm.com/docs/gitsubmodules/), and [git-repo](https://git-repo.info). All
those are great tools but lacking some features or essential characteristics.

So ESysRepo was created to make it simpler and more efficient to use the multi-repo pattern for the
SW developer to use and define CI pipelines.

# Requirements

The main requirements for a tool to help the handling of muti-repos are:

* Platform independent: it must support Linux, Windows, and macOS

* Solve the issue of commit dependencies across git repositories, especially in the context of CI

* Efficient: the tool should minimize the time needed for getting the source since it can be a
sizeable percentage of the time spent by a CI engine

* Fast execution: the time spent to run a CI is previous

* Have a certain level of compatibility with existing tools solving similar issues, i.e., Google
repo tool

* Has own manifest format for supporting new functionalities but supports conversion from and
towards other manifest formats

* Built as a library to allow scripting extension, easy inclusion in other tools

* Built as a modular SW, not created as a single executable

* Decent amount of unit tests

* Self-contained: not relying on and using other command-line tools, i.e., git

# Features and characteristics

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


# User’s guide

## Overview

## Commands

### Help

#### Description

#### Usage

#### Options






### Init

#### Description

Always the first command used as it initializes the current workspace. It will create a folder
called *.esysrepo* where various configuration files will be stored as well as few git
repositories.

In its simplest form, the only parameter of the *init* command is the URL of the git repository
where the manifest is located. The steps then followed are:

* Clone the git repository with the manifest is a temporary folder inside the *.esysrepo* folder

* Detect the format of the manifest file. Is it following the Google repo tool manifest format or
the ESysRepo manifest format

* Depending of the format of the manifest, create configurations files and move the git repo with
the manifest to its final folder inside the *.esysrepo* folder

The content of the folder *.esysrepo* is not secret, but it’s not part of the public interface of
the tool and may change with different version. So it’s strongly advised to use only the command
line tool itself and not change by hand any of the files found in that folder, except if explicitly
documented.

#### Usage

```
esysrepo init -u <URL> [options …]
```

#### Options

Available options:

* --manifest-url / -u <URL\> : The URL of the git repository holding the manifest

* --manifest-branch / -b <BRANCH\> : Manifest branch or revision to be checked out (default
“master”)

* --manifest-name / -m <NAME\>: Manifest file name used to initialize workspace (default
“default.xml”).

* --google / -g: The manifest file has the Google repo tool format

* --output / -o <PATH\>: The folder where to initialize the workspace (default is the current
folder)

#### Examples

To get the source code of ESysRepo, this would be the command line to use if using SSH (you need to
be a contributor):

```
esysrepo init -u ssh://git@gitlab.com/libesys/esysbuild/manifest.git
```

Or simply using HTTPS, which will work for everyone:

```
esysrepo init -u https://gitlab.com/libesys/esysbuild/manifest.git
```








### Info

#### Description

Show information about the manifest branch, current branch or unmerged branches of all git repos
found in the manifest file. The information provided for each git repository are:

* The name

* The path

* The current revision

* The current branch

* The list of local branches

#### Usage

```
esysrepo info [options…]
```

#### Options

Currently none are yet implemented.

#### Examples

When ran while working on the ESysRepo SW, it looked like this, only the first few lines are shown
for conciseness:






### List

#### Description

#### Usage

#### Options






### Manifest

#### Description

#### Usage

#### Options




### Status

#### Description

#### Usage

#### Options




### Sync

#### Description

#### Usage

#### Options




### Version

#### Description

#### Usage

#### Options




## Manifest formats

### Supported features of google repo

### Own manifest format





