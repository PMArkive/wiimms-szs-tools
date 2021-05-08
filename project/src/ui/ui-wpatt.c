
/***************************************************************************
 *                       _______ _______ _______                           *
 *                      |  ___  |____   |  ___  |                          *
 *                      | |   |_|    / /| |   |_|                          *
 *                      | |_____    / / | |_____                           *
 *                      |_____  |  / /  |_____  |                          *
 *                       _    | | / /    _    | |                          *
 *                      | |___| |/ /____| |___| |                          *
 *                      |_______|_______|_______|                          *
 *                                                                         *
 *                           Wiimms SZS Tools                              *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 *   This file is part of the SZS project.                                 *
 *   Visit https://szs.wiimm.de/ for project details and sources.          *
 *                                                                         *
 *   Copyright (c) 2011-2021 by Dirk Clemens <wiimm@wiimm.de>              *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   See file gpl-2.0.txt or http://www.gnu.org/licenses/gpl-2.0.txt       *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 *   >>>  This file is automatically generated by './src/gen-ui.c'.  <<<   *
 *   >>>                   Do not edit this file!                    <<<   *
 *                                                                         *
 ***************************************************************************/

#include <getopt.h>
#include "ui-wpatt.h"

//
///////////////////////////////////////////////////////////////////////////////
///////////////                  OptionInfo[]                   ///////////////
///////////////////////////////////////////////////////////////////////////////

