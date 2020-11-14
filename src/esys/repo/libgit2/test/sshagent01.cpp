/*!
 * \file esys/repo/libgit2/test/sshagent01_libgit2.cpp
 * \brief For precompiled headers
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#include "esys/repo/test/esysrepo_t_prec.h"

#include <esys/repo/libgit2/git.h>

#include <libssh2.h>

#include <boost/filesystem.hpp>

#include <iostream>

namespace esys
{

namespace repo
{

namespace libgit2
{

namespace test
{

/*! \class SSHAgent01LibGit2 esys/build/libgit2/test/sshagent01_libgit2.cpp
 * "esys/build/libgit2/test/sshagent01_libgit2.cpp"
 *
 *  \brief
 *
 */

ESYSTEST_AUTO_TEST_CASE(SSHAgent01LibGit2)
{
    boost::filesystem::path file_path;

    file_path = repo::test::TestCaseCtrl::get().GetTempFilesFolder();
    file_path /= ("sshagent01libgit2");

    bool remove_all = true;

    try
    {
        if (boost::filesystem::exists(file_path)) boost::filesystem::remove_all(file_path);
    }
    catch (const boost::filesystem::filesystem_error &e)
    {
        remove_all = false;
        std::cerr << e.what() << std::endl;
    }

    ESYSTEST_REQUIRE_EQUAL(remove_all, true);

    LIBSSH2_SESSION *session = libssh2_session_init();
    LIBSSH2_AGENT *agent = libssh2_agent_init(session);

    int error = libssh2_agent_connect(agent);
    if (error != LIBSSH2_ERROR_NONE)
    {
        char *msg;
        libssh2_session_last_error(session, &msg, nullptr, 0);
        std::cout << "agent error (" << error << ") : " << msg << std::endl;
    }

    libssh2_agent_disconnect(agent);
    libssh2_agent_free(agent);
    libssh2_session_free(session);

    /*Git git;

    int result = git.clone("https://gitlab.com/libesys/esystest.git", file_path.normalize().make_preferred().string());
    ESYSTEST_REQUIRE_EQUAL(result, 0);

    result = git.close();
    ESYSTEST_REQUIRE_EQUAL(result, 0); */
}

} // namespace test

} // namespace libgit2

} // namespace repo

} // namespace esys
