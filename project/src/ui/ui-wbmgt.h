
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
 *   Copyright (c) 2011-2022 by Dirk Clemens <wiimm@wiimm.de>              *
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


#ifndef SZS_UI_WBMGT_H
#define SZS_UI_WBMGT_H
#include "dclib-basics.h"
#include "dclib-ui.h"

//
///////////////////////////////////////////////////////////////////////////////
///////////////                enum enumOptions                 ///////////////
///////////////////////////////////////////////////////////////////////////////

typedef enum enumOptions
{
	OPT_NONE,

	//----- command specific options -----

	OPT_LONG,
	OPT_NO_HEADER,
	OPT_BRIEF,
	OPT_DEST,
	OPT_DEST2,
	OPT_ESC,
	OPT_OVERWRITE,
	OPT_NUMBER,
	OPT_REMOVE_DEST,
	OPT_UPDATE,
	OPT_PRESERVE,
	OPT_IGNORE,
	OPT_ALIGN,
	OPT_PATCH_BMG,
	OPT_MACRO_BMG,
	OPT_FILTER_BMG,
	OPT_BMG_ENDIAN,
	OPT_BMG_ENCODING,
	OPT_BMG_INF_SIZE,
	OPT_BMG_MID,
	OPT_FORCE_ATTRIB,
	OPT_DEF_ATTRIB,
	OPT_NO_ATTRIB,
	OPT_X_ESCAPES,
	OPT_OLD_ESCAPES,
	OPT_SINGLE_LINE,
	OPT_NO_BMG_COLORS,
	OPT_BMG_COLORS,
	OPT_NO_BMG_INLINE,
	OPT_EXPORT,
	OPT_SECTIONS,

	OPT__N_SPECIFIC, // == 32

	//----- global options -----

	OPT_VERSION,
	OPT_HELP,
	OPT_XHELP,
	OPT_CONFIG,
	OPT_ALLOW_ALL,
	OPT_COMPATIBLE,
	OPT_WIDTH,
	OPT_MAX_WIDTH,
	OPT_QUIET,
	OPT_VERBOSE,
	OPT_LOGGING,
	OPT_WARN,
	OPT_DE,
	OPT_COLORS,
	OPT_NO_COLORS,
	OPT_CT_CODE,
	OPT_LE_CODE,
	OPT_CHDIR,
	OPT_CONST,
	OPT_MAX_FILE_SIZE,
	OPT_TRACKS,
	OPT_ARENAS,
	OPT_POINTS,
	OPT_UTF_8,
	OPT_NO_UTF_8,
	OPT_TEST,
	OPT_FORCE,
	OPT_REPAIR_MAGICS,
	OPT_OLD,
	OPT_STD,
	OPT_NEW,
	OPT_EXTRACT,

	OPT__N_TOTAL // == 64

} enumOptions;

//
///////////////////////////////////////////////////////////////////////////////
///////////////               enum enumOptionsBit               ///////////////
///////////////////////////////////////////////////////////////////////////////

//	*****  only for verification  *****