static const InfoOption_t OptionInfo[OPT__N_TOTAL+1] =
{
    {0,0,0,0,0,0,0,0,0,0}, // OPT_NONE,

    //----- command specific options -----

    {	OPT_ROUND, false, false, false, false, false, 0, "round",
	0,
	"Print additional lines with rounded values (to 3 and 2 bytes for"
	" floats and 7 and 6 bytes for doubles)."
    },

    {	OPT_LONG, false, false, false, false, false, 'l', "long",
	0,
	"Print long numeric message IDs instead of alternative message names"
	" like Txx, Uxx or Mxx."
    },

    {	OPT_NO_HEADER, false, false, false, false, false, 'H', "no-header",
	0,
	"Suppress the syntax information section in BMG text files."
    },

    {	OPT_BRIEF, false, false, false, false, false, 'B', "brief",
	0,
	"Suppress cross reference comments."
    },

    {	OPT_NO_PARAM, false, false, false, false, false, 'P', "no-param",
	0,
	"Disable parameter support in decoded KMP text files."
    },

    {	OPT_NO_ECHO, false, false, false, false, false, 0, "no-echo",
	0,
	"Suppress output of @ECHO commands while scanning text files."
    },

    {	OPT_NO_CHECK, false, false, false, false, false, 'N', "no-check",
	0,
	"Do not make plausibility checks for KMP files."
    },

    {	OPT_DEST, false, false, false, false, true, 'd', "dest",
	"path",
	"Define a destination path (directory/file). The destination - means:"
	" write to standard output.\n"
	"  The path may contain escape sequences: %Q is replaced by the fully"
	" qualified source name. %P and %F are replaced by the source path or"
	" by the filename. %N and %E are replaced by source filename without"
	" extension or by the source extension. Finally, %T is replaced by the"
	" default extension of the destination format.\n"
	"  A '?' direct behind '%' in %E and %T conversions avoid that the"
	" same extension is used twice in row. Read"
	" https://szs.wiimm.de/opt/dest for more details."
    },

    {	OPT_DEST2, false, false, false, false, false, 'D', "DEST",
	"path",
	"Like --dest, but create the directory path automatically."
    },

    {	OPT_ESC, false, false, false, false, false, 'E', "esc",
	"char",
	"Define an alternative escape character for destination files. The"
	" default is '%'. For Windows batch files it is a good choice to set"
	" '-E$'."
    },

    {	OPT_OVERWRITE, false, false, false, false, false, 'o', "overwrite",
	0,
	"Overwrite already existing files without warning and ignore option"
	" --number."
    },

    {	OPT_NUMBER, false, false, false, false, false, 0, "number",
	0,
	"If a file already exist, append a number directly before the file"
	" extension to make the filename unique. If other numbered files"
	" already exist (ignoring case), use the maximum existing index+1."
	" --num is a short cut."
    },

    {	OPT_REMOVE_DEST, false, false, false, false, false, 'r', "remove-dest",
	0,
	"Remove already existing files before creating it. If set, --overwrite"
	" is ignored. --rm-dest is a short cut."
    },

    {	OPT_UPDATE, false, false, false, false, false, 'u', "update",
	0,
	"Update only existing files and don't create new files. If set,"
	" --overwrite and --remove-dest are ignored."
    },

    {	OPT_PRESERVE, false, false, false, false, false, 'p', "preserve",
	0,
	"Preserve file times (atime+mtime) while converting or copying files."
    },

    {	OPT_IGNORE, false, false, false, false, false, 'i', "ignore",
	0,
	"Ignore non existing source files without warning."
    },

    {	OPT_SECTIONS, false, false, false, false, true, 0, "sections",
	0,
	"Print in machine readable sections and parameter lines."
    },

    {0,0,0,0,0,0,0,0,0,0}, // OPT__N_SPECIFIC == 18

    //----- global options -----

    {	OPT_VERSION, false, false, false, false, false, 'V', "version",
	0,
	"Stop parsing the command line, print a version info and exit."
    },

    {	OPT_HELP, false, false, false, false, false, 'h', "help",
	0,
	"Stop parsing the command line, print a help message and exit."
    },

    {	OPT_XHELP, false, false, false, false, false, 0, "xhelp",
	0,
	"Stop parsing the command line and print a help message with all"
	" commands included. Exit after printing."
    },

    {	OPT_CONFIG, false, false, false, false, false, 0, "config",
	"file",
	"Define a configuration file or a directory as source. In later case,"
	" file 'wiimms-szs-tools.conf' is searched.\n"
	"  If option is not not set, then file 'wiimms-szs-tools.conf' is"
	" searched in different directories. Use command 'wszst CONFIG' to get"
	" more details."
    },

    {	OPT_ALLOW_ALL, false, false, false, false, false, 0, "allow-all",
	0,
	"Usually commands accept only options with impact to the command. All"
	" other options fire a syntax error. But if --allow-all is set, all"
	" commands accept all options.\n"
	"  This makes changing the command of a long command line without"
	" removing useless options easier. It also helps to override wrong"
	" option permissions."
    },

    {	OPT_COMPATIBLE, false, false, false, false, false, 0, "compatible",
	"vers",
	"The option expects a version number (format '#.##' or 'v#.##') or a"
	" revision number (format 'r#') as parameter. If set, the tools try to"
	" create BMG and KMP text files, that are compatible to the entered"
	" version of the tools. This may override other legacy options."
    },

    {	OPT_WIDTH, false, false, false, true, false, 0, "width",
	"width",
	"Define the terminal width (number of columns) for help and some other"
	" messages and disable the automatic detection of the terminal width."
    },

    {	OPT_MAX_WIDTH, false, false, false, true, false, 0, "max-width",
	"maxwidth",
	"Define the maximum terminal width (number of columns) for help and"
	" some other messages and disable the automatic detection of the"
	" terminal width. This option is ignored if --width is set."
    },

    {	OPT_QUIET, false, false, false, false, false, 'q', "quiet",
	0,
	"Be quiet and print only error messages. Multiple usage is possible."
	" The impact is command dependent. In general: If set three times,"
	" different file format warnings are suppressed."
    },

    {	OPT_VERBOSE, false, false, false, false, false, 'v', "verbose",
	0,
	"Be verbose and print more progress information. Multiple usage is"
	" possible. The impact is command dependent."
    },

    {	OPT_LOGGING, false, false, false, false, false, 'L', "logging",
	0,
	"This debug option enables the logging of internal lists and maps."
    },

    {	OPT_DE, false, false, false, false, false, 0, "de",
	0,
	"Use german track and arena names."
    },

    {	OPT_COLORS, true, false, false, true, false, 0, "colors",
	"[=modus]",
	"Define the modus for colored text output. Allowed keywords are: OFF"
	" or NO-COLORS to disable colors, AUTO (default) for automatic"
	" detection, ON for automatic detection but never OFF, 8-COLORS and"
	" 256-COLORS to force 8 or 256 color support. Without parameter, ON is"
	" used.\n"
	"  AUTO will enable colorized output only for terminals. AUTO and ON"
	" use environment variable TERM to find the correct color modus.\n"
	"  If a command is prefixed by 'C-', then --color=ON is used"
	" implicitly as default."
    },

    {	OPT_NO_COLORS, false, false, false, true, false, 0, "no-colors",
	0,
	"Deactive colorized text. This is the default, if an output file is"
	" not a terminal."
    },

    {	OPT_CT_CODE, false, false, false, false, false, 0, "ct-code",
	0,
	"Enable CT-CODE support. See https://szs.wiimm.de/opt/ctcode for"
	" details."
    },

    {	OPT_LE_CODE, true, false, false, false, false, 0, "le-code",
	"[=param]",
	"This option is completely ignored by wlect. It only exists due to"
	" compatibility with the other tools."
    },

    {	OPT_CHDIR, false, false, false, false, false, 0, "chdir",
	"dir",
	"Set a new working directory for all following options, for all"
	" parameters and for the command execution. This option can be used"
	" multiple times, but for parameter parsing and for command execution"
	" only the last usage is relevant. Nevertheless, '@param' values are"
	" scanned while reading the command line."
    },

    {	OPT_CONST, false, false, false, false, false, 'c', "const",
	"list",
	"Define constant values, that are used by the internal encoders and by"
	" the numeric options as predefined global variables. This option"
	" allows a conditional encoding of text files. It can be used multiple"
	" times for multiple definitions.\n"
	"  The parameter is a comma separated list of terms and a term is"
	" 'name=expression'. The expression is calculated by the text parser."
    },

    {	OPT_MAX_FILE_SIZE, false, false, false, false, false, 'M', "max-file-size",
	"size",
	"This security option defines the maximum file size for input files;"
	" larger files are ignored with a warning. The default unit is MiB and"
	" the default size is 100 MiB; that should be enough for standard"
	" usage."
    },

    {	OPT_TRACKS, false, true, false, false, false, 'T', "tracks",
	"tracks",
	"Define a new track order. A comma separated list in the format [a=]b"
	" or a:=b is expected. 'a' and 'b' are track names or slot numbers."
	" 'a' is the destination slot and 'b' the assigned track. If 'a' is"
	" omitted, the next slot is used; this means [a=]b,c,d is possible.\n"
	"  Tracks will only be exchanged so that always all tracks are"
	" assigned. But if using ':=' the new slots are assigned without"
	" exchanging and the old values are lost."
    },

    {	OPT_ARENAS, false, true, false, false, false, 'A', "arenas",
	"arenas",
	"Define a new arena order. A comma separated list in the format [a=]b"
	" or a:=b is expected. 'a' and 'b' are arena names or slot numbers."
	" 'a' is the destination slot and 'b' the assigned arena. If 'a' is"
	" omitted, the next slot is used; this means [a=]b,c,d is possible.\n"
	"  Arenas will only be exchanged so that always all arenas are"
	" assigned. But if using ':=' the new slots are assigned without"
	" exchanging and the old values are lost."
    },

    {	OPT_PAT, false, false, false, false, false, 0, "pat",
	"list",
	"Set global options for PAT processing. Parameter 'list' is a comma"
	" separated list of keywords. A minus sign before a keyword disables a"
	" setting. Each occurrence of the option will only change entered"
	" settings and all other settings are untouched.\n"
	"  Keyword DEFAULT resets the default settings and CLEAR disables all."
	" The other allowed keywords are: AUTO, SIMPLE, COMPLEX, BOTH, SILENT"
	" and LOG. See https://szs.wiimm.de/opt/pat for details."
    },

    {	OPT_UTF_8, false, true, false, false, true, 0, "utf-8",
	0,
	"Enables UTF-8 support for filenames (default)."
    },

    {	OPT_NO_UTF_8, false, true, false, false, false, 0, "no-utf-8",
	0,
	"Disables UTF-8 support for filenames."
    },

    {	OPT_TEST, false, false, false, false, true, 't', "test",
	0,
	"Run in test mode, modify nothing.\n"
	">>> USE THIS OPTION IF UNSURE! <<<"
    },

    {	OPT_FORCE, false, false, false, false, false, 0, "force",
	0,
	"The tools analyse input files and reject files with invalid data"
	" structures. If --force is set, little repairable issues are ignored"
	" and a warning is printed.\n"
	"Option '--kmp force' does the same, but only for KMP files.\n"
	">>> THE RESULT MAY BE INVALID OUTPUT FILES! <<<"
    },

    {	OPT_REPAIR_MAGICS, true, false, false, false, false, 0, "repair-magics",
	"[=mode]",
	"Control the reparing of missing or wrong magics of files and"
	" sub-files by analysing file path and file extension. MODE is one of"
	" OFF (default), ANALYZE or REPAIR (default, if set without mode). OFF"
	" disables this feature, ANALYZE enables it for analysis only, and"
	" REPAIR repairs all magics while reading the files. Keyword FNAME can"
	" be appended (separated by a comma) to give filename scanning the"
	" highest priority.\n"
	">>> THE RESULT MAY BE INVALID OUTPUT FILES! <<<"
    },

    {	OPT_OLD, false, true, false, false, false, 0, "OLD",
	0,
	"Developer option: Cancel --NEW and use old implementation if"
	" available."
    },

    {	OPT_STD, false, true, false, false, false, 0, "STD",
	0,
	"Developer option: Cancel --OLD and --NEW and use standard"
	" implementation (default)."
    },

    {	OPT_NEW, false, true, false, false, false, 0, "NEW",
	0,
	"Developer option: Cancel --OLD and use new implementation if"
	" available."
    },

    {	OPT_EXTRACT, false, true, false, false, false, 0, "EXTRACT",
	0,
	"Create the directory and extract different objects in different"
	" formats at the moment when they are seen. This is a development"
	" helper option."
    },

    {0,0,0,0,0,0,0,0,0,0} // OPT__N_TOTAL == 49

};

