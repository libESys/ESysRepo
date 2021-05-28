![]({{< image_src "images/esysrepo_landscape_title.svg" >}})
With any sizeable SW project, working with several git repositories is usually inevitable.
Typically, this leads to the debate about the mono-repo vs. multi-repo pattern. ESysRepo is a tool
to simplify handling a multi-repo, including the issues related to their CI. It takes inspiration
from the [Google repo](https://gerrit.googlesource.com/git-repo/) tool, [git
superproject](https://git-scm.com/docs/gitsubmodules/), and [git-repo](https://git-repo.info). All
those are great tools but lacking some features or essential characteristics.

So ESysRepo was created to make it simpler and more efficient to use the multi-repo pattern for the
SW developer to use and define CI pipelines.