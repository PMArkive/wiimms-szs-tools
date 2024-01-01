
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
 *   Copyright (c) 2011-2024 by Dirk Clemens <wiimm@wiimm.de>              *
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


#ifndef SZS_UI_WMDLT_H
#define SZS_UI_WMDLT_H
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

	OPT_SCALE,
	OPT_SHIFT,
	OPT_XSS,
	OPT_YSS,
	OPT_ZSS,
	OPT_ROT,
	OPT_XROT,
	OPT_YROT,
	OPT_ZROT,
	OPT_TRANSLATE,
	OPT_NULL,
	OPT_NEXT,
	OPT_ASCALE,
	OPT_AROT,
	OPT_TFORM_SCRIPT,
	OPT_ROUND,
	OPT_LONG,
	OPT_NO_HEADER,
	OPT_BRIEF,
	OPT_NO_WILDCARDS,
	OPT_IN_ORDER,
	OPT_NO_PARAM,
	OPT_NO_ECHO,
	OPT_NO_CHECK,
	OPT_DEST,
	OPT_DEST2,
	OPT_ESC,
	OPT_OVERWRITE,
	OPT_NUMBER,
	OPT_REMOVE_DEST,
	OPT_UPDATE,
	OPT_PRESERVE,
	OPT_IGNORE,
	OPT_SECTIONS,

	OPT__N_SPECIFIC, // == 35

	//----- global options -----

	OPT_VERSION,
	OPT_HELP,
	OPT_XHELP,
	OPT_CONFIG,
	OPT_ALLOW_ALL,
	OPT_COMPATIBLE,
	OPT_WIDTH,
	OPT_MAX_WIDTH,
	OPT_NO_PAGER,
	OPT_QUIET,
	OPT_VERBOSE,
	OPT_LOGGING,
	OPT_EXT_ERRORS,
	OPT_TIMING,
	OPT_WARN,
	OPT_DE,
	OPT_COLORS,
	OPT_NO_COLORS,
	OPT_CT_CODE,
	OPT_LE_CODE,
	OPT_CHDIR,
	OPT_CONST,
	OPT_MDL,
	OPT_MAX_FILE_SIZE,
	OPT_TRACKS,
	OPT_ARENAS,
	OPT_UTF_8,
	OPT_NO_UTF_8,
	OPT_TEST,
	OPT_FORCE,
	OPT_REPAIR_MAGICS,
	OPT_TINY,
	OPT_OLD,
	OPT_STD,
	OPT_NEW,
	OPT_EXTRACT,

	OPT__N_TOTAL // == 71

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
//	OB_SCALE		= 1llu << OPT_SCALE,
//	OB_SHIFT		= 1llu << OPT_SHIFT,
//	OB_XSS			= 1llu << OPT_XSS,
//	OB_YSS			= 1llu << OPT_YSS,
//	OB_ZSS			= 1llu << OPT_ZSS,
//	OB_ROT			= 1llu << OPT_ROT,
//	OB_XROT			= 1llu << OPT_XROT,
//	OB_YROT			= 1llu << OPT_YROT,
//	OB_ZROT			= 1llu << OPT_ZROT,
//	OB_TRANSLATE		= 1llu << OPT_TRANSLATE,
//	OB_NULL			= 1llu << OPT_NULL,
//	OB_NEXT			= 1llu << OPT_NEXT,
//	OB_ASCALE		= 1llu << OPT_ASCALE,
//	OB_AROT			= 1llu << OPT_AROT,
//	OB_TFORM_SCRIPT		= 1llu << OPT_TFORM_SCRIPT,
//	OB_ROUND		= 1llu << OPT_ROUND,
//	OB_LONG			= 1llu << OPT_LONG,
//	OB_NO_HEADER		= 1llu << OPT_NO_HEADER,
//	OB_BRIEF		= 1llu << OPT_BRIEF,
//	OB_NO_WILDCARDS		= 1llu << OPT_NO_WILDCARDS,
//	OB_IN_ORDER		= 1llu << OPT_IN_ORDER,
//	OB_NO_PARAM		= 1llu << OPT_NO_PARAM,
//	OB_NO_ECHO		= 1llu << OPT_NO_ECHO,
//	OB_NO_CHECK		= 1llu << OPT_NO_CHECK,
//	OB_DEST			= 1llu << OPT_DEST,
//	OB_DEST2		= 1llu << OPT_DEST2,
//	OB_ESC			= 1llu << OPT_ESC,
//	OB_OVERWRITE		= 1llu << OPT_OVERWRITE,
//	OB_NUMBER		= 1llu << OPT_NUMBER,
//	OB_REMOVE_DEST		= 1llu << OPT_REMOVE_DEST,
//	OB_UPDATE		= 1llu << OPT_UPDATE,
//	OB_PRESERVE		= 1llu << OPT_PRESERVE,
//	OB_IGNORE		= 1llu << OPT_IGNORE,
//	OB_SECTIONS		= 1llu << OPT_SECTIONS,
//
//	//----- group & command options -----
//
//	OB_GRP_TRANSFORM	= OB_SCALE
//				| OB_SHIFT
//				| OB_XSS
//				| OB_YSS
//				| OB_ZSS
//				| OB_ROT
//				| OB_XROT
//				| OB_YROT
//				| OB_ZROT
//				| OB_TRANSLATE
//				| OB_NULL
//				| OB_ASCALE
//				| OB_AROT
//				| OB_TFORM_SCRIPT
//				| OB_NEXT,
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
//	OB_GRP_TEXTOUT		= OB_IGNORE
//				| OB_NO_HEADER
//				| OB_BRIEF,
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
//	OB_CMD_EXPAND		= ~(u64)0,
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
//	OB_CMD_FILETYPE		= OB_NO_WILDCARDS
//				| OB_IN_ORDER
//				| OB_IGNORE
//				| OB_LONG,
//
//	OB_CMD_FILEATTRIB	= OB_NO_HEADER,
//
//	OB_CMD_SYMBOLS		= OB_NO_HEADER,
//
//	OB_CMD_FUNCTIONS	= OB_NO_HEADER
//				| OB_BRIEF
//				| OB_LONG,
//
//	OB_CMD_CALCULATE	= 0,
//
//	OB_CMD_MATRIX		= OB_GRP_TRANSFORM
//				| OB_BRIEF
//				| OB_LONG,
//
//	OB_CMD_FLOAT		= OB_ROUND,
//
//	OB_CMD_EXPORT		= 0,
//
//	OB_CMD_CAT		= OB_NO_WILDCARDS
//				| OB_IN_ORDER
//				| OB_IGNORE
//				| OB_GRP_TEXTOUT
//				| OB_NO_ECHO
//				| OB_NO_CHECK
//				| OB_GRP_TRANSFORM,
//
//	OB_CMD_DECODE		= OB_NO_WILDCARDS
//				| OB_IN_ORDER
//				| OB_IGNORE
//				| OB_GRP_DEST
//				| OB_GRP_TEXTOUT
//				| OB_NO_ECHO
//				| OB_NO_CHECK
//				| OB_GRP_TRANSFORM,
//
//	OB_CMD_ENCODE		= OB_NO_WILDCARDS
//				| OB_IN_ORDER
//				| OB_IGNORE
//				| OB_GRP_DEST
//				| OB_NO_ECHO
//				| OB_NO_CHECK
//				| OB_GRP_TRANSFORM,
//
//	OB_CMD_STRINGS		= OB_NO_WILDCARDS
//				| OB_IN_ORDER
//				| OB_IGNORE
//				| OB_GRP_TEXTOUT
//				| OB_NO_ECHO
//				| OB_NO_CHECK
//				| OB_GRP_TRANSFORM,
//
//	OB_CMD_GEOMETRY		= OB_NO_WILDCARDS
//				| OB_IN_ORDER
//				| OB_IGNORE
//				| OB_GRP_TEXTOUT
//				| OB_NO_ECHO
//				| OB_NO_CHECK
//				| OB_GRP_TRANSFORM,
//
//	OB_CMD_XTEST		= OB_NO_WILDCARDS
//				| OB_IN_ORDER
//				| OB_IGNORE
//				| OB_GRP_TEXTOUT
//				| OB_NO_ECHO
//				| OB_NO_CHECK
//				| OB_GRP_TRANSFORM,
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
	CMD_EXPAND,
	CMD_TEST,
	CMD_COLORS,
	CMD_ERROR,
	CMD_FILETYPE,
	CMD_FILEATTRIB,
	CMD_SYMBOLS,
	CMD_FUNCTIONS,
	CMD_CALCULATE,
	CMD_MATRIX,
	CMD_FLOAT,
	CMD_EXPORT,

	CMD_CAT,
	CMD_DECODE,
	CMD_ENCODE,

	CMD_STRINGS,
	CMD_GEOMETRY,
	CMD_XTEST,

	CMD__N // == 23

} enumCommands;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                   enumGetOpt                    ///////////////
///////////////////////////////////////////////////////////////////////////////