//
///////////////////////////////////////////////////////////////////////////////
///////////////             alternate option infos              ///////////////
///////////////////////////////////////////////////////////////////////////////

static const InfoOption_t option_grp_TEXTOUT_NO_HEADER =
    {	OPT_NO_HEADER, false, false, false, false, false, 'H', "no-header",
	0,
	"Suppress the syntax information section in PAT text files."
    };

static const InfoOption_t option_cmd_VERSION_BRIEF =
    {	OPT_BRIEF, false, false, false, false, false, 'B', "brief",
	0,
	"Print only the version number, revision and system. If set twice,"
	" print only the version number."
    };

static const InfoOption_t option_cmd_VERSION_LONG =
    {	OPT_LONG, false, false, false, false, false, 'l', "long",
	0,
	"Print in long format. Ignored if option --sections is set."
    };

static const InfoOption_t option_cmd_CONFIG_BRIEF =
    {	OPT_BRIEF, false, false, false, false, false, 'B', "brief",
	0,
	" Suppress configuration search list."
    };

static const InfoOption_t option_cmd_CONFIG_LONG =
    {	OPT_LONG, false, false, false, false, false, 'l', "long",
	0,
	"If set, print the global search list too. If set twice, print the"
	" auto-add search list too."
    };

static const InfoOption_t option_cmd_COLORS_LONG =
    {	OPT_LONG, false, false, false, false, false, 'l', "long",
	0,
	"Print also a list of all colored text types. If set twice, include"
	" alternative names. If set three times, include raw color names."
    };

static const InfoOption_t option_cmd_COLORS_BRIEF =
    {	OPT_BRIEF, false, false, false, false, false, 'B', "brief",
	0,
	"Ignore option --long and print a single status line about current"
	" color settings."
    };

