
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


#ifndef SZS_UI_WLECT_H
#define SZS_UI_WLECT_H
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

	OPT_ROUND,
	OPT_LONG,
	OPT_NO_HEADER,
	OPT_BRIEF,
	OPT_EXPORT,
	OPT_NO_PARAM,
	OPT_NO_ECHO,
	OPT_LT_CLEAR,
	OPT_LT_ONLINE,
	OPT_LT_N_PLAYERS,
	OPT_LE_DEFINE,
	OPT_LPAR,
	OPT_ALIAS,
	OPT_ENGINE,
	OPT_200CC,
	OPT_PERFMON,
	OPT_CUSTOM_TT,
	OPT_XPFLAGS,
	OPT_SPEEDOMETER,
	OPT_DEBUG,
	OPT_TRACK_DIR,
	OPT_COPY_TRACKS,
	OPT_MOVE_TRACKS,
	OPT_MOVE1_TRACKS,
	OPT_LINK_TRACKS,
	OPT_COMPLETE,
	OPT_LOAD_BMG,
	OPT_PATCH_BMG,
	OPT_MACRO_BMG,
	OPT_PATCH_NAMES,
	OPT_ORDER_BY,
	OPT_ORDER_ALL,
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

	OPT__N_SPECIFIC, // == 43

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
	OPT_DE,
	OPT_COLORS,
	OPT_NO_COLORS,
	OPT_CT_CODE,
	OPT_LE_CODE,
	OPT_CHDIR,
	OPT_CONST,
	OPT_MAX_FILE_SIZE,
	OPT_UTF_8,
	OPT_NO_UTF_8,
	OPT_LT_COND_BIT,
	OPT_LT_GAME_MODE,
	OPT_LT_ENGINE,
	OPT_LT_RANDOM,
	OPT_LEX_PURGE,
	OPT_LEX_RM_FEAT,
	OPT_TEST,
	OPT_FORCE,
	OPT_REPAIR_MAGICS,
	OPT_OLD,
	OPT_STD,
	OPT_NEW,
	OPT_EXTRACT,

	OPT__N_TOTAL // == 77

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
//	OB_ROUND		= 1llu << OPT_ROUND,
//	OB_LONG			= 1llu << OPT_LONG,
//	OB_NO_HEADER		= 1llu << OPT_NO_HEADER,
//	OB_BRIEF		= 1llu << OPT_BRIEF,
//	OB_EXPORT		= 1llu << OPT_EXPORT,
//	OB_NO_PARAM		= 1llu << OPT_NO_PARAM,
//	OB_NO_ECHO		= 1llu << OPT_NO_ECHO,
//	OB_LT_CLEAR		= 1llu << OPT_LT_CLEAR,
//	OB_LT_ONLINE		= 1llu << OPT_LT_ONLINE,
//	OB_LT_N_PLAYERS		= 1llu << OPT_LT_N_PLAYERS,
//	OB_LE_DEFINE		= 1llu << OPT_LE_DEFINE,
//	OB_LPAR			= 1llu << OPT_LPAR,
//	OB_ALIAS		= 1llu << OPT_ALIAS,
//	OB_ENGINE		= 1llu << OPT_ENGINE,
//	OB_200CC		= 1llu << OPT_200CC,
//	OB_PERFMON		= 1llu << OPT_PERFMON,
//	OB_CUSTOM_TT		= 1llu << OPT_CUSTOM_TT,
//	OB_XPFLAGS		= 1llu << OPT_XPFLAGS,
//	OB_SPEEDOMETER		= 1llu << OPT_SPEEDOMETER,
//	OB_DEBUG		= 1llu << OPT_DEBUG,
//	OB_TRACK_DIR		= 1llu << OPT_TRACK_DIR,
//	OB_COPY_TRACKS		= 1llu << OPT_COPY_TRACKS,
//	OB_MOVE_TRACKS		= 1llu << OPT_MOVE_TRACKS,
//	OB_MOVE1_TRACKS		= 1llu << OPT_MOVE1_TRACKS,
//	OB_LINK_TRACKS		= 1llu << OPT_LINK_TRACKS,
//	OB_COMPLETE		= 1llu << OPT_COMPLETE,
//	OB_LOAD_BMG		= 1llu << OPT_LOAD_BMG,
//	OB_PATCH_BMG		= 1llu << OPT_PATCH_BMG,
//	OB_MACRO_BMG		= 1llu << OPT_MACRO_BMG,
//	OB_PATCH_NAMES		= 1llu << OPT_PATCH_NAMES,
//	OB_ORDER_BY		= 1llu << OPT_ORDER_BY,
//	OB_ORDER_ALL		= 1llu << OPT_ORDER_ALL,
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
//	OB_GRP_DEST		= OB_DEST
//				| OB_DEST2
//				| OB_ESC
//				| OB_OVERWRITE
//				| OB_NUMBER
//				| OB_REMOVE_DEST
//				| OB_UPDATE
//				| OB_PRESERVE,
//
//	OB_GRP_PARAM		= OB_ENGINE
//				| OB_200CC
//				| OB_PERFMON
//				| OB_CUSTOM_TT
//				| OB_XPFLAGS
//				| OB_SPEEDOMETER
//				| OB_DEBUG,
//
//	OB_GRP_PATCH		= OB_LE_DEFINE
//				| OB_LPAR
//				| OB_ALIAS
//				| OB_GRP_PARAM,
//
//	OB_GRP_TRACK_COPY	= OB_TRACK_DIR
//				| OB_COPY_TRACKS
//				| OB_MOVE_TRACKS
//				| OB_MOVE1_TRACKS
//				| OB_LINK_TRACKS,
//
//	OB_GRP_TEXTOPT		= OB_NO_HEADER
//				| OB_BRIEF
//				| OB_EXPORT,
//
//	OB_GRP_TEXTOUT		= OB_IGNORE
//				| OB_GRP_TEXTOPT,
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
//	OB_CMD_SYMBOLS		= OB_NO_HEADER,
//
//	OB_CMD_FUNCTIONS	= OB_NO_HEADER
//				| OB_BRIEF
//				| OB_LONG,
//
//	OB_CMD_CALCULATE	= 0,
//
//	OB_CMD_FLOAT		= OB_ROUND,
//
//	OB_CMD_EXPORT		= 0,
//
//	OB_CMD_DPAD		= 0,
//
//	OB_CMD_DUMP		= OB_GRP_PATCH
//				| OB_LONG
//				| OB_GRP_PATCH,
//
//	OB_CMD_DL		= OB_CMD_DUMP,
//
//	OB_CMD_DLL		= OB_CMD_DUMP,
//
//	OB_CMD_BIN_DIFF		= 0,
//
//	OB_CMD_PATCH		= OB_GRP_PATCH
//				| OB_GRP_TRACK_COPY
//				| OB_GRP_DEST
//				| OB_IGNORE,
//
//	OB_CMD_LPAR		= OB_GRP_PATCH
//				| OB_GRP_DEST
//				| OB_GRP_TEXTOUT,
//
//	OB_CMD_CREATE		= OB_GRP_TEXTOUT
//				| OB_NO_ECHO
//				| OB_GRP_DEST
//				| OB_LPAR
//				| OB_LT_CLEAR
//				| OB_LT_ONLINE
//				| OB_LT_N_PLAYERS
//				| OB_GRP_PARAM,
//
//	OB_CMD_CAT		= OB_COMPLETE
//				| OB_GRP_TEXTOUT
//				| OB_NO_ECHO
//				| OB_IGNORE,
//
//	OB_CMD_DECODE		= OB_COMPLETE
//				| OB_GRP_DEST
//				| OB_GRP_TEXTOUT
//				| OB_NO_ECHO
//				| OB_IGNORE,
//
//	OB_CMD_ENCODE		= OB_COMPLETE
//				| OB_GRP_DEST
//				| OB_NO_ECHO
//				| OB_IGNORE,
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
	CMD_SYMBOLS,
	CMD_FUNCTIONS,
	CMD_CALCULATE,
	CMD_FLOAT,
	CMD_EXPORT,
	CMD_DPAD,

	CMD_DUMP,
	CMD_DL,
	CMD_DLL,
	CMD_BIN_DIFF,
	CMD_PATCH,
	CMD_LPAR,

	CMD_CREATE,
	CMD_CAT,
	CMD_DECODE,
	CMD_ENCODE,


	CMD__N // == 26

} enumCommands;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                   enumGetOpt                    ///////////////
///////////////////////////////////////////////////////////////////////////////