typedef enum enumGetOpt
{
	GO__ERR			= '?',

	GO_ARENAS		= 'A',
	GO_BRIEF		= 'B',
	GO_DEST2		= 'D',
	GO_ESC			= 'E',
	GO_NO_HEADER		= 'H',
	GO_LOGGING		= 'L',
	GO_MAX_FILE_SIZE	= 'M',
	GO_NO_CHECK		= 'N',
	GO_NO_PARAM		= 'P',
	GO_TRACKS		= 'T',
	GO_VERSION		= 'V',
	GO_WARN			= 'W',
	GO_EXT_ERRORS		= 'Y',

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
	GO_NO_PAGER,
	GO_TIMING,
	GO_DE,
	GO_COLORS,
	GO_NO_COLORS,
	GO_CT_CODE,
	GO_LE_CODE,
	GO_CHDIR,
	GO_MDL,
	GO_SCALE,
	GO_SHIFT,
	GO_XSS,
	GO_YSS,
	GO_ZSS,
	GO_ROT,
	GO_XROT,
	GO_YROT,
	GO_ZROT,
	GO_TRANSLATE,
	GO_NULL,
	GO_NEXT,
	GO_ASCALE,
	GO_AROT,
	GO_TFORM_SCRIPT,
	GO_ROUND,
	GO_NO_WILDCARDS,
	GO_IN_ORDER,
	GO_NO_ECHO,
	GO_UTF_8,
	GO_NO_UTF_8,
	GO_FORCE,
	GO_REPAIR_MAGICS,
	GO_TINY,
	GO_OLD,
	GO_STD,
	GO_NEW,
	GO_EXTRACT,
	GO_NUMBER,
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
//UIOPT_INDEX_SIZE := 0x14a = 330
//extern const InfoCommand_t CommandInfo[CMD__N+1];
extern const InfoUI_t InfoUI_wmdlt;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                       END                       ///////////////
///////////////////////////////////////////////////////////////////////////////

#endif // SZS_UI_WMDLT_H