//typedef enum enumOptionsBit
//{
//	//----- command specific options -----
//
//	OB_LONG			= 1llu << OPT_LONG,
//	OB_NO_HEADER		= 1llu << OPT_NO_HEADER,
//	OB_BRIEF		= 1llu << OPT_BRIEF,
//	OB_DEST			= 1llu << OPT_DEST,
//	OB_DEST2		= 1llu << OPT_DEST2,
//	OB_ESC			= 1llu << OPT_ESC,
//	OB_OVERWRITE		= 1llu << OPT_OVERWRITE,
//	OB_NUMBER		= 1llu << OPT_NUMBER,
//	OB_REMOVE_DEST		= 1llu << OPT_REMOVE_DEST,
//	OB_UPDATE		= 1llu << OPT_UPDATE,
//	OB_PRESERVE		= 1llu << OPT_PRESERVE,
//	OB_IGNORE		= 1llu << OPT_IGNORE,
//	OB_ALIGN		= 1llu << OPT_ALIGN,
//	OB_PATCH_BMG		= 1llu << OPT_PATCH_BMG,
//	OB_MACRO_BMG		= 1llu << OPT_MACRO_BMG,
//	OB_FILTER_BMG		= 1llu << OPT_FILTER_BMG,
//	OB_BMG_ENDIAN		= 1llu << OPT_BMG_ENDIAN,
//	OB_BMG_ENCODING		= 1llu << OPT_BMG_ENCODING,
//	OB_BMG_INF_SIZE		= 1llu << OPT_BMG_INF_SIZE,
//	OB_BMG_MID		= 1llu << OPT_BMG_MID,
//	OB_FORCE_ATTRIB		= 1llu << OPT_FORCE_ATTRIB,
//	OB_DEF_ATTRIB		= 1llu << OPT_DEF_ATTRIB,
//	OB_NO_ATTRIB		= 1llu << OPT_NO_ATTRIB,
//	OB_X_ESCAPES		= 1llu << OPT_X_ESCAPES,
//	OB_OLD_ESCAPES		= 1llu << OPT_OLD_ESCAPES,
//	OB_SINGLE_LINE		= 1llu << OPT_SINGLE_LINE,
//	OB_NO_BMG_COLORS	= 1llu << OPT_NO_BMG_COLORS,
//	OB_BMG_COLORS		= 1llu << OPT_BMG_COLORS,
//	OB_NO_BMG_INLINE	= 1llu << OPT_NO_BMG_INLINE,
//	OB_EXPORT		= 1llu << OPT_EXPORT,
//	OB_SECTIONS		= 1llu << OPT_SECTIONS,
//
//	//----- group & command options -----
//
//	OB_GRP_DEST		= OB_DEST
//				| OB_DEST2
//				| OB_ESC
//				| OB_OVERWRITE
//				| OB_NUMBER
//				| OB_REMOVE_DEST
//				| OB_UPDATE
//				| OB_PRESERVE,
//
//	OB_GRP_TEXTOUT		= OB_NO_HEADER
//				| OB_BRIEF
//				| OB_BMG_ENDIAN
//				| OB_BMG_ENCODING
//				| OB_BMG_INF_SIZE
//				| OB_BMG_MID
//				| OB_FORCE_ATTRIB
//				| OB_DEF_ATTRIB
//				| OB_NO_ATTRIB
//				| OB_X_ESCAPES
//				| OB_OLD_ESCAPES
//				| OB_SINGLE_LINE
//				| OB_NO_BMG_COLORS
//				| OB_BMG_COLORS
//				| OB_NO_BMG_INLINE
//				| OB_LONG
//				| OB_EXPORT,
//
//	OB_CMD_VERSION		= OB_BRIEF
//				| OB_SECTIONS
//				| OB_LONG,
//
//	OB_CMD_HELP		= ~(u64)0,
//
//	OB_CMD_CONFIG		= OB_BRIEF
//				| OB_LONG,
//
//	OB_CMD_ARGTEST		= ~(u64)0,
//
//	OB_CMD_TEST		= ~(u64)0,
//
//	OB_CMD_COLORS		= OB_LONG
//				| OB_BRIEF,
//
//	OB_CMD_ERROR		= OB_SECTIONS
//				| OB_NO_HEADER
//				| OB_LONG
//				| OB_BRIEF,
//
//	OB_CMD_FILETYPE		= OB_LONG
//				| OB_IGNORE,
//
//	OB_CMD_FILEATTRIB	= OB_NO_HEADER,
//
//	OB_CMD_POINTS		= OB_BRIEF
//				| OB_LONG,
//
//	OB_CMD_REGEXP		= 0,
//
//	OB_CMD_EXTRACT		= OB_NO_HEADER,
//
//	OB_CMD_SECTIONS		= OB_IGNORE,
//
//	OB_CMD_LIST		= OB_IGNORE
//				| OB_PATCH_BMG
//				| OB_MACRO_BMG
//				| OB_FILTER_BMG,
//
//	OB_CMD_SLOTS		= OB_IGNORE
//				| OB_PATCH_BMG
//				| OB_MACRO_BMG
//				| OB_FILTER_BMG,
//
//	OB_CMD_DIFF		= OB_PATCH_BMG
//				| OB_MACRO_BMG
//				| OB_FILTER_BMG
//				| OB_DEST
//				| OB_ESC,
//
//	OB_CMD_CAT		= OB_GRP_TEXTOUT
//				| OB_IGNORE
//				| OB_PATCH_BMG
//				| OB_MACRO_BMG
//				| OB_FILTER_BMG,
//
//	OB_CMD_MIX		= OB_CMD_CAT,
//
//	OB_CMD_IDENTIFIER	= OB_GRP_TEXTOUT,
//
//	OB_CMD_DECODE		= OB_GRP_DEST
//				| OB_GRP_TEXTOUT
//				| OB_IGNORE
//				| OB_PATCH_BMG
//				| OB_MACRO_BMG
//				| OB_FILTER_BMG,
//
//	OB_CMD_ENCODE		= OB_GRP_DEST
//				| OB_BMG_ENDIAN
//				| OB_BMG_ENCODING
//				| OB_BMG_INF_SIZE
//				| OB_BMG_MID
//				| OB_FORCE_ATTRIB
//				| OB_IGNORE
//				| OB_PATCH_BMG
//				| OB_MACRO_BMG
//				| OB_FILTER_BMG
//				| OB_ALIGN,
//
//	OB_CMD_PATCH		= OB_GRP_DEST
//				| OB_GRP_TEXTOUT
//				| OB_IGNORE
//				| OB_PATCH_BMG
//				| OB_MACRO_BMG
//				| OB_FILTER_BMG
//				| OB_ALIGN,
//
//} enumOptionsBit;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                enum enumCommands                ///////////////
///////////////////////////////////////////////////////////////////////////////

