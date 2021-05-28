---
title: manifest
weight: 60
pre: "4.6. "
---

## Description

This command provides an utility to inspect and manipulate manifests. For the moment, the only
important option is to be able to output a manifest where all revisions have been replaced by the
git commit hash found on the remote git repositories. Note that since all the remote git
repositories will be checked, it may take some time, especially that this command is mono-threaded.

## Usage

```
esysrepo manifest [options…]
```

## Options

The available options are:

* --folder : the folder where the local workspace is located

* --output-file / -o <FILE\> : the output file

* --revision-as-HEAD / -r : save all revisions as the git commit hash of the HEAD

## Examples

Again taking a fresh workspace for SW development of ESysRepo, the following command and its result
are show below:

```
esysrepo manifest
```

![alt text]({{< image_src "images/manifest_example01.png" >}})

When using the option -r, the results is as follow:

```
esysrepo manifest -r
```

![alt text]({{< image_src "images/manifest_example02.png" >}} "The text")