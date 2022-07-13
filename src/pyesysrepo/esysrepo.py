##
# __legal_b__
##
# Copyright (c) 2022 Michel Gillet
# Distributed under the wxWindows Library Licence, Version 3.1.
# (See accompanying file LICENSE_3_1.txt or
# copy at http://www.wxwidgets.org/about/licence)
##
# __legal_e__
##

import sys

py_ver = "%s.%s" % (sys.version_info.major, sys.version_info.minor)
if py_ver == "3.10":
    from esysrepo_py3_10 import *
elif py_ver == "3.9":
    from esysrepo_py3_9 import *
elif py_ver == "3.8":
    from esysrepo_py3_8 import *
elif py_ver == "3.7":
    from esysrepo_py3_7 import *
elif py_ver == "3.6":
    from esysrepo_py3_6 import *
