static const std::vector<msword2md::cpp::String> cmdstatus_doc_strings = {
{{termcolor::bold, termcolor::green}, "Description"},
{"\n\n"},
{"Show the working tree status, including new files, modified files, etc.\n\n"},
{{termcolor::bold, termcolor::green}, "Usage"},
{"\n\n"},
{termcolor::cyan, "esysrepo status [options ...]\n\n"},
{{termcolor::bold, termcolor::green}, "Options"},
{"\n\n"},
{"The available options are:\n\n"},
{"* --folder: the folder where the local workspace is located\n\n"},
{"* --quiet / -q: Only print the name of modified projects\n\n"},
{{termcolor::bold, termcolor::green}, "Examples"},
{"\n\n"},
{"On a fresh sync of the ESysRepo development tree, where there are two new log.txt files:\n\n"},
{"ESysRepo 0.1.0\n"},
{"\n"},
{ "["}, 
{ termcolor::color<112, 173, 71>, "info", termcolor::reset}, 
{"] Status ...\n"},
{ "["}, 
{ termcolor::color<112, 173, 71>, "info", termcolor::reset}, 
{"] Repository : .                                    master\n"},
{"--     log.txt\n"},
{ "["}, 
{ termcolor::color<112, 173, 71>, "info", termcolor::reset}, 
{"] Repository : src/esysrepo                         master\n"},
{"--     log.txt\n"},
{ "["}, 
{ termcolor::color<112, 173, 71>, "info", termcolor::reset}, 
{"] Repository : extlib/libgit2\n"},
{ "["}, 
{ termcolor::color<112, 173, 71>, "info", termcolor::reset}, 
{"] Repository : extlib/libssh2\n"},
{ "["}, 
{ termcolor::color<112, 173, 71>, "info", termcolor::reset}, 
{"] Repository : extlib/nlohmann_json\n"},
{ "["}, 
{ termcolor::color<112, 173, 71>, "info", termcolor::reset}, 
{"] Status done.\n"},
{"    elapsed time (s): 0.763\n\n"},
{"\n"},
{"\n\n"},
};
