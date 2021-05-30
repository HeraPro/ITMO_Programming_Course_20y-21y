#pragma once

#ifndef _GEOMETRY_H_INCLUDED_
#define _GEOMETRY_H_INCLUDED_

#ifdef MODE_OPENGL

enum BitmapFontType
{
    BITMAP_FONT_TYPE_8_BY_13,
    BITMAP_FONT_TYPE_9_BY_15,
    BITMAP_FONT_TYPE_HELVETICA_10,
    BITMAP_FONT_TYPE_HELVETICA_12,
    BITMAP_FONT_TYPE_HELVETICA_18,
    BITMAP_FONT_TYPE_TIMES_ROMAN_10,
    BITMAP_FONT_TYPE_TIMES_ROMAN_24
};

struct BitmapFontData
{
    char*           Name;         /* The source font name             */
    int             Quantity;     /* Number of chars in font          */
    int             Height;       /* Height of the characters         */
    const GLubyte** Characters;   /* The characters mapping           */

    float           xorig, yorig; /* Relative origin of the character */
};

class GeometryProvider
{
	public:
		void renderGridColor( GLdouble dSize, double red, double green, double blue);
		void renderCubeColor( GLdouble dSize, double color);
		void renderTextFull(float x, float y, char *str);
		void renderSide(struct mycolor *colors);
		void renderSideCells();
		void renderGrid(float y, float range);

	private:
		void beginRenderText(int nWindowWidth, int nWindowHeight);
		void endRenderText( void );
		void renderText( float x, float y, BitmapFontType fontType, char *string );
		const BitmapFontData* getBitmapFontDataByType( BitmapFontType font );
};

//-----------------------------------------------------------------------------

/*
 * freeglut_geometry.c
 *
 * Freeglut geometry rendering methods.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Fri Dec 3 1999
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <GL/gl.h>

/* The font structure: */

