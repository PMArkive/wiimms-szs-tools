
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
 *   Copyright (c) 2011-2023 by Dirk Clemens <wiimm@wiimm.de>              *
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


#ifndef SZS_UI_WSZST_H
#define SZS_UI_WSZST_H
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

	OPT_PLUS,
	OPT_SPLIT,
	OPT_PRINTF,
	OPT_TOUCH,
	OPT_AUTO,
	OPT_SET_FLAGS,
	OPT_SET_SCALE,
	OPT_SET_ROT,
	OPT_SET_X,
	OPT_SET_Y,
	OPT_SET_Z,
	OPT_XCENTER,
	OPT_YCENTER,
	OPT_ZCENTER,
	OPT_CENTER,
	OPT_SCALE,
	OPT_SHIFT,
	OPT_XSS,
	OPT_YSS,
	OPT_ZSS,
	OPT_ROT,
	OPT_XROT,
	OPT_YROT,
	OPT_ZROT,
	OPT_YPOS,
	OPT_TRANSLATE,
	OPT_NULL,
	OPT_NEXT,
	OPT_ASCALE,
	OPT_AROT,
	OPT_TFORM_SCRIPT,
	OPT_MINIMAP,
	OPT_RM_GOBJ,
	OPT_SLOT,
	OPT_KCL_FLAG,
	OPT_KCL_SCRIPT,
	OPT_FLAG_FILE,
	OPT_REPAIR_XPF,
	OPT_GAMEMODES,
	OPT_LOAD_BMG,
	OPT_PATCH_BMG,
	OPT_MACRO_BMG,
	OPT_FILTER_BMG,
	OPT_LE_MENU,
	OPT_TITLE_SCREEN,
	OPT_CUP_ICONS,
	OPT_NO_COPY,
	OPT_ID,
	OPT_BASE64,
	OPT_DB64,
	OPT_CODING,
	OPT_VERIFY,
	OPT_ROUND,
	OPT_LONG,
	OPT_NO_HEADER,
	OPT_BRIEF,
	OPT_IN_ORDER,
	OPT_PIPE,
	OPT_DELTA,
	OPT_DIFF,
	OPT_EPSILON,
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
	OPT_NO_PARAM,
	OPT_SORT,
	OPT_TRANSFORM,
	OPT_STRIP,
	OPT_FMODES,
	OPT_INSTALL,
	OPT_ANALYZE,
	OPT_ANALYZE_MODE,
	OPT_SOURCE,
	OPT_REFERENCE,
	OPT_DEST,
	OPT_DEST2,
	OPT_ESC,
	OPT_OVERWRITE,
	OPT_NUMBER,
	OPT_REMOVE_SRC,
	OPT_REMOVE_DEST,
	OPT_UPDATE,
	OPT_PRESERVE,
	OPT_IGNORE,
	OPT_IGNORE_SETUP,
	OPT_PURGE,
	OPT_ALIGN_U8,
	OPT_ALIGN_PACK,
	OPT_ALIGN_BRRES,
	OPT_ALIGN_BREFF,
	OPT_ALIGN_BREFT,
	OPT_ALIGN,
	OPT_ENCODE_ALL,
	OPT_ENCODE_IMG,
	OPT_NO_ENCODE,
	OPT_NO_RECURSE,
	OPT_AUTO_ADD,
	OPT_NO_ECHO,
	OPT_NO_CHECK,
	OPT_PT_DIR,
	OPT_RM_AIPARAM,
	OPT_U8,
	OPT_SZS,
	OPT_WU8,
	OPT_XWU8,
	OPT_WBZ,
	OPT_PACK,
	OPT_BRRES,
	OPT_BREFF,
	OPT_BREFT,
	OPT_NO_COMPRESS,
	OPT_COMPRESS,
	OPT_FAST,
	OPT_NORM,
	OPT_LINKS,
	OPT_BASEDIR,
	OPT_RECURSE,
	OPT_EXT,
	OPT_DECODE,
	OPT_MIPMAPS,
	OPT_NO_MIPMAPS,
	OPT_N_MIPMAPS,
	OPT_MAX_MIPMAPS,
	OPT_MIPMAP_SIZE,
	OPT_FAST_MIPMAPS,
	OPT_CMPR_DEFAULT,
	OPT_CUT,
	OPT_ALL,
	OPT_RAW,
	OPT_SECTIONS,

	OPT__N_SPECIFIC, // == 142

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
	OPT_LOAD_PREFIX,
	OPT_LOAD_CATEGORY,
	OPT_CHDIR,
	OPT_CONST,
	OPT_BATTLE,
	OPT_EXPORT_FLAGS,
	OPT_ROUTE_OPTIONS,
	OPT_WIM0,
	OPT_LOAD_KCL,
	OPT_KCL,
	OPT_TRI_AREA,
	OPT_TRI_HEIGHT,
	OPT_XTRIDATA,
	OPT_KMP,
	OPT_SPEED_MOD,
	OPT_KTPT2,
	OPT_TFORM_KMP,
	OPT_MDL,
	OPT_PAT,
	OPT_PATCH_FILE,
	OPT_KMG_LIMIT,
	OPT_KMG_COPY,
	OPT_LT_CLEAR,
	OPT_LT_ONLINE,
	OPT_LT_N_PLAYERS,
	OPT_LT_COND_BIT,
	OPT_LT_GAME_MODE,
	OPT_LT_ENGINE,
	OPT_LT_RANDOM,
	OPT_LEX_PURGE,
	OPT_LEX_FEATURES,
	OPT_LEX_RM_FEAT,
	OPT_CACHE,
	OPT_CNAME,
	OPT_LOG_CACHE,
	OPT_PARALLEL,
	OPT_MAX_FILE_SIZE,
	OPT_TRACKS,
	OPT_ARENAS,
	OPT_AUTOADD_PATH,
	OPT_UTF_8,
	OPT_NO_UTF_8,
	OPT_TEST,
	OPT_FORCE,
	OPT_REPAIR_MAGICS,
	OPT_TINY,
	OPT_YAZ0,
	OPT_YAZ1,
	OPT_XYZ,
	OPT_BZ,
	OPT_SH,
	OPT_BASH,
	OPT_JSON,
	OPT_PHP,
	OPT_MAKEDOC,
	OPT_VAR,
	OPT_ARRAY,
	OPT_AVAR,
	OPT_CASE,
	OPT_OLD,
	OPT_STD,
	OPT_NEW,
	OPT_EXTRACT,

	OPT__N_TOTAL // == 225

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
//	OB_PLUS			= 1llu << OPT_PLUS,
//	OB_SPLIT		= 1llu << OPT_SPLIT,
//	OB_PRINTF		= 1llu << OPT_PRINTF,
//	OB_TOUCH		= 1llu << OPT_TOUCH,
//	OB_AUTO			= 1llu << OPT_AUTO,
//	OB_SET_FLAGS		= 1llu << OPT_SET_FLAGS,
//	OB_SET_SCALE		= 1llu << OPT_SET_SCALE,
//	OB_SET_ROT		= 1llu << OPT_SET_ROT,
//	OB_SET_X		= 1llu << OPT_SET_X,
//	OB_SET_Y		= 1llu << OPT_SET_Y,
//	OB_SET_Z		= 1llu << OPT_SET_Z,
//	OB_XCENTER		= 1llu << OPT_XCENTER,
//	OB_YCENTER		= 1llu << OPT_YCENTER,
//	OB_ZCENTER		= 1llu << OPT_ZCENTER,
//	OB_CENTER		= 1llu << OPT_CENTER,
//	OB_SCALE		= 1llu << OPT_SCALE,
//	OB_SHIFT		= 1llu << OPT_SHIFT,
//	OB_XSS			= 1llu << OPT_XSS,
//	OB_YSS			= 1llu << OPT_YSS,
//	OB_ZSS			= 1llu << OPT_ZSS,
//	OB_ROT			= 1llu << OPT_ROT,
//	OB_XROT			= 1llu << OPT_XROT,
//	OB_YROT			= 1llu << OPT_YROT,
//	OB_ZROT			= 1llu << OPT_ZROT,
//	OB_YPOS			= 1llu << OPT_YPOS,
//	OB_TRANSLATE		= 1llu << OPT_TRANSLATE,
//	OB_NULL			= 1llu << OPT_NULL,
//	OB_NEXT			= 1llu << OPT_NEXT,
//	OB_ASCALE		= 1llu << OPT_ASCALE,
//	OB_AROT			= 1llu << OPT_AROT,
//	OB_TFORM_SCRIPT		= 1llu << OPT_TFORM_SCRIPT,
//	OB_MINIMAP		= 1llu << OPT_MINIMAP,
//	OB_RM_GOBJ		= 1llu << OPT_RM_GOBJ,
//	OB_SLOT			= 1llu << OPT_SLOT,
//	OB_KCL_FLAG		= 1llu << OPT_KCL_FLAG,
//	OB_KCL_SCRIPT		= 1llu << OPT_KCL_SCRIPT,
//	OB_FLAG_FILE		= 1llu << OPT_FLAG_FILE,
//	OB_REPAIR_XPF		= 1llu << OPT_REPAIR_XPF,
//	OB_GAMEMODES		= 1llu << OPT_GAMEMODES,
//	OB_LOAD_BMG		= 1llu << OPT_LOAD_BMG,
//	OB_PATCH_BMG		= 1llu << OPT_PATCH_BMG,
//	OB_MACRO_BMG		= 1llu << OPT_MACRO_BMG,
//	OB_FILTER_BMG		= 1llu << OPT_FILTER_BMG,
//	OB_LE_MENU		= 1llu << OPT_LE_MENU,
//	OB_TITLE_SCREEN		= 1llu << OPT_TITLE_SCREEN,
//	OB_CUP_ICONS		= 1llu << OPT_CUP_ICONS,
//	OB_NO_COPY		= 1llu << OPT_NO_COPY,
//	OB_ID			= 1llu << OPT_ID,
//	OB_BASE64		= 1llu << OPT_BASE64,
//	OB_DB64			= 1llu << OPT_DB64,
//	OB_CODING		= 1llu << OPT_CODING,
//	OB_VERIFY		= 1llu << OPT_VERIFY,
//	OB_ROUND		= 1llu << OPT_ROUND,
//	OB_LONG			= 1llu << OPT_LONG,
//	OB_NO_HEADER		= 1llu << OPT_NO_HEADER,
//	OB_BRIEF		= 1llu << OPT_BRIEF,
//	OB_IN_ORDER		= 1llu << OPT_IN_ORDER,
//	OB_PIPE			= 1llu << OPT_PIPE,
//	OB_DELTA		= 1llu << OPT_DELTA,
//	OB_DIFF			= 1llu << OPT_DIFF,
//	OB_EPSILON		= 1llu << OPT_EPSILON,
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
//	OB_NO_PARAM		= 1llu << OPT_NO_PARAM,
//	OB_SORT			= 1llu << OPT_SORT,
//	OB_TRANSFORM		= 1llu << OPT_TRANSFORM,
//	OB_STRIP		= 1llu << OPT_STRIP,
//	OB_FMODES		= 1llu << OPT_FMODES,
//	OB_INSTALL		= 1llu << OPT_INSTALL,
//	OB_ANALYZE		= 1llu << OPT_ANALYZE,
//	OB_ANALYZE_MODE		= 1llu << OPT_ANALYZE_MODE,
//	OB_SOURCE		= 1llu << OPT_SOURCE,
//	OB_REFERENCE		= 1llu << OPT_REFERENCE,
//	OB_DEST			= 1llu << OPT_DEST,
//	OB_DEST2		= 1llu << OPT_DEST2,
//	OB_ESC			= 1llu << OPT_ESC,
//	OB_OVERWRITE		= 1llu << OPT_OVERWRITE,
//	OB_NUMBER		= 1llu << OPT_NUMBER,
//	OB_REMOVE_SRC		= 1llu << OPT_REMOVE_SRC,
//	OB_REMOVE_DEST		= 1llu << OPT_REMOVE_DEST,
//	OB_UPDATE		= 1llu << OPT_UPDATE,
//	OB_PRESERVE		= 1llu << OPT_PRESERVE,
//	OB_IGNORE		= 1llu << OPT_IGNORE,
//	OB_IGNORE_SETUP		= 1llu << OPT_IGNORE_SETUP,
//	OB_PURGE		= 1llu << OPT_PURGE,
//	OB_ALIGN_U8		= 1llu << OPT_ALIGN_U8,
//	OB_ALIGN_PACK		= 1llu << OPT_ALIGN_PACK,
//	OB_ALIGN_BRRES		= 1llu << OPT_ALIGN_BRRES,
//	OB_ALIGN_BREFF		= 1llu << OPT_ALIGN_BREFF,
//	OB_ALIGN_BREFT		= 1llu << OPT_ALIGN_BREFT,
//	OB_ALIGN		= 1llu << OPT_ALIGN,
//	OB_ENCODE_ALL		= 1llu << OPT_ENCODE_ALL,
//	OB_ENCODE_IMG		= 1llu << OPT_ENCODE_IMG,
//	OB_NO_ENCODE		= 1llu << OPT_NO_ENCODE,
//	OB_NO_RECURSE		= 1llu << OPT_NO_RECURSE,
//	OB_AUTO_ADD		= 1llu << OPT_AUTO_ADD,
//	OB_NO_ECHO		= 1llu << OPT_NO_ECHO,
//	OB_NO_CHECK		= 1llu << OPT_NO_CHECK,
//	OB_PT_DIR		= 1llu << OPT_PT_DIR,
//	OB_RM_AIPARAM		= 1llu << OPT_RM_AIPARAM,
//	OB_U8			= 1llu << OPT_U8,
//	OB_SZS			= 1llu << OPT_SZS,
//	OB_WU8			= 1llu << OPT_WU8,
//	OB_XWU8			= 1llu << OPT_XWU8,
//	OB_WBZ			= 1llu << OPT_WBZ,
//	OB_PACK			= 1llu << OPT_PACK,
//	OB_BRRES		= 1llu << OPT_BRRES,
//	OB_BREFF		= 1llu << OPT_BREFF,
//	OB_BREFT		= 1llu << OPT_BREFT,
//	OB_NO_COMPRESS		= 1llu << OPT_NO_COMPRESS,
//	OB_COMPRESS		= 1llu << OPT_COMPRESS,
//	OB_FAST			= 1llu << OPT_FAST,
//	OB_NORM			= 1llu << OPT_NORM,
//	OB_LINKS		= 1llu << OPT_LINKS,
//	OB_BASEDIR		= 1llu << OPT_BASEDIR,
//	OB_RECURSE		= 1llu << OPT_RECURSE,
//	OB_EXT			= 1llu << OPT_EXT,
//	OB_DECODE		= 1llu << OPT_DECODE,
//	OB_MIPMAPS		= 1llu << OPT_MIPMAPS,
//	OB_NO_MIPMAPS		= 1llu << OPT_NO_MIPMAPS,
//	OB_N_MIPMAPS		= 1llu << OPT_N_MIPMAPS,
//	OB_MAX_MIPMAPS		= 1llu << OPT_MAX_MIPMAPS,
//	OB_MIPMAP_SIZE		= 1llu << OPT_MIPMAP_SIZE,
//	OB_FAST_MIPMAPS		= 1llu << OPT_FAST_MIPMAPS,
//	OB_CMPR_DEFAULT		= 1llu << OPT_CMPR_DEFAULT,
//	OB_CUT			= 1llu << OPT_CUT,
//	OB_ALL			= 1llu << OPT_ALL,
//	OB_RAW			= 1llu << OPT_RAW,
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
//				| OB_YPOS
//				| OB_TRANSLATE
//				| OB_NULL
//				| OB_NEXT
//				| OB_ASCALE
//				| OB_AROT
//				| OB_TFORM_SCRIPT,
//
//	OB_GRP_TRANSFORM2	= OB_GRP_TRANSFORM
//				| OB_RM_GOBJ
//				| OB_SLOT
//				| OB_KCL_FLAG
//				| OB_KCL_SCRIPT
//				| OB_REPAIR_XPF
//				| OB_MINIMAP
//				| OB_PATCH_BMG
//				| OB_MACRO_BMG
//				| OB_FILTER_BMG
//				| OB_LE_MENU
//				| OB_TITLE_SCREEN
//				| OB_CUP_ICONS,
//
//	OB_GRP_DEST		= OB_DEST
//				| OB_DEST2
//				| OB_ESC
//				| OB_PRESERVE
//				| OB_UPDATE
//				| OB_OVERWRITE
//				| OB_NUMBER
//				| OB_REMOVE_DEST,
//
//	OB_GRP_FFORMAT1		= OB_U8
//				| OB_WU8
//				| OB_SZS
//				| OB_XWU8
//				| OB_WBZ,
//
//	OB_GRP_FFORMAT2		= OB_U8
//				| OB_WU8
//				| OB_PACK
//				| OB_BRRES
//				| OB_BREFF
//				| OB_BREFT
//				| OB_SZS
//				| OB_XWU8
//				| OB_WBZ,
//
//	OB_GRP_SCRIPT		= OB_SECTIONS,
//
//	OB_GRP_ALIGN		= OB_ALIGN_U8
//				| OB_ALIGN_PACK
//				| OB_ALIGN_BRRES
//				| OB_ALIGN_BREFF
//				| OB_ALIGN_BREFT
//				| OB_ALIGN,
//
//	OB_GRP_TEXTOUT		= OB_IGNORE
//				| OB_NO_HEADER
//				| OB_BRIEF
//				| OB_DELTA
//				| OB_DIFF
//				| OB_EXPORT
//				| OB_NO_PARAM,
//
//	OB_GRP_BMG		= OB_BMG_ENDIAN
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
//	OB_GRP_ENCODE		= OB_ENCODE_ALL
//				| OB_ENCODE_IMG
//				| OB_ALL
//				| OB_NO_ENCODE
//				| OB_NO_RECURSE
//				| OB_NO_ECHO
//				| OB_NO_CHECK
//				| OB_TRANSFORM
//				| OB_STRIP,
//
//	OB_GRP_CREATE		= OB_IGNORE_SETUP
//				| OB_GRP_FFORMAT2
//				| OB_PT_DIR
//				| OB_LINKS
//				| OB_RM_AIPARAM
//				| OB_GRP_ALIGN
//				| OB_GRP_ENCODE
//				| OB_AUTO_ADD
//				| OB_MIPMAPS
//				| OB_NO_MIPMAPS
//				| OB_N_MIPMAPS
//				| OB_MAX_MIPMAPS
//				| OB_MIPMAP_SIZE
//				| OB_FAST_MIPMAPS
//				| OB_CMPR_DEFAULT,
//
//	OB_GRP_NORM		= OB_NORM
//				| OB_LINKS
//				| OB_GRP_ALIGN
//				| OB_PT_DIR
//				| OB_RM_AIPARAM
//				| OB_AUTO_ADD,
//
//	OB_GRP_EXTRACT		= OB_BASEDIR
//				| OB_RECURSE
//				| OB_EXT
//				| OB_LINKS
//				| OB_DECODE
//				| OB_MIPMAPS
//				| OB_NO_MIPMAPS
//				| OB_FAST_MIPMAPS
//				| OB_CMPR_DEFAULT
//				| OB_CUT
//				| OB_ALL
//				| OB_GRP_TEXTOUT
//				| OB_NO_CHECK
//				| OB_RAW,
//
//	OB_CMD_VERSION		= OB_BRIEF
//				| OB_SECTIONS
//				| OB_LONG,
//
//	OB_CMD_HELP		= ~(u64)0,
//
//	OB_CMD_CONFIG		= OB_INSTALL
//				| OB_BRIEF
//				| OB_LONG
//				| OB_GRP_SCRIPT,
//
//	OB_CMD_INSTALL		= 0,
//
//	OB_CMD_ARGTEST		= ~(u64)0,
//
//	OB_CMD_EXPAND		= ~(u64)0,
//
//	OB_CMD_WILDCARDS	= OB_IGNORE
//				| OB_IN_ORDER,
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
//				| OB_NO_HEADER
//				| OB_IGNORE,
//
//	OB_CMD_UI_CHECK		= OB_LONG
//				| OB_NO_HEADER
//				| OB_IN_ORDER
//				| OB_IGNORE,
//
//	OB_CMD_FILEATTRIB	= OB_NO_HEADER,
//
//	OB_CMD_BRSUB		= OB_IGNORE
//				| OB_NO_HEADER
//				| OB_LONG,
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
//	OB_CMD_VR_CALC		= OB_NO_HEADER
//				| OB_BRIEF,
//
//	OB_CMD_VR_RACE		= OB_LONG,
//
//	OB_CMD_AUTOADD		= OB_IGNORE
//				| OB_DEST
//				| OB_DEST2
//				| OB_OVERWRITE
//				| OB_REMOVE_DEST
//				| OB_PRESERVE,
//
//	OB_CMD_TRACKS		= OB_ALL
//				| OB_LONG
//				| OB_PIPE
//				| OB_LOAD_BMG,
//
//	OB_CMD_SCANCACHE	= OB_PURGE
//				| OB_FAST,
//
//	OB_CMD_EXPORT		= 0,
//
//	OB_CMD_SIZEOF		= OB_SORT
//				| OB_BRIEF,
//
//	OB_CMD_CODE		= 0,
//
//	OB_CMD_RECODE		= 0,
//
//	OB_CMD_SUBFILE		= OB_GRP_DEST,
//
//	OB_CMD_LIST		= OB_RECURSE
//				| OB_EXT
//				| OB_CUT
//				| OB_ALL
//				| OB_LONG
//				| OB_SORT
//				| OB_NO_HEADER
//				| OB_IN_ORDER
//				| OB_GRP_CREATE
//				| OB_IGNORE
//				| OB_NORM
//				| OB_LINKS
//				| OB_RM_AIPARAM
//				| OB_SLOT,
//
//	OB_CMD_LIST_L		= OB_CMD_LIST,
//
//	OB_CMD_LIST_LL		= OB_CMD_LIST_L,
//
//	OB_CMD_LIST_LLL		= OB_CMD_LIST_LL,
//
//	OB_CMD_LIST_A		= OB_CMD_LIST_L,
//
//	OB_CMD_LIST_LA		= OB_CMD_LIST_A,
//
//	OB_CMD_NAME_REF		= OB_SORT
//				| OB_BRIEF
//				| OB_LONG,
//
//	OB_CMD_ILIST		= OB_RECURSE
//				| OB_ALL
//				| OB_LONG
//				| OB_SORT
//				| OB_NO_HEADER
//				| OB_GRP_CREATE
//				| OB_IGNORE
//				| OB_NORM
//				| OB_LINKS,
//
//	OB_CMD_ILIST_L		= OB_CMD_ILIST,
//
//	OB_CMD_ILIST_LL		= OB_CMD_ILIST_L,
//
//	OB_CMD_ILIST_A		= OB_CMD_ILIST,
//
//	OB_CMD_ILIST_LA		= OB_CMD_ILIST_A,
//
//	OB_CMD_MEMORY		= OB_RECURSE
//				| OB_EXT
//				| OB_DECODE
//				| OB_MIPMAPS
//				| OB_CUT
//				| OB_ALL
//				| OB_LONG
//				| OB_GRP_CREATE
//				| OB_IGNORE
//				| OB_NORM
//				| OB_LINKS
//				| OB_RM_AIPARAM
//				| OB_SLOT,
//
//	OB_CMD_MEMORY_A		= OB_CMD_MEMORY,
//
//	OB_CMD_DUMP		= OB_GRP_CREATE
//				| OB_IGNORE
//				| OB_NORM
//				| OB_LINKS,
//
//	OB_CMD_SHA1		= OB_IGNORE
//				| OB_NORM
//				| OB_LINKS
//				| OB_GRP_CREATE
//				| OB_ID
//				| OB_BASE64
//				| OB_DB64
//				| OB_CODING
//				| OB_VERIFY
//				| OB_BRIEF
//				| OB_LONG,
//
//	OB_CMD_ANALYZE		= OB_LONG
//				| OB_IGNORE
//				| OB_GRP_SCRIPT
//				| OB_REFERENCE
//				| OB_DEST
//				| OB_DEST2,
//
//	OB_CMD_SPLIT		= OB_PLUS
//				| OB_SPLIT
//				| OB_PRINTF
//				| OB_IGNORE
//				| OB_GRP_SCRIPT
//				| OB_DEST
//				| OB_DEST2,
//
//	OB_CMD_IS_TEXTURE	= OB_IGNORE
//				| OB_REFERENCE
//				| OB_LONG,
//
//	OB_CMD_FEATURES		= OB_BRIEF
//				| OB_LONG
//				| OB_IGNORE
//				| OB_GRP_SCRIPT
//				| OB_FMODES
//				| OB_DEST
//				| OB_DEST2,
//
//	OB_CMD_DISTRIBUTION	= OB_IGNORE
//				| OB_NORM
//				| OB_LINKS
//				| OB_GRP_CREATE
//				| OB_BASE64
//				| OB_DB64
//				| OB_CODING
//				| OB_SOURCE,
//
//	OB_CMD_DIFF		= OB_RECURSE
//				| OB_CUT
//				| OB_ALL
//				| OB_DEST
//				| OB_ESC,
//
//	OB_CMD_CHECK		= OB_NO_CHECK
//				| OB_IGNORE
//				| OB_BRIEF
//				| OB_LONG
//				| OB_GRP_CREATE
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_SLOTS		= OB_IGNORE
//				| OB_BRIEF
//				| OB_GRP_CREATE
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_STGI		= OB_NO_HEADER
//				| OB_IGNORE,
//
//	OB_CMD_ISARENA		= OB_NO_HEADER
//				| OB_BRIEF
//				| OB_IGNORE,
//
//	OB_CMD_NORMALIZE	= OB_GRP_DEST
//				| OB_REMOVE_SRC
//				| OB_GRP_FFORMAT1
//				| OB_IGNORE
//				| OB_GRP_NORM
//				| OB_FAST
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_PATCH		= OB_GRP_DEST
//				| OB_REMOVE_SRC
//				| OB_NO_COPY
//				| OB_GRP_FFORMAT1
//				| OB_IGNORE
//				| OB_COMPRESS
//				| OB_GRP_NORM
//				| OB_FAST
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_COPY		= OB_CMD_PATCH,
//
//	OB_CMD_DUPLICATE	= OB_GAMEMODES
//				| OB_CMD_PATCH,
//
//	OB_CMD_MINIMAP		= OB_LONG
//				| OB_REMOVE_DEST
//				| OB_PRESERVE
//				| OB_IGNORE
//				| OB_COMPRESS
//				| OB_GRP_NORM
//				| OB_FAST
//				| OB_TOUCH
//				| OB_AUTO
//				| OB_SET_FLAGS
//				| OB_SET_SCALE
//				| OB_SET_ROT
//				| OB_SET_X
//				| OB_SET_Y
//				| OB_SET_Z
//				| OB_XCENTER
//				| OB_YCENTER
//				| OB_ZCENTER
//				| OB_CENTER
//				| OB_GRP_TRANSFORM,
//
//	OB_CMD_COMPRESS		= OB_GRP_DEST
//				| OB_REMOVE_SRC
//				| OB_GRP_FFORMAT1
//				| OB_IGNORE
//				| OB_COMPRESS
//				| OB_GRP_NORM
//				| OB_FAST
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_DECOMPRESS	= OB_GRP_DEST
//				| OB_REMOVE_SRC
//				| OB_U8
//				| OB_WU8
//				| OB_IGNORE
//				| OB_GRP_NORM
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_ENCODE		= OB_IGNORE_SETUP
//				| OB_GRP_ALIGN
//				| OB_GRP_ENCODE
//				| OB_MIPMAPS
//				| OB_NO_MIPMAPS
//				| OB_N_MIPMAPS
//				| OB_MAX_MIPMAPS
//				| OB_MIPMAP_SIZE
//				| OB_FAST_MIPMAPS
//				| OB_CMPR_DEFAULT
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_CREATE		= OB_GRP_DEST
//				| OB_GRP_CREATE
//				| OB_NO_COMPRESS
//				| OB_COMPRESS
//				| OB_FAST
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_UPDATE		= OB_SOURCE
//				| OB_IGNORE
//				| OB_GRP_DEST
//				| OB_ESC
//				| OB_NO_COMPRESS
//				| OB_COMPRESS
//				| OB_FAST
//				| OB_RECURSE
//				| OB_ALL
//				| OB_GRP_ENCODE
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_EXTRACT		= OB_GRP_DEST
//				| OB_GRP_EXTRACT
//				| OB_IGNORE
//				| OB_ANALYZE
//				| OB_ANALYZE_MODE
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_XDECODE		= OB_CMD_EXTRACT,
//
//	OB_CMD_XEXPORT		= OB_CMD_EXTRACT,
//
//	OB_CMD_XALL		= OB_CMD_EXTRACT,
//
//	OB_CMD_XCOMMON		= OB_GRP_DEST
//				| OB_IGNORE,
//
//	OB_CMD_BINARY		= OB_IGNORE
//				| OB_GRP_DEST,
//
//	OB_CMD_TEXT		= OB_IGNORE
//				| OB_DECODE
//				| OB_GRP_TEXTOUT
//				| OB_GRP_BMG
//				| OB_GRP_DEST,
//
//	OB_CMD_CAT		= OB_IGNORE
//				| OB_DECODE
//				| OB_GRP_TEXTOUT
//				| OB_GRP_BMG,
//
//	OB_CMD_BMG		= OB_IGNORE
//				| OB_NO_HEADER
//				| OB_BRIEF
//				| OB_GRP_BMG,
//
//	OB_CMD_KCL		= OB_IGNORE
//				| OB_NO_HEADER
//				| OB_BRIEF
//				| OB_NO_PARAM
//				| OB_NO_CHECK
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_KMP		= OB_IGNORE
//				| OB_NO_HEADER
//				| OB_BRIEF
//				| OB_EXPORT
//				| OB_NO_PARAM
//				| OB_NO_CHECK
//				| OB_GRP_TRANSFORM2,
//
//	OB_CMD_LEX		= OB_IGNORE
//				| OB_NO_HEADER
//				| OB_BRIEF
//				| OB_EXPORT,
//
//	OB_CMD_INFO		= OB_IGNORE
//				| OB_NO_HEADER,
//
//	OB_CMD_GHOST		= OB_IGNORE
//				| OB_NO_HEADER
//				| OB_GRP_SCRIPT
//				| OB_DEST
//				| OB_DEST2,
//
//	OB_CMD_YAZDUMP		= OB_GRP_DEST,
//
//	OB_CMD_VEHICLE		= OB_SOURCE
//				| OB_DEST
//				| OB_DEST2
//				| OB_OVERWRITE
//				| OB_BRIEF,
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
	CMD_INSTALL,
	CMD_ARGTEST,
	CMD_EXPAND,
	CMD_WILDCARDS,
	CMD_TEST,
	CMD_COLORS,
	CMD_ERROR,
	CMD_FILETYPE,
	CMD_UI_CHECK,
	CMD_FILEATTRIB,
	CMD_BRSUB,
	CMD_SYMBOLS,
	CMD_FUNCTIONS,
	CMD_CALCULATE,
	CMD_MATRIX,
	CMD_FLOAT,
	CMD_VR_CALC,
	CMD_VR_RACE,
	CMD_AUTOADD,
	CMD_TRACKS,
	CMD_SCANCACHE,
	CMD_EXPORT,
	CMD_SIZEOF,
	CMD_CODE,
	CMD_RECODE,
	CMD_SUBFILE,
	CMD_TESTNORM,

	CMD_LIST,
	CMD_LIST_L,
	CMD_LIST_LL,
	CMD_LIST_LLL,
	CMD_LIST_A,
	CMD_LIST_LA,
	CMD_NAME_REF,

	CMD_ILIST,
	CMD_ILIST_L,
	CMD_ILIST_LL,
	CMD_ILIST_A,
	CMD_ILIST_LA,

	CMD_MEMORY,
	CMD_MEMORY_A,
	CMD_DUMP,

	CMD_SHA1,
	CMD_ANALYZE,
	CMD_SPLIT,
	CMD_IS_TEXTURE,
	CMD_FEATURES,
	CMD_DISTRIBUTION,

	CMD_DIFF,

	CMD_CHECK,
	CMD_SLOTS,
	CMD_STGI,
	CMD_ISARENA,
	CMD_NORMALIZE,
	CMD_PATCH,
	CMD_COPY,
	CMD_DUPLICATE,
	CMD_MINIMAP,
	CMD_COMPRESS,
	CMD_DECOMPRESS,
	CMD_ENCODE,
	CMD_CREATE,
	CMD_UPDATE,
	CMD_EXTRACT,
	CMD_XDECODE,
	CMD_XEXPORT,
	CMD_XALL,
	CMD_XCOMMON,

	CMD_BINARY,
	CMD_TEXT,
	CMD_CAT,
	CMD_BMG,
	CMD_KCL,
	CMD_KMP,
	CMD_LEX,
	CMD_INFO,
	CMD_GHOST,
	CMD_YAZDUMP,

	CMD_VEHICLE,

	CMD__N // == 83

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
	GO_COMPRESS		= 'C',
	GO_DEST2		= 'D',
	GO_ESC			= 'E',
	GO_NO_HEADER		= 'H',
	GO_LOGGING		= 'L',
	GO_MAX_FILE_SIZE	= 'M',
	GO_NO_CHECK		= 'N',
	GO_NO_PARAM		= 'P',
	GO_RECURSE		= 'R',
	GO_SORT			= 'S',
	GO_TRACKS		= 'T',
	GO_VERSION		= 'V',
	GO_WARN			= 'W',
	GO_EXPORT		= 'X',
	GO_EXT_ERRORS		= 'Y',

	GO_ALL			= 'a',
	GO_CONST		= 'c',
	GO_DEST			= 'd',
	GO_EXT			= 'e',
	GO_HELP			= 'h',
	GO_IGNORE		= 'i',
	GO_LONG			= 'l',
	GO_NORM			= 'n',
	GO_OVERWRITE		= 'o',
	GO_PRESERVE		= 'p',
	GO_QUIET		= 'q',
	GO_REMOVE_DEST		= 'r',
	GO_SOURCE		= 's',
	GO_TEST			= 't',
	GO_UPDATE		= 'u',
	GO_VERBOSE		= 'v',
	GO_TRANSFORM		= 'x',

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
	GO_LOAD_PREFIX,
	GO_LOAD_CATEGORY,
	GO_PLUS,
	GO_SPLIT,
	GO_PRINTF,
	GO_CHDIR,
	GO_TOUCH,
	GO_AUTO,
	GO_SET_FLAGS,
	GO_SET_SCALE,
	GO_SET_ROT,
	GO_SET_X,
	GO_SET_Y,
	GO_SET_Z,
	GO_XCENTER,
	GO_YCENTER,
	GO_ZCENTER,
	GO_CENTER,
	GO_SCALE,
	GO_SHIFT,
	GO_XSS,
	GO_YSS,
	GO_ZSS,
	GO_ROT,
	GO_XROT,
	GO_YROT,
	GO_ZROT,
	GO_YPOS,
	GO_TRANSLATE,
	GO_NULL,
	GO_NEXT,
	GO_ASCALE,
	GO_AROT,
	GO_TFORM_SCRIPT,
	GO_MINIMAP,
	GO_RM_GOBJ,
	GO_BATTLE,
	GO_EXPORT_FLAGS,
	GO_ROUTE_OPTIONS,
	GO_WIM0,
	GO_SLOT,
	GO_LOAD_KCL,
	GO_KCL,
	GO_KCL_FLAG,
	GO_KCL_SCRIPT,
	GO_TRI_AREA,
	GO_TRI_HEIGHT,
	GO_FLAG_FILE,
	GO_XTRIDATA,
	GO_KMP,
	GO_SPEED_MOD,
	GO_KTPT2,
	GO_TFORM_KMP,
	GO_REPAIR_XPF,
	GO_GAMEMODES,
	GO_MDL,
	GO_PAT,
	GO_PATCH_FILE,
	GO_KMG_LIMIT,
	GO_KMG_COPY,
	GO_LT_CLEAR,
	GO_LT_ONLINE,
	GO_LT_N_PLAYERS,
	GO_LT_COND_BIT,
	GO_LT_GAME_MODE,
	GO_LT_ENGINE,
	GO_LT_RANDOM,
	GO_LEX_PURGE,
	GO_LEX_FEATURES,
	GO_LEX_RM_FEAT,
	GO_LOAD_BMG,
	GO_PATCH_BMG,
	GO_MACRO_BMG,
	GO_FILTER_BMG,
	GO_LE_MENU,
	GO_TITLE_SCREEN,
	GO_CUP_ICONS,
	GO_NO_COPY,
	GO_CACHE,
	GO_CNAME,
	GO_LOG_CACHE,
	GO_PARALLEL,
	GO_ID,
	GO_BASE64,
	GO_DB64,
	GO_CODING,
	GO_VERIFY,
	GO_ROUND,
	GO_IN_ORDER,
	GO_PIPE,
	GO_DELTA,
	GO_DIFF,
	GO_EPSILON,
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
	GO_AUTOADD_PATH,
	GO_STRIP,
	GO_UTF_8,
	GO_NO_UTF_8,
	GO_FORCE,
	GO_REPAIR_MAGICS,
	GO_TINY,
	GO_YAZ0,
	GO_YAZ1,
	GO_XYZ,
	GO_BZ,
	GO_SH,
	GO_BASH,
	GO_JSON,
	GO_PHP,
	GO_MAKEDOC,
	GO_VAR,
	GO_ARRAY,
	GO_AVAR,
	GO_CASE,
	GO_FMODES,
	GO_INSTALL,
	GO_ANALYZE,
	GO_ANALYZE_MODE,
	GO_OLD,
	GO_STD,
	GO_NEW,
	GO_EXTRACT,
	GO_REFERENCE,
	GO_NUMBER,
	GO_REMOVE_SRC,
	GO_IGNORE_SETUP,
	GO_PURGE,
	GO_ALIGN_U8,
	GO_ALIGN_PACK,
	GO_ALIGN_BRRES,
	GO_ALIGN_BREFF,
	GO_ALIGN_BREFT,
	GO_ALIGN,
	GO_ENCODE_ALL,
	GO_ENCODE_IMG,
	GO_NO_ENCODE,
	GO_NO_RECURSE,
	GO_AUTO_ADD,
	GO_NO_ECHO,
	GO_PT_DIR,
	GO_RM_AIPARAM,
	GO_U8,
	GO_SZS,
	GO_WU8,
	GO_XWU8,
	GO_WBZ,
	GO_PACK,
	GO_BRRES,
	GO_BREFF,
	GO_BREFT,
	GO_NO_COMPRESS,
	GO_FAST,
	GO_LINKS,
	GO_BASEDIR,
	GO_DECODE,
	GO_MIPMAPS,
	GO_NO_MIPMAPS,
	GO_N_MIPMAPS,
	GO_MAX_MIPMAPS,
	GO_MIPMAP_SIZE,
	GO_FAST_MIPMAPS,
	GO_CMPR_DEFAULT,
	GO_CUT,
	GO_RAW,
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
//UIOPT_INDEX_SIZE := 0x140 = 320
//extern const InfoCommand_t CommandInfo[CMD__N+1];
extern const InfoUI_t InfoUI_wszst;

//
///////////////////////////////////////////////////////////////////////////////
///////////////                       END                       ///////////////
///////////////////////////////////////////////////////////////////////////////

#endif // SZS_UI_WSZST_H

