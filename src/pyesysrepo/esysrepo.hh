// PySwig 0.0.1

%module(directors="1") esysrepo
%include typemaps.i
%include std_string.i
%include std_vector.i
%include stdint.i
%include std_shared_ptr.i

%import esyslog.hh

%{

#include <stdio.h>
#include <esys/log/loggerbase.h>

#include "esys/repo/esysrepo_defs.h"

%}

#define ESYSREPO_API
#define PYESYSREPO_API

%include version.hh
%include git/branchtype.hh
%include git/branch.hh
%include git/commit.hh
%include git/remote.hh
%include gitbase.hh
%include githelper.hh
%include git.hh
%include libgit2/git.hh
%include pyversion.hh