static const InfoOption_t option_cmd_ERROR_LONG =
    {	OPT_LONG, false, false, false, false, false, 'l', "long",
	0,
	"Print message text instead of message name."
    };

static const InfoOption_t option_cmd_ERROR_BRIEF =
    {	OPT_BRIEF, false, false, false, false, false, 'B', "brief",
	0,
	"Print message number instead of message name."
    };

static const InfoOption_t option_cmd_FILETYPE_LONG =
    {	OPT_LONG, false, false, false, false, false, 'l', "long",
	0,
	"Print an additional column with the decompressed file type and"
	" version. If entered twice, a validation status column is added."
    };

static const InfoOption_t option_cmd_FUNCTIONS_BRIEF =
    {	OPT_BRIEF, false, false, false, false, false, 'B', "brief",
	0,
	"Suppress the output of the description and print only function type"
	" and syntax."
    };

static const InfoOption_t option_cmd_FUNCTIONS_LONG =
    {	OPT_LONG, false, false, false, false, false, 'l', "long",
	0,
	"Usually only the function syntax is compared to the keywords. But if"
	" --long is set, the descriptions are compared too."
    };


//
///////////////////////////////////////////////////////////////////////////////
///////////////                  CommandTab[]                   ///////////////
///////////////////////////////////////////////////////////////////////////////

static const KeywordTab_t CommandTab[] =
{
    { CMD_VERSION,	"VERSION",	0,		0 },
    { CMD_HELP,		"HELP",		"H",		0 },
    { CMD_HELP,		"?",		0,		0 },
    { CMD_CONFIG,	"CONFIG",	0,		0 },
    { CMD_ARGTEST,	"ARGTEST",	0,		0 },
    { CMD_TEST,		"TEST",		0,		0 },
    { CMD_COLORS,	"COLORS",	0,		0 },
    { CMD_ERROR,	"ERROR",	"ERR",		0 },
    { CMD_FILETYPE,	"FILETYPE",	"FT",		0 },
    { CMD_FILEATTRIB,	"FILEATTRIB",	"FA",		0 },
    { CMD_SYMBOLS,	"SYMBOLS",	0,		0 },
    { CMD_FUNCTIONS,	"FUNCTIONS",	0,		0 },
    { CMD_CALCULATE,	"CALCULATE",	0,		0 },
    { CMD_FLOAT,	"FLOAT",	0,		0 },
    { CMD_EXPORT,	"_EXPORT",	0,		0 },
    { CMD_CAT,		"CAT",		0,		0 },
    { CMD_DECODE,	"DECODE",	"DEC",		0 },
    { CMD_ENCODE,	"ENCODE",	"ENC",		0 },

    { CMD__N,0,0,0 }
};

//
///////////////////////////////////////////////////////////////////////////////
///////////////            OptionShort & OptionLong             ///////////////
///////////////////////////////////////////////////////////////////////////////

static const char OptionShort[] = "VhqvLc:lHBPNM:T:A:td:D:E:orupi";

static const struct option OptionLong[] =
{
	{ "version",		0, 0, 'V' },
	{ "help",		0, 0, 'h' },
	{ "xhelp",		0, 0, GO_XHELP },
	{ "config",		1, 0, GO_CONFIG },
	{ "allow-all",		0, 0, GO_ALLOW_ALL },
	 { "allowall",		0, 0, GO_ALLOW_ALL },
	{ "compatible",		1, 0, GO_COMPATIBLE },
	{ "width",		1, 0, GO_WIDTH },
	{ "max-width",		1, 0, GO_MAX_WIDTH },
	 { "maxwidth",		1, 0, GO_MAX_WIDTH },
	{ "quiet",		0, 0, 'q' },
	{ "verbose",		0, 0, 'v' },
	{ "logging",		0, 0, 'L' },
	{ "de",			0, 0, GO_DE },
	{ "colors",		2, 0, GO_COLORS },
	{ "no-colors",		0, 0, GO_NO_COLORS },
	 { "nocolors",		0, 0, GO_NO_COLORS },
	{ "ct-code",		0, 0, GO_CT_CODE },
	 { "ctcode",		0, 0, GO_CT_CODE },
	{ "le-code",		2, 0, GO_LE_CODE },
	 { "lecode",		2, 0, GO_LE_CODE },
	{ "chdir",		1, 0, GO_CHDIR },
	{ "const",		1, 0, 'c' },
	{ "round",		0, 0, GO_ROUND },
	{ "long",		0, 0, 'l' },
	{ "no-header",		0, 0, 'H' },
	 { "noheader",		0, 0, 'H' },
	{ "brief",		0, 0, 'B' },
	{ "no-param",		0, 0, 'P' },
	 { "noparam",		0, 0, 'P' },
	{ "no-echo",		0, 0, GO_NO_ECHO },
	 { "noecho",		0, 0, GO_NO_ECHO },
	{ "no-check",		0, 0, 'N' },
	 { "nocheck",		0, 0, 'N' },
	{ "max-file-size",	1, 0, 'M' },
	 { "maxfilesize",	1, 0, 'M' },
	{ "tracks",		1, 0, 'T' },
	{ "arenas",		1, 0, 'A' },
	{ "pat",		1, 0, GO_PAT },
	{ "utf-8",		0, 0, GO_UTF_8 },
	 { "utf8",		0, 0, GO_UTF_8 },
	{ "no-utf-8",		0, 0, GO_NO_UTF_8 },
	 { "no-utf8",		0, 0, GO_NO_UTF_8 },
	 { "noutf8",		0, 0, GO_NO_UTF_8 },
	{ "test",		0, 0, 't' },
	{ "force",		0, 0, GO_FORCE },
	{ "repair-magics",	2, 0, GO_REPAIR_MAGICS },
	 { "repairmagics",	2, 0, GO_REPAIR_MAGICS },
	{ "OLD",		0, 0, GO_OLD },
	{ "STD",		0, 0, GO_STD },
	{ "NEW",		0, 0, GO_NEW },
	{ "EXTRACT",		0, 0, GO_EXTRACT },
	{ "dest",		1, 0, 'd' },
	{ "DEST",		1, 0, 'D' },
	{ "esc",		1, 0, 'E' },
	{ "overwrite",		0, 0, 'o' },
	{ "number",		0, 0, GO_NUMBER },
	 { "num",		0, 0, GO_NUMBER },
	{ "remove-dest",	0, 0, 'r' },
	 { "removedest",	0, 0, 'r' },
	 { "rm-dest",		0, 0, 'r' },
	 { "rmdest",		0, 0, 'r' },
	 { "remove",		0, 0, 'r' },
	{ "update",		0, 0, 'u' },
	{ "preserve",		0, 0, 'p' },
	{ "ignore",		0, 0, 'i' },
	{ "sections",		0, 0, GO_SECTIONS },

	{0,0,0,0}
};