typedef enum enumGetOpt
{
	GO__ERR			= '?',

	GO_BRIEF		= 'B',
	GO_COMPLETE		= 'C',
	GO_DEST2		= 'D',
	GO_ESC			= 'E',
	GO_NO_HEADER		= 'H',
	GO_LOGGING		= 'L',
	GO_MAX_FILE_SIZE	= 'M',
	GO_NO_PARAM		= 'P',
	GO_VERSION		= 'V',
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
	GO_ROUND,
	GO_NO_ECHO,
	GO_UTF_8,
	GO_NO_UTF_8,
	GO_LT_CLEAR,
	GO_LT_ONLINE,
	GO_LT_N_PLAYERS,
	GO_LT_COND_BIT,
	GO_LT_GAME_MODE,
	GO_LT_ENGINE,
	GO_LT_RANDOM,
	GO_LEX_PURGE,
	GO_LEX_RM_FEAT,
	GO_FORCE,
	GO_REPAIR_MAGICS,
	GO_OLD,
	GO_STD,
	GO_NEW,
	GO_EXTRACT,
	GO_LE_DEFINE,
	GO_LPAR,
	GO_ALIAS,
	GO_ENGINE,
	GO_200CC,
	GO_PERFMON,
	GO_CUSTOM_TT,
	GO_XPFLAGS,
	GO_SPEEDOMETER,
	GO_DEBUG,
	GO_TRACK_DIR,
	GO_COPY_TRACKS,
	GO_MOVE_TRACKS,
	GO_MOVE1_TRACKS,
	GO_LINK_TRACKS,
	GO_LOAD_BMG,
	GO_PATCH_BMG,
	GO_MACRO_BMG,
	GO_PATCH_NAMES,
	GO_ORDER_BY,
	GO_ORDER_ALL,
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
//UIOPT_INDEX_SIZE := 0x136 = 310
//extern const InfoCommand_t CommandInfo[CMD__N+1];
extern const InfoUI_t InfoUI_wlect;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                       END                       ///////////////
///////////////////////////////////////////////////////////////////////////////

#endif // SZS_UI_WLECT_H

