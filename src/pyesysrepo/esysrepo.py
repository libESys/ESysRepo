# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _esysrepo
else:
    import _esysrepo

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


import weakref

class SwigPyIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _esysrepo.delete_SwigPyIterator

    def value(self):
        return _esysrepo.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _esysrepo.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _esysrepo.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _esysrepo.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _esysrepo.SwigPyIterator_equal(self, x)

    def copy(self):
        return _esysrepo.SwigPyIterator_copy(self)

    def next(self):
        return _esysrepo.SwigPyIterator_next(self)

    def __next__(self):
        return _esysrepo.SwigPyIterator___next__(self)

    def previous(self):
        return _esysrepo.SwigPyIterator_previous(self)

    def advance(self, n):
        return _esysrepo.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _esysrepo.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _esysrepo.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _esysrepo.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _esysrepo.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _esysrepo.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _esysrepo.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self

# Register SwigPyIterator in _esysrepo:
_esysrepo.SwigPyIterator_swigregister(SwigPyIterator)

SHARED_PTR_DISOWN = _esysrepo.SHARED_PTR_DISOWN
import esyslog
BranchType_NOT_SET = _esysrepo.BranchType_NOT_SET
BranchType_LOCAL = _esysrepo.BranchType_LOCAL
BranchType_REMOTE = _esysrepo.BranchType_REMOTE
BranchType_ALL = _esysrepo.BranchType_ALL
class Branch(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _esysrepo.Branch_swiginit(self, _esysrepo.new_Branch(*args))
    __swig_destroy__ = _esysrepo.delete_Branch

    def set_name(self, name):
        return _esysrepo.Branch_set_name(self, name)

    def get_name(self):
        return _esysrepo.Branch_get_name(self)

    def set_ref_name(self, ref_name):
        return _esysrepo.Branch_set_ref_name(self, ref_name)

    def get_ref_name(self):
        return _esysrepo.Branch_get_ref_name(self)

    def set_type(self, type):
        return _esysrepo.Branch_set_type(self, type)

    def get_type(self):
        return _esysrepo.Branch_get_type(self)

    def set_is_head(self, is_head):
        return _esysrepo.Branch_set_is_head(self, is_head)

    def get_is_head(self):
        return _esysrepo.Branch_get_is_head(self)

    def set_remote_branch(self, remote_branch):
        return _esysrepo.Branch_set_remote_branch(self, remote_branch)

    def get_remote_branch(self):
        return _esysrepo.Branch_get_remote_branch(self)

    def set_remote_name(self, remote_name):
        return _esysrepo.Branch_set_remote_name(self, remote_name)

    def get_remote_name(self):
        return _esysrepo.Branch_get_remote_name(self)

# Register Branch in _esysrepo:
_esysrepo.Branch_swigregister(Branch)

class CommitHash(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self):
        _esysrepo.CommitHash_swiginit(self, _esysrepo.new_CommitHash())
    __swig_destroy__ = _esysrepo.delete_CommitHash

    def set_hash(self, hash):
        return _esysrepo.CommitHash_set_hash(self, hash)

    def get_hash(self):
        return _esysrepo.CommitHash_get_hash(self)

# Register CommitHash in _esysrepo:
_esysrepo.CommitHash_swigregister(CommitHash)

class Commit(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self):
        _esysrepo.Commit_swiginit(self, _esysrepo.new_Commit())
    __swig_destroy__ = _esysrepo.delete_Commit

    def set_hash(self, hash):
        return _esysrepo.Commit_set_hash(self, hash)

    def get_hash(self):
        return _esysrepo.Commit_get_hash(self)

    def set_message(self, message):
        return _esysrepo.Commit_set_message(self, message)

    def get_message(self):
        return _esysrepo.Commit_get_message(self)

    def set_author(self, author):
        return _esysrepo.Commit_set_author(self, author)

    def get_author(self):
        return _esysrepo.Commit_get_author(self)

    def set_email(self, email):
        return _esysrepo.Commit_set_email(self, email)

    def get_email(self):
        return _esysrepo.Commit_get_email(self)

    def set_date_time(self, date_time):
        return _esysrepo.Commit_set_date_time(self, date_time)

    def get_date_time(self):
        return _esysrepo.Commit_get_date_time(self)

# Register Commit in _esysrepo:
_esysrepo.Commit_swigregister(Commit)

class Remote(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self):
        _esysrepo.Remote_swiginit(self, _esysrepo.new_Remote())
    __swig_destroy__ = _esysrepo.delete_Remote

    def set_name(self, name):
        return _esysrepo.Remote_set_name(self, name)

    def get_name(self):
        return _esysrepo.Remote_get_name(self)

    def set_url(self, url):
        return _esysrepo.Remote_set_url(self, url)

    def get_url(self):
        return _esysrepo.Remote_get_url(self)

# Register Remote in _esysrepo:
_esysrepo.Remote_swigregister(Remote)

class ProgressCallbackBase(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _esysrepo.delete_ProgressCallbackBase

    def git_progress_notif(self, progress):
        return _esysrepo.ProgressCallbackBase_git_progress_notif(self, progress)

# Register ProgressCallbackBase in _esysrepo:
_esysrepo.ProgressCallbackBase_swigregister(ProgressCallbackBase)

class GitBase(esyslog.User):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _esysrepo.delete_GitBase

    def open_folder(self, folder):
        return _esysrepo.GitBase_open_folder(self, folder)

    def is_open(self):
        return _esysrepo.GitBase_is_open(self)

    def close(self):
        return _esysrepo.GitBase_close(self)

    def get_remotes(self, remotes):
        return _esysrepo.GitBase_get_remotes(self, remotes)

    def get_branches(self, *args):
        return _esysrepo.GitBase_get_branches(self, *args)

    def clone(self, *args):
        return _esysrepo.GitBase_clone(self, *args)

    def checkout(self, branch, force=False):
        return _esysrepo.GitBase_checkout(self, branch, force)

    def reset(self, *args):
        return _esysrepo.GitBase_reset(self, *args)

    def fastforward(self, commit):
        return _esysrepo.GitBase_fastforward(self, commit)

    def get_last_commit(self, commit):
        return _esysrepo.GitBase_get_last_commit(self, commit)

    def get_parent_commit(self, commit, parent, nth_parent=1):
        return _esysrepo.GitBase_get_parent_commit(self, commit, parent, nth_parent)

    def is_dirty(self, dirty):
        return _esysrepo.GitBase_is_dirty(self, dirty)

    def is_detached(self, detached):
        return _esysrepo.GitBase_is_detached(self, detached)

    def get_status(self, status):
        return _esysrepo.GitBase_get_status(self, status)

    def is_ssh_agent_running(self, log_once=True):
        return _esysrepo.GitBase_is_ssh_agent_running(self, log_once)

    def detect_ssh_agent(self, log_once=True):
        return _esysrepo.GitBase_detect_ssh_agent(self, log_once)

    def merge_analysis(self, refs, merge_analysis_result, commits):
        return _esysrepo.GitBase_merge_analysis(self, refs, merge_analysis_result, commits)

    def fetch(self, *args):
        return _esysrepo.GitBase_fetch(self, *args)

    def reset_to_parent(self, nth_parent=1):
        return _esysrepo.GitBase_reset_to_parent(self, nth_parent)

    def has_branch(self, *args):
        return _esysrepo.GitBase_has_branch(self, *args)

    def get_hash(self, *args):
        return _esysrepo.GitBase_get_hash(self, *args)

    def walk_commits(self, walk_commit):
        return _esysrepo.GitBase_walk_commits(self, walk_commit)

    def diff(self, commit_hash, diff):
        return _esysrepo.GitBase_diff(self, commit_hash, diff)

    @staticmethod
    def is_repo(path):
        return _esysrepo.GitBase_is_repo(path)

    def set_id(self, id):
        return _esysrepo.GitBase_set_id(self, id)

    def get_id(self):
        return _esysrepo.GitBase_get_id(self)

    def set_debug(self, debug):
        return _esysrepo.GitBase_set_debug(self, debug)

    def get_debug(self):
        return _esysrepo.GitBase_get_debug(self)

    def get_version(self):
        return _esysrepo.GitBase_get_version(self)

    def get_lib_name(self):
        return _esysrepo.GitBase_get_lib_name(self)

    def handle_sideband_progress(self, text):
        return _esysrepo.GitBase_handle_sideband_progress(self, text)

    def handle_transfer_progress(self, progress):
        return _esysrepo.GitBase_handle_transfer_progress(self, progress)

    def set_progress(self, progress):
        return _esysrepo.GitBase_set_progress(self, progress)

    def get_progress(self, progress):
        return _esysrepo.GitBase_get_progress(self, progress)

    def set_progress_callback(self, progress_callback):
        return _esysrepo.GitBase_set_progress_callback(self, progress_callback)

    def get_progress_callback(self):
        return _esysrepo.GitBase_get_progress_callback(self)

    @staticmethod
    def decode_sideband_progress(txt, progress):
        return _esysrepo.GitBase_decode_sideband_progress(txt, progress)

    def cmd_start(self):
        return _esysrepo.GitBase_cmd_start(self)

    def cmd_end(self):
        return _esysrepo.GitBase_cmd_end(self)

    def open_time(self):
        return _esysrepo.GitBase_open_time(self)

    def close_time(self):
        return _esysrepo.GitBase_close_time(self)

    def get_open_time(self):
        return _esysrepo.GitBase_get_open_time(self)

    def get_last_cmd_elapsed_time(self):
        return _esysrepo.GitBase_get_last_cmd_elapsed_time(self)

# Register GitBase in _esysrepo:
_esysrepo.GitBase_swigregister(GitBase)

def GitBase_is_repo(path):
    return _esysrepo.GitBase_is_repo(path)

def GitBase_decode_sideband_progress(txt, progress):
    return _esysrepo.GitBase_decode_sideband_progress(txt, progress)

class GitHelper(esyslog.User):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    THOUSAND = _esysrepo.GitHelper_THOUSAND
    CLEAN_OUT_REPETITION = _esysrepo.GitHelper_CLEAN_OUT_REPETITION

    def __init__(self, git=0, log_if=0, repo_idx=-1):
        _esysrepo.GitHelper_swiginit(self, _esysrepo.new_GitHelper(git, log_if, repo_idx))
    __swig_destroy__ = _esysrepo.delete_GitHelper

    def debug(self, level, msg):
        return _esysrepo.GitHelper_debug(self, level, msg)

    def info(self, msg):
        return _esysrepo.GitHelper_info(self, msg)

    def warn(self, msg):
        return _esysrepo.GitHelper_warn(self, msg)

    def critical(self, msg):
        return _esysrepo.GitHelper_critical(self, msg)

    def log(self, *args):
        return _esysrepo.GitHelper_log(self, *args)

    def error(self, *args):
        return _esysrepo.GitHelper_error(self, *args)

    def done(self, msg, elapsed_time):
        return _esysrepo.GitHelper_done(self, msg, elapsed_time)

    def open(self, folder, log_level, debug_level=0):
        return _esysrepo.GitHelper_open(self, folder, log_level, debug_level)

    def clone_branch(self, url, branch, path, do_close, log_level, debug_level=0):
        return _esysrepo.GitHelper_clone_branch(self, url, branch, path, do_close, log_level, debug_level)

    def clone(self, *args):
        return _esysrepo.GitHelper_clone(self, *args)

    def close(self, log_level, debug_level=0):
        return _esysrepo.GitHelper_close(self, log_level, debug_level)

    def fastforward(self, commit, log_level, debug_level=0):
        return _esysrepo.GitHelper_fastforward(self, commit, log_level, debug_level)

    def fetch(self, *args):
        return _esysrepo.GitHelper_fetch(self, *args)

    def get_branches(self, branches, branch_type, log_level, debug_level=0):
        return _esysrepo.GitHelper_get_branches(self, branches, branch_type, log_level, debug_level)

    def has_branch(self, name, branch_type, log_level, debug_level=0):
        return _esysrepo.GitHelper_has_branch(self, name, branch_type, log_level, debug_level)

    def get_hash(self, revision, hash, log_level, debug_level=0):
        return _esysrepo.GitHelper_get_hash(self, revision, hash, log_level, debug_level)

    def get_hash_local(self, revision, hash, log_level, debug_level=0):
        return _esysrepo.GitHelper_get_hash_local(self, revision, hash, log_level, debug_level)

    def is_dirty(self, dirty, log_level, debug_level=0):
        return _esysrepo.GitHelper_is_dirty(self, dirty, log_level, debug_level)

    def is_detached(self, detached, log_level, debug_level=0):
        return _esysrepo.GitHelper_is_detached(self, detached, log_level, debug_level)

    def get_status(self, status, log_level, debug_level=0):
        return _esysrepo.GitHelper_get_status(self, status, log_level, debug_level)

    def checkout(self, branch, force, log_level, debug_level=0):
        return _esysrepo.GitHelper_checkout(self, branch, force, log_level, debug_level)

    def merge_analysis(self, refs, merge_analysis_result, commits, log_level, debug_level=0):
        return _esysrepo.GitHelper_merge_analysis(self, refs, merge_analysis_result, commits, log_level, debug_level)

    def move(self, src, dst, recursive, log_level, debug_level=0):
        return _esysrepo.GitHelper_move(self, src, dst, recursive, log_level, debug_level)

    def set_git(self, git):
        return _esysrepo.GitHelper_set_git(self, git)

    def get_git(self):
        return _esysrepo.GitHelper_get_git(self)

    def set_auto_close(self, auto_close=True):
        return _esysrepo.GitHelper_set_auto_close(self, auto_close)

    def get_auto_close(self):
        return _esysrepo.GitHelper_get_auto_close(self)

    def set_repo_idx(self, repo_idx):
        return _esysrepo.GitHelper_set_repo_idx(self, repo_idx)

    def get_repo_idx(self):
        return _esysrepo.GitHelper_get_repo_idx(self)

    def set_display_repo_idx(self, display_repo_idx):
        return _esysrepo.GitHelper_set_display_repo_idx(self, display_repo_idx)

    def get_display_repo_idx(self):
        return _esysrepo.GitHelper_get_display_repo_idx(self)

    def init_oss(self, *args):
        return _esysrepo.GitHelper_init_oss(self, *args)

    def init_oss_done(self):
        return _esysrepo.GitHelper_init_oss_done(self)

    def init_oss_clear(self):
        return _esysrepo.GitHelper_init_oss_clear(self)

    def is_init_oss_done(self):
        return _esysrepo.GitHelper_is_init_oss_done(self)

    def clean_cout(self):
        return _esysrepo.GitHelper_clean_cout(self)

# Register GitHelper in _esysrepo:
_esysrepo.GitHelper_swigregister(GitHelper)

ESYSREPO_USE_LIBGIT2 = _esysrepo.ESYSREPO_USE_LIBGIT2
class Git(GitBase):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self):
        _esysrepo.Git_swiginit(self, _esysrepo.new_Git())
    __swig_destroy__ = _esysrepo.delete_Git

    @staticmethod
    def new_ptr():
        return _esysrepo.Git_new_ptr()

    def open_folder(self, folder):
        return _esysrepo.Git_open_folder(self, folder)

    def is_open(self):
        return _esysrepo.Git_is_open(self)

    def close(self):
        return _esysrepo.Git_close(self)

    def get_remotes(self, remotes):
        return _esysrepo.Git_get_remotes(self, remotes)

    def get_branches(self, *args):
        return _esysrepo.Git_get_branches(self, *args)

    def clone(self, *args):
        return _esysrepo.Git_clone(self, *args)

    def checkout(self, branch, force=False):
        return _esysrepo.Git_checkout(self, branch, force)

    def reset(self, *args):
        return _esysrepo.Git_reset(self, *args)

    def fastforward(self, commit):
        return _esysrepo.Git_fastforward(self, commit)

    def get_last_commit(self, commit):
        return _esysrepo.Git_get_last_commit(self, commit)

    def get_parent_commit(self, commit, parent, nth_parent=1):
        return _esysrepo.Git_get_parent_commit(self, commit, parent, nth_parent)

    def is_dirty(self, dirty):
        return _esysrepo.Git_is_dirty(self, dirty)

    def is_detached(self, detached):
        return _esysrepo.Git_is_detached(self, detached)

    def get_status(self, repo_status):
        return _esysrepo.Git_get_status(self, repo_status)

    def is_ssh_agent_running(self, log_once=True):
        return _esysrepo.Git_is_ssh_agent_running(self, log_once)

    def detect_ssh_agent(self, log_once=True):
        return _esysrepo.Git_detect_ssh_agent(self, log_once)

    def merge_analysis(self, refs, merge_analysis_result, commits):
        return _esysrepo.Git_merge_analysis(self, refs, merge_analysis_result, commits)

    def fetch(self, *args):
        return _esysrepo.Git_fetch(self, *args)

    def has_branch(self, *args):
        return _esysrepo.Git_has_branch(self, *args)

    def get_hash(self, *args):
        return _esysrepo.Git_get_hash(self, *args)

    def walk_commits(self, walk_commit):
        return _esysrepo.Git_walk_commits(self, walk_commit)

    def diff(self, commit_hash, diff):
        return _esysrepo.Git_diff(self, commit_hash, diff)

    def set_url(self, url):
        return _esysrepo.Git_set_url(self, url)

    def get_url(self):
        return _esysrepo.Git_get_url(self)

    def set_folder(self, folder):
        return _esysrepo.Git_set_folder(self, folder)

    def get_folder(self):
        return _esysrepo.Git_get_folder(self)

    def get_version(self):
        return _esysrepo.Git_get_version(self)

    def get_lib_name(self):
        return _esysrepo.Git_get_lib_name(self)

    def debug(self, level, msg):
        return _esysrepo.Git_debug(self, level, msg)

    @staticmethod
    def s_get_version():
        return _esysrepo.Git_s_get_version()

    @staticmethod
    def s_get_lib_name():
        return _esysrepo.Git_s_get_lib_name()

    @staticmethod
    def s_get_ssh_version():
        return _esysrepo.Git_s_get_ssh_version()

    @staticmethod
    def s_get_ssh_lib_name():
        return _esysrepo.Git_s_get_ssh_lib_name()

    def get_impl(self):
        return _esysrepo.Git_get_impl(self)

    def set_logger_if(self, logger_if):
        return _esysrepo.Git_set_logger_if(self, logger_if)

# Register Git in _esysrepo:
_esysrepo.Git_swigregister(Git)

def Git_new_ptr():
    return _esysrepo.Git_new_ptr()

def Git_s_get_version():
    return _esysrepo.Git_s_get_version()

def Git_s_get_lib_name():
    return _esysrepo.Git_s_get_lib_name()

def Git_s_get_ssh_version():
    return _esysrepo.Git_s_get_ssh_version()

def Git_s_get_ssh_lib_name():
    return _esysrepo.Git_s_get_ssh_lib_name()

Format_NOT_SET = _esysrepo.Format_NOT_SET
Format_UNKNOWN = _esysrepo.Format_UNKNOWN
Format_XML = _esysrepo.Format_XML
Format_JSON = _esysrepo.Format_JSON

def convert_format_to_text(format):
    return _esysrepo.convert_format_to_text(format)
class Repository(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _esysrepo.Repository_swiginit(self, _esysrepo.new_Repository(*args))
    __swig_destroy__ = _esysrepo.delete_Repository

    def set_name(self, name):
        return _esysrepo.Repository_set_name(self, name)

    def get_name(self):
        return _esysrepo.Repository_get_name(self)

    def set_path(self, path):
        return _esysrepo.Repository_set_path(self, path)

    def get_path(self):
        return _esysrepo.Repository_get_path(self)

    def set_revision(self, revision):
        return _esysrepo.Repository_set_revision(self, revision)

    def get_revision(self):
        return _esysrepo.Repository_get_revision(self)

    def get_location_str(self):
        return _esysrepo.Repository_get_location_str(self)

    def set_location(self, *args):
        return _esysrepo.Repository_set_location(self, *args)

    def get_location(self):
        return _esysrepo.Repository_get_location(self)

    def get_groups(self):
        return _esysrepo.Repository_get_groups(self)

    def __eq__(self, repository):
        return _esysrepo.Repository___eq__(self, repository)

    def __ne__(self, repository):
        return _esysrepo.Repository___ne__(self, repository)

# Register Repository in _esysrepo:
_esysrepo.Repository_swigregister(Repository)

class Group(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _esysrepo.Group_swiginit(self, _esysrepo.new_Group(*args))
    __swig_destroy__ = _esysrepo.delete_Group

    def set_name(self, name):
        return _esysrepo.Group_set_name(self, name)

    def get_name(self):
        return _esysrepo.Group_get_name(self)

    def add_repo(self, repo):
        return _esysrepo.Group_add_repo(self, repo)

    def get_repos(self):
        return _esysrepo.Group_get_repos(self)

    def find_repo_by_path(self, path):
        return _esysrepo.Group_find_repo_by_path(self, path)

    def find_repo_by_name(self, name):
        return _esysrepo.Group_find_repo_by_name(self, name)

# Register Group in _esysrepo:
_esysrepo.Group_swigregister(Group)

class Location(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _esysrepo.Location_swiginit(self, _esysrepo.new_Location(*args))
    __swig_destroy__ = _esysrepo.delete_Location

    def set_name(self, name):
        return _esysrepo.Location_set_name(self, name)

    def get_name(self):
        return _esysrepo.Location_get_name(self)

    def set_address(self, address):
        return _esysrepo.Location_set_address(self, address)

    def get_address(self):
        return _esysrepo.Location_get_address(self)

    def is_address_ssh(self):
        return _esysrepo.Location_is_address_ssh(self)

    def set_alt_address(self, alt_address):
        return _esysrepo.Location_set_alt_address(self, alt_address)

    def get_alt_address(self):
        return _esysrepo.Location_get_alt_address(self)

    def is_alt_address_ssh(self):
        return _esysrepo.Location_is_alt_address_ssh(self)

    def add_repo(self, *args):
        return _esysrepo.Location_add_repo(self, *args)

    def get_repos(self):
        return _esysrepo.Location_get_repos(self)

    def find_repo_by_path(self, path):
        return _esysrepo.Location_find_repo_by_path(self, path)

    def find_repo_by_name(self, name):
        return _esysrepo.Location_find_repo_by_name(self, name)

    def find_path_by_repo(self, git_repo_name):
        return _esysrepo.Location_find_path_by_repo(self, git_repo_name)

    def __eq__(self, location):
        return _esysrepo.Location___eq__(self, location)

    def __ne__(self, location):
        return _esysrepo.Location___ne__(self, location)

# Register Location in _esysrepo:
_esysrepo.Location_swigregister(Location)


def __lshift__(os, location):
    return _esysrepo.__lshift__(os, location)
Type_NOT_SET = _esysrepo.Type_NOT_SET
Type_UNKNOWN = _esysrepo.Type_UNKNOWN
Type_GOOGLE_MANIFEST = _esysrepo.Type_GOOGLE_MANIFEST
Type_ESYSREPO_MANIFEST = _esysrepo.Type_ESYSREPO_MANIFEST
Type_GIT_SUPER_PROJECT = _esysrepo.Type_GIT_SUPER_PROJECT

def convert_text_to_format(*args):
    return _esysrepo.convert_text_to_format(*args)
class FileError(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self):
        _esysrepo.FileError_swiginit(self, _esysrepo.new_FileError())
    __swig_destroy__ = _esysrepo.delete_FileError

    def set_msg(self, msg):
        return _esysrepo.FileError_set_msg(self, msg)

    def get_msg(self):
        return _esysrepo.FileError_get_msg(self)

    def set_value(self, value):
        return _esysrepo.FileError_set_value(self, value)

    def get_value(self):
        return _esysrepo.FileError_get_value(self)

    def set_line_number(self, line_number):
        return _esysrepo.FileError_set_line_number(self, line_number)

    def get_line_number(self):
        return _esysrepo.FileError_get_line_number(self)

# Register FileError in _esysrepo:
_esysrepo.FileError_swigregister(FileError)

class Manifest(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self):
        _esysrepo.Manifest_swiginit(self, _esysrepo.new_Manifest())
    __swig_destroy__ = _esysrepo.delete_Manifest

    def set_type(self, type):
        return _esysrepo.Manifest_set_type(self, type)

    def get_type(self):
        return _esysrepo.Manifest_get_type(self)

    def set_kind(self, kind):
        return _esysrepo.Manifest_set_kind(self, kind)

    def get_kind(self):
        return _esysrepo.Manifest_get_kind(self)

    def set_format(self, format):
        return _esysrepo.Manifest_set_format(self, format)

    def get_format(self):
        return _esysrepo.Manifest_get_format(self)

    def add_location(self, location, is_default=False):
        return _esysrepo.Manifest_add_location(self, location, is_default)

    def get_locations(self):
        return _esysrepo.Manifest_get_locations(self)

    def get_map_locations(self):
        return _esysrepo.Manifest_get_map_locations(self)

    def find_location(self, name):
        return _esysrepo.Manifest_find_location(self, name)

    def find_repo_by_path(self, path):
        return _esysrepo.Manifest_find_repo_by_path(self, path)

    def find_path_by_repo(self, git_repo_name):
        return _esysrepo.Manifest_find_path_by_repo(self, git_repo_name)

    def get_default_location(self):
        return _esysrepo.Manifest_get_default_location(self)

    def set_default_location(self, *args):
        return _esysrepo.Manifest_set_default_location(self, *args)

    def get_default_location_str(self):
        return _esysrepo.Manifest_get_default_location_str(self)

    def set_default_revision(self, default_revision):
        return _esysrepo.Manifest_set_default_revision(self, default_revision)

    def get_default_revision(self):
        return _esysrepo.Manifest_get_default_revision(self)

    def set_default_job_count(self, default_job_count):
        return _esysrepo.Manifest_set_default_job_count(self, default_job_count)

    def get_default_job_count(self):
        return _esysrepo.Manifest_get_default_job_count(self)

    def get_repo_revision(self, repo):
        return _esysrepo.Manifest_get_repo_revision(self, repo)

    def clear(self):
        return _esysrepo.Manifest_clear(self)

    def get_groups(self):
        return _esysrepo.Manifest_get_groups(self)

    def __eq__(self, other):
        return _esysrepo.Manifest___eq__(self, other)

    def __ne__(self, other):
        return _esysrepo.Manifest___ne__(self, other)

# Register Manifest in _esysrepo:
_esysrepo.Manifest_swigregister(Manifest)

class FileBase(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _esysrepo.delete_FileBase

    def set_data(self, manifest):
        return _esysrepo.FileBase_set_data(self, manifest)

    def get_data(self):
        return _esysrepo.FileBase_get_data(self)

    def read(self, path):
        return _esysrepo.FileBase_read(self, path)

    def write(self, *args):
        return _esysrepo.FileBase_write(self, *args)

    def get_errors(self):
        return _esysrepo.FileBase_get_errors(self)

    def add_error(self, *args):
        return _esysrepo.FileBase_add_error(self, *args)

# Register FileBase in _esysrepo:
_esysrepo.FileBase_swigregister(FileBase)

class GRepoManifest(FileBase):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self):
        _esysrepo.GRepoManifest_swiginit(self, _esysrepo.new_GRepoManifest())
    __swig_destroy__ = _esysrepo.delete_GRepoManifest

    def read(self, filename):
        return _esysrepo.GRepoManifest_read(self, filename)

    def write(self, *args):
        return _esysrepo.GRepoManifest_write(self, *args)

    def __eq__(self, other):
        return _esysrepo.GRepoManifest___eq__(self, other)

    def __ne__(self, other):
        return _esysrepo.GRepoManifest___ne__(self, other)

    def get_impl(self):
        return _esysrepo.GRepoManifest_get_impl(self)

    @staticmethod
    def get_folder_name():
        return _esysrepo.GRepoManifest_get_folder_name()

# Register GRepoManifest in _esysrepo:
_esysrepo.GRepoManifest_swigregister(GRepoManifest)

def GRepoManifest_get_folder_name():
    return _esysrepo.GRepoManifest_get_folder_name()
