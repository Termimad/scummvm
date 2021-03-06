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

#ifndef MOHAWK_CURSORS_H
#define MOHAWK_CURSORS_H

#include "common/scummsys.h"

namespace Common {
	class MacResManager;
	class NEResources;
	class SeekableReadStream;
	class String;
}

#include "mohawk/resource.h"

namespace Mohawk {

// 803-805 are animated, one large bmp which is in chunks - these are NEVER USED
// Other cursors (200, 300, 400, 500, 600, 700) are not the same in each stack
enum {
	kDefaultMystCursor = 100,				// The default hand
	kWhitePageCursor = 800,					// Holding a white page
	kRedPageCursor = 801,					// Holding a red page
	kBluePageCursor = 802,					// Holding a blue page
	// kDroppingWhitePageAnimCursor = 803,
	// kDroppingRedPageAnimCursor = 804,
	// kDroppingBluePageAnimCursor = 805,
	kNewMatchCursor = 900,					// Match that has not yet been lit
	kLitMatchCursor = 901,					// Match that's burning
	kDeadMatchCursor = 902,					// Match that's been extinguished
	kKeyCursor = 903, 						// Key in Lighthouse in Stoneship
	kRotateClockwiseCursor = 904, 			// Rotate gear clockwise (boiler on Myst)
	kRotateCounterClockwiseCursor = 905,	// Rotate gear counter clockwise (boiler on Myst)
	kMystZipModeCursor = 999				// Zip Mode cursor
};

enum {
	kRivenOpenHandCursor = 2003,
	kRivenClosedHandCursor = 2004,
	kRivenMainCursor = 3000,
	kRivenPelletCursor = 5000,
	kRivenHideCursor = 9000
};

class MohawkArchive;
class MohawkEngine;
class MohawkEngine_Myst;
class MystBitmap;

class CursorManager {
public:
	CursorManager() {}
	virtual ~CursorManager() {}

	virtual void showCursor();
	virtual void hideCursor();
	virtual void setCursor(uint16 id);
	virtual void setDefaultCursor();

protected:
	// Handles the Mac version of the xor/and map cursor
	void decodeMacXorCursor(Common::SeekableReadStream *stream, byte *cursor);

	// Set a tCUR resource as the current cursor
	void setStandardCursor(Common::SeekableReadStream *stream);
};

// The default Mohawk cursor manager
// Uses standard tCUR resources
class DefaultCursorManager : public CursorManager {
public:
	DefaultCursorManager(MohawkEngine *vm, uint32 tag = ID_TCUR) : _vm(vm), _tag(tag) {}
	~DefaultCursorManager() {}

	void setCursor(uint16 id);

private:
	MohawkEngine *_vm;
	uint32 _tag;
};

// The cursor manager for Myst
// Uses WDIB + CLRC resources
class MystCursorManager : public CursorManager {
public:
	MystCursorManager(MohawkEngine_Myst *vm);
	~MystCursorManager();

	void showCursor();
	void hideCursor();
	void setCursor(uint16 id);
	void setDefaultCursor();

private:
	MohawkEngine_Myst *_vm;
	MystBitmap *_bmpDecoder;
};


// The cursor manager for Riven
// Uses hardcoded cursors
class RivenCursorManager : public CursorManager {
public:
	RivenCursorManager() {}
	~RivenCursorManager() {}

	void setCursor(uint16 id);
	void setDefaultCursor();
};

// The cursor manager for NE exe's
class NECursorManager : public CursorManager {
public:
	NECursorManager(const Common::String &appName);
	~NECursorManager();

	void setCursor(uint16 id);

private:
	Common::NEResources *_exe;
};

// The cursor manager for Mac applications
class MacCursorManager : public CursorManager {
public:
	MacCursorManager(const Common::String &appName);
	~MacCursorManager();

	void setCursor(uint16 id);

private:
	Common::MacResManager *_resFork;
};

// The cursor manager for Living Books v2+ games
// Handles custom generated cursors in addition to tCUR resources
class LivingBooksCursorManager_v2 : public CursorManager {
public:
	LivingBooksCursorManager_v2();
	~LivingBooksCursorManager_v2();

	void setCursor(uint16 id);

private:
	MohawkArchive *_sysArchive;
};

} // End of namespace Mohawk

#endif
