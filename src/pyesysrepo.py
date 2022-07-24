#!/usr/bin/env python3

##
# __legal_b__
##
# Copyright (c) 2020-2022 Michel Gillet
# Distributed under the wxWindows Library Licence, Version 3.1.
# (See accompanying file LICENSE_3_1.txt or
# copy at http://www.wxwidgets.org/about/licence)
##
# __legal_e__
##

import os
import sys

if "PYSWIG" in os.environ:
    PYSWIG_DIR = os.path.abspath(os.environ.get("PYSWIG"))
    print("pySwig found at %s" % PYSWIG_DIR)
    sys.path.append(PYSWIG_DIR)

import pyswig

print("pyesysrepo.py begins ...\n")

file_config = pyswig.FileConfig()
file_config.set_input_dir("../include/esys/repo")
file_config.set_base_inc_dir("esys/repo")

# path to all sources, but relative to the input directory given above
source = [
    "version.h",
    "resultcode.h",
    "errorinfo.h",
    "result.h",
    "errorstack.h",
    "git/branchtype.h",
    "git/branch.h",
    "git/branches.h",
    "git/commithash.h",
    "git/commit.h",
    "git/remote.h",
    "progresscallbackbase.h",
    "gitbase.h",
    "githelper.h",
    "git.h",
    "libgit2/git.h",
    "manifest/format.h",
    "manifest/repository.h",
    "manifest/group.h",
    "manifest/location.h",
    "manifest/type.h",
    "manifest/fileerror.h",
    "manifest/include.h",
    "config.h",
    "configfolder.h",
    "manifest/detect.h",
    "manifest.h",
    "manifest/filebase.h",
    "grepo/manifest.h",
    "loadfolder.h",
    "exe/cmd.h",
    "exe/cmdinit.h",
    "exe/cmdsync.h",
]

file_config.set_source_files(source)

pyswig_obj = pyswig.PySwig()
pyswig_obj.add_file_config(file_config)

file_config_extra = pyswig.FileConfig()
file_config_extra.set_input_dir("../include/pyesysrepo")
file_config_extra.set_src_output_dir("./pyesysrepo")

# path to all sources, but relative to the input directory given above
source_extra = ["pyversion.h"]

file_config_extra.set_source_files(source_extra)

pyswig_obj.add_file_config(file_config_extra)

# Configure the generation of the input files for Swig
py_ver = ""
module_name = "esysrepo"
if "SWIG_TARGET_PYTHON_VERSION" in os.environ:
    target_version = os.environ["SWIG_TARGET_PYTHON_VERSION"]
    print("WARNING: SWIG_TARGET_PYTHON_VERSION = %s" % target_version)
    target_version = target_version.replace(".", "_")
    py_ver = "_py" + target_version
    module_name += py_ver

pyswig_obj.set_module_name(module_name)
pyswig_obj.set_use_director(True)
pyswig_obj.set_src_output_dir("./pyesysrepo")
pyswig_obj.set_inc_output_dir("../include/pyesysrepo")
pyswig_obj.set_output_file_ext("hh")

pyswig_obj.add_typemap("std_string.i")
pyswig_obj.add_typemap("std_vector.i")
pyswig_obj.add_typemap("stdint.i")
pyswig_obj.add_typemap("std_shared_ptr.i")

pyswig_obj.add_include("stdio.h", False)
pyswig_obj.add_include("esys/repo/esysrepo_defs.h")
pyswig_obj.add_include("esys/log/loggerbase.h", False)

pyswig_obj.add_define("ESYSREPO_API")
pyswig_obj.add_define("PYESYSREPO_API")

pyswig_obj.add_import("esyslog" + py_ver + ".hh")
if "ESYSLOG" in os.environ:
    esyslog_dir = os.environ["ESYSLOG"] + os.sep + "src" + os.sep + "pyesyslog"
    pyswig_obj.add_include_lib(esyslog_dir)
else:
    print("ERROR: env variable ESYSLOG not defined")

pyswig_obj.generate()

pyswig_obj.set_all_warnings()
pyswig_obj.set_process_cpp()
pyswig_obj.set_language("python")

pyswig_obj.run_swig()

print("pyesysrepo.py ends.")
