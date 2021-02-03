
/***************************************************************************
 *                                                                         *
 *                     _____     ____                                      *
 *                    |  __ \   / __ \   _     _ _____                     *
 *                    | |  \ \ / /  \_\ | |   | |  _  \                    *
 *                    | |   \ \| |      | |   | | |_| |                    *
 *                    | |   | || |      | |   | |  ___/                    *
 *                    | |   / /| |   __ | |   | |  _  \                    *
 *                    | |__/ / \ \__/ / | |___| | |_| |                    *
 *                    |_____/   \____/  |_____|_|_____/                    *
 *                                                                         *
 *                       Wiimms source code library                        *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 *        Copyright (c) 2012-2021 by Dirk Clemens <wiimm@wiimm.de>         *
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
 ***************************************************************************/

#define _GNU_SOURCE 1

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <signal.h>
#include <sys/ioctl.h>
//#include <ncurses/curses.h>
//#include <term.h>

#include "dclib-color.h"
#include "dclib-basics.h"
#include "dclib-utf8.h"

#ifdef DCLIB_TERMINAL
 #include "dclib-terminal.h"
#endif

//
///////////////////////////////////////////////////////////////////////////////
///////////////			    color modes			///////////////
///////////////////////////////////////////////////////////////////////////////

const KeywordTab_t color_mode_keywords[] =
{
    { COLMD_OFF,	"OFF",		"NONE",		0 },
    { COLMD_OFF,	"NO-COLORS",	"NOCOLORS",	0 },
    { COLMD_OFF,	"0-COLORS",	"0COLORS",	0 },
    { COLMD_AUTO,	"AUTO",		0,		0 },
    { COLMD_ON,		"ON",		0,		0 },
    { COLMD_8_COLORS,	"8-COLORS",	"8COLORS",	0 },
    { COLMD_256_COLORS,	"256-COLORS",	"256COLORS",	0 },
    {0,0,0,0}
};

ColorMode_t opt_colorize = COLMD_AUTO;

///////////////////////////////////////////////////////////////////////////////

