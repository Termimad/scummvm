/* ScummVM - Graphic Adventure Engine
*
* ScummVM is the legal property of its developers, whose names
* are too numerous to list here. Please refer to the COPYRIGHT
* file distributed with this source distribution.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
* $URL$
* $Id$
*
*/

#ifndef PICTURE_H
#define PICTURE_H

#include "common/stream.h"
#include "common/array.h"
#include "common/func.h"
#include "common/str.h"

#include "toon.h"

namespace Toon {

class ToonEngine;
class Picture {

public:
	Picture(ToonEngine *vm);
	bool loadPicture(Common::String file, bool totalPalette = false);
	void setupPalette();
	void draw(Graphics::Surface &surface, int32 x, int32 y, int32 dx, int32 dy);
	void drawMask(Graphics::Surface &surface, int32 x, int32 y, int32 dx, int32 dy);
	void drawLineOnMask(int32 x, int32 y, int32 x2, int32 y2, bool walkable);
	void floodFillNotWalkableOnMask( int32 x, int32 y );
	uint8 getData(int32 x, int32 y);
	uint8 *getDataPtr() { return _data; }
	int32 getWidth() const { return _width; }
	int32 getHeight() const { return _height; }
protected:
	int32 _width;
	int32 _height;
	uint8 *_data;
	uint8 *_palette; // need to be copied at 3-387
	int32 _paletteEntries;
	bool _useFullPalette;

	ToonEngine *_vm;
};

} // End of namespace Toon

#endif