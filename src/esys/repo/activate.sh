#!/usr/bin/env sh

# This file must be used with "source bin/activate" *from bash*
# you cannot run it directly

if [ -n "$BASH_SOURCE" ]; then
    THIS_SCRIPT_=$BASH_SOURCE
elif [ -n "$ZSH_NAME" ]; then
    THIS_SCRIPT_=$0
else
    THIS_SCRIPT_="$(pwd)/activate.sh"
fi

THIS_SCRIPT=$(readlink -f "$THIS_SCRIPT_")
ESYSREPO_BIN_PATH=$(dirname "$THIS_SCRIPT")

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

_ESYSREPO_OLD_PATH="$PATH"
PATH="$ESYSREPO_BIN_PATH:$PATH"
export PATH

if [ -z "${ENV_DISABLE_PROMPT:-}" ] ; then
    _ESYSREPO_OLD_PS1="${PS1:-}"
    PS1=$(echo $_ESYSREPO_OLD_PS1 | sed 's+\$+(esysrepo)$+')
    export PS1
fi

# This should detect bash and zsh, which have a hash command that must
# be called to get it to fo_get past commands.  Without forgetting
# past commands the $PATH changes we made may not be respected
if [ -n "${BASH:-}" -o -n "${ZSH_VERSION:-}" ] ; then
    hash -r 2> /dev/null
fi
