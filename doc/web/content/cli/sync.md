---
title: sync
weight: 20
pre: "4.2. "
---

## Description

Typically, this is the second command called just after *init*; this command downloads new changes and
updates the working files in your local workspace. If you run repo sync without arguments, it
synchronizes the files for all projects.

When you run repo sync, this is what happens to the manifest:

* The first time sync is run on a local workspace; nothing should happen since the manifest should
be up to date

* If the git repository holding the manifest has local changes, the sync procedure is aborted

* If the git repository is detached, the sync procedure is aborted

* If no branch was specified and if the current HEAD can be fast-forwarded, the git repository is
fast-forwarded; if it can’t, the sync procedure is also aborted

* If a branch was specified and if it exists, then it is checkout; otherwise, the same process as
if not branch had been specified is followed

And for every git repository found in the manifest, set to be synced, the following happens:

* If the git repository is not found in the local workspace, it will be cloned. If a branch was
specified, this branch would be checkout if it exists in this repo

* The update procedure starts by checking if there are any changes in the git repository. If
changes are found, the sync operation is aborted

* If no branch was specified:

    * If the git repository is detached, abort

    * Do a git fetch on the repository

    * Check if possible to fast-forward the HEAD of the local repository. If it can, do it;
otherwise, abort

* If a branch was specified and exists, that branch is checkout. Otherwise, handle it as if no
branch had been specified

## Usage

```
esysrepo sync [options…]
```

## Options

Available options are:

* -- force-sync: overwrite an existing git directory if it needs to point to a different object
directory. WARNING: this may cause loss of data

* --job / -j <N\>: number of jobs to run in parallel (default: 1)

* --folder: the folder where the local workspace is located

* --groups / -g <LIST\>: the list of groups to sync. The list should be separated by commas and
have not white spaces

* --branch / -b <BRANCH\>: the branch will be checkout if existing in all targeted git
repositories; otherwise all repositories without such branch will be synced normally

## Examples

To sync the manifest and all git repositories with 4 parallel jobs:

```
esysrepo sync -j4
```

To sync only the manifest and a given list of groups

```
esysrepo sync -g grp1,grp2,grp3
```