typedef enum enumCommands
{
	CMD__NONE,

	CMD_VERSION,
	CMD_HELP,
	CMD_CONFIG,
	CMD_ARGTEST,
	CMD_TEST,
	CMD_COLORS,
	CMD_ERROR,
	CMD_FILETYPE,
	CMD_FILEATTRIB,
	CMD_POINTS,
	CMD_REGEXP,

	CMD_EXTRACT,
	CMD_SECTIONS,
	CMD_LIST,
	CMD_SLOTS,
	CMD_DIFF,

	CMD_CAT,
	CMD_MIX,
	CMD_IDENTIFIER,
	CMD_DECODE,
	CMD_ENCODE,
	CMD_PATCH,


	CMD__N // == 23

} enumCommands;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                   enumGetOpt                    ///////////////
///////////////////////////////////////////////////////////////////////////////

typedef enum enumGetOpt
{
	GO_SINGLE_LINE		= '1',

	GO__ERR			= '?',

	GO_ARENAS		= 'A',
	GO_BRIEF		= 'B',
	GO_DEST2		= 'D',
	GO_ESC			= 'E',
	GO_NO_HEADER		= 'H',
	GO_LOGGING		= 'L',
	GO_MAX_FILE_SIZE	= 'M',
	GO_PATCH_BMG		= 'P',
	GO_TRACKS		= 'T',
	GO_VERSION		= 'V',
	GO_WARN			= 'W',
	GO_EXPORT		= 'X',

	GO_CONST		= 'c',
	GO_DEST			= 'd',
	GO_HELP			= 'h',
	GO_IGNORE		= 'i',
	GO_LONG			= 'l',
	GO_OVERWRITE		= 'o',
	GO_PRESERVE		= 'p',
	GO_QUIET		= 'q',
	GO_REMOVE_DEST		= 'r',
	GO_TEST			= 't',
	GO_UPDATE		= 'u',
	GO_VERBOSE		= 'v',

	GO_XHELP		= 0x80,
	GO_CONFIG,
	GO_ALLOW_ALL,
	GO_COMPATIBLE,
	GO_WIDTH,
	GO_MAX_WIDTH,
	GO_DE,
	GO_COLORS,
	GO_NO_COLORS,
	GO_CT_CODE,
	GO_LE_CODE,
	GO_CHDIR,
	GO_POINTS,
	GO_UTF_8,
	GO_NO_UTF_8,
	GO_FORCE,
	GO_REPAIR_MAGICS,
	GO_OLD,
	GO_STD,
	GO_NEW,
	GO_EXTRACT,
	GO_NUMBER,
	GO_ALIGN,
	GO_MACRO_BMG,
	GO_FILTER_BMG,
	GO_BMG_ENDIAN,
	GO_BMG_ENCODING,
	GO_BMG_INF_SIZE,
	GO_BMG_MID,
	GO_FORCE_ATTRIB,
	GO_DEF_ATTRIB,
	GO_NO_ATTRIB,
	GO_X_ESCAPES,
	GO_OLD_ESCAPES,
	GO_NO_BMG_COLORS,
	GO_BMG_COLORS,
	GO_NO_BMG_INLINE,
	GO_SECTIONS,

} enumGetOpt;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                  external vars                  ///////////////
///////////////////////////////////////////////////////////////////////////////

//extern const InfoOption_t OptionInfo[OPT__N_TOTAL+1];
//extern const KeywordTab_t CommandTab[];
//extern const char OptionShort[];
//extern const struct option OptionLong[];
//extern u8 OptionUsed[OPT__N_TOTAL+1];
//extern const OptionIndex_t OptionIndex[UIOPT_INDEX_SIZE];
//UIOPT_INDEX_SIZE := 0x136 = 310
//extern const InfoCommand_t CommandInfo[CMD__N+1];
extern const InfoUI_t InfoUI_wbmgt;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                       END                       ///////////////
///////////////////////////////////////////////////////////////////////////////

#endif // SZS_UI_WBMGT_H

