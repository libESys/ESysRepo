---
title: Usage
weight: 40
pre: "<b>4. </b>"
chapter: false
---

The command-line tool is very similar to both the [Google
repo](https://gerrit.googlesource.com/git-repo/) tool and [git-repo](https://git-repo.info). Since
it’s already known and well done, there was no point in being creative on that front. Note that
only the main commands are implemented, typically with fewer options and some additions. But it
should be very straightforward for anyone who used any of the tools mentioned above.

Every command follows the same pattern:

```
esysrepo <COMMAND> [options …]
```

The list of the supported commands is:

* init

* sync

* info

* status

* list

* manifest

* version

* help