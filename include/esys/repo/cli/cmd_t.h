/*!
 * \file esys/repo/cli/cmd_t.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * Copyright (c) 2020-2021 Michel Gillet
 * Distributed under the wxWindows Library Licence, Version 3.1.
 * (See accompanying file LICENSE_3_1.txt or
 * copy at http://www.wxwidgets.org/about/licence)
 *
 * __legal_e__
 * \endcond
 *
 */

#pragma once

#include "esys/repo/esysrepo_defs.h"
#include "esys/repo/cli/cmd.h"

namespace esys
{

namespace repo
{

namespace cli
{

template<typename CMD>
class Cmd_t : public Cmd
{
public:
    typedef CMD CmdType;

    Cmd_t(AppBase *app, const std::string &name);
    virtual ~Cmd_t();

    CMD &get_cmd();

    exe::Cmd &get_cmd_base() override;
    virtual int configure_cmd(CMD &cmd) = 0;

    int parse_and_configure() override;
    int run() override;

protected:
    CMD m_cmd;
};

template<typename CMD>
Cmd_t<CMD>::Cmd_t(AppBase *app, const std::string &name)
    : Cmd(app, name)
{
}

template<typename CMD>
Cmd_t<CMD>::~Cmd_t()
{
}

template<typename CMD>
CMD &Cmd_t<CMD>::get_cmd()
{
    return m_cmd;
}

template<typename CMD>
exe::Cmd &Cmd_t<CMD>::get_cmd_base()
{
    return m_cmd;
}

template<typename CMD>
int Cmd_t<CMD>::parse_and_configure()
{
    int result = parse();
    if (result < 0) return result;

    if (m_vm.count("command") == 0) return -1;
    std::string cmd_txt = m_vm["command"].as<std::string>();
    if (cmd_txt != get_name())
    {
        //! \TODO add log
        return -1;
    }

    result = Cmd::configure_cmd(get_cmd_base());
    if (result < 0) return result;

    return configure_cmd(get_cmd());
}

template<typename CMD>
int Cmd_t<CMD>::run()
{
    int result = parse_and_configure();
    if (result < 0) return result;

    get_cmd().set_logger_if(this->get_logger_if());
    return get_cmd().run();
}

} // namespace cli

} // namespace repo

} // namespace esys