#!/usr/bin/env sh

# This file must be used with "source bin/activate" *from bash*
# you cannot run it directly

if [ -n "$BASH_SOURCE" ]; then
    THIS_SCRIPT_=$BASH_SOURCE
elif [ -n "$ZSH_NAME" ]; then
    THIS_SCRIPT_=$0
else
    THIS_SCRIPT_="$(pwd)/deactivate.sh"
fi

THIS_SCRIPT=$(readlink -f "$THIS_SCRIPT_")
ESYSREPO_BIN_PATH=$(dirname "$THIS_SCRIPT")

echo "THIS_SCRIPT_ = $THIS_SCRIPT_"
echo "THIS_SCRIPT = $THIS_SCRIPT"
echo "ESYSREPO_BIN_PATH = $ESYSREPO_BIN_PATH"

deactivate () {
    # reset old environment variables
    if [ -n "${_ESYSREPO_OLD_PATH:-}" ] ; then
        PATH="${_ESYSREPO_OLD_PATH:-}"
        export PATH
        unset _ESYSREPO_OLD_PATH
    fi

    # This should detect bash and zsh, which have a hash command that must
    # be called to get it to forget past commands.  Without forgetting
    # past commands the $PATH changes we made may not be respected
    if [ -n "${BASH:-}" -o -n "${ZSH_VERSION:-}" ] ; then
        hash -r 2> /dev/null
    fi

    if [ -n "${_ESYSREPO_OLD_PS1:-}" ] ; then
        PS1="${_ESYSREPO_OLD_PS1:-}"
        export PS1
        unset _ESYSREPO_OLD_PS1
    fi

    if [ ! "${1:-}" = "nondestructive" ] ; then
    # Self destruct!
        unset -f deactivate
    fi
}

# unset irrelevant variables
deactivate nondestructive