int ScanOptColorize ( ColorMode_t *opt, ccp arg, ccp err_prefix )
{
    if (!opt)
	opt = &opt_colorize;

    if (!arg)
    {
	if ( *opt < COLMD_ON )
	    *opt = COLMD_ON;
	return 0;
    }

    int abbrev;
    const KeywordTab_t *key = ScanKeyword(&abbrev,arg,color_mode_keywords);
    if (!key)
	 return PrintKeywordError( color_mode_keywords, arg, abbrev,
			err_prefix ? err_prefix : "Option --color: ",
			"keyword");

    *opt = key->id;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////

ccp GetColorModeName ( ColorMode_t col_mode, ccp res_not_found )
{
    return GetKewordNameById(color_mode_keywords,col_mode,res_not_found);
}

///////////////////////////////////////////////////////////////////////////////

ColorMode_t NormalizeColorMode ( ColorMode_t col_mode, int n_colors )
{
    // returns COLMD_OFF or COLMD_8_COLORS or COLMD_256_COLORS

    switch (col_mode)
    {
	case COLMD_OFF:
	case COLMD_8_COLORS:
	case COLMD_256_COLORS:
	    return col_mode;

	case COLMD_ON:
	    return n_colors < 256 ? COLMD_8_COLORS : COLMD_256_COLORS;

	default:
	//case COLMD_AUTO:
	    return n_colors < 8 ? COLMD_OFF
			: n_colors < 256 ? COLMD_8_COLORS : COLMD_256_COLORS;
    }
}

///////////////////////////////////////////////////////////////////////////////

ColorMode_t NormalizeColorModeByTermName
(
    ColorMode_t		col_mode,	// predefind mode
    ccp			term_name	// find "256color" in terminal name.
					// if NULL: use getenv("TERM")
					// assume 8 or 256 colors!
)
{
    if (!term_name)
	term_name = getenv("TERM");
    const int n_colors = term_name && strstr(term_name,"256color") ? 256 : 8;
    return NormalizeColorMode(col_mode,n_colors);
}

///////////////////////////////////////////////////////////////////////////////

ColorMode_t GetNextColorMode ( ColorMode_t col_mode )
{
    switch(col_mode)
    {
	case COLMD_8_COLORS:	return COLMD_256_COLORS;
	case COLMD_256_COLORS:	return COLMD_OFF;
	default:		return COLMD_8_COLORS;
    }
}

///////////////////////////////////////////////////////////////////////////////

ColorMode_t GetPrevColorMode ( ColorMode_t col_mode )
{
    switch(col_mode)
    {
	case COLMD_8_COLORS:	return COLMD_OFF;
	case COLMD_256_COLORS:	return COLMD_8_COLORS;
	default:		return COLMD_256_COLORS;
    }
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////		print lines with autobreak		///////////////
///////////////////////////////////////////////////////////////////////////////

void PutLines
(
    FILE	* f,		// valid output stream
    int		indent,		// indent of output
    int		fw,		// field width of output
    int		first_line,	// length without prefix of already printed first line
    ccp		prefix,		// NULL or prefix for each line
    ccp		text,		// text to print
    ccp		eol		// End-Of-Line text. If NULL -> LF
)
{
    DASSERT(f);
    DASSERT( indent >= 0 );

    if (!prefix)
	prefix = "";
    if (!eol)
	eol = "\n";
    TRACE("PutLines(,%d,%d,%d,%.10s,%.20s)\n",indent,fw,first_line,prefix,text);
    fw -= strlen(prefix);
    if ( fw < 10 )
	fw = 10;

    ccp prefix1 = "";
    int indent1, fw1;
    if ( indent > first_line )
    {
	indent1 = indent - first_line;
	fw1 = fw - indent;
    }
    else
    {
	indent1 = 0;
	fw1 = fw - first_line;
    }

    fw -= indent;
    if ( fw < 20 )
	fw = 20;

    if ( fw1 < 20 )
    {
	fputs(eol,f);
	indent1 = indent;
	fw1 = fw;
	prefix1 = prefix;
    }

    while ( *text )
    {
	// skip blank and control
	if ( *text == '\n' )
	{
	    // don't skip spaces behind a LF ==> needed for tables
	    while ( *text > 0 && *text < ' ' )
		text++;
	}
	else
	{
	    // but ignore spaces on an automatic line break
	    while ( *text > 0 && *text <= ' ' )
		text++;
	}

	// setup
	ccp start = text, last_blank = text;
	ccp max = text + fw1;

	while ( text < max && *text && *text != '\n' )
	{
	    if ( *text > 0 && *text <= ' ' )
		last_blank = text;
	    text++;
	}

	// set back to last blank
	if ( last_blank > start && (u8)*text > ' ' )
	    text = last_blank;

	// print out
	if ( *text || text > start )
	    fprintf(f,"%s%*s%.*s%s",
		prefix1, indent1, "",
		(int)(text-start), start, eol );

	// use standard values for next lines
	indent1 = indent;
	fw1 = fw;
	prefix1 = prefix;
    }
}

///////////////////////////////////////////////////////////////////////////////

void PrintArgLines
(
    FILE	* f,		// valid output stream
    int		indent,		// indent of output
    int		fw,		// field width of output
    int		first_line,	// length without prefix of already printed first line
    ccp		prefix,		// NULL or prefix for each line
    ccp		format,		// format string for vsnprintf()
    va_list	arg		// parameters for 'format'
)
{
    DASSERT(f);
    DASSERT(format);

    char buf[10000];

    va_list arg2;
    va_copy(arg2,arg);
    int stat = vsnprintf(buf,sizeof(buf),format,arg2);
    va_end(arg2);

    if ( stat < sizeof(buf) )
    {
	PutLines(f,indent,fw,first_line,prefix,buf,0);
	return;
    }


    //--- buffer too small, use dynamic memory

    noPRINT("PrintArgGrowBuffer() -> MALLOC(%u)\n",stat+1);

    char *temp = MALLOC(stat+1);
    vsnprintf(temp,stat+1,format,arg);
    va_end(arg);
    PutLines(f,indent,fw,first_line,prefix,temp,0);
    FREE(temp);
}

///////////////////////////////////////////////////////////////////////////////

void PrintLines
(
    FILE	* f,		// valid output stream
    int		indent,		// indent of output
    int		fw,		// field width of output
    int		first_line,	// length without prefix of already printed first line
    ccp		prefix,		// NULL or prefix for each line
    ccp		format,		// format string for vsnprintf()
    ...				// arguments for 'vsnprintf(format,...)'
)
{
    DASSERT(f);
    DASSERT(format);

    va_list arg;
    va_start(arg,format);
    PrintArgLines(f,indent,fw,first_line,prefix,format,arg);
    va_end(arg);
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////		print colored lines with autobreak	///////////////
///////////////////////////////////////////////////////////////////////////////

uint PutColoredLines
(
    // returns the number of written lines

    FILE		* f,		// valid output stream
    const ColorSet_t	*colset,	// NULL or color set
    int			indent,		// indent of output
    int			fw,		// field width; indent+prefix+eol don't count
    ccp			prefix,		// NULL or prefix for each line
    ccp			eol,		// End-Of-Line text. If NULL -> LF
    ccp			text		// text to print
)
{
    DASSERT(f);
    DASSERT(text);


    //--- normalize params

    indent = NormalizeIndent(indent);

    if ( fw < 1 || fw > 1000 )
	fw = 1000;
    else if ( fw < 20 )
	fw = 20;

    if (!eol)
	eol = "\n";

    if (!prefix)
	prefix = "";
    indent += strlen(prefix);

    if (!colset)
	colset = GetFileColorSet(f);


    //--- setup tabs

    u8 is_tab[200];
    memset(is_tab,0,sizeof(is_tab));


    //--- prepare output buffer

    char buf[10000];
    char *buf_end = buf + 3*sizeof(buf)/4;
    int  cont_indent = -1;
    uint n_lines = 0, n_space = 0;
    uint column = 0;
    //ccp col_begin = "";

    enum { GB_NONE, GB_SIGN, GB_COMMA, GB_SPACE } gb_mode = GB_NONE;

    struct gb_save_t
    {
	ccp	text;		// text position before code assignment
	char	*dest;		// destination
	ccp	col_active;	// NULL or active color by last "{name}"
	ccp	col_embed;	// NULL or active color "{name|text}"
    };
    struct gb_save_t cur = { text, buf, 0, 0 };
    struct gb_save_t save = cur; // only valid if gb_mode != GB_NONE


    //--- main loop

    for(;;)
    {
     #ifdef TEST
	if ( n_lines > 1000 )
	    return n_lines;
     #endif

	cur.text = text;
	u32 code = ScanUTF8AnsiChar(&text);
	switch(code)
	{
	 case 0:
	    if (!column)
		return n_lines;
	    // fall through

	 case '\r':
	    if ( *text == '\n' )
		code = *text++;
	    // fall through

	 case '\n':
	    cur.text = text;
	  new_line:
	    *cur.dest = 0;
	    fprintf(f,"%-*s%s%s%s", indent,prefix, buf,
			cur.col_active || cur.col_embed ? colset->reset : "", eol );
	    cur.dest = buf;
	    text = cur.text;
	    n_lines++;
	    column = 0;
	    n_space = 0;
	    gb_mode = GB_NONE;

	    if ( code == '\n' )
		cont_indent = -1;
	    else if (!code)
		return n_lines;
	    else if ( cont_indent > 0 )
		n_space = cont_indent;

	    if ( cur.col_embed )
		cur.dest = StringCopyE(cur.dest,buf+sizeof(buf),cur.col_embed);
	    else if ( cur.col_active )
		cur.dest = StringCopyE(cur.dest,buf+sizeof(buf),cur.col_active);
	    break;

	 case '{':
	    if ( *text == '{' )
	    {
		text++;
		goto is_char;
	    }
	    else if ( *text == '}' )
	    {
		cur.dest = StringCopyE(cur.dest,buf+sizeof(buf),colset->reset);
		cur.col_active = cur.col_embed = 0;
		text++;
	    }
	    else
	    {
		ccp name = text;
		while ( *text && *text != '|' && *text != '}' )
		    text++;
		if (!*text)
		    break;

		ccp col = "";
		char namebuf[20];
		const uint nlen = text - name;
		if ( nlen < sizeof(namebuf) )
		{
		    memcpy(namebuf,name,nlen);
		    namebuf[nlen] = 0;
		    col = GetColorByName(colset,namebuf);
		}

		if (*col)
		{
		    cur.dest = StringCopyE(cur.dest,buf+sizeof(buf),col);
		    if ( *text == '}' )
			cur.col_active = col;
		    else
			cur.col_embed = col;
		}
		else if ( *text == '|' )
		    cur.col_embed = ""; // to detect the closing '}'
		text++;
	    }
	    break;

	 case '}':
	    if (!cur.col_embed)
		goto is_char;
	    cur.col_embed = 0;
	    cur.dest = StringCopyE(cur.dest,buf+sizeof(buf),
				cur.col_active ? cur.col_active : colset->reset );
	    break;

	 case '\t':
	 case ' ':
	    if ( !n_space++ && column )
	    {
		gb_mode = column < fw/2 ? GB_COMMA : GB_SPACE;
		save = cur;
	    }
	    if ( code == '\t' )
	    {
		uint pos;
		for ( pos = column + n_space; pos < sizeof(is_tab); pos++ )
		    if (is_tab[pos])
		    {
			n_space = pos - column;
			break;
		    }
	    }
	    break;

	 case '|':
	    if ( *text == '|' )
	    {
		text++;
		goto is_char;
	    }
	    else if ( *text == '+' )
	    {
		text++;
		uint pos = column + n_space;
		if ( pos < sizeof(is_tab) )
		    is_tab[pos] = 1;
	    }
	    else if ( *text == '-' )
	    {
		uint pos = column + n_space;
		if ( pos < sizeof(is_tab) )
		    is_tab[pos] = 0;
	    }
	    else if ( *text == '[' )
	    {
		text++;
		memset(is_tab,0,sizeof(is_tab));
		for(;;)
		{
		    while ( *text == ',' )
			text++;

		    char *end;
		    uint num = str2ul(text,&end,10);
		    if ( text == end )
			break;
		    text = end;
		    if ( num < sizeof(is_tab) )
			is_tab[num] = 1;

		    if ( *text == '*' )
		    {
			text++;
			uint delta = str2ul(text,&end,10);
			if ( text == end )
			    break;
			if ( delta > 0 )
			    for ( ; num < sizeof(is_tab); num += delta )
				is_tab[num] = 1;
		    }
		}
		if ( *text == ']' )
		    text++;
		//HexDump16(stderr,0,0,is_tab,sizeof(is_tab));
	    }
	    else
	    {
		if ( *text == '>' )
		    text++;
		cont_indent = column + n_space;
		if ( cont_indent > fw/2 )
		    cont_indent = fw/2;
	    }
	    break;

	 case '+':
	 case '-':
	 case '=':
	 case '/':
	    if ( gb_mode <= GB_SIGN )
	    {
		gb_mode = GB_SIGN;
		save = cur;
	    }
	    // fall through

	 default:
	 is_char:
	    column += n_space;
	    if ( column >= fw )
	    {
		// auto break line
		if ( gb_mode > GB_NONE )
		    cur = save;
		while ( *cur.text == ' ' )
		    cur.text++;
		goto new_line;
	    }

	    while ( n_space > 0 )
		*cur.dest++ = ' ', n_space--;
	    cur.dest = PrintUTF8Char(cur.dest,code);
	    if ( cur.dest > buf_end )
		goto new_line; // should never happen!
	    column++;

	    if ( gb_mode <= GB_COMMA && ( code == ',' || code == ';' ))
	    {
		gb_mode = GB_COMMA;
		save = cur;
		save.text++;
	    }
	    break;
	}
    }
}

///////////////////////////////////////////////////////////////////////////////

uint PrintArgColoredLines
(
    // returns the number of written lines

    FILE		* f,		// valid output stream
    const ColorSet_t	*colset,	// NULL or color set
    int			indent,		// indent of output
    int			fw,		// field width; indent+prefix+eol don't count
    ccp			prefix,		// NULL or prefix for each line
    ccp			eol,		// End-Of-Line text. If NULL -> LF
    ccp			format,		// format string for vsnprintf()
    va_list		arg		// parameters for 'format'
)
{
    DASSERT(f);
    DASSERT(format);

    char buf[10000];

    va_list arg2;
    va_copy(arg2,arg);
    int stat = vsnprintf(buf,sizeof(buf),format,arg2);
    va_end(arg2);

    if ( stat < sizeof(buf) )
	return PutColoredLines(f,colset,indent,fw,prefix,eol,buf);


    //--- buffer too small, use dynamic memory

    noPRINT("PrintArgGrowBuffer() -> MALLOC(%u)\n",stat+1);

    char *temp = MALLOC(stat+1);
    stat = vsnprintf(temp,stat+1,format,arg);
    const uint res = PutColoredLines(f,colset,indent,fw,prefix,eol,temp);
    FREE(temp);
    return res;
}

///////////////////////////////////////////////////////////////////////////////

uint PrintColoredLines
(
    // returns the number of written lines

    FILE		* f,		// valid output stream
    const ColorSet_t	*colset,	// NULL or color set
    int			indent,		// indent of output
    int			fw,		// field width; indent+prefix+eol don't count
    ccp			prefix,		// NULL or prefix for each line
    ccp			eol,		// End-Of-Line text. If NULL -> LF
    ccp			format,		// format string for vsnprintf()
    ...					// arguments for 'vsnprintf(format,...)'
)
{
    DASSERT(f);
    DASSERT(format);

    va_list arg;
    va_start(arg,format);
    const uint res
	= PrintArgColoredLines(f,colset,indent,fw,prefix,eol,format,arg);
    va_end(arg);
    return res;
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////		global commands: TESTCOLORS		///////////////
///////////////////////////////////////////////////////////////////////////////
// [[color_info_t]]

typedef struct color_info_t
{
    bool	valid;		// >0: data below is valid

    u8		m_index;	// index of 0..255 for "\e[*m"

    s8		m_red;		// -1:invalid, 0..5:  red value of 'm_index'
    s8		m_green;	// -1:invalid, 0..5:  green value of 'm_index'
    s8		m_blue;		// -1:invalid, 0..5:  blue value of 'm_index'
    s8		m_gray;		// -1:invalid, 0..23: gray value of 'm_index'

    u32		ref_color;	// reference colors, based on 'm_index';
    u32		src_color;	// scanned color
}
color_info_t;

///////////////////////////////////////////////////////////////////////////////

static bool AssignColorInfo ( color_info_t *ci, u32 rgb )
{
    DASSERT(ci);
    memset(ci,0,sizeof(*ci));

    ci->src_color = rgb & 0xffffff;
    ci->m_index   = ConvertColorRGBToM256(ci->src_color);
    ci->ref_color = ConvertColorM256ToRGB(ci->m_index);

    const uint r = ci->ref_color >> 16 & 0xff;
    const uint g = ci->ref_color >>  8 & 0xff;
    const uint b = ci->ref_color       & 0xff;

    ci->m_red   = SingleColorToM6(r);
    ci->m_green = SingleColorToM6(g);
    ci->m_blue  = SingleColorToM6(b);

    ci->m_gray  = ( r + g + b + 21 ) / 30;
    if ( ci->m_gray > 23 )
	ci->m_gray = 23;
    else if ( ci->m_gray > 0 )
	ci->m_gray--;

    return ci->valid = 1;
}

///////////////////////////////////////////////////////////////////////////////

static bool ScanColorInfo ( color_info_t *ci, ccp arg )
{
    DASSERT(ci);
    memset(ci,0,sizeof(*ci));
    if ( arg && *arg )
    {
	arg = SkipControls(arg);

	ulong num, r, g, b;
	if ( *arg >= 'g' && *arg <= 'z' )
	{
	    const char mode = *arg;
	    arg = SkipControls(arg+1);

	    num = str2ul(arg,0,10);
	    switch (mode)
	    {
		case 'm':
		    return AssignColorInfo(ci,ConvertColorM256ToRGB(num));

		case 'g':
		    return AssignColorInfo(ci,ConvertColorM256ToRGB(232 + num % 24));

		case 'c':
		    r = num / 100 % 10;
		    g = num / 10  % 10;
		    b = num       % 10;
		    goto rgb5;
	    }
	}
	else
	{
	    char *end;
	    num = str2ul(arg,&end,16);

	    ci->valid = true;
	    if ( end - arg <= 3 )
	    {
		r = num >> 8 & 15;
		g = num >> 4 & 15;
		b = num      & 15;

		rgb5:
		if ( r > 5 ) r = 5;
		if ( g > 5 ) g = 5;
		if ( b > 5 ) b = 5;
		return AssignColorInfo(ci,ConvertColorM256ToRGB(16 + 36*r + 6*g + b));
	    }
	    return AssignColorInfo(ci,num);
	}
    }

    return ci->valid;
}

///////////////////////////////////////////////////////////////////////////////

static void PrintColorInfo ( FILE *f, color_info_t *ci )
{
    DASSERT(f);
    DASSERT(ci);

    if (ci->valid)
	fprintf(f," %06x -> %06x : %3u : %u,%u,%u : %2u"
		" \e[48;5;16;38;5;%um test \e[0m"
		" \e[48;5;244;38;5;%um test \e[0m"
		" \e[48;5;231;38;5;%um test \e[0m "
		" \e[38;5;16;48;5;%um test \e[0m"
		" \e[38;5;244;48;5;%um test \e[0m"
		" \e[38;5;231;48;5;%um test \e[0m\n",
		ci->src_color, ci->ref_color,
		ci->m_index, ci->m_red, ci->m_green, ci->m_blue, ci->m_gray,
		ci->m_index, ci->m_index, ci->m_index,
		ci->m_index, ci->m_index, ci->m_index );
    else
	fputs(" --\n",f);
}

///////////////////////////////////////////////////////////////////////////////

enumError Command_TESTCOLORS ( int argc, char ** argv )
{
 #if HAVE_PRINT
    GetColorByName(colout,"blue");
 #endif

    printf("TEST COLORS: %u arguments:\n",argc);

    bool sep = true;
    int idx;
    for ( idx = 0; idx < argc; idx++ )
    {
	ccp minus = strchr(argv[idx],'-');
	if ( minus || sep )
	{
	    putchar('\n');
	    sep = false;
	    if ( strlen(argv[idx]) == 1 )
		continue;
	}

	color_info_t ci1;
	ScanColorInfo(&ci1,argv[idx]);
	PrintColorInfo(stdout,&ci1);

	if (!minus)
	    continue;

	color_info_t ci2;
	ScanColorInfo(&ci2,minus+1);
	if ( ci2.ref_color == ci1.ref_color )
	    continue;

	int r1 = ci1.ref_color >> 16 & 0xff;
	int g1 = ci1.ref_color >>  8 & 0xff;
	int b1 = ci1.ref_color       & 0xff;
	int r2 = ci2.ref_color >> 16 & 0xff;
	int g2 = ci2.ref_color >>  8 & 0xff;
	int b2 = ci2.ref_color       & 0xff;

	int n_steps = abs( r2 - r1 );
	int diff = abs( g2 - g1 );
	if ( n_steps < diff )
	    n_steps = diff;
	diff = abs( b2 - b1 );
	if ( n_steps < diff )
	    n_steps = diff;

	u8 prev_m = ci1.m_index;
	u32 prev_rgb = ci1.ref_color;
	int i;
	for ( i = 1; i <= n_steps; i++ )
	{
	    uint r = ( r2 - r1 ) * i / n_steps + r1;
	    uint g = ( g2 - g1 ) * i / n_steps + g1;
	    uint b = ( b2 - b1 ) * i / n_steps + b1;
	    u8 new_m = ConvertColorRGB3ToM256(r,g,b);
	    if ( prev_m != new_m )
	    {
		prev_m = new_m;
		color_info_t ci3;
		AssignColorInfo(&ci3,r<<16|g<<8|b);
		if ( prev_rgb != ci3.ref_color )
		{
		    prev_rgb = ci3.src_color = ci3.ref_color;
		    PrintColorInfo(stdout,&ci3);
		}
	    }
	}
	sep = true;
    }
    putchar('\n');
    return ERR_OK;
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////			color helpers			///////////////
///////////////////////////////////////////////////////////////////////////////
//
// https://en.wikipedia.org/wiki/ANSI_escape_code
// https://jonasjacek.github.io/colors/
//
// 0..15:  000000 800000 008000 808000  000080 800080 008080 c0c0c0
//	   808080 ff0000 00ff00 ffff00  0000ff ff00ff 00ffff ffffff
//		=> real colors varies on implementation
//
// 6x6x6: 0 95 135 175 215 255 == 00 5f 87 af d7 ff
//
// gray:  8 18 28 ... 238 == 08 12 1c 26 30 3a ... e4 ee f8
//
///////////////////////////////////////////////////////////////////////////////
//
//  mkw-ana testcol 000000-ffffff
//  mkw-ana testcol 500-550 550-050 050-055 055-005 005-505 505-500
//
///////////////////////////////////////////////////////////////////////////////

u32 ColorTab_M0_M15[16] =
{
	0x000000, 0x800000, 0x008000, 0x808000,
	0x000080, 0x800080, 0x008080, 0xc0c0c0,
	0x808080, 0xff0000, 0x00ff00, 0xffff00,
	0x0000ff, 0xff00ff, 0x00ffff, 0xffffff,
};

///////////////////////////////////////////////////////////////////////////////

u8 ConvertColorRGB3ToM256 ( u8 r, u8 g, u8 b )
{
    // 0..5
    const int r6 = SingleColorToM6(r);
    const int g6 = SingleColorToM6(g);
    const int b6 = SingleColorToM6(b);

    u8	 m256	= 36*r6 + 6*g6 + b6 + 16;
    uint delta	= abs ( ( r6 ? 55 + 40 * r6 : 0 ) - r  )
		+ abs ( ( g6 ? 55 + 40 * g6 : 0 ) - g  )
		+ abs ( ( b6 ? 55 + 40 * b6 : 0 ) - b  );

    //printf("%02x>%u %02x>%u %02x>%u : m=%u delta=%d\n",r,r6,g,g6,b,b6,m256,delta);

    int m, gray, prev = 0x1000000;
    for ( m = 232, gray = 8; m < 256; m++, gray += 10 )
    {
	const uint d = abs( gray - r ) + abs( gray - g ) + abs( gray - b );
	if ( d > prev )
	    break;
	if ( d <= delta )
	{
	    delta = d;
	    m256  = m;
	}
	prev = d;
    }

    return m256;
}

///////////////////////////////////////////////////////////////////////////////

u8 ConvertColorRGBToM256 ( u32 rgb )
{
    return ConvertColorRGB3ToM256( rgb >> 16, rgb >> 8, rgb );
}

///////////////////////////////////////////////////////////////////////////////

u32 ConvertColorM256ToRGB ( u8 m256 )
{
    if ( m256 < 16 )
	return ColorTab_M0_M15[m256];

    if ( m256 < 232 )
    {
	m256 -= 16;
	const uint r =  m256 / 36;
	const uint g =  m256 / 6 % 6;
	const uint b =  m256 % 6;

	u32 col = 0;
	if (r) col |= 0x370000 + 0x280000 * r;
	if (g) col |= 0x003700 + 0x002800 * g;
	if (b) col |= 0x000037 + 0x000028 * b;
	return col;
    }

    m256 -= 232;
    return 0x080808 + m256 * 0x0a0a0a;
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////			  terminal			///////////////
///////////////////////////////////////////////////////////////////////////////

// Sequence counter for output to stdout (and stderr).
// Functions shall increment it on output, so that other functions
// know about a destroyed screen.

uint stdout_seq_count = 0;

///////////////////////////////////////////////////////////////////////////////

uint opt_width = 0;
uint opt_max_width = 0;
uint opt_height = 0;
uint opt_max_height = 0;

//-----------------------------------------------------------------------------

int ScanOptWidth ( ccp arg )
{
    return ERR_OK != ScanSizeOptU32(
			&opt_width,		// u32 * num
			arg,			// ccp source
			1,			// default_factor1
			0,			// int force_base
			"width",		// ccp opt_name
			40,			// u64 min
			10000,			// u64 max
			1,			// u32 multiple
			0,			// u32 pow2
			true			// bool print_err
			);
}

int ScanOptMaxWidth ( ccp arg )
{
    return ERR_OK != ScanSizeOptU32(
			&opt_max_width,		// u32 * num
			arg,			// ccp source
			1,			// default_factor1
			0,			// int force_base
			"max-width",		// ccp opt_name
			40,			// u64 min
			10000,			// u64 max
			1,			// u32 multiple
			0,			// u32 pow2
			true			// bool print_err
			);
}

//-----------------------------------------------------------------------------

int ScanOptHeight ( ccp arg )
{
    return ERR_OK != ScanSizeOptU32(
			&opt_height,		// u32 * num
			arg,			// ccp source
			1,			// default_factor1
			0,			// int force_base
			"height",		// ccp opt_name
			40,			// u64 min
			10000,			// u64 max
			1,			// u32 multiple
			0,			// u32 pow2
			true			// bool print_err
			);
}

int ScanOptMaxHeight ( ccp arg )
{
    return ERR_OK != ScanSizeOptU32(
			&opt_max_height,	// u32 * num
			arg,			// ccp source
			1,			// default_factor1
			0,			// int force_base
			"max-height",		// ccp opt_name
			40,			// u64 min
			10000,			// u64 max
			1,			// u32 multiple
			0,			// u32 pow2
			true			// bool print_err
			);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

term_size_t GetTermSize ( int default_width, int default_height )
{
    PRINT0("GetTermWidth(%d,%d) opt=%d,%d, max=%d,%d\n",
	default_width, default_height,
	opt_width, opt_height, opt_max_width, opt_max_height );

    term_size_t ts;
    if ( opt_width > 0 && opt_height > 0 )
    {
	ts.width = opt_width;
	ts.height = opt_height;
    }
    else
    {
	ts = GetTermSizeFD(STDOUT_FILENO,default_width,default_height);

	if ( opt_width > 0 )
	    ts.width = opt_width;
	else if ( opt_max_width > 0 && ts.width > opt_max_width )
	    ts.width = opt_max_width;

	if ( opt_height > 0 )
	    ts.height = opt_height;
	else if ( opt_max_height > 0 && ts.height > opt_max_height )
	    ts.height = opt_max_height;
    }

    return ts;
}

///////////////////////////////////////////////////////////////////////////////

term_size_t GetTermSizeFD ( int fd, int default_width, int default_height )
{
    PRINT("GetTermSizeFD(%d,%d,%d)\n",fd,default_width,default_height);

 #ifdef TIOCGSIZE
    TRACE(" - have TIOCGSIZE\n");
 #endif

 #ifdef TIOCGWINSZ
    TRACE(" - have TIOCGWINSZ\n");
 #endif

 #ifndef WIN_SZS_LIB
    if (isatty(fd))
    {
	TRACE(" - isatty\n");

     #ifdef TIOCGSIZE
	{
	    struct ttysize ts;
	    if ( !ioctl(fd,TIOCGSIZE,&ts))
	    {
		PRINT(" - TIOCGSIZE = %d*%d\n",ts.ts_cols,ts.ts_lines);
		if ( ts.ts_cols > 0 && ts.ts_lines > 0 )
		{
		    term_size_t tes = {ts.ts_cols,ts.ts_lines};
		    return tes;
		}
	    }
	}
     #endif

     #ifdef TIOCGWINSZ
	{
	    struct winsize ws;
	    if ( !ioctl(fd,TIOCGWINSZ,&ws))
	    {
		PRINT(" - TIOCGWINSZ = %d*%d\n",ws.ws_col,ws.ws_row);
		if ( ws.ws_col > 0 && ws.ws_row > 0 )
		{
		    term_size_t ts = {ws.ws_col,ws.ws_row};
		    return ts;
		}
	    }
	}
     #endif
    }
 #endif

    term_size_t ts = {default_width,default_height};
    return ts;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int GetTermWidth ( int default_value, int min_value )
{
    TRACE("GetTermWidth(%d,%d) opt=%d\n",default_value,min_value,opt_width);

    const term_size_t ts = GetTermSize(default_value,25);
    return ts.width > min_value ? ts.width : min_value;
}

///////////////////////////////////////////////////////////////////////////////

int GetTermWidthFD ( int fd, int default_value, int min_value )
{
    TRACE("GetTermWidthFD(%d,%d,%d)\n",fd,default_value,min_value);

    const term_size_t ts = GetTermSizeFD(fd,default_value,25);
    return ts.width > min_value ? ts.width : min_value;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int GetTermHeight ( int default_value, int min_value )
{
    TRACE("GetTermHeight(%d,%d) opt=%d\n",default_value,min_value,opt_height);

    const term_size_t ts = GetTermSize(80,default_value);
    return ts.width > min_value ? ts.width : min_value;
}

///////////////////////////////////////////////////////////////////////////////

int GetTermHeightFD ( int fd, int default_value, int min_value )
{
    TRACE("GetTermHeightFD(%d,%d,%d)\n",fd,default_value,min_value);

    const term_size_t ts = GetTermSizeFD(fd,80,default_value);
    return ts.height > min_value ? ts.height : min_value;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

term_size_t auto_term_size	= {80,25};
uint auto_term_resized		= 0;	// incremented for each resize, init by 0
uint auto_term_size_dirty	= 0;	// >0: SIGWINCH received, auto_term_size is dirty

//-----------------------------------------------------------------------------

bool GetAutoTermSize()
{
    // return true if changed

    auto_term_size_dirty = 0;
    int fd = isatty(1) ? 1 : isatty(0) ? 0 : -1;
    if ( fd >= 0 )
    {
	term_size_t size
	    = GetTermSizeFD(fd,auto_term_size.width,auto_term_size.height);
	if (memcmp(&auto_term_size,&size,sizeof(size)))
	{
	    auto_term_size = size;
	    if (!++auto_term_resized)
		auto_term_resized++;
	    return true;
	}
    }
    return false;
}

//-----------------------------------------------------------------------------

static void Signal_SIGWINCH ( int signal )
{
    if (!++auto_term_size_dirty)
	auto_term_size_dirty++;
}

void EnableAutoTermSize()
{
    signal(SIGWINCH,Signal_SIGWINCH);
    GetAutoTermSize();
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ccp TermCursorUp	= TERM_CURSOR_UP;	// move cursor up
ccp TermCursorDown	= TERM_CURSOR_DOWN;	// move cursor down
ccp TermCursorRight	= TERM_CURSOR_RIGHT;	// move cursor right
ccp TermCursorLeft	= TERM_CURSOR_LEFT;	// move cursor left

ccp TermCursorUpN	= TERM_CURSOR_UP_N;	// move cursor N* up    (format 1 '%d')
ccp TermCursorDownN	= TERM_CURSOR_DOWN_N;	// move cursor N* down  (format 1 '%d')
ccp TermCursorRightN	= TERM_CURSOR_RIGHT_N;	// move cursor N* right (format 1 '%d')
ccp TermCursorLeftN	= TERM_CURSOR_LEFT_N;	// move cursor N* left  (format 1 '%d')

ccp TermClearEOL	= TERM_CLEAR_EOL;	// clear from cursor to end of line
ccp TermClearBOL	= TERM_CLEAR_BOL;	// clear from beginning of line to cursor
ccp TermClearLine	= TERM_CLEAR_LINE;	// clear entire line

ccp TermClearEOD	= TERM_CLEAR_EOD;	// clear from cursor to end of display
ccp TermClearBOD	= TERM_CLEAR_BOD;	// clear from beginning of display to cursor
ccp TermClearDisplay	= TERM_CLEAR_DISPLAY;	// clear Entire display

ccp TermSetWrap		= TERM_SET_WRAP;	// enabled line wrapping
ccp TermResetWrap	= TERM_RESET_WRAP;	// disable line wrapping

ccp TermTextModeBeg	= TERM_TEXT_MODE_BEG;	// begin of text mode sequence
ccp TermTextModeEnd	= TERM_TEXT_MODE_END;	// end of text mode sequence
ccp TermTextModeReset	= TERM_TEXT_MODE_RESET;	// reset text mode

static uint grayscale_tab[4] = {0,8,7,15};

#if SUPPORT_36_COLORS

 const char ColorIndexName[TCI__N][16] =
 {
	"black",
	"dark_gray_1",
	"dark_gray_2",
	"dark_gray_3",
	"light_gray_1",
	"light_gray_2",
	"light_gray_3",
	"white",

	"red",
	"red_orange",
	"orange",
	"orange_yellow",
	"yellow",
	"yellow_green",
	"green",
	"green_cyan",
	"cyan",
	"cyan_blue",
	"blue",
	"blue_magenta",
	"magenta",
	"magenta_red",

	"b_red",
	"b_red_orange",
	"b_orange",
	"b_orange_yellow",
	"b_yellow",
	"b_yellow_green",
	"b_green",
	"b_green_cyan",
	"b_cyan",
	"b_cyan_blue",
	"b_blue",
	"b_blue_magenta",
	"b_magenta",
	"b_magenta_red",
 };
#else // !SUPPORT_36_COLORS

 const char ColorIndexName[TCI__N][11] =
 {
	"black",
	"dark gray",
	"light gray",
	"white",

	"red",
	"orange",
	"yellow",
	"green",
	"cyan",
	"blue",
	"magenta",

	"b_red",
	"b_orange",
	"b_yellow",
	"b_green",
	"b_cyan",
	"b_blue",
	"b_magenta",
 };
#endif // !SUPPORT_36_COLORS

const int Color18Index[18+1] = // 18 elements + -1 as terminator
{
	TCI_BLACK,			// gray scale
	TCI_DARKGRAY,
	TCI_LIGHTGRAY,
	TCI_WHITE,

	TCI_RED,			// normal colors in rainbow order
	TCI_ORANGE,
	TCI_YELLOW,
	TCI_GREEN,
	TCI_CYAN,
	TCI_BLUE,
	TCI_MAGENTA,

	TCI_B_RED,			// bold colors in rainbow order
	TCI_B_ORANGE,
	TCI_B_YELLOW,
	TCI_B_GREEN,
	TCI_B_CYAN,
	TCI_B_BLUE,
	TCI_B_MAGENTA,

	-1
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static char * GetColorCircBuf ( uint len )
{
    static char  circ_buf[1024];
    static char *circ_ptr = circ_buf;
    DASSERT( circ_ptr >= circ_buf && circ_ptr <= circ_buf + sizeof(circ_buf) );

    if ( len > sizeof(circ_buf)/8 )
	return GetCircBuf(len);

    if ( circ_buf + sizeof(circ_buf) - circ_ptr < len )
	circ_ptr = circ_buf;

    char *buf = circ_ptr;
    circ_ptr += len;
    DASSERT( circ_ptr >= circ_buf && circ_ptr <= circ_buf + sizeof(circ_buf) );

    return buf;
}

//-----------------------------------------------------------------------------

ccp GetTextMode
(
    // returns a pointer to an internal circulary buffer (not GetCircBuf())
    ColorMode_t		col_mode,	// if < COLMD_ON: return an empty string
    TermTextMode_t	mode		// mode for text generation
)
{
    if ( col_mode < COLMD_ON )
	return EmptyString;

    if ( mode == TTM_RESET )
	return TermTextModeReset;

    uint len = strlen(TermTextModeBeg) + strlen(TermTextModeEnd) + 2;

    if ( mode & TTM_F_COLOR )
	len += 3;
    else if ( mode & TTM_F_GRAYSCALE )
	len += 8;

    if ( mode & TTM_F_BG_COLOR )
	len += 3;
    else if ( mode & TTM_F_BG_GRAYSCALE )
	len += 8;

    if ( mode & TTM_RESET )
	len += 2;
    if ( mode & (TTM_BOLD|TTM_NO_BOLD) )
	len += 3;
    if ( mode & (TTM_UL|TTM_NO_UL) )
	len += 3;

    //--- use a private circulary buffer (long term valid)

    char *buf = GetColorCircBuf(len);

    //--- compose string

    uint sep = 0;
    char *end = buf + len;
    char *dest = StringCopyS(buf,len,TermTextModeBeg);

    if ( mode & TTM_RESET )
    {
	*dest++ = '0';
	sep++;
    }

    if ( mode & TTM_BOLD )
    {
	if (sep++)
	    *dest++ = ';';
	*dest++ = '1';
    }
    else if ( mode & TTM_NO_BOLD )
    {
	if (sep++)
	    *dest++ = ';';
	*dest++ = '2';
	*dest++ = '2';
    }

    if ( mode & TTM_UL )
    {
	if (sep++)
	    *dest++ = ';';
	*dest++ = '4';
    }
    else if ( mode & TTM_NO_UL )
    {
	if (sep++)
	    *dest++ = ';';
	*dest++ = '2';
	*dest++ = '4';
    }

    if ( mode & TTM_F_COLOR )
    {
	if (sep++)
	    *dest++ = ';';
	dest = snprintfE(dest,end,"%u",(mode&TTM_M_COLOR)+30);
    }
    else if ( mode & TTM_F_GRAYSCALE )
    {
	if (sep++)
	    *dest++ = ';';
	dest = snprintfE(dest,end,"38;5;%u",
		grayscale_tab[ mode & TTM_M_GRAYSCALE ]);
    }

    if ( mode & TTM_F_BG_COLOR )
    {
	if (sep++)
	    *dest++ = ';';
	dest = snprintfE(dest,end,"%u",((mode&TTM_M_BG_COLOR)>>TTM_SHIFT_BG)+40);
    }
    else if ( mode & TTM_F_BG_GRAYSCALE )
    {
	if (sep++)
	    *dest++ = ';';
	dest = snprintfE(dest,end,"48;5;%u",
		grayscale_tab[ (mode & TTM_M_BG_GRAYSCALE) >> TTM_SHIFT_BG ]);
    }

    StringCopyE(dest,end,TermTextModeEnd);
    return buf;
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#if SUPPORT_36_COLORS

 ccp GetColorMode // 36 colors version
 (
    // returns a pointer to an internal circulary buffer (not GetCircBuf())

    ColorMode_t		col_mode,	// if < COLMD_ON: return an empty string
    TermColorIndex_t	font_index,	// index of font color
    TermColorIndex_t	bg_index,	// index of background color
    GetColorOption_t	option		// execution options
 )
 {
    col_mode = NormalizeColorMode(col_mode,8);
    if ( col_mode < COLMD_ON )
	return EmptyString;


    //--- recommended combinations

    if ( option & GCM_ALT
	&& (uint)font_index < TCI__IGNORE
	&& (uint)bg_index < TCI__IGNORE )
    {
	static const u8 tab[TCI__N_BG][TCI__N_FONT] =
	{
	    //--- TCI_GRAY0 = TCI_BLACK
	    {
		TCI_GRAY2,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY2,		// TCI_GRAY1
		TCI_GRAY3,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_B_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GRAY1
	    {
		TCI_GRAY3,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY3,		// TCI_GRAY1
		TCI_GRAY4,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY4,		// TCI_GRAY3
		TCI_GRAY5,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_B_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GRAY2 = TCI_DARKGRAY
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY0,		// TCI_GRAY1
		TCI_GRAY0,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY4,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_B_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GRAY3
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY0,		// TCI_GRAY1
		TCI_GRAY1,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY1,		// TCI_GRAY3
		TCI_GRAY5,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_B_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GRAY4 = TCI_LIGHTGRAY
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY1,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY2,		// TCI_GRAY3
		TCI_GRAY2,		// TCI_GRAY4
		TCI_GRAY6,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GRAY5 = TCI_LIGHTGRAY
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY2,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY3,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY7,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GRAY6
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY2,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY3,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY4,		// TCI_GRAY6
		TCI_GRAY4,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_ORANGE_YELLOW,	// TCI_YELLOW
		TCI_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_GREEN,		// TCI_GREEN
		TCI_GREEN_CYAN,		// TCI_GREEN_CYAN
		TCI_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GRAY7 = TCI_WHITE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY4,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY5,		// TCI_GRAY6
		TCI_GRAY5,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_ORANGE_YELLOW,	// TCI_YELLOW
		TCI_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_GREEN,		// TCI_GREEN
		TCI_GREEN_CYAN,		// TCI_GREEN_CYAN
		TCI_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_RED
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY1,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY4,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_ORANGE,		// TCI_RED
		TCI_B_ORANGE,		// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_B_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA_RED
	    },

	    //--- TCI_RED_ORANGE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY2,		// TCI_GRAY3
		TCI_GRAY5,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED,		// TCI_RED_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_ORANGE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED,		// TCI_RED_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_ORANGE_YELLOW
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY6,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED,		// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_YELLOW
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY2,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY3,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_YELLOW_GREEN
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY6,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GREEN
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_GREEN_CYAN
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY6,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_CYAN
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY6,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_CYAN_BLUE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY1,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY2,		// TCI_GRAY3
		TCI_GRAY2,		// TCI_GRAY4
		TCI_GRAY6,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_BLUE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY0,		// TCI_GRAY1
		TCI_GRAY3,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY4,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_B_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_BLUE_MAGENTA
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY0,		// TCI_GRAY1
		TCI_GRAY3,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY4,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED,		// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_B_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_MAGENTA
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY1,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY4,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED_ORANGE,	// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_MAGENTA_RED
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY1,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY4,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_RED_ORANGE,	// TCI_RED
		TCI_B_RED_ORANGE,	// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_B_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_RED
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY1,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY4,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_B_ORANGE,		// TCI_RED
		TCI_B_ORANGE,		// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA
		TCI_B_MAGENTA,		// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_RED_ORANGE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY2,		// TCI_GRAY3
		TCI_GRAY5,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED,		// TCI_RED_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_ORANGE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY3,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_ORANGE_YELLOW
	    {

		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY4,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_YELLOW,		// TCI_YELLOW
		TCI_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_GREEN,		// TCI_GREEN
		TCI_GREEN_CYAN,		// TCI_GREEN_CYAN
		TCI_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_YELLOW
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY4,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY5,		// TCI_GRAY6
		TCI_GRAY5,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_YELLOW,		// TCI_YELLOW
		TCI_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_GREEN,		// TCI_GREEN
		TCI_GREEN_CYAN,		// TCI_GREEN_CYAN
		TCI_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_YELLOW_GREEN
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY4,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY5,		// TCI_GRAY6
		TCI_GRAY5,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_YELLOW,		// TCI_YELLOW
		TCI_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_GREEN,		// TCI_GREEN
		TCI_GREEN_CYAN,		// TCI_GREEN_CYAN
		TCI_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_GREEN
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY4,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY5,		// TCI_GRAY6
		TCI_GRAY5,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_YELLOW,		// TCI_YELLOW
		TCI_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_GREEN,		// TCI_GREEN
		TCI_GREEN_CYAN,		// TCI_GREEN_CYAN
		TCI_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_GREEN_CYAN
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY4,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY5,		// TCI_GRAY6
		TCI_GRAY5,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_YELLOW,		// TCI_YELLOW
		TCI_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_GREEN,		// TCI_GREEN
		TCI_GREEN_CYAN,		// TCI_GREEN_CYAN
		TCI_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_CYAN
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY4,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY5,		// TCI_GRAY6
		TCI_GRAY5,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_YELLOW,		// TCI_YELLOW
		TCI_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_GREEN,		// TCI_GREEN
		TCI_GREEN_CYAN,		// TCI_GREEN_CYAN
		TCI_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_CYAN_BLUE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_BLUE
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_BLUE_MAGENTA
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_B_CYAN_BLUE,	// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_MAGENTA
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED_ORANGE,		// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },

	    //--- TCI_B_MAGENTA_RED
	    {
		TCI_GRAY0,		// TCI_GRAY0 = TCI_BLACK
		TCI_GRAY1,		// TCI_GRAY1
		TCI_GRAY2,		// TCI_GRAY2 = TCI_DARKGRAY
		TCI_GRAY3,		// TCI_GRAY3
		TCI_GRAY4,		// TCI_GRAY4
		TCI_GRAY5,		// TCI_GRAY5 = TCI_LIGHTGRAY
		TCI_GRAY6,		// TCI_GRAY6
		TCI_GRAY7,		// TCI_GRAY7 = TCI_WHITE

		TCI_RED,		// TCI_RED
		TCI_RED,		// TCI_RED_ORANGE
		TCI_B_ORANGE,		// TCI_ORANGE
		TCI_B_ORANGE_YELLOW,	// TCI_ORANGE_YELLOW
		TCI_B_YELLOW,		// TCI_YELLOW
		TCI_B_YELLOW_GREEN,	// TCI_YELLOW_GREEN
		TCI_B_GREEN,		// TCI_GREEN
		TCI_B_GREEN_CYAN,	// TCI_GREEN_CYAN
		TCI_B_CYAN,		// TCI_CYAN
		TCI_CYAN_BLUE,		// TCI_CYAN_BLUE
		TCI_BLUE,		// TCI_BLUE
		TCI_BLUE_MAGENTA,	// TCI_BLUE_MAGENTA
		TCI_MAGENTA,		// TCI_MAGENTA
		TCI_MAGENTA_RED,	// TCI_MAGENTA_RED
	    },
	};

	const uint font	= font_index < TCI_B_RED ? font_index
			: font_index - (TCI_B_RED-TCI_RED);
	font_index = tab[bg_index][font];
    }


    //--- color index

    static const u8 color_index_8[] =
    {
	 0,	// TCI_GRAY0 = TCI_BLACK
	 0,	// TCI_GRAY1
	 8,	// TCI_GRAY2 = TCI_DARKGRAY
	 8,	// TCI_GRAY3
	 7,	// TCI_GRAY4
	 7,	// TCI_GRAY5 = TCI_LIGHTGRAY
	15,	// TCI_GRAY6
	15,	// TCI_GRAY7 = TCI_WHITE

	 1,	// TCI_RED
	 1,	// TCI_RED_ORANGE
	 1,	// TCI_ORANGE
	 1,	// TCI_ORANGE_YELLOW
	 3,	// TCI_YELLOW
	 3,	// TCI_YELLOW_GREEN
	 2,	// TCI_GREEN
	 2,	// TCI_GREEN_CYAN
	 6,	// TCI_CYAN
	 6,	// TCI_CYAN_BLUE
	 4,	// TCI_BLUE
	 4,	// TCI_BLUE_MAGENTA
	 5,	// TCI_MAGENTA
	 5,	// TCI_MAGENTA_RED

	 9,	// TCI_B_RED
	 9,	// TCI_B_RED_ORANGE
	 9,	// TCI_B_ORANGE
	 9,	// TCI_B_ORANGE_YELLOW
	11,	// TCI_B_YELLOW
	11,	// TCI_B_YELLOW_GREEN
	10,	// TCI_B_GREEN
	10,	// TCI_B_GREEN_CYAN
	14,	// TCI_B_CYAN
	14,	// TCI_B_CYAN_BLUE
	12,	// TCI_B_BLUE
	12,	// TCI_B_BLUE_MAGENTA
	13,	// TCI_B_MAGENTA
	13,	// TCI_B_MAGENTA_RED
    };

    static const u8 color_index_256[] =
    {
	232,	// TCI_GRAY0 = TCI_BLACK
	236,	// TCI_GRAY1
	240,	// TCI_GRAY2 = TCI_DARKGRAY
	243,	// TCI_GRAY3
	246,	// TCI_GRAY4
	249,	// TCI_GRAY5 = TCI_LIGHTGRAY
	252,	// TCI_GRAY6
	255,	// TCI_GRAY7 = TCI_WHITE

	160,	// TCI_RED
	166,	// TCI_RED_ORANGE
	172,	// TCI_ORANGE
	136,	// TCI_ORANGE_YELLOW
	142,	// TCI_YELLOW
	106,	// TCI_YELLOW_GREEN
	 34,	// TCI_GREEN
	 36,	// TCI_GREEN_CYAN
	 37,	// TCI_CYAN
	 32,	// TCI_CYAN_BLUE
	 21,	// TCI_BLUE
	 92,	// TCI_BLUE_MAGENTA
	164,	// TCI_MAGENTA
	162,	// TCI_MAGENTA_RED

	196,	// TCI_B_RED
	202,	// TCI_B_RED_ORANGE
	208,	// TCI_B_ORANGE
	214,	// TCI_B_ORANGE_YELLOW
	226,	// TCI_B_YELLOW
	154,	// TCI_B_YELLOW_GREEN
	 46,	// TCI_B_GREEN
	 49,	// TCI_B_GREEN_CYAN
	 51,	// TCI_B_CYAN
	 75,	// TCI_B_CYAN_BLUE
	105,	// TCI_B_BLUE
	177,	// TCI_B_BLUE_MAGENTA
	207,	// TCI_B_MAGENTA
	204,	// TCI_B_MAGENTA_RED
    };

    const u8 *color_index;
    uint x_bg;
    if ( col_mode == COLMD_256_COLORS )
    {
	color_index = color_index_256;
	x_bg = 8;
    }
    else
    {
	color_index = color_index_8;
	x_bg = 16;
	option |= GCM_SHORT;
    }


    //--- output

    char buf[100], *end = buf + sizeof(buf);
    char *dest = StringCopyE(buf,end,TermTextModeBeg);

    const uint bg = (uint)bg_index < TCI__IGNORE ? color_index[bg_index] : ~0;

    ccp sep = "";
    if ( (uint)font_index < TCI__IGNORE )
    {
	uint idx = color_index[font_index];
	if ( idx < 16 && idx == (bg&7) && option & GCM_ALT )
	    idx = idx ^ 8;

	if ( !(option & GCM_SHORT) || idx >= 16 )
	    dest = snprintfE(dest,end,"38;5;%u",idx);
	else if ( idx < 8 )
	    dest = snprintfE(dest,end,"0;%u",30+idx);
	else
	    dest = snprintfE(dest,end,"1;%u",22+idx);
	sep  = ";";
    }

    if ( (uint)bg_index < TCI__IGNORE )
    {
	if ( !(option & GCM_SHORT) || bg >= x_bg )
	    dest = snprintfE(dest,end,"%s48;5;%u",sep,bg);
	else
	    dest = snprintfE(dest,end,"%s%u",sep,40+(bg&7));
    }

    dest = StringCopyE(dest,end,TermTextModeEnd);
    const int len = dest + 1 - buf;
    char *res = GetColorCircBuf(len);
    memcpy(res,buf,len);
    return res;
 }

#else // !SUPPORT_36_COLORS

 ccp GetColorMode // 18 colors version
 (
    // returns a pointer to an internal circulary buffer (not GetCircBuf())

    ColorMode_t		col_mode,	// if < COLMD_ON: return an empty string
    TermColorIndex_t	font_index,	// index of font color
    TermColorIndex_t	bg_index,	// index of background color
    GetColorOption_t	option		// execution options
 )
 {
    col_mode = NormalizeColorMode(col_mode,8);
    if ( col_mode < COLMD_ON )
	return EmptyString;


    //--- recommended combinations

    if ( option & GCM_ALT
	&& (uint)font_index < TCI__IGNORE
	&& (uint)bg_index < TCI__IGNORE )
    {

	static const u8 tab[TCI__N_BG][TCI__N_FONT] =
	{
	    //--- TCI_BLACK
	    {
		TCI_DARKGRAY,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_LIGHTGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_B_RED,	// TCI_RED
		TCI_B_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_B_BLUE,	// TCI_BLUE
		TCI_B_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_DARKGRAY
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_LIGHTGRAY,	// TCI_DARKGRAY
		TCI_LIGHTGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_B_RED,	// TCI_RED
		TCI_B_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_B_BLUE,	// TCI_BLUE
		TCI_B_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_LIGHTGRAY
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_DARKGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_GREEN,	// TCI_GREEN
		TCI_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_WHITE
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_LIGHTGRAY,	// TCI_LIGHTGRAY
		TCI_LIGHTGRAY,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_ORANGE,	// TCI_YELLOW
		TCI_GREEN,	// TCI_GREEN
		TCI_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_RED
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_LIGHTGRAY,	// TCI_DARKGRAY
		TCI_LIGHTGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_B_RED,	// TCI_RED
		TCI_B_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_B_BLUE,	// TCI_BLUE
		TCI_B_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_ORANGE
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_WHITE,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_B_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_YELLOW
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_WHITE,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_GREEN
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_LIGHTGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_CYAN
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_LIGHTGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_BLUE
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_LIGHTGRAY,	// TCI_DARKGRAY
		TCI_LIGHTGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_CYAN,	// TCI_BLUE
		TCI_B_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_MAGENTA
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_LIGHTGRAY,	// TCI_DARKGRAY
		TCI_LIGHTGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_CYAN,	// TCI_BLUE
		TCI_B_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_B_RED
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_WHITE,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_B_ORANGE
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_WHITE,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_B_YELLOW
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_DARKGRAY,	// TCI_LIGHTGRAY
		TCI_DARKGRAY,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_YELLOW,	// TCI_YELLOW
		TCI_GREEN,	// TCI_GREEN
		TCI_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_B_GREEN
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_DARKGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_GREEN,	// TCI_GREEN
		TCI_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_B_CYAN
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_DARKGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_ORANGE,	// TCI_ORANGE
		TCI_YELLOW,	// TCI_YELLOW
		TCI_GREEN,	// TCI_GREEN
		TCI_CYAN,	// TCI_CYAN
		TCI_BLUE,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_B_BLUE
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_DARKGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_B_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_B_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_CYAN,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },

	    //--- TCI_B_MAGENTA
	    {
		TCI_BLACK,	// TCI_BLACK
		TCI_DARKGRAY,	// TCI_DARKGRAY
		TCI_DARKGRAY,	// TCI_LIGHTGRAY
		TCI_WHITE,	// TCI_WHITE
		TCI_RED,	// TCI_RED
		TCI_B_ORANGE,	// TCI_ORANGE
		TCI_B_YELLOW,	// TCI_YELLOW
		TCI_GREEN,	// TCI_GREEN
		TCI_B_CYAN,	// TCI_CYAN
		TCI_CYAN,	// TCI_BLUE
		TCI_MAGENTA,	// TCI_MAGENTA
	    },
	};

	const uint font	= font_index < TCI_B_RED ? font_index
			: font_index - (TCI_B_RED-TCI_RED);
	font_index = tab[bg_index][font];
    }


    //--- color index

    static const u8 color_index_8[] =
    {
	 0,	// TCI_BLACK
	 8,	// TCI_DARKGRAY
	 7,	// TCI_LIGHTGRAY
	15,	// TCI_WHITE

	 1,	// TCI_RED
	 1,	// TCI_ORANGE
	 3,	// TCI_YELLOW
	 2,	// TCI_GREEN
	 6,	// TCI_CYAN
	 4,	// TCI_BLUE
	 5,	// TCI_MAGENTA

	 9,	// TCI_B_RED
	 9,	// TCI_B_ORANGE
	11,	// TCI_B_YELLOW
	10,	// TCI_B_GREEN
	14,	// TCI_B_CYAN
	12,	// TCI_B_BLUE
	13,	// TCI_B_MAGENTA
    };

    static const u8 color_index_256[] =
    {
	  0,	// TCI_BLACK
	  8,	// TCI_DARKGRAY
	  7,	// TCI_LIGHTGRAY
	 15,	// TCI_WHITE

	160,	// TCI_RED
	172,	// TCI_ORANGE
	142,	// TCI_YELLOW
	 34,	// TCI_GREEN
	 37,	// TCI_CYAN
	 21,	// TCI_BLUE
	164,	// TCI_MAGENTA

	196,	// TCI_B_RED
	208,	// TCI_B_ORANGE
	226,	// TCI_B_YELLOW
	 46,	// TCI_B_GREEN
	 51,	// TCI_B_CYAN
	105,	// TCI_B_BLUE
	207,	// TCI_B_MAGENTA
    };

    const u8 *color_index;
    uint x_bg;
    if ( col_mode == COLMD_256_COLORS )
    {
	color_index = color_index_256;
	x_bg = 8;
    }
    else
    {
	color_index = color_index_8;
	x_bg = 16;
	option |= GCM_SHORT;
    }


    //--- output

    char buf[100], *end = buf + sizeof(buf);
    char *dest = StringCopyE(buf,end,TermTextModeBeg);

    ccp sep = "";
    if ( (uint)font_index < TCI__IGNORE )
    {
	const uint idx = color_index[font_index];
	if ( !(option & GCM_SHORT) || idx >= 16 )
	    dest = snprintfE(dest,end,"38;5;%u",idx);
	else if ( idx < 8 )
	    dest = snprintfE(dest,end,"0;%u",30+idx);
	else
	    dest = snprintfE(dest,end,"1;%u",22+idx);
	sep  = ";";
    }

    if ( (uint)bg_index < TCI__IGNORE )
    {
	const uint idx = color_index[bg_index];
	if ( !(option & GCM_SHORT) || idx >= x_bg )
	    dest = snprintfE(dest,end,"%s48;5;%u",sep,idx);
	else
	    dest = snprintfE(dest,end,"%s%u",sep,40+(idx&7));
    }

    dest = StringCopyE(dest,end,TermTextModeEnd);
    const int len = dest + 1 - buf;
    char *res = GetColorCircBuf(len);
    memcpy(res,buf,len);
    return res;
 }

#endif // !SUPPORT_36_COLORS

//
///////////////////////////////////////////////////////////////////////////////
///////////////			   colors			///////////////
///////////////////////////////////////////////////////////////////////////////

const ColorSet_t * GetColorSet0()
{
    static ColorSet_t col = {0};
    if (!col.col_mode)
    {
	col.col_mode	= COLMD_OFF;
	col.colorize	= false;
	col.n_colors	= 0;

	col.space	= EmptyString;
	col.tab		= EmptyString;
	col.lf		= EmptyString;

	ccp *ptr = &col.reset;
	ccp *end = (ccp*)((ccp)&col + sizeof(col));
	while ( ptr < end )
	    *ptr++ = EmptyString;
    }
    return &col;
}

///////////////////////////////////////////////////////////////////////////////

const ColorSet_t * GetColorSet8()
{
    // [[new-color]]

    static ColorSet_t col = {0};
    if (!col.col_mode)
    {
	col.col_mode		= COLMD_8_COLORS;
	col.colorize		= true;
	col.n_colors		= 8;

	col.space		= Space200;
	col.tab			= Tabs20;
	col.lf			= LF20;

	 col.reset		= TermTextModeReset;
	col.setup		= STRDUP(GetTextMode(1,TTM_COL_SETUP));
	col.run			= STRDUP(GetTextMode(1,TTM_COL_RUN));
	col.abort		= STRDUP(GetTextMode(1,TTM_COL_ABORT));
	col.finish		= STRDUP(GetTextMode(1,TTM_COL_FINISH));
	col.script		= STRDUP(GetTextMode(1,TTM_COL_SCRIPT));
	col.open		= STRDUP(GetTextMode(1,TTM_COL_OPEN));
	col.close		= STRDUP(GetTextMode(1,TTM_COL_CLOSE));
	col.file		= STRDUP(GetTextMode(1,TTM_COL_FILE));
	col.job			= STRDUP(GetTextMode(1,TTM_COL_JOB));
	 col.info		= STRDUP(GetTextMode(1,TTM_COL_INFO));
	 col.hint		= STRDUP(GetTextMode(1,TTM_COL_HINT));
	 col.warn		= STRDUP(GetTextMode(1,TTM_COL_WARN));
	 col.debug		= STRDUP(GetTextMode(1,TTM_COL_DEBUG));
	 col.log		= STRDUP(GetTextMode(1,TTM_COL_LOG));
	col.name		= STRDUP(GetTextMode(1,TTM_COL_NAME));
	col.op			= STRDUP(GetTextMode(1,TTM_COL_OP));
	col.value		= STRDUP(GetTextMode(1,TTM_COL_VALUE));
	col.success		= STRDUP(GetTextMode(1,TTM_COL_SUCCESS));
	col.error		= STRDUP(GetTextMode(1,TTM_COL_ERROR));
	col.fail		= STRDUP(GetTextMode(1,TTM_COL_FAIL));
	col.fail2		= STRDUP(GetTextMode(1,TTM_COL_FAIL2));
	col.fatal		= STRDUP(GetTextMode(1,TTM_COL_FATAL));
	col.mark		= STRDUP(GetTextMode(1,TTM_COL_MARK));
	col.bad			= STRDUP(GetTextMode(1,TTM_COL_BAD));
	 col.select		= STRDUP(GetTextMode(1,TTM_COL_SELECT));
	 col.differ		= STRDUP(GetTextMode(1,TTM_COL_DIFFER));
	 col.stat_line		= STRDUP(GetTextMode(1,TTM_COL_STAT_LINE));
	 col.warn_line		= STRDUP(GetTextMode(1,TTM_COL_WARN_LINE));
	 col.proc_line		= STRDUP(GetTextMode(1,TTM_COL_PROC_LINE));
	 col.cite		= STRDUP(GetTextMode(1,TTM_COL_CITE));
	 col.status		= STRDUP(GetTextMode(1,TTM_COL_STATUS));
	 col.highlight		= STRDUP(GetTextMode(1,TTM_COL_HIGHLIGHT));
	 col.hide		= STRDUP(GetTextMode(1,TTM_COL_HIDE));
	col.heading		= STRDUP(GetTextMode(1,TTM_COL_HEADING));
	col.caption		= STRDUP(GetTextMode(1,TTM_COL_CAPTION));
	col.section		= STRDUP(GetTextMode(1,TTM_COL_SECTION));
	col.syntax		= STRDUP(GetTextMode(1,TTM_COL_SYNTAX));
	col.cmd			= STRDUP(GetTextMode(1,TTM_COL_CMD));
	col.option		= STRDUP(GetTextMode(1,TTM_COL_OPTION));
	col.param		= STRDUP(GetTextMode(1,TTM_COL_PARAM));
	 col.on			= STRDUP(GetTextMode(1,TTM_COL_ON));
	 col.off		= STRDUP(GetTextMode(1,TTM_COL_OFF));

	col.black		= STRDUP(GetTextMode(1,TTM_NO_BOLD|TTM_BLACK));
	col.b_black		= STRDUP(GetTextMode(1,TTM_BOLD|TTM_BLACK));
	col.white		= STRDUP(GetTextMode(1,TTM_NO_BOLD|TTM_WHITE));
	col.b_white		= STRDUP(GetTextMode(1,TTM_BOLD|TTM_WHITE));

	col.red			= STRDUP(GetTextMode(1,TTM_NO_BOLD|TTM_RED));
	col.red_orange		= col.red;
	col.orange		= col.red;
	col.yellow		= STRDUP(GetTextMode(1,TTM_NO_BOLD|TTM_YELLOW));
	col.orange_yellow	= col.yellow;
	col.yellow_green	= col.yellow;
	col.green		= STRDUP(GetTextMode(1,TTM_NO_BOLD|TTM_GREEN));
	col.green_cyan		= col.green;
	col.cyan		= STRDUP(GetTextMode(1,TTM_NO_BOLD|TTM_CYAN));
	col.cyan_blue		= col.cyan;
	col.blue		= STRDUP(GetTextMode(1,TTM_NO_BOLD|TTM_BLUE));
	col.blue_magenta	= col.blue;
	col.magenta		= STRDUP(GetTextMode(1,TTM_NO_BOLD|TTM_MAGENTA));
	col.magenta_red		= col.magenta;

	col.b_red		= STRDUP(GetTextMode(1,TTM_BOLD|TTM_RED));
	col.b_red_orange	= col.b_red;
	col.b_orange		= col.b_red;
	col.b_yellow		= STRDUP(GetTextMode(1,TTM_BOLD|TTM_YELLOW));
	col.b_orange_yellow	= col.b_yellow;
	col.b_yellow_green	= col.b_yellow;
	col.b_green		= STRDUP(GetTextMode(1,TTM_BOLD|TTM_GREEN));
	col.b_green_cyan	= col.b_green;
	col.b_cyan		= STRDUP(GetTextMode(1,TTM_BOLD|TTM_CYAN));
	col.b_cyan_blue		= col.b_cyan;
	col.b_blue		= STRDUP(GetTextMode(1,TTM_BOLD|TTM_BLUE));
	col.b_blue_magenta	= col.b_blue;
	col.b_magenta		= STRDUP(GetTextMode(1,TTM_BOLD|TTM_MAGENTA));
	col.b_magenta_red	= col.b_magenta;

	TermColorIndex_t font, bg;
	for ( font = 0; font < TCI__N_FONT; font++ )
	    for ( bg = 0; bg < TCI__N_BG; bg++ )
		col.matrix[font][bg]
		    = STRDUP(GetColorMode(COLMD_8_COLORS,font,bg,GCM_ALT|GCM_SHORT));
    }

    return &col;
}

///////////////////////////////////////////////////////////////////////////////

const ColorSet_t * GetColorSet256()
{
    // [[new-color]]

    static ColorSet_t col = {0};
    if (!col.col_mode)
    {
	//--- default settings (copy of 8-COLORS)

	memcpy(&col,GetColorSet8(),sizeof(col));
	col.col_mode	= COLMD_256_COLORS;
	col.n_colors	= 256;


	//--- special settings

	col.setup	= "\e[38;5;86;40m";
	col.run		= "\e[38;5;229;40m";
	col.abort	= "\e[38;5;198;40m";
	col.finish	= "\e[38;5;154;40m";
	col.script	= "\e[0;30;48;5;219m";
	col.open	= "\e[38;5;225;40m";
	col.close	= "\e[38;5;219;40m";
	col.heading	= "\e[38;5;111;40m";
	col.info	= "\e[38;5;49;40m";
	col.hint	= "\e[38;5;220;40m";
	col.warn	= "\e[38;5;208;40m";
	col.debug	= "\e[38;5;210;40m";
	col.error	= "\e[38;5;255;48;5;130m";
	col.fail	= "\e[38;5;251;48;5;88m";
	col.fail2	= "\e[38;5;255;48;5;88m";
	col.fatal	= "\e[38;5;255;48;5;129m";
	col.differ	= "\e[38;5;226;48;5;19m";
	col.stat_line	= "\e[38;5;231;48;5;19m";
	col.warn_line	= "\e[38;5;215;48;5;19m";
	col.hide	= "\e[38;5;245;40m";


	//--- special settings: color names

	// dark:
	// ./mkw-ana testcol 400-420  420-330  330-030  030-033  033-005  005-404  404-400
	// ./mkw-ana testcol 400 410 420 320 330 230 030 032 033 024 005 204 404 402 400

	col.red			= "\e[38;5;160m";
	col.red_orange		= "\e[38;5;166m";
	col.orange		= "\e[38;5;172m";
	col.orange_yellow	= "\e[38;5;136m";
	col.yellow		= "\e[38;5;142m";
	col.yellow_green	= "\e[38;5;106m";
	col.green		= "\e[38;5;34m";
	col.green_cyan		= "\e[38;5;36m";
	col.cyan		= "\e[38;5;37m";
	col.cyan_blue		= "\e[38;5;32m";
	col.blue		= "\e[38;5;21m";
	col.blue_magenta	= "\e[38;5;92m";
	col.magenta		= "\e[38;5;164m";
	col.magenta_red		= "\e[38;5;162m";

	// bold:
	// ./mkw-ana testcol 500-520  520-550  550-050  050-055  055-225  225-515  515-500
	// ./mkw-ana testcol 500 510 520 530 550 350 050 053 055 135 225 425 515 512 500

	col.b_red		= "\e[38;5;196m";
	col.b_red_orange	= "\e[38;5;202m";
	col.b_orange		= "\e[38;5;208m";
	col.b_orange_yellow	= "\e[38;5;214m";
	col.b_yellow		= "\e[38;5;226m";
	col.b_yellow_green	= "\e[38;5;154m";
	col.b_green		= "\e[38;5;46m";
	col.b_green_cyan	= "\e[38;5;49m";
	col.b_cyan		= "\e[38;5;51m";
	col.b_cyan_blue		= "\e[38;5;75m";
	col.b_blue		= "\e[38;5;105m";
	col.b_blue_magenta	= "\e[38;5;177m";
	col.b_magenta		= "\e[38;5;207m";
	col.b_magenta_red	= "\e[38;5;204m";

	TermColorIndex_t font, bg;
	for ( font = 0; font < TCI__N_FONT; font++ )
	    for ( bg = 0; bg < TCI__N_BG; bg++ )
		col.matrix[font][bg]
		    = STRDUP(GetColorMode(COLMD_256_COLORS,font,bg,GCM_ALT|GCM_SHORT));
    }

    return &col;

//---------- old definitions ----------
//
//	col.differ	= STRDUP(GetColorMode(COLMD_256_COLORS,
//				TCI_YELLOW, TCI_BLUE, GCM_ALT|GCM_SHORT ));
//	col.stat_line	= STRDUP(GetColorMode(COLMD_256_COLORS,
//				TCI_WHITE, TCI_BLUE, GCM_ALT|GCM_SHORT ));
//	col.warn_line	= STRDUP(GetColorMode(COLMD_256_COLORS,
//				TCI_ORANGE, TCI_BLUE, GCM_ALT|GCM_SHORT ));
//
//	col.orange	= STRDUP(GetColorMode(COLMD_256_COLORS,
//				TCI_ORANGE, TCI__IGNORE, GCM_ALT|GCM_SHORT ));
//	col.b_orange	= STRDUP(GetColorMode(COLMD_256_COLORS,
//				TCI_B_ORANGE, TCI__IGNORE, GCM_ALT|GCM_SHORT ));
//
//-------------------------------------
}

///////////////////////////////////////////////////////////////////////////////

int setupterm(char *term, int fildes, int *errret);
int tigetnum(char *capname);

const ColorSet_t * GetColorSetAuto ( bool force_on )
{
    static ColorMode_t auto_mode = COLMD_AUTO;
    if ( opt_colorize != COLMD_AUTO )
    {
	if ( opt_colorize == COLMD_ON )
	    force_on = true;
	else
	    auto_mode = opt_colorize;
    }

    if ( auto_mode == COLMD_AUTO )
    {
	int error;
	setupterm(getenv("TERM"),1,&error);
	const int ncol = tigetnum("colors");

	auto_mode = ncol >= 256 ? COLMD_256_COLORS
		  : ncol >=   8 ? COLMD_8_COLORS
				: COLMD_OFF;
	if ( auto_mode == COLMD_OFF && !strcmp(getenv("TERM"),"cygwin") )
	    auto_mode = COLMD_8_COLORS;

     #ifdef TEST
	fprintf(stderr,">>> GetColorSetAuto(%d) => \"%s\" n=%d => %d [%s]\n",
		force_on, getenv("TERM"), ncol,
		auto_mode, GetColorModeName(auto_mode,0) );
     #endif
    }

    switch(auto_mode)
    {
	case COLMD_8_COLORS:
	    return GetColorSet8();

	case COLMD_256_COLORS:
	    return GetColorSet256();

	default:
	    return force_on ? GetColorSet8() : GetColorSet0();
    }
}

///////////////////////////////////////////////////////////////////////////////

const ColorSet_t * GetColorSet ( ColorMode_t col_mode )
{
    switch(col_mode)
    {
	case COLMD_AUTO:
	    return GetColorSetAuto(false);

	case COLMD_ON:
	    return GetColorSetAuto(true);

	case COLMD_8_COLORS:
	    return GetColorSet8();

	case COLMD_256_COLORS:
	    return GetColorSet256();

	default:
	    return GetColorSet0();
    }
}

///////////////////////////////////////////////////////////////////////////////

const ColorSet_t * GetFileColorSet ( FILE *f )
{
     return GetColorSet(GetFileColorized(f));
}

///////////////////////////////////////////////////////////////////////////////

bool SetupColorSet ( ColorSet_t *cs, FILE *f )
{
    DASSERT(cs);
    memcpy(cs,GetColorSet(GetFileColorized(f)),sizeof(*cs));
    return cs->colorize;
}

///////////////////////////////////////////////////////////////////////////////

ccp GetColorByName ( const ColorSet_t *colset, ccp name )
{
    struct cdef_t
    {
	u16  delta;
	char name[16];
    };

    #undef DEF1
    #undef DEF2
    #define DEF1(n)   { offsetof(ColorSet_t,n), #n },
    #define DEF2(t,n) { offsetof(ColorSet_t,n), #t },

    static const struct cdef_t tab[] =
    {
	// [[new-color]]
	DEF1(abort)
	DEF1(b_black)
	DEF1(b_blue)
	DEF1(b_blue_magenta)
	DEF1(b_cyan)
	DEF1(b_cyan_blue)
	DEF1(b_green)
	DEF1(b_green_cyan)
	DEF1(b_magenta)
	DEF1(b_magenta_red)
	DEF1(b_orange)
	DEF1(b_orange_yellow)
	DEF1(b_red)
	DEF1(b_red_orange)
	DEF1(b_white)
	DEF1(b_yellow)
	DEF1(b_yellow_green)
	DEF1(bad)
	DEF1(black)
	DEF1(blue)
	DEF1(blue_magenta)
	DEF1(caption)
	DEF1(cite)
	DEF1(close)
	DEF1(cmd)
	DEF1(cyan)
	DEF1(cyan_blue)
	DEF1(debug)
	DEF1(differ)
	DEF1(error)
	DEF1(fail)
	DEF1(fail2)
	DEF1(fatal)
	DEF1(file)
	DEF1(finish)
	DEF1(green)
	DEF1(green_cyan)
	DEF2(head,heading)
	DEF1(heading)
	DEF1(hide)
	DEF1(highlight)
	DEF1(hint)
	DEF2(hl,highlight)
	DEF1(info)
	DEF1(job)
	DEF1(log)
	DEF1(magenta)
	DEF1(magenta_red)
	DEF1(mark)
	DEF1(name)
	DEF1(off)
	DEF1(on)
	DEF1(op)
	DEF1(open)
	DEF2(opt,option)
	DEF1(option)
	DEF1(orange)
	DEF1(orange_yellow)
	DEF2(par,param)
	DEF1(param)
	DEF1(proc_line)
	DEF1(red)
	DEF1(red_orange)
	DEF1(reset)
	DEF1(run)
	DEF1(script)
	DEF1(section)
	DEF1(select)
	DEF1(setup)
	DEF1(stat_line)
	DEF1(status)
	DEF1(success)
	DEF1(syntax)
	DEF2(val,value)
	DEF1(value)
	DEF1(warn)
	DEF1(warn_line)
	DEF1(white)
	DEF1(yellow)
	DEF1(yellow_green)
    };

 #if HAVE_PRINT
    static bool done = false;
    if (!done)
    {
	done = true;
	uint i, max_len = 0, err_count = 0;
	const struct cdef_t *cd = tab;
	for ( i = 0; i < sizeof(tab)/sizeof(*tab); i++, cd++ )
	{
	    if ( max_len < strlen(cd->name) )
		 max_len = strlen(cd->name);

	    if ( i > 0 && strcmp(cd[-1].name,cd->name) >= 0 )
	    {
		err_count++;
		PRINT("WRONG COL ORDER: %s > %s\n", cd[-1].name, cd->name);
	    }
	}

	DASSERT_MSG( max_len < sizeof(cd->name),
			"%s(): max name len = %d, possible = %zd\n",
			__FUNCTION__, max_len, sizeof(cd->name)-1  );
	DASSERT_MSG( !err_count,
			"%s(): color order is %d* wrong!\n",
			__FUNCTION__, err_count );
    }
 #endif

    //--- search the name

    if ( colset && name )
    {
	int beg = 0;
	int end = sizeof(tab)/sizeof(*tab) - 1;
	while ( beg <= end )
	{
	    const uint idx = (beg+end)/2;
	    const int stat = strcmp(name,tab[idx].name);
	    if ( stat < 0 )
		end = idx - 1 ;
	    else if ( stat > 0 )
		beg = idx + 1;
	    else
		return *(ccp*)((u8*)colset+tab[idx].delta);
	}
    }
    return EmptyString;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void PrintColorSetHelper
(
    FILE		*f,		// valid output file
    int			indent,		// indention of output
    const ColorSet_t	*cs,		// valid color set; if NULL: use std colors
    PrintColorFunc	func,		// output function, never NULL
    uint		mode		// output mode (bit field, NULL=default):
					//   1: print normal colors (e.g. RED)
					//   2: print bold colors (e.g. B_RED)
					//   4: print background (e.g. BLUE_RED)
					//   8: print color names (e.g. HIGHLIGHT)
					//  16: include alternative names too (e.g. HL)
)
{
    // [[new-color]]

    DASSERT(f);
    DASSERT(func);

    if (!cs)
	cs = GetColorSet(COLMD_ON);
    indent = NormalizeIndent(indent) + 10; // +10 is max name width
    if (!mode)
	mode = 15;

    #undef JOB1
    #undef JOB2
    #define JOB1(m,n)	func(f,indent,cs,m,#n,cs->n)
    #define JOB2(m,t,n)	func(f,indent,cs,m,#t,cs->n)

    if ( mode & 1 )
    {
	func(f,indent,cs,1,0,0);
	JOB1(1,black);
	JOB1(1,red);
	JOB1(1,red_orange);
	JOB1(1,orange);
	JOB1(1,orange_yellow);
	JOB1(1,yellow);
	JOB1(1,yellow_green);
	JOB1(1,green);
	JOB1(1,green_cyan);
	JOB1(1,cyan);
	JOB1(1,cyan_blue);
	JOB1(1,blue);
	JOB1(1,blue_magenta);
	JOB1(1,magenta);
	JOB1(1,magenta_red);
	JOB1(1,white);
    }

    if ( mode & 2 )
    {
	func(f,indent,cs,2,0,0);
	JOB1(2,b_black);
	JOB1(2,b_red);
	JOB1(2,b_red_orange);
	JOB1(2,b_orange);
	JOB1(2,b_orange_yellow);
	JOB1(2,b_yellow);
	JOB1(2,b_yellow_green);
	JOB1(2,b_green);
	JOB1(2,b_green_cyan);
	JOB1(2,b_cyan);
	JOB1(2,b_cyan_blue);
	JOB1(2,b_blue);
	JOB1(2,b_blue_magenta);
	JOB1(2,b_magenta);
	JOB1(2,b_magenta_red);
	JOB1(2,b_white);
    }

    if ( mode & 8 )
    {
	const bool alt = ( mode & 16 ) != 0;
	func(f,indent,cs,8,0,0);

	JOB1(4,setup);
	JOB1(4,run);
	JOB1(4,abort);
	JOB1(4,finish);
	JOB1(4,script);
	JOB1(4,open);
	JOB1(4,close);
	JOB1(4,file);
	JOB1(4,job);

	JOB1(4,info);
	JOB1(4,hint);
	JOB1(4,warn);
	JOB1(4,debug);
	JOB1(4,log);

	JOB1(4,name);
	JOB1(4,op);
	JOB1(4,value);		if (alt) JOB2(12,val,value);
	JOB1(4,success);
	JOB1(4,error);
	JOB1(4,fail);
	JOB1(4,fail2);
	JOB1(4,fatal);
	JOB1(4,mark);
	JOB1(4,bad);

	JOB1(4,select);
	JOB1(4,differ);
	JOB1(4,stat_line);
	JOB1(4,warn_line);
	JOB1(4,proc_line);
	JOB1(4,cite);
	JOB1(4,status);
	JOB1(4,highlight);	if (alt) JOB2(12,hl,highlight);
	JOB1(4,hide);

	JOB1(4,heading);	if (alt) JOB2(12,head,heading);
	JOB1(4,caption);
	JOB1(4,section);
	JOB1(4,syntax);
	JOB1(4,cmd);
	JOB1(4,option);		if (alt) JOB2(12,opt,option);
	JOB1(4,param);		if (alt) JOB2(12,par,param);

	JOB1(4,off);
	JOB1(4,on);
    }

    #undef JOB1
    #undef JOB2
}

///////////////////////////////////////////////////////////////////////////////

static void PrintColorSetCOL
(
    // On start of group: col_name := NULL, col_string := NULL

    FILE		*f,		// valid output file
    int			indent,		// normalized indention of output
    const ColorSet_t	*cs,		// valid color set, never NULL
    uint		mode,		// output mode of PrintColorSetHelper()
    ccp			col_name,	// name of color
    ccp			col_string	// escape string for the color
)
{
    if (!col_name)
	fputc('\n',f);
    else
    {
	DASSERT(col_string);
     #ifdef TEST
	fprintf(f,"%*s %s %s %s | %s %s %s\n", \
			indent, col_name, col_string, col_name, cs->reset,
			GetColorByName(cs,col_name), col_name, cs->reset );
     #else
	fprintf(f,"%*s %s %s %s\n",
			indent, col_name, col_string, col_name, cs->reset );
     #endif
    }
}

//-----------------------------------------------------------------------------

static void PrintColorSetSH
(
    // On start of group: col_name := NULL, col_string := NULL

    FILE		*f,		// valid output file
    int			indent,		// normalized indention of output
    const ColorSet_t	*cs,		// valid color set, never NULL
    uint		mode,		// output mode of PrintColorSetHelper()
    ccp			col_name,	// name of color
    ccp			col_string	// escape string for the color
)
{
    if (col_name)
    {
	DASSERT(col_string);

	char name[50], buf[50];
	char *dest = name;
	while ( *col_name && dest < name + sizeof(name) - 1 )
	    *dest++ = toupper((int)*col_name++);
	*dest = 0;

	PrintEscapedString(buf,sizeof(buf),col_string,-1,CHMD_ESC,0,0);
	if (memcmp(buf,"\\x1B",4))
	    fprintf(f,"COL_%s=$'%s'\n",name,buf);
	else
	    fprintf(f,"COL_%s='\\033%s'\n",name,buf+4);
    }
}

//-----------------------------------------------------------------------------

static void PrintColorSetPHP
(
    // On start of group: col_name := NULL, col_string := NULL

    FILE		*f,		// valid output file
    int			indent,		// normalized indention of output
    const ColorSet_t	*cs,		// valid color set, never NULL
    uint		mode,		// output mode of PrintColorSetHelper()
    ccp			col_name,	// name of color
    ccp			col_string	// escape string for the color
)
{
    if (col_name)
    {
	DASSERT(col_string);

	fprintf(f,"    $COL->%s%.*s= ", col_name, (29-(int)strlen(col_name))/8, Tabs20 );

	char buf[50];
	PrintEscapedString(buf,sizeof(buf),col_string,-1,CHMD_ESC,0,0);
	if (memcmp(buf,"\\x1B",4))
	    fprintf(f,"\"%s\";\n",buf);
	else
	    fprintf(f,"\"\\033%s\";\n",buf+4);
    }
}

//-----------------------------------------------------------------------------

void PrintColorSet
(
    FILE		*f,		// valid output file
    int			indent,		// indention of output
    const ColorSet_t	*cs		// valid color set; if NULL: use std colors
)
{
    DASSERT(f);
    PrintColorSetHelper(f,indent,cs,PrintColorSetCOL,4);
    fputc('\n',f);
}

//-----------------------------------------------------------------------------

void PrintColorSetEx
(
    FILE		*f,		// valid output file
    int			indent,		// indention of output
    const ColorSet_t	*cs,		// valid color set; if NULL: use std colors
    uint		mode,		// output mode => see PrintColorSetHelper()
    uint		format		// output format
					//   0: colored list
					//   1: shell definitions
					//   2: php class
)
{
    DASSERT(f);
    char buf[50];

    switch(format)
    {
	case 1:
	    if (!cs)
		cs = GetColorSet(COLMD_ON);
	    PrintColorSetHelper(f,indent,cs,PrintColorSetSH,mode);
	    PrintEscapedString(buf,sizeof(buf),cs->reset,-1,CHMD_ESC,0,0);
	    if (memcmp(buf,"\\x1B",4))
		fprintf(f,"COL0=$'%s'\n",buf);
	    else
		fprintf(f,"COL0=$'\\033%s'\n",buf+4);
	    break;

	case 2:
	    if (!cs)
		cs = GetColorSet(COLMD_ON);
	    PrintColorSetHelper(f,indent,cs,PrintColorSetPHP,mode);
	    break;

	default:
	    PrintColorSetHelper(f,indent,cs,PrintColorSetCOL,mode);
	    fputc('\n',f);
	    break;
    }
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////			    ViewColor*()		///////////////
///////////////////////////////////////////////////////////////////////////////

void SetupColorView ( ColorView_t *cv )
{
    DASSERT(cv);

    if (!cv->f)
	cv->f = stdout;
    cv->indent = NormalizeIndent(cv->indent);

#ifdef DCLIB_TERMINAL
    cv->col_mode = cv->colset
			? cv->colset->col_mode
			: NormalizeColorMode(cv->col_mode,
						cv->term ? cv->term->colors : 8 );
#else
    cv->col_mode = cv->colset
			? cv->colset->col_mode
			: NormalizeColorMode(cv->col_mode,8);
#endif
    if (!cv->colset)
	cv->colset = GetColorSet(cv->col_mode);

    switch(cv->order)
    {
	case 'r': case 'R': cv->order = 0; break;
	case 'g': case 'G': cv->order = 1; break;
	case 'b': case 'B': cv->order = 2; break;
    }
}

///////////////////////////////////////////////////////////////////////////////

void SetupColorViewMode ( ColorView_t *cv, ColorMode_t col_mode )
{
    DASSERT(cv);
    cv->col_mode = col_mode;
    cv->colset = 0;
    SetupColorView(cv);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static ccp col_names[] =
{
	"black:",
	"red:",
	"green:",
	"yellow:",
	"blue:",
	"magenta:",
	"cyan:",
	"white:",
	0
};

//-----------------------------------------------------------------------------

void ViewColorsAttrib8 ( ColorView_t *cv )
{
    DASSERT(cv);
    SetupColorView(cv);
    DASSERT(cv->colset);

 #ifdef TEST
    fprintf(cv->f,"%*s%s() %s, %u colors, mode %d, stdcol %d, order %d\n",
	cv->indent,"", __FUNCTION__,
	GetColorModeName(cv->colset->col_mode,0),
	cv->colset->n_colors, cv->mode, cv->std_col, cv->order );
 #endif

    //--------------------------------------------------

    fprintf(cv->f,
	"%s\n%*sStandard font colors with attributes (ul=underline) for mode %s:\n\n",
	cv->colset->reset, cv->indent, "",
	GetColorModeName(cv->col_mode,0) );

    uint fg = 0, bg = 0;
    switch( (int)cv->std_col )
    {
	case TCI_BLACK:
	case TCI_DARKGRAY:	fg = TTM_WHITE|TTM_BOLD;    bg = TTM_BG_BLACK; break;
	case TCI_LIGHTGRAY:
	case TCI_WHITE:		fg = TTM_BLACK;		    bg = TTM_BG_WHITE; break;
	case TCI_RED:
	case TCI_B_RED:
	case TCI_ORANGE:
	case TCI_B_ORANGE:	fg = TTM_WHITE|TTM_BOLD;    bg = TTM_BG_RED; break;
	case TCI_YELLOW:
	case TCI_B_YELLOW:	fg = TTM_BLACK;		    bg = TTM_BG_YELLOW; break;
	case TCI_GREEN:
	case TCI_B_GREEN:	fg = TTM_WHITE|TTM_BOLD;    bg = TTM_BG_GREEN; break;
	case TCI_CYAN:
	case TCI_B_CYAN:	fg = TTM_BLACK;		    bg = TTM_BG_CYAN; break;
	case TCI_BLUE:
	case TCI_B_BLUE:	fg = TTM_WHITE|TTM_BOLD;    bg = TTM_BG_BLUE; break;
	case TCI_MAGENTA:
	case TCI_B_MAGENTA:	fg = TTM_WHITE|TTM_BOLD;    bg = TTM_BG_MAGENTA; break;
    }

    ccp *cname;
    TermTextMode_t mode = TTM_BLACK;
    for ( cname = col_names; *cname; cname++, mode += 0x01 )
    {
	fprintf(cv->f,"%*s%s %u %-9s %snormal %sbold %sbold+ul %sul%s reset %s\n",
		cv->indent, "",
		GetTextMode(cv->col_mode,fg|bg),
		(int)(cname - col_names) + 30,
		*cname,
		GetTextMode(cv->col_mode,bg|mode),
		GetTextMode(cv->col_mode,bg|TTM_BOLD),
		GetTextMode(cv->col_mode,bg|TTM_UL),
		GetTextMode(cv->col_mode,bg|TTM_NO_BOLD),
		GetTextMode(cv->col_mode,bg|TTM_RESET),
		cv->colset->reset );
    }

    //--------------------------------------------------

    fprintf(cv->f,
	"\n%*sStandard background colors with attributes (ul=underline) for mode %s:\n\n",
	cv->indent, "", GetColorModeName(cv->col_mode,0) );

    mode = TTM_BG_BLACK;
    for ( cname = col_names; *cname; cname++, mode += 0x10 )
    {
	fprintf(cv->f,"%*s %u %-9s %s white %s bold %sul%s   black %sbold %sul%s %s\n",
		cv->indent, "",
		(int)(cname - col_names) + 40,
		*cname,
		GetTextMode(cv->col_mode,mode|TTM_WHITE),
		GetTextMode(cv->col_mode,TTM_BOLD),
		GetTextMode(cv->col_mode,TTM_UL|TTM_NO_BOLD),
		GetTextMode(cv->col_mode,mode|TTM_BLACK|TTM_RESET),
		GetTextMode(cv->col_mode,TTM_BOLD),
		GetTextMode(cv->col_mode,TTM_UL|TTM_NO_BOLD),
		GetTextMode(cv->col_mode,TTM_NO_UL),
		GetTextMode(cv->col_mode,TTM_RESET) );
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void ViewColorsCombi8 ( ColorView_t *cv )
{
    DASSERT(cv);
    SetupColorView(cv);
    DASSERT(cv->colset);

 #ifdef TEST
    fprintf(cv->f,"%*s%s() %s, %u colors, mode %d, stdcol %d, order %d\n",
	cv->indent,"", __FUNCTION__,
	GetColorModeName(cv->colset->col_mode,0),
	cv->colset->n_colors, cv->mode, cv->std_col, cv->order );
 #endif

    fprintf(cv->f,
	"%s\n%*sFont and background color combinations (no=normal, bo=bold) for mode %s:\n\n",
	cv->colset->reset, cv->indent, "",
	GetColorModeName(cv->col_mode,0) );

    uint mode = TTM_BG_BLACK;
    ccp *cname;
    for ( cname = col_names; *cname; cname++, mode += 0x10 )
    {
	fprintf(cv->f,"%*s %u %-9s ",
		cv->indent, "",
		(int)(cname - col_names) + 40,
		*cname );

	TermTextMode_t mode2;
	for ( mode2 = TTM_BLACK; mode2 <= TTM_WHITE; mode2++ )
	    fprintf(cv->f,"%s no %sbo ",
		GetTextMode(cv->col_mode,mode|mode2|TTM_NO_BOLD),
		GetTextMode(cv->col_mode,TTM_BOLD) );
	fprintf(cv->f," %s\n",cv->colset->reset );
    }
}

///////////////////////////////////////////////////////////////////////////////

void ViewColors18 ( ColorView_t *cv )
{
    DASSERT(cv);
    SetupColorView(cv);
    DASSERT(cv->colset);

 #ifdef TEST
    fprintf(cv->f,"%*s%s() %s, %u colors, mode %d, stdcol %d, order %d\n",
	cv->indent,"", __FUNCTION__,
	GetColorModeName(cv->colset->col_mode,0),
	cv->colset->n_colors, cv->mode, cv->std_col, cv->order );
 #endif

    GetColorOption_t col_option = cv->col_option & ~GCM_ALT;

    fprintf(cv->f,
	"%s\n%*s18x18 color table ('0'=std, '1'=optimized%s) for mode %s:\n\n",
	cv->colset->reset, cv->indent, "",
	col_option & GCM_SHORT ? "; allow short codes" : "",
	GetColorModeName(cv->col_mode,0) );

    const int *pbg;
    for ( pbg = Color18Index; *pbg >= 0; pbg++ )
    {
	uint bg = *pbg;
	if ( bg == TCI_RED || bg == TCI_B_RED )
		fputc('\n',cv->f);
	fprintf(cv->f,"%*s %-12s ",
		cv->indent, "", ColorIndexName[bg] );

	const int *pfont;
	for ( pfont = Color18Index; *pfont >= 0; pfont++ )
	{
	    uint font = *pfont;
	    if ( font == TCI_RED || font == TCI_B_RED )
		fprintf(cv->f," %s ",TERM_TEXT_MODE_RESET);
	    fprintf(cv->f,"%s 0%s1",
		GetColorMode(cv->col_mode,font,bg,col_option),
		GetColorMode(cv->col_mode,font,bg,col_option|GCM_ALT) );
	}
	fprintf(cv->f," %s\n",TERM_TEXT_MODE_RESET);
    }
}

///////////////////////////////////////////////////////////////////////////////

void ViewColorsDC ( ColorView_t *cv, bool optimized )
{
    DASSERT(cv);
    SetupColorView(cv);
    DASSERT(cv->colset);

 #ifdef TEST
    fprintf(cv->f,"%*s%s() %s, %u colors, mode %d, stdcol %d, order %d\n",
	cv->indent,"", __FUNCTION__,
	GetColorModeName(cv->colset->col_mode,0),
	cv->colset->n_colors, cv->mode, cv->std_col, cv->order );
 #endif

    GetColorOption_t col_option = cv->col_option & ~GCM_ALT;
    if (optimized)
	col_option |= GCM_ALT;

    fprintf(cv->f,
	"%s\n%*s%ux%u color table (%s%s) for mode %s:\n\n",
	cv->colset->reset, cv->indent, "",
	TCI__N, TCI__N,
	optimized ? "optimized" : "standard",
	col_option & GCM_SHORT ? "; allow short codes" : "",
	GetColorModeName(cv->col_mode,0) );

    uint bg;
    for ( bg = 0; bg < TCI__N; bg++ )
    {
	if ( bg == TCI_RED || bg == TCI_B_RED )
		fputc('\n',cv->f);
	fprintf(cv->f,"%*s %-15s ",
		cv->indent, "", ColorIndexName[bg] );

	ccp fill = " ";
	uint font;
	for ( font = 0; font < TCI__N; font++ )
	{
	    if ( font == TCI_RED || font == TCI_B_RED )
	    {
		fprintf(cv->f," %s ",TERM_TEXT_MODE_RESET);
		fill = " ";
	    }
	    fprintf(cv->f,"%s%sx",
		GetColorMode(cv->col_mode,font,bg,col_option), fill );
	    fill = "";
	}
	fprintf(cv->f," %s\n",TERM_TEXT_MODE_RESET);
    }
}

///////////////////////////////////////////////////////////////////////////////

static void ViewColors256_helper
(
    ColorView_t		*cv,		// basic data
    uint		beg,		// first color printed
    uint		end,		// first color not printed
    uint		step		// increment
)
{
    if ( cv->colset->n_colors < 8 )
    {
	uint i;
	for ( i = beg; i < end; i += step )
		fprintf(cv->f," %03u ",i);
    }
 #if 0 // [[2do]]
    else if ( cv->colset->n_colors < 256 )
    {
    }
 #endif
    else
    {
	const int mode = cv->mode & 1 ? 48 : 38;

	uint i;
	for ( i = beg; i < end; i += step )
		fprintf(cv->f,"\e[%u;5;%um %03u ",mode,i,i);
	fputs("\e[0m",cv->f);
    }
}

//-----------------------------------------------------------------------------

void ViewColors256 ( ColorView_t *cv )
{
    DASSERT(cv);
    SetupColorView(cv);
    DASSERT(cv->colset);

 #ifdef TEST
    fprintf(cv->f,"%*s%s() %s, %u colors, mode %d, stdcol %d, order %d\n",
	cv->indent,"", __FUNCTION__,
	GetColorModeName(cv->colset->col_mode,0),
	cv->colset->n_colors, cv->mode, cv->std_col, cv->order );
 #endif

    fprintf(cv->f,
	"%s\n%*s256 colors = 16 std colors + 6x6x6 colors + 24 gray for mode %s:\n",
	cv->colset->reset, cv->indent, "",
	GetColorModeName(cv->col_mode,0) );

    int step, inc_horz, inc_vert;
    switch (cv->order)
    {
	case 1:
	    step      =  1;
	    inc_horz  =  6;
	    inc_vert  = 36;
	    break;

	case 2:
	    step      =  6;
	    inc_horz  =  1;
	    inc_vert  = 36;
	    break;

	default:
	    step      =  1;
	    inc_horz  = 36;
	    inc_vert  =  6;
	    break;
    }

    //--- 16 standard colors in 2 rows

    fprintf(cv->f,"\n%*s ",cv->indent,"");
    ViewColors256_helper(cv,0,8,1);
    fprintf(cv->f,"\n%*s ",cv->indent,"");
    ViewColors256_helper(cv,8,16,1);
    fputs("\e[0m\n\n",cv->f);

    uint bl, num = 16;

    for ( bl = 0; bl < 3; bl++ )
    {
	uint i, n = num;
	for ( i = 0; i < 6; i++ )
	{
	    fprintf(cv->f,"%*s ",cv->indent,"");
	    ViewColors256_helper(cv,n,n+6*step,step);
	    fputs("  ",cv->f);

	    ViewColors256_helper(cv,n+inc_horz,n+inc_horz+6*step,step);
	    fputc('\n',cv->f);
	    n += inc_vert;
	}

	fputc('\n',cv->f);
	num += 2*inc_horz;
    }

    fprintf(cv->f,"%*s ",cv->indent,"");
    ViewColors256_helper(cv,232,232+12,1);
    fprintf(cv->f,"\n%*s ",cv->indent,"");
    ViewColors256_helper(cv,232+12,232+24,1);
    fputs("\e[0m\n",cv->f);
}

///////////////////////////////////////////////////////////////////////////////

static void ViewColorsPredef_helper
(
    ColorView_t		*cv,		// basic data
    ccp			col_name,	// name of color
    ccp			col_string	// escape string for the color
)
{
    DASSERT(cv);
    DASSERT(col_string);

    if ( col_string && *col_string )
	fprintf(cv->f,"%*s %s %-15s %s \\e%s\n",
		cv->indent, col_name, col_string, col_name,
		cv->colset->reset, col_string+1 );
    else
	fprintf(cv->f,"%*s  %s\n",
		cv->indent, col_name, col_name );
}

//-----------------------------------------------------------------------------

void ViewColorsPredef ( ColorView_t *cv, uint mode )
{
    // [[new-color]]

    DASSERT(cv);
    SetupColorView(cv);
    DASSERT(cv->colset);

 #ifdef TEST
    fprintf(cv->f,"%*s%s() %s, %u colors, mode %d, stdcol %d, order %d\n",
	cv->indent,"", __FUNCTION__,
	GetColorModeName(cv->colset->col_mode,0),
	cv->colset->n_colors, cv->mode, cv->std_col, cv->order );
 #endif

    fprintf(cv->f,
	"%s\n%*sPredefined%s color names for mode %s:\n\n",
	cv->colset->reset, cv->indent, "",
	( mode & 3 ) == 1 ? " semantic" : "",
	GetColorModeName(cv->col_mode,0) );

    cv->indent += 14;

    #undef JOB1
    #undef JOB2
    #define JOB1(n)   ViewColorsPredef_helper(cv,#n,cv->colset->n)
    #define JOB2(n,c) ViewColorsPredef_helper(cv,#n,cv->colset->c)

    if ( mode & 1 )
    {
	const bool alt = cv->mode & 1;

	JOB1(setup);
	JOB1(run);
	JOB1(abort);
	JOB1(finish);
	JOB1(script);
	JOB1(open);
	JOB1(close);
	JOB1(file);
	JOB1(job);

	JOB1(info);
	JOB1(hint);
	JOB1(warn);
	JOB1(debug);
	JOB1(log);

	JOB1(name);
	JOB1(op);
	JOB1(value);	if (alt) JOB2(val,value);
	JOB1(success);
	JOB1(error);
	JOB1(fail);
	JOB1(fail2);
	JOB1(fatal);
	JOB1(mark);
	JOB1(bad);

	JOB1(select);
	JOB1(differ);
	JOB1(stat_line);
	JOB1(warn_line);
	JOB1(proc_line);
	JOB1(cite);
	JOB1(status);
	JOB1(highlight); if (alt) JOB2(hl,highlight);
	JOB1(hide);

	JOB1(heading);
	JOB1(caption);
	JOB1(section);
	JOB1(syntax);
	JOB1(cmd);
	JOB1(option);	if (alt) JOB2(opt,option);
	JOB1(param);	if (alt) JOB2(par,param);

	JOB1(off);
	JOB1(on);
    }

    if ( mode & 2 )
    {
	if ( mode & 1 )
	    fputc('\n',cv->f);
	JOB1(black);
	JOB1(b_black);
	JOB1(white);
	JOB1(b_white);

	if ( !(mode & 1) )
	    fputc('\n',cv->f);
	JOB1(red);
	JOB1(red_orange);
	JOB1(orange);
	JOB1(orange_yellow);
	JOB1(yellow);
	JOB1(yellow_green);
	JOB1(green);
	JOB1(green_cyan);
	JOB1(cyan);
	JOB1(cyan_blue);
	JOB1(blue);
	JOB1(blue_magenta);
	JOB1(magenta);
	JOB1(magenta_red);
	JOB1(red);

	if ( !(mode & 1) )
	    fputc('\n',cv->f);
	JOB1(b_red);
	JOB1(b_red_orange);
	JOB1(b_orange);
	JOB1(b_orange_yellow);
	JOB1(b_yellow);
	JOB1(b_yellow_green);
	JOB1(b_green);
	JOB1(b_green_cyan);
	JOB1(b_cyan);
	JOB1(b_cyan_blue);
	JOB1(b_blue);
	JOB1(b_blue_magenta);
	JOB1(b_magenta);
	JOB1(b_magenta_red);
	JOB1(b_red);
    }

    #undef JOB1
    #undef JOB2
    cv->indent -= 14;
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////		    old color views (wrapper)		///////////////
///////////////////////////////////////////////////////////////////////////////

void PrintTextModes
(
    FILE	*f,		// valid output file
    int		indent,		// indention of output
    ColorMode_t	col_mode	// color mode
)
{
    ColorView_t cv;
    InitializeColorView(&cv);
    cv.f	= f;
    cv.indent	= indent;
    cv.col_mode	= col_mode;
    ViewColorsAttrib8(&cv);
    ViewColorsCombi8(&cv);
}

///////////////////////////////////////////////////////////////////////////////

void PrintColorModes
(
    FILE		*f,		// valid output file
    int			indent,		// indention of output
    ColorMode_t		col_mode,	// color mode -> NormalizeColorMode()
    GetColorOption_t	option		// execution options (GCM_ALT ignored)
)
{
    ColorView_t cv;
    InitializeColorView(&cv);
    cv.f		= f;
    cv.indent		= indent;
    cv.col_mode		= col_mode;
    cv.col_option	= option;
    ViewColors18(&cv);
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////		stdout, stderr, stdlog and colors	///////////////
///////////////////////////////////////////////////////////////////////////////

FILE *stdlog		= 0;	// NULL or logfile
bool close_stdlog	= 0;	// true: close file behing 'stdlog'

FILE *stdmsg		= 0;	// 'stdlog' or 'stdout' or 'stderr' or NULL
FILE *stdwrn		= 0;	// used by PrintError(), initialized with 'stderr'

ColorMode_t colorize_stdout	= COLMD_AUTO;
ColorMode_t colorize_stderr	= COLMD_AUTO;
ColorMode_t colorize_stdlog	= COLMD_AUTO;
ColorMode_t colorize_stdmsg	= COLMD_AUTO;
ColorMode_t colorize_stdwrn	= COLMD_AUTO;

const ColorSet_t *colout = 0;	// color set for 'stdout'
const ColorSet_t *colerr = 0;	// color set for 'stderr'
const ColorSet_t *collog = 0;	// color set for 'stdlog'
const ColorSet_t *colmsg = 0;	// color set for 'stdmsg'
const ColorSet_t *colwrn = 0;	// color set for 'stdwrn'

///////////////////////////////////////////////////////////////////////////////

ColorMode_t GetFileColorized ( FILE *f )
{
    if (!stdmsg)
	SetupStdMsg();

    return !f						? COLMD_OFF
	 : f == stdlog && colorize_stdlog != COLMD_AUTO	? colorize_stdlog
	 : f == stdout && colorize_stdout != COLMD_AUTO	? colorize_stdout
	 : f == stderr && colorize_stderr != COLMD_AUTO	? colorize_stderr
	 : f == stdmsg && colorize_stdmsg != COLMD_AUTO	? colorize_stdmsg
	 : f == stdwrn && colorize_stdwrn != COLMD_AUTO	? colorize_stdwrn
	 : opt_colorize >= COLMD_ON			? opt_colorize
	 : opt_colorize == COLMD_AUTO && isatty(fileno(f))
							? COLMD_AUTO
	 : COLMD_OFF;
}

///////////////////////////////////////////////////////////////////////////////

void SetupStdMsg()
{
    //--- setup

    static bool active = false; // avoid loops
    if (!active)
    {
	active = true;

	stdwrn = stderr;
	colwrn = colerr;
	colorize_stdwrn = colorize_stderr;

	if (!colout)
	{
	    colorize_stdout = GetFileColorized(stdout);
	    colout = GetColorSet(colorize_stdout);
	}

	if (!colerr)
	{
	    colorize_stderr = GetFileColorized(stderr);
	    colerr = GetColorSet(colorize_stderr);
	}

	if (!collog)
	{
	    colorize_stdlog = GetFileColorized(stdlog);
	    collog = GetColorSet(colorize_stdlog);
	}

	active = false;
    }

    //--- assign to msg

    if (stdlog)
    {
	stdmsg = stdlog;
	colmsg = collog;
	colorize_stdmsg = colorize_stdlog;
    }
    else if (stdout)
    {
	stdmsg = stdout;
	colmsg = colout;
	colorize_stdmsg = colorize_stdout;
    }
    else if (stderr)
    {
	stdmsg = stderr;
	colmsg = colerr;
	colorize_stdmsg = colorize_stderr;
    }
    else
    {
	stdmsg = 0;
	colmsg = GetColorSet0();
	colorize_stdmsg = 0;
    }

    noPRINT("SetupStdMsg() : out=%d[%zd], err=%d[%zd], log=%d[%zd], msg=%d[%zd]\n",
	colorize_stdout, colout ? strlen(colout->reset) : -1,
	colorize_stderr, colerr ? strlen(colerr->reset) : -1,
	colorize_stdlog, collog ? strlen(collog->reset) : -1,
	colorize_stdmsg, colmsg ? strlen(colmsg->reset) : -1 );
}

///////////////////////////////////////////////////////////////////////////////

enumError OpenStdLog
(
    ccp fname,		// If NULL or empty: don't open and use 'fallback'
			// If first char == '+': open file in append mode
    FILE *fallback	// Fall back to this file, if no file name given
			// If NULL: just clode 'stdlog'.
)
{
    CloseStdLog();

    bool append = fname && *fname == '+';
    if (append)
	fname++;

    if ( !fname || !*fname )
    {
	if (fallback)
	{
	    stdlog = fallback;
	    colorize_stdlog = GetFileColorized(stdlog);
	    PRINT("COLORIZE/LOG/FALLBACK: opt=%d, out=%d, err=%d, log=%d\n",
		opt_colorize, colorize_stdout, colorize_stderr, colorize_stdlog );
	}
    }
    else
    {
	if (!strcmp(fname,"-"))
	{
	    stdlog = stdout;
	    colorize_stdlog = colorize_stdout;
	}
	else
	{
	    stdlog = fopen( fname, append ? "ab" : "wb" );
	    if (!stdlog)
		return ERROR1(ERR_CANT_CREATE,
			"Can't open log file (mode=%s): %s\n",
			append ? "append" : "create", fname );

	    close_stdlog = true;
	    colorize_stdlog = GetFileColorized(stdlog);
	}

	PRINT("COLORIZE/LOG: opt=%d, out=%d, err=%d, log=%d\n",
	    opt_colorize, colorize_stdout, colorize_stderr, colorize_stdlog );
    }

    collog = GetColorSet(colorize_stdlog);
    SetupStdMsg();
    return ERR_OK;
}

///////////////////////////////////////////////////////////////////////////////

void CloseStdLog()
{
    if (stdlog)
    {
	if (close_stdlog)
	    fclose(stdlog);
	else
	    fflush(stdlog);
	stdlog = 0;
    }

    close_stdlog = false;
    colorize_stdlog = 0;
    collog = GetColorSet0();

    SetupStdMsg();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void SaveStdFiles ( SavedStdFiles_t *ssf )
{
    DASSERT(ssf);

    ssf->std_out = stdout;
    ssf->std_err = stderr;
    ssf->std_log = stdlog;
    ssf->std_msg = stdmsg;
    ssf->std_wrn = stdwrn;

    ssf->col_out = colout;
    ssf->col_err = colerr;
    ssf->col_log = collog;
    ssf->col_msg = colmsg;
    ssf->col_wrn = colwrn;

    ssf->stdout_seq_count = stdout_seq_count;

    ssf->f	= 0;
    ssf->data	= 0;
    ssf->size	= 0;
    ssf->marker	= 0;
}

///////////////////////////////////////////////////////////////////////////////

void RestoreStdFiles ( SavedStdFiles_t *ssf )
{
    DASSERT(ssf);

    stdout = ssf->std_out;
    stderr = ssf->std_err;
    stdlog = ssf->std_log;
    stdmsg = ssf->std_msg;
    stdwrn = ssf->std_wrn;

    colout = ssf->col_out;
    colerr = ssf->col_err;
    collog = ssf->col_log;
    colmsg = ssf->col_msg;
    colwrn = ssf->col_wrn;

    stdout_seq_count = ssf->stdout_seq_count;
}

///////////////////////////////////////////////////////////////////////////////

void RedirectStdFiles
(
    SavedStdFiles_t	*ssf,	// not NULL: save old output here
    FILE		*f,	// use this as out,err,log and msg, never NULL
    const ColorSet_t	*colset,// new colset; if NULL: use GetFileColorSet(f)
    bool		err_too	// true: redirect stderr too
)
{
    DASSERT(f);
    if (ssf)
	SaveStdFiles(ssf);

    stdout = stdwrn = stdmsg = f;
    colout = colwrn = colmsg = colset ? colset : GetFileColorSet(f);

    // special handling for stdlog
    if (stdlog)
    {
	stdlog = stdout;
	collog = colout;
    }

    if (err_too)
    {
	stderr = stdout;
	colerr = colout;
    }
}

///////////////////////////////////////////////////////////////////////////////
#ifndef __APPLE__

enumError CatchStdFiles
(
    SavedStdFiles_t	*ssf,	// save old output and data here, never NULL
    const ColorSet_t	*colset	// new colset; if NULL: no color support
)
{
    DASSERT(ssf);
    SaveStdFiles(ssf);
    FILE *f = open_memstream(&ssf->data,&ssf->size);
    if (!f)
	return ERR_CANT_CREATE;

    ssf->f = f;
    RedirectStdFiles(0,f,colset,false);
    return ERR_OK;
}

#endif // !__APPLE__
///////////////////////////////////////////////////////////////////////////////

void TermCatchStdFiles ( SavedStdFiles_t *ssf )
{
    DASSERT(ssf);
    RestoreStdFiles(ssf);
    if (ssf->f)
    {
	fclose(ssf->f);
	ssf->f = 0;
    }
}

//
///////////////////////////////////////////////////////////////////////////////
///////////////				END			///////////////
///////////////////////////////////////////////////////////////////////////////