//
///////////////////////////////////////////////////////////////////////////////
///////////////            OptionUsed & OptionIndex             ///////////////
///////////////////////////////////////////////////////////////////////////////

static u8 OptionUsed[OPT__N_TOTAL+1] = {0};

static const OptionIndex_t OptionIndex[UIOPT_INDEX_SIZE] =
{
	/* 0x000   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x010   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x020   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x030   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x040   */	 0,
	/* 0x041 A */	OPT_ARENAS,
	/* 0x042 B */	OPT_BRIEF,
	/* 0x043   */	 0,
	/* 0x044 D */	OPT_DEST2,
	/* 0x045 E */	OPT_ESC,
	/* 0x046   */	 0,0,
	/* 0x048 H */	OPT_NO_HEADER,
	/* 0x049   */	 0,0,0,
	/* 0x04c L */	OPT_LOGGING,
	/* 0x04d M */	OPT_MAX_FILE_SIZE,
	/* 0x04e N */	OPT_NO_CHECK,
	/* 0x04f   */	 0,
	/* 0x050 P */	OPT_NO_PARAM,
	/* 0x051   */	 0,0,0,
	/* 0x054 T */	OPT_TRACKS,
	/* 0x055   */	 0,
	/* 0x056 V */	OPT_VERSION,
	/* 0x057   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 
	/* 0x063 c */	OPT_CONST,
	/* 0x064 d */	OPT_DEST,
	/* 0x065   */	 0,0,0,
	/* 0x068 h */	OPT_HELP,
	/* 0x069 i */	OPT_IGNORE,
	/* 0x06a   */	 0,0,
	/* 0x06c l */	OPT_LONG,
	/* 0x06d   */	 0,0,
	/* 0x06f o */	OPT_OVERWRITE,
	/* 0x070 p */	OPT_PRESERVE,
	/* 0x071 q */	OPT_QUIET,
	/* 0x072 r */	OPT_REMOVE_DEST,
	/* 0x073   */	 0,
	/* 0x074 t */	OPT_TEST,
	/* 0x075 u */	OPT_UPDATE,
	/* 0x076 v */	OPT_VERBOSE,
	/* 0x077   */	 0,0,0,0, 0,0,0,0, 0,
	/* 0x080   */	OPT_XHELP,
	/* 0x081   */	OPT_CONFIG,
	/* 0x082   */	OPT_ALLOW_ALL,
	/* 0x083   */	OPT_COMPATIBLE,
	/* 0x084   */	OPT_WIDTH,
	/* 0x085   */	OPT_MAX_WIDTH,
	/* 0x086   */	OPT_DE,
	/* 0x087   */	OPT_COLORS,
	/* 0x088   */	OPT_NO_COLORS,
	/* 0x089   */	OPT_CT_CODE,
	/* 0x08a   */	OPT_LE_CODE,
	/* 0x08b   */	OPT_CHDIR,
	/* 0x08c   */	OPT_ROUND,
	/* 0x08d   */	OPT_NO_ECHO,
	/* 0x08e   */	OPT_PAT,
	/* 0x08f   */	OPT_UTF_8,
	/* 0x090   */	OPT_NO_UTF_8,
	/* 0x091   */	OPT_FORCE,
	/* 0x092   */	OPT_REPAIR_MAGICS,
	/* 0x093   */	OPT_OLD,
	/* 0x094   */	OPT_STD,
	/* 0x095   */	OPT_NEW,
	/* 0x096   */	OPT_EXTRACT,
	/* 0x097   */	OPT_NUMBER,
	/* 0x098   */	OPT_SECTIONS,
	/* 0x099   */	 0,0,0,0, 0,0,0,
	/* 0x0a0   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x0b0   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x0c0   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x0d0   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x0e0   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x0f0   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x100   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x110   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x120   */	 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 0x130   */	 0,0,0,0, 0,0,
};

//
///////////////////////////////////////////////////////////////////////////////
///////////////                opt_allowed_cmd_*                ///////////////
///////////////////////////////////////////////////////////////////////////////

