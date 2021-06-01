---
title: init
weight: 10
pre: "4.1. "
---

## Description

Since this command initializes the current workspace, you will always start with this command. It
will create a folder called *.esysrepo* storing various configuration files as well as few git
repositories.

In its simplest form, the only parameter of the *init* command is the URL of the git repository
where the manifest is located. The steps then followed are:

* Clone the git repository with the manifest is a temporary folder inside the *.esysrepo* folder

* Detect the format of the manifest file. Is it following the Google repo tool manifest format or
the ESysRepo manifest format

* Depending on the manifest's format, it creates configurations files and moves the git repo with
the manifest to its final folder inside the *.esysrepo* folder

The folder's content of the folder .esysrepo is not secret, but it's not part of the public
interface of the tool and may change with different versions. So it's strongly advised to use only
the command line tool itself and not change by hand any of the files found in that folder, except
if explicitly documented.

## Usage

```
esysrepo init -u <URL> [options ...]
```

## Options

Available options:

* --manifest-URL / -u <URL\>: The URL of the git repository holding the manifest

* --manifest-branch / -b <BRANCH\>: Manifest branch or revision to be checked out (default
"master")

* --manifest-name / -m <NAME\>: Manifest file name used to initialize workspace (default
"default.xml").

* --google / -g: The manifest file has the Google repo tool format

* --output / -o <PATH\>: The folder where to initialize the workspace (default is the current
folder)

## Examples

To get the source code of ESysRepo, this would be the command line to use if using SSH (you need to
be a contributor):

```
esysrepo init -u ssh://git@gitlab.com/libesys/esysbuild/manifest.git
```

Or simply using HTTPS, which will work for everyone:

```
esysrepo init -u https://gitlab.com/libesys/esysbuild/manifest.git
```




