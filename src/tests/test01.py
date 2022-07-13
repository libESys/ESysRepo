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

import unittest
import esysrepo
import os

print(__file__)
print("cwd = %s" % os.getcwd())


class TestSomething(unittest.TestCase):
    def test_something(self):
        repocfg = esysrepo.GRepoManifest()
        result = repocfg.read("src/esysrepo/res/esysrepo_t/grepo/default02.xml")
        self.assertEqual(result, 0)
        manifest = repocfg.get_data()
        path = manifest.find_repo_path_by_url("ssh://git@gitlab.com/libesys/esysos")
        self.assertEqual(path, "src/esysos")
        path = manifest.find_repo_path_by_url("https://gitlab.com/libesys/esysos")
        self.assertEqual(path, "src/esysos")
        path = manifest.find_repo_path_by_url(
            "ssh://git@gitlab.com/libesys/extlib/arduino1710"
        )
        self.assertEqual(path, "extlib/arduino1710")
        path = manifest.find_repo_path_by_url(
            "https://gitlab.com/libesys/extlib/arduino1710"
        )
        self.assertEqual(path, "extlib/arduino1710")


if __name__ == "__main__":
    unittest.main()