static u8 option_allowed_cmd_VERSION[18] = // cmd #1
{
    0,0,1,0,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,1
};

static u8 option_allowed_cmd_HELP[18] = // cmd #2
{
    1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1
};

static u8 option_allowed_cmd_CONFIG[18] = // cmd #3
{
    0,0,1,0,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,0
};

static u8 option_allowed_cmd_ARGTEST[18] = // cmd #4
{
    1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1
};

static u8 option_allowed_cmd_TEST[18] = // cmd #5
{
    1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1
};

static u8 option_allowed_cmd_COLORS[18] = // cmd #6
{
    0,0,1,0,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,0
};

static u8 option_allowed_cmd_ERROR[18] = // cmd #7
{
    0,0,1,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,1
};

static u8 option_allowed_cmd_FILETYPE[18] = // cmd #8
{
    0,0,1,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,0
};

static u8 option_allowed_cmd_FILEATTRIB[18] = // cmd #9
{
    0,0,0,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0
};

static u8 option_allowed_cmd_SYMBOLS[18] = // cmd #10
{
    0,0,0,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0
};

static u8 option_allowed_cmd_FUNCTIONS[18] = // cmd #11
{
    0,0,1,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,0
};

static u8 option_allowed_cmd_CALCULATE[18] = // cmd #12
{
    0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0
};

static u8 option_allowed_cmd_FLOAT[18] = // cmd #13
{
    0,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0
};

static u8 option_allowed_cmd_EXPORT[18] = // cmd #14
{
    0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0
};

static u8 option_allowed_cmd_CAT[18] = // cmd #15
{
    0,0,0,1,1, 0,1,1,0,0,  0,0,0,0,0, 0,1,0
};

static u8 option_allowed_cmd_DECODE[18] = // cmd #16
{
    0,0,0,1,1, 0,1,1,1,1,  1,1,1,1,1, 1,1,0
};

static u8 option_allowed_cmd_ENCODE[18] = // cmd #17
{
    0,0,0,0,0, 0,1,1,1,1,  1,1,1,1,1, 1,1,0
};


//
///////////////////////////////////////////////////////////////////////////////
///////////////                 InfoOption tabs                 ///////////////
///////////////////////////////////////////////////////////////////////////////

static const InfoOption_t * option_tab_tool[] =
{
	OptionInfo + OPT_VERSION,
	OptionInfo + OPT_HELP,
	OptionInfo + OPT_XHELP,
	OptionInfo + OPT_CONFIG,
	OptionInfo + OPT_ALLOW_ALL,
	OptionInfo + OPT_COMPATIBLE,
	OptionInfo + OPT_WIDTH,
	OptionInfo + OPT_MAX_WIDTH,
	OptionInfo + OPT_QUIET,
	OptionInfo + OPT_VERBOSE,
	OptionInfo + OPT_LOGGING,
	OptionInfo + OPT_DE,
	OptionInfo + OPT_COLORS,
	OptionInfo + OPT_NO_COLORS,
	OptionInfo + OPT_CT_CODE,
	OptionInfo + OPT_LE_CODE,
	OptionInfo + OPT_CHDIR,
	OptionInfo + OPT_CONST,
	OptionInfo + OPT_MAX_FILE_SIZE,
	OptionInfo + OPT_PAT,

	OptionInfo + OPT_NONE, // separator

	OptionInfo + OPT_TEST,
	OptionInfo + OPT_FORCE,
	OptionInfo + OPT_REPAIR_MAGICS,

	0
};

static const InfoOption_t * option_tab_cmd_VERSION[] =
{
	&option_cmd_VERSION_BRIEF,
	OptionInfo + OPT_SECTIONS,
	&option_cmd_VERSION_LONG,

	0
};

static const InfoOption_t * option_tab_cmd_HELP[] =
{
	OptionInfo + OPT_WIDTH,
	OptionInfo + OPT_MAX_WIDTH,

	0
};

static const InfoOption_t * option_tab_cmd_CONFIG[] =
{
	OptionInfo + OPT_CONFIG,
	&option_cmd_CONFIG_BRIEF,
	&option_cmd_CONFIG_LONG,

	0
};

static const InfoOption_t * option_tab_cmd_ARGTEST[] =
{

	0
};

static const InfoOption_t * option_tab_cmd_TEST[] =
{

	0
};

static const InfoOption_t * option_tab_cmd_COLORS[] =
{
	OptionInfo + OPT_COLORS,
	OptionInfo + OPT_NO_COLORS,
	&option_cmd_COLORS_LONG,
	&option_cmd_COLORS_BRIEF,

	0
};

static const InfoOption_t * option_tab_cmd_ERROR[] =
{
	OptionInfo + OPT_SECTIONS,
	OptionInfo + OPT_NO_HEADER,
	&option_cmd_ERROR_LONG,
	&option_cmd_ERROR_BRIEF,

	0
};

static const InfoOption_t * option_tab_cmd_FILETYPE[] =
{
	&option_cmd_FILETYPE_LONG,
	OptionInfo + OPT_IGNORE,

	0
};

static const InfoOption_t * option_tab_cmd_FILEATTRIB[] =
{
	OptionInfo + OPT_NO_HEADER,

	0
};

static const InfoOption_t * option_tab_cmd_SYMBOLS[] =
{
	OptionInfo + OPT_NO_HEADER,

	0
};

