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


class LoadFolder01(unittest.TestCase):
    def test_loading_grepo(self):
        load_folder = esysrepo.LoadFolder()
        folder_base = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
        folder = os.path.join(folder_base, "res/esysrepo_t/grepo/repo01")
        folder = os.path.normpath(folder)
        result = load_folder.run(folder)
        self.assertEqual(result, 0)

        manifest = load_folder.get_manifest()
        self.assertNotEqual(manifest, None)

        locations = manifest.get_locations()
        self.assertEqual(locations.size(), 2)

        loc_origin = manifest.find_location("origin")
        self.assertNotEqual(loc_origin, None)
        self.assertEqual(loc_origin.get_address(), "ssh://git@gitlab.com/libesys")

        loc_github = manifest.find_location("github")
        self.assertNotEqual(loc_github, None)
        self.assertEqual(loc_github.get_address(), "https://github.com")

        rel_path = load_folder.find_repo_path_by_url(
            "ssh://git@gitlab.com/libesys/esyscli/esyscli"
        )
        self.assertEqual(rel_path, "src/esyscli")

        rel_path = load_folder.find_repo_path_by_url(
            "ssh://git@gitlab.com/libesys/esyscli/esyscli.git"
        )
        self.assertEqual(rel_path, "src/esyscli")


if __name__ == "__main__":
    unittest.main()