static const GLubyte Helvetica10_Character_032[] = {  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; /* " " */
static const GLubyte Helvetica10_Character_097[] = {  5,  0,  0,104,144,144,112, 16,224,  0,  0,  0,  0,  0}; /* "a" */
static const GLubyte Helvetica10_Character_098[] = {  6,  0,  0,176,200,136,136,200,176,128,128,  0,  0,  0}; /* "b" */
static const GLubyte Helvetica10_Character_099[] = {  5,  0,  0, 96,144,128,128,144, 96,  0,  0,  0,  0,  0}; /* "c" */
static const GLubyte Helvetica10_Character_100[] = {  6,  0,  0,104,152,136,136,152,104,  8,  8,  0,  0,  0}; /* "d" */
static const GLubyte Helvetica10_Character_101[] = {  5,  0,  0, 96,144,128,240,144, 96,  0,  0,  0,  0,  0}; /* "e" */
static const GLubyte Helvetica10_Character_102[] = {  4,  0,  0, 64, 64, 64, 64, 64,224, 64, 48,  0,  0,  0}; /* "f" */
static const GLubyte Helvetica10_Character_103[] = {  6,112,  8,104,152,136,136,152,104,  0,  0,  0,  0,  0}; /* "g" */
static const GLubyte Helvetica10_Character_104[] = {  6,  0,  0,136,136,136,136,200,176,128,128,  0,  0,  0}; /* "h" */
static const GLubyte Helvetica10_Character_105[] = {  2,  0,  0,128,128,128,128,128,128,  0,128,  0,  0,  0}; /* "i" */
static const GLubyte Helvetica10_Character_106[] = {  2,  0,128,128,128,128,128,128,128,  0,128,  0,  0,  0}; /* "j" */
static const GLubyte Helvetica10_Character_107[] = {  5,  0,  0,144,144,160,192,160,144,128,128,  0,  0,  0}; /* "k" */
static const GLubyte Helvetica10_Character_108[] = {  2,  0,  0,128,128,128,128,128,128,128,128,  0,  0,  0}; /* "l" */
static const GLubyte Helvetica10_Character_109[] = {  8,  0,  0,146,146,146,146,146,236,  0,  0,  0,  0,  0}; /* "m" */
static const GLubyte Helvetica10_Character_110[] = {  6,  0,  0,136,136,136,136,200,176,  0,  0,  0,  0,  0}; /* "n" */
static const GLubyte Helvetica10_Character_111[] = {  6,  0,  0,112,136,136,136,136,112,  0,  0,  0,  0,  0}; /* "o" */
static const GLubyte Helvetica10_Character_112[] = {  6,128,128,176,200,136,136,200,176,  0,  0,  0,  0,  0}; /* "p" */
static const GLubyte Helvetica10_Character_113[] = {  6,  8,  8,104,152,136,136,152,104,  0,  0,  0,  0,  0}; /* "q" */
static const GLubyte Helvetica10_Character_114[] = {  4,  0,  0,128,128,128,128,192,160,  0,  0,  0,  0,  0}; /* "r" */
static const GLubyte Helvetica10_Character_115[] = {  5,  0,  0, 96,144, 16, 96,144, 96,  0,  0,  0,  0,  0}; /* "s" */
static const GLubyte Helvetica10_Character_116[] = {  4,  0,  0, 96, 64, 64, 64, 64,224, 64, 64,  0,  0,  0}; /* "t" */
static const GLubyte Helvetica10_Character_117[] = {  5,  0,  0,112,144,144,144,144,144,  0,  0,  0,  0,  0}; /* "u" */
static const GLubyte Helvetica10_Character_118[] = {  6,  0,  0, 32, 32, 80, 80,136,136,  0,  0,  0,  0,  0}; /* "v" */
static const GLubyte Helvetica10_Character_119[] = {  8,  0,  0, 40, 40, 84, 84,146,146,  0,  0,  0,  0,  0}; /* "w" */
static const GLubyte Helvetica10_Character_120[] = {  6,  0,  0,136,136, 80, 32, 80,136,  0,  0,  0,  0,  0}; /* "x" */
static const GLubyte Helvetica10_Character_121[] = {  5,128, 64, 64, 96,160,160,144,144,  0,  0,  0,  0,  0}; /* "y" */
static const GLubyte Helvetica10_Character_122[] = {  5,  0,  0,240,128, 64, 32, 16,240,  0,  0,  0,  0,  0}; /* "z" */
static const GLubyte Helvetica10_Character_065[] = {  7,  0,  0,130,130,124, 68, 40, 40, 16, 16,  0,  0,  0}; /* "A" */
static const GLubyte Helvetica10_Character_066[] = {  7,  0,  0,240,136,136,136,240,136,136,240,  0,  0,  0}; /* "B" */
static const GLubyte Helvetica10_Character_067[] = {  8,  0,  0,120,132,128,128,128,128,132,120,  0,  0,  0}; /* "C" */
static const GLubyte Helvetica10_Character_068[] = {  8,  0,  0,240,136,132,132,132,132,136,240,  0,  0,  0}; /* "D" */
static const GLubyte Helvetica10_Character_069[] = {  7,  0,  0,248,128,128,128,248,128,128,248,  0,  0,  0}; /* "E" */
static const GLubyte Helvetica10_Character_070[] = {  6,  0,  0,128,128,128,128,240,128,128,248,  0,  0,  0}; /* "F" */
static const GLubyte Helvetica10_Character_071[] = {  8,  0,  0,116,140,132,140,128,128,132,120,  0,  0,  0}; /* "G" */
static const GLubyte Helvetica10_Character_072[] = {  8,  0,  0,132,132,132,132,252,132,132,132,  0,  0,  0}; /* "H" */
static const GLubyte Helvetica10_Character_073[] = {  3,  0,  0,128,128,128,128,128,128,128,128,  0,  0,  0}; /* "I" */
static const GLubyte Helvetica10_Character_074[] = {  5,  0,  0, 96,144, 16, 16, 16, 16, 16, 16,  0,  0,  0}; /* "J" */
static const GLubyte Helvetica10_Character_075[] = {  7,  0,  0,136,136,144,144,224,160,144,136,  0,  0,  0}; /* "K" */
static const GLubyte Helvetica10_Character_076[] = {  6,  0,  0,240,128,128,128,128,128,128,128,  0,  0,  0}; /* "L" */
static const GLubyte Helvetica10_Character_077[] = {  9,  0,  0,  0,  0,146,  0,146,  0,146,  0,170,  0,170,  0,198,  0,198,  0,130,  0,  0,  0,  0,  0,  0,  0}; /* "M" */
static const GLubyte Helvetica10_Character_078[] = {  8,  0,  0,140,140,148,148,164,164,196,196,  0,  0,  0}; /* "N" */
static const GLubyte Helvetica10_Character_079[] = {  8,  0,  0,120,132,132,132,132,132,132,120,  0,  0,  0}; /* "O" */
static const GLubyte Helvetica10_Character_080[] = {  7,  0,  0,128,128,128,128,240,136,136,240,  0,  0,  0}; /* "P" */
static const GLubyte Helvetica10_Character_081[] = {  8,  0,  2,124,140,148,132,132,132,132,120,  0,  0,  0}; /* "Q" */
static const GLubyte Helvetica10_Character_082[] = {  7,  0,  0,136,136,136,136,240,136,136,240,  0,  0,  0}; /* "R" */
static const GLubyte Helvetica10_Character_083[] = {  7,  0,  0,112,136,136,  8,112,128,136,112,  0,  0,  0}; /* "S" */
static const GLubyte Helvetica10_Character_084[] = {  5,  0,  0, 32, 32, 32, 32, 32, 32, 32,248,  0,  0,  0}; /* "T" */
static const GLubyte Helvetica10_Character_085[] = {  8,  0,  0,120,132,132,132,132,132,132,132,  0,  0,  0}; /* "U" */
static const GLubyte Helvetica10_Character_086[] = {  7,  0,  0, 16, 40, 40, 68, 68, 68,130,130,  0,  0,  0}; /* "V" */
static const GLubyte Helvetica10_Character_087[] = {  9,  0,  0,  0,  0, 34,  0, 34,  0, 34,  0, 85,  0, 73,  0, 73,  0,136,128,136,128,  0,  0,  0,  0,  0,  0}; /* "W" */
static const GLubyte Helvetica10_Character_088[] = {  7,  0,  0,136,136, 80, 80, 32, 80,136,136,  0,  0,  0}; /* "X" */
static const GLubyte Helvetica10_Character_089[] = {  7,  0,  0, 16, 16, 16, 40, 40, 68, 68,130,  0,  0,  0}; /* "Y" */
static const GLubyte Helvetica10_Character_090[] = {  7,  0,  0,248,128, 64, 32, 32, 16,  8,248,  0,  0,  0}; /* "Z" */
static const GLubyte Helvetica10_Character_048[] = {  6,  0,  0,112,136,136,136,136,136,136,112,  0,  0,  0}; /* "0" */
static const GLubyte Helvetica10_Character_049[] = {  6,  0,  0, 64, 64, 64, 64, 64, 64,192, 64,  0,  0,  0}; /* "1" */
static const GLubyte Helvetica10_Character_050[] = {  6,  0,  0,248,128, 64, 48,  8,  8,136,112,  0,  0,  0}; /* "2" */
static const GLubyte Helvetica10_Character_051[] = {  6,  0,  0,112,136,  8,  8, 48,  8,136,112,  0,  0,  0}; /* "3" */
static const GLubyte Helvetica10_Character_052[] = {  6,  0,  0, 16, 16,248,144, 80, 80, 48, 16,  0,  0,  0}; /* "4" */
static const GLubyte Helvetica10_Character_053[] = {  6,  0,  0,112,136,  8,  8,240,128,128,248,  0,  0,  0}; /* "5" */
static const GLubyte Helvetica10_Character_054[] = {  6,  0,  0,112,136,136,200,176,128,136,112,  0,  0,  0}; /* "6" */
static const GLubyte Helvetica10_Character_055[] = {  6,  0,  0, 64, 64, 32, 32, 16, 16,  8,248,  0,  0,  0}; /* "7" */
static const GLubyte Helvetica10_Character_056[] = {  6,  0,  0,112,136,136,136,112,136,136,112,  0,  0,  0}; /* "8" */
static const GLubyte Helvetica10_Character_057[] = {  6,  0,  0,112,136,  8,104,152,136,136,112,  0,  0,  0}; /* "9" */
static const GLubyte Helvetica10_Character_096[] = {  3,  0,  0,  0,  0,  0,  0,  0,128,128, 64,  0,  0,  0}; /* "`" */
static const GLubyte Helvetica10_Character_126[] = {  7,  0,  0,  0,  0,  0,152,100,  0,  0,  0,  0,  0,  0}; /* "~" */
static const GLubyte Helvetica10_Character_033[] = {  3,  0,  0,128,  0,128,128,128,128,128,128,  0,  0,  0}; /* "!" */
static const GLubyte Helvetica10_Character_064[] = { 11, 62,  0, 64,  0,155,  0,164,128,164,128,162, 64,146, 64, 77, 64, 32,128, 31,  0,  0,  0,  0,  0,  0,  0}; /* "@" */
static const GLubyte Helvetica10_Character_035[] = {  6,  0,  0, 80, 80,248, 40,124, 40, 40,  0,  0,  0,  0}; /* "#" */
static const GLubyte Helvetica10_Character_036[] = {  6,  0, 32,112,168, 40,112,160,168,112, 32,  0,  0,  0}; /* "$" */
static const GLubyte Helvetica10_Character_037[] = {  9,  0,  0,  0,  0, 38,  0, 41,  0, 22,  0, 16,  0,  8,  0,104,  0,148,  0,100,  0,  0,  0,  0,  0,  0,  0}; /* "%" */
static const GLubyte Helvetica10_Character_094[] = {  6,  0,  0,  0,  0,  0,136, 80, 80, 32, 32,  0,  0,  0}; /* "^" */
static const GLubyte Helvetica10_Character_038[] = {  8,  0,  0,100,152,152,164, 96, 80, 80, 32,  0,  0,  0}; /* "&" */
static const GLubyte Helvetica10_Character_042[] = {  4,  0,  0,  0,  0,  0,  0,  0,160, 64,160,  0,  0,  0}; /* "*" */
static const GLubyte Helvetica10_Character_040[] = {  4, 32, 64, 64,128,128,128,128, 64, 64, 32,  0,  0,  0}; /* "(" */
static const GLubyte Helvetica10_Character_041[] = {  4,128, 64, 64, 32, 32, 32, 32, 64, 64,128,  0,  0,  0}; /* ")" */
static const GLubyte Helvetica10_Character_045[] = {  7,  0,  0,  0,  0,  0,248,  0,  0,  0,  0,  0,  0,  0}; /* "-" */
static const GLubyte Helvetica10_Character_095[] = {  6,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; /* "_" */
static const GLubyte Helvetica10_Character_061[] = {  5,  0,  0,  0,  0,240,  0,240,  0,  0,  0,  0,  0,  0}; /* "=" */
static const GLubyte Helvetica10_Character_043[] = {  6,  0,  0,  0, 32, 32,248, 32, 32,  0,  0,  0,  0,  0}; /* "+" */
static const GLubyte Helvetica10_Character_091[] = {  3,192,128,128,128,128,128,128,128,128,192,  0,  0,  0}; /* "[" */
static const GLubyte Helvetica10_Character_123[] = {  3, 32, 64, 64, 64, 64,128, 64, 64, 64, 32,  0,  0,  0}; /* "{" */
static const GLubyte Helvetica10_Character_125[] = {  3,128, 64, 64, 64, 64, 32, 64, 64, 64,128,  0,  0,  0}; /* "}" */
static const GLubyte Helvetica10_Character_093[] = {  3,192, 64, 64, 64, 64, 64, 64, 64, 64,192,  0,  0,  0}; /* "]" */
static const GLubyte Helvetica10_Character_059[] = {  3,128, 64, 64,  0,  0,  0,  0, 64,  0,  0,  0,  0,  0}; /* ";" */
static const GLubyte Helvetica10_Character_058[] = {  3,  0,  0,128,  0,  0,  0,  0,128,  0,  0,  0,  0,  0}; /* ":" */
static const GLubyte Helvetica10_Character_044[] = {  3,128, 64, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; /* "," */
static const GLubyte Helvetica10_Character_046[] = {  3,  0,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; /* "." */
static const GLubyte Helvetica10_Character_060[] = {  6,  0,  0,  0, 32, 64,128, 64, 32,  0,  0,  0,  0,  0}; /* "<" */
static const GLubyte Helvetica10_Character_062[] = {  6,  0,  0,  0,128, 64, 32, 64,128,  0,  0,  0,  0,  0}; /* ">" */
static const GLubyte Helvetica10_Character_047[] = {  3,  0,  0,128,128, 64, 64, 64, 64, 32, 32,  0,  0,  0}; /* "/" */
static const GLubyte Helvetica10_Character_063[] = {  6,  0,  0, 64,  0, 64, 64, 32, 16,144, 96,  0,  0,  0}; /* "?" */
static const GLubyte Helvetica10_Character_092[] = {  3,  0,  0, 32, 32, 64, 64, 64, 64,128,128,  0,  0,  0}; /* "\" */
static const GLubyte Helvetica10_Character_034[] = {  4,  0,  0,  0,  0,  0,  0,  0,  0,160,160,  0,  0,  0}; /* """ */

/* Missing Characters filled in by John Fay by hand ... */
static const GLubyte Helvetica10_Character_039[] = {  3,  0,  0,  0,  0,  0,  0,  0,128, 64, 64,  0,  0,  0}; /* "'" */
static const GLubyte Helvetica10_Character_124[] = {  3, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,  0,  0}; /* "|" */

static const GLubyte* Helvetica10_Character_Map[] = {Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_032,Helvetica10_Character_033,Helvetica10_Character_034,Helvetica10_Character_035,Helvetica10_Character_036,Helvetica10_Character_037,
 Helvetica10_Character_038,Helvetica10_Character_039,Helvetica10_Character_040,Helvetica10_Character_041,Helvetica10_Character_042,Helvetica10_Character_043,Helvetica10_Character_044,Helvetica10_Character_045,Helvetica10_Character_046,Helvetica10_Character_047,Helvetica10_Character_048,Helvetica10_Character_049,Helvetica10_Character_050,Helvetica10_Character_051,Helvetica10_Character_052,Helvetica10_Character_053,Helvetica10_Character_054,Helvetica10_Character_055,Helvetica10_Character_056,Helvetica10_Character_057,Helvetica10_Character_058,Helvetica10_Character_059,Helvetica10_Character_060,Helvetica10_Character_061,Helvetica10_Character_062,Helvetica10_Character_063,Helvetica10_Character_064,Helvetica10_Character_065,Helvetica10_Character_066,Helvetica10_Character_067,Helvetica10_Character_068,Helvetica10_Character_069,Helvetica10_Character_070,Helvetica10_Character_071,Helvetica10_Character_072,Helvetica10_Character_073,Helvetica10_Character_074,Helvetica10_Character_075,Helvetica10_Character_076,
 Helvetica10_Character_077,Helvetica10_Character_078,Helvetica10_Character_079,Helvetica10_Character_080,Helvetica10_Character_081,Helvetica10_Character_082,Helvetica10_Character_083,Helvetica10_Character_084,Helvetica10_Character_085,Helvetica10_Character_086,Helvetica10_Character_087,Helvetica10_Character_088,Helvetica10_Character_089,Helvetica10_Character_090,Helvetica10_Character_091,Helvetica10_Character_092,Helvetica10_Character_093,Helvetica10_Character_094,Helvetica10_Character_095,Helvetica10_Character_096,Helvetica10_Character_097,Helvetica10_Character_098,Helvetica10_Character_099,Helvetica10_Character_100,Helvetica10_Character_101,Helvetica10_Character_102,Helvetica10_Character_103,Helvetica10_Character_104,Helvetica10_Character_105,Helvetica10_Character_106,Helvetica10_Character_107,Helvetica10_Character_108,Helvetica10_Character_109,Helvetica10_Character_110,Helvetica10_Character_111,Helvetica10_Character_112,Helvetica10_Character_113,Helvetica10_Character_114,Helvetica10_Character_115,
 Helvetica10_Character_116,Helvetica10_Character_117,Helvetica10_Character_118,Helvetica10_Character_119,Helvetica10_Character_120,Helvetica10_Character_121,Helvetica10_Character_122,Helvetica10_Character_123,Helvetica10_Character_124,Helvetica10_Character_125,Helvetica10_Character_126,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,
 Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,
 Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,
 Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,NULL};
const BitmapFontData FontHelvetica10 = { "-adobe-helvetica-medium-r-normal--10-100-75-75-p-56-iso8859-1", 93, 13, Helvetica10_Character_Map, -1.0f, 2.0f };

#endif // OPENGL Defined

#endif // _GEOMETRY_H_