static const InfoOption_t * option_tab_cmd_FUNCTIONS[] =
{
	OptionInfo + OPT_NO_HEADER,
	&option_cmd_FUNCTIONS_BRIEF,
	&option_cmd_FUNCTIONS_LONG,

	0
};

static const InfoOption_t * option_tab_cmd_CALCULATE[] =
{
	OptionInfo + OPT_CONST,

	0
};

static const InfoOption_t * option_tab_cmd_FLOAT[] =
{
	OptionInfo + OPT_ROUND,

	0
};

static const InfoOption_t * option_tab_cmd_EXPORT[] =
{

	0
};

static const InfoOption_t * option_tab_cmd_CAT[] =
{
	OptionInfo + OPT_IGNORE,
	&option_grp_TEXTOUT_NO_HEADER,
	OptionInfo + OPT_BRIEF,
	OptionInfo + OPT_NO_ECHO,
	OptionInfo + OPT_NO_CHECK,

	0
};

static const InfoOption_t * option_tab_cmd_DECODE[] =
{
	OptionInfo + OPT_DEST,
	OptionInfo + OPT_DEST2,
	OptionInfo + OPT_ESC,
	OptionInfo + OPT_PAT,

	OptionInfo + OPT_NONE, // separator

	OptionInfo + OPT_OVERWRITE,
	OptionInfo + OPT_NUMBER,
	OptionInfo + OPT_REMOVE_DEST,
	OptionInfo + OPT_UPDATE,
	OptionInfo + OPT_PRESERVE,
	OptionInfo + OPT_IGNORE,
	&option_grp_TEXTOUT_NO_HEADER,
	OptionInfo + OPT_BRIEF,
	OptionInfo + OPT_NO_ECHO,
	OptionInfo + OPT_NO_CHECK,

	0
};

static const InfoOption_t * option_tab_cmd_ENCODE[] =
{
	OptionInfo + OPT_DEST,
	OptionInfo + OPT_DEST2,
	OptionInfo + OPT_ESC,
	OptionInfo + OPT_PAT,

	OptionInfo + OPT_NONE, // separator

	OptionInfo + OPT_OVERWRITE,
	OptionInfo + OPT_NUMBER,
	OptionInfo + OPT_REMOVE_DEST,
	OptionInfo + OPT_UPDATE,
	OptionInfo + OPT_PRESERVE,
	OptionInfo + OPT_NO_ECHO,
	OptionInfo + OPT_NO_CHECK,
	OptionInfo + OPT_IGNORE,

	0
};


//
///////////////////////////////////////////////////////////////////////////////
///////////////                   InfoCommand                   ///////////////
///////////////////////////////////////////////////////////////////////////////

