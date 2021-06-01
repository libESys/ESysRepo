---
title: manifest
weight: 60
pre: "4.6. "
---

## Description

This command provides a utility to inspect and manipulate manifests. For the moment, the only
meaningful option is to be able to output a manifest where all revisions have been replaced by the
git commit hash found on the remote git repositories. Note that since esysrepo will check all the
remote git repositories, it may take some time, especially that this command is mono-threaded.

## Usage

```
esysrepo manifest [options ...]
```

## Options

The available options are:

* --folder: the folder where the local workspace is located

* --output-file / -o <FILE\> : the output file

* --revision-as-HEAD / -r: save all revisions as the git commit hash of the HEAD

## Examples

Again taking a fresh workspace for SW development of ESysRepo, the following command and its result
are shown below:

```
esysrepo manifest
```

![alt text]({{< image_src "images/manifest_example01.png" >}} "The text")

When using the option -r, the result is as follow:

```
esysrepo manifest -r
```

![alt text]({{< image_src "images/manifest_example02.png" >}} "The text")