static const InfoCommand_t CommandInfo[CMD__N+1] =
{
    {	0,
	false,
	false,
	false,
	"wpatt",
	0,
	"wpatt [option]... command [option|parameter|file]...",
	"Wiimms PAT Tool : Decode raw PAT and encode text PAT files.",
	0,
	23,
	option_tab_tool,
	0
    },

    {	CMD_VERSION,
	false,
	false,
	false,
	"VERSION",
	0,
	"wpatt VERSION [ignored]...",
	"Print program name and version and exit.",
	0,
	3,
	option_tab_cmd_VERSION,
	option_allowed_cmd_VERSION
    },

    {	CMD_HELP,
	false,
	false,
	false,
	"HELP",
	"H",
	"wpatt HELP [--width=wd] OPT|OPTION ...\n"
	"wpatt HELP [--width=wd] CMD|COMMAND [ignored]...\n"
	"wpatt HELP [--width=wd] command [-b] [ignored]...\n"
	"wpatt HELP [--width=wd] [ignored]...",
	"Print help for commands and options.",
	"Print help for commands and options.\n"
	"  The first variant (with keyword OPT or OPTION) prints a list of all"
	" global and command specific options. If at least one option is set,"
	" only info about the declared options are printed. The second variant"
	" (with keyword CMD or COMMAND) prints an overview about all commands."
	" The third variant (with a valid command name) prints details about"
	" the declared command. The fourth variant prints an overview about"
	" all commands and all global options.",
	2,
	option_tab_cmd_HELP,
	option_allowed_cmd_HELP
    },

    {	CMD_CONFIG,
	false,
	false,
	false,
	"CONFIG",
	0,
	"wpatt CONFIG [options]...",
	"Show all information about the search for the configuration file and"
	" its content.",
	0,
	3,
	option_tab_cmd_CONFIG,
	option_allowed_cmd_CONFIG
    },

    {	CMD_ARGTEST,
	false,
	false,
	false,
	"ARGTEST",
	0,
	"wpatt ARGTEST ...",
	"This debug command accepts all kinds of parameters and prints one"
	" line for each parameter.",
	0,
	0,
	option_tab_cmd_ARGTEST,
	option_allowed_cmd_ARGTEST
    },

    {	CMD_TEST,
	false,
	false,
	false,
	"TEST",
	0,
	"wpatt TEST [options]... [ignored]...",
	"This debugging command accepts all options and parameters and prints"
	" a list of the internal option values. The command is designed to"
	" test the option parameters. The non option parameters are completely"
	" ignored.",
	0,
	0,
	option_tab_cmd_TEST,
	option_allowed_cmd_TEST
    },

    {	CMD_COLORS,
	false,
	false,
	false,
	"COLORS",
	0,
	"wpatt COLORS",
	"Ignore all parameters and print colored text for testing.",
	0,
	4,
	option_tab_cmd_COLORS,
	option_allowed_cmd_COLORS
    },

    {	CMD_ERROR,
	false,
	false,
	false,
	"ERROR",
	"ERR",
	"wpatt ERROR [error_code]",
	"Translate an exit code to a message name. If no exit code is entered,"
	" print a table with all error messages.",
	0,
	4,
	option_tab_cmd_ERROR,
	option_allowed_cmd_ERROR
    },

    {	CMD_FILETYPE,
	false,
	false,
	false,
	"FILETYPE",
	"FT",
	"wpatt FILETYPE file...",
	"Scan the header of the entered files and print file type and path for"
	" each file as list.",
	0,
	2,
	option_tab_cmd_FILETYPE,
	option_allowed_cmd_FILETYPE
    },

    {	CMD_FILEATTRIB,
	false,
	false,
	false,
	"FILEATTRIB",
	"FA",
	"wpatt FILEATTRIB [keyword]...",
	"Print a table with attributes for all known file types. If at least"
	" one keyword is entered, only matching file types are printed. A"
	" keyword is either a file type (like 'BRRES' or 'BMG') or one of the"
	" printed keywords (like 'ARCHIVE' or 'EXTRACT').",
	0,
	1,
	option_tab_cmd_FILEATTRIB,
	option_allowed_cmd_FILEATTRIB
    },

    {	CMD_SYMBOLS,
	false,
	false,
	false,
	"SYMBOLS",
	0,
	"wpatt SYMBOLS",
	"Print predefined symbols of text parser to standard output. The PAT"
	" specific symbols are included.",
	0,
	1,
	option_tab_cmd_SYMBOLS,
	option_allowed_cmd_SYMBOLS
    },

    {	CMD_FUNCTIONS,
	false,
	false,
	false,
	"FUNCTIONS",
	0,
	"wpatt FUNCTIONS [key]...",
	"Print a list with all parser functions including the PAT specific"
	" functions. If one key ore more key entered, then only functions that"
	" match at least one key are printed.",
	0,
	3,
	option_tab_cmd_FUNCTIONS,
	option_allowed_cmd_FUNCTIONS
    },

    {	CMD_CALCULATE,
	false,
	false,
	false,
	"CALCULATE",
	0,
	"wpatt CALCULATE expression...",
	"Calculate each expression and print the result to standard output.",
	0,
	1,
	option_tab_cmd_CALCULATE,
	option_allowed_cmd_CALCULATE
    },

    {	CMD_FLOAT,
	false,
	false,
	false,
	"FLOAT",
	0,
	"wpatt FLOAT number...",
	"This commands helps to convert hex values into floating point numbers"
	" and vice versa. For each non empty parameter, a line with 4 bytes"
	" hex and a float, 8 bytes hex and a double float, and the parameter"
	" itself is printed. If a parameter begins with 'x' or '0x', it is a"
	" hex string, otherwise it is a floating point number.\n"
	"  The special parameters \"+\" and \"-\" mean: Increment or decrement"
	" the previous value by the smallest possible value. Use different"
	" increments for floats and doubles.\n"
	"  All conversions are done using big endian.",
	0,
	1,
	option_tab_cmd_FLOAT,
	option_allowed_cmd_FLOAT
    },

    {	CMD_EXPORT,
	true,
	false,
	false,
	"_EXPORT",
	0,
	"wszst _EXPORT key...",
	"This hidden command exports some definitions to standard output. Use"
	" keyword HELP to get a list of possible keywords.",
	0,
	0,
	option_tab_cmd_EXPORT,
	option_allowed_cmd_EXPORT
    },

    {	CMD_CAT,
	false,
	false,
	true,
	"CAT",
	0,
	"wpatt CAT [source]...",
	"Read the entered PAT files (text or binary) and print them as decoded"
	" text files to standard output (stdout). The output of all source"
	" files is concatenated.",
	0,
	5,
	option_tab_cmd_CAT,
	option_allowed_cmd_CAT
    },

    {	CMD_DECODE,
	false,
	false,
	false,
	"DECODE",
	"DEC",
	"wpatt DECODE [source]...",
	"Read the entered PAT files (text or binary) and decode them to text"
	" files. The default destination is '%P/%N.txt'.",
	0,
	14,
	option_tab_cmd_DECODE,
	option_allowed_cmd_DECODE
    },

    {	CMD_ENCODE,
	false,
	false,
	false,
	"ENCODE",
	"ENC",
	"wpatt ENCODE [source]...",
	"Read the entered PAT files (text or binary) and encode (compile) them"
	" to binary files. The default destination is '%P/%N.pat'.",
	0,
	12,
	option_tab_cmd_ENCODE,
	option_allowed_cmd_ENCODE
    },

    {0,0,0,0,0,0,0,0,0,0,0,0}
};

//
///////////////////////////////////////////////////////////////////////////////
///////////////                     InfoUI                      ///////////////
///////////////////////////////////////////////////////////////////////////////

const InfoUI_t InfoUI_wpatt =
{
	"wpatt",
	CMD__N,
	CommandTab,
	CommandInfo,
	OPT__N_SPECIFIC,
	OPT__N_TOTAL,
	OptionInfo,
	OptionUsed,
	OptionIndex,
	OptionShort,
	OptionLong
};

//
///////////////////////////////////////////////////////////////////////////////
///////////////                       END                       ///////////////
///////////////////////////////////////////////////////////////////////////////

