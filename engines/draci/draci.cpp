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

#include "common/scummsys.h"
 
#include "common/config-manager.h"
#include "common/events.h"
#include "common/file.h"

#include "graphics/cursorman.h"
#include "graphics/font.h"
 
#include "draci/draci.h"
#include "draci/barchive.h"
#include "draci/gpldisasm.h"
#include "draci/font.h"
#include "draci/sprite.h"
#include "draci/screen.h"

namespace Draci {

DraciEngine::DraciEngine(OSystem *syst, const ADGameDescription *gameDesc) 
 : Engine(syst) {
	// Put your engine in a sane state, but do nothing big yet;
	// in particular, do not load data from files; rather, if you
	// need to do such things, do them from init().
 
	// Do not initialize graphics here
 
	// However this is the place to specify all default directories
	//Common::File::addDefaultDirectory(_gameDataPath + "sound/");

	_screenHeight = 200;
	_screenWidth = 320;
 	
	// Here is the right place to set up the engine specific debug levels
	Common::addDebugChannel(kDraciGeneralDebugLevel, "general", "Draci general debug level");
	Common::addDebugChannel(kDraciBytecodeDebugLevel, "bytecode", "GPL bytecode instructions");
	Common::addDebugChannel(kDraciArchiverDebugLevel, "archiver", "BAR archiver debug info");
 
	// Don't forget to register your random source
	_eventMan->registerRandomSource(_rnd, "draci");
}

int DraciEngine::init() {
	// Initialize graphics using following:
	initGraphics(_screenWidth, _screenHeight, false);

	_screen = new Screen(this);
	_font = new Font();

	// Load default font
	_font->setFont(kFontBig);

	// Basic archive test
	debugC(2, kDraciGeneralDebugLevel, "Running archive tests...");	
	Common::String path("INIT.DFW");	
	BArchive ar(path);
	BAFile *f;
	debugC(3, kDraciGeneralDebugLevel, "Number of file streams in archive: %d", ar.size());	
	
	if(ar.isOpen()) {
		f = ar[0];	
	} else {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Archive not opened");
		return 0;
	}	
		
	debugC(3, kDraciGeneralDebugLevel, "First 10 bytes of file %d: ", 0);
	for (unsigned int i = 0; i < 10; ++i) {
		debugC(3, kDraciGeneralDebugLevel, "0x%02x%c", f->_data[i], (i < 9) ? ' ' : '\n');
	}

	// Read in GPL script for the first game location	
	debugC(2, kDraciBytecodeDebugLevel, "Disassembling GPL script " 
		"for the first game location...");		

	path = "MIST.DFW";
	ar.openArchive(path);
	
	if(ar.isOpen()) {
		f = ar[3];	
	} else {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Archive not opened");
		return 0;
	}	

	// Disassemble GPL script for the first location
	gpldisasm(f->_data, f->_length);

	return 0;
}

int DraciEngine::go() {
	debugC(1, kDraciGeneralDebugLevel, "DraciEngine::go()");
 
	debugC(2, kDraciGeneralDebugLevel, "Running graphics/animation test...");

	Common::String path("PALETY.DFW");	
	BArchive ar(path);
	BAFile *f;

	ar.openArchive(path);
	
	if(ar.isOpen()) {
		f = ar[0];	
	} else {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Archive not opened");
		return 0;
	}	

	_screen->setPalette(f->_data, 0, kNumColours);
	
	// Fill screen with white
	_screen->fillScreen(255);

	// Draw big string
	Common::String testString = "Testing, testing, read all about it!";
	Graphics::Surface *surf = _screen->getSurface();
	_font->drawString(surf, testString, 
		(320 - _font->getStringWidth(testString, 1)) / 2, 130, 1);

	// Draw small string
	_font->setFont(kFontSmall);
	testString = "I'm smaller than the font above me.";
	_font->drawString(surf, testString, 
		(320 - _font->getStringWidth(testString, 1)) / 2, 150, 1);

	// Overflow handling test
	testString = "Checking overflooooooooooooooooooooooooow...";
	_font->drawString(surf, testString, 50, 170, 1);

	_screen->copyToScreen();

	// Draw and animate the dragon
	path = "OBR_AN.DFW";
	ar.openArchive(path);
	
	if(!ar.isOpen()) {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Archive not opened");
		return 0;
	}	

	for (unsigned int t = 0; t < 25; ++t) {
		debugC(5, kDraciGeneralDebugLevel, "Drawing frame %d...", t);

		// Load frame to memory
		f = ar[t];
		Sprite sp(f->_data, f->_length, ((320 - 50) / 2), 60, true);
		_screen->drawSprite(sp);
		_screen->copyToScreen();
		_system->delayMillis(100);

		debugC(5, kDraciGeneralDebugLevel, "Finished frame %d", t);	
	}	
	
	path = "HRA.DFW";
	ar.openArchive(path);
	
	if(ar.isOpen()) {
		f = ar[0];	
	} else {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Archive not opened");
		return 0;
	}	

	Sprite sp(f->_data, f->_length, 0, 0, true);
	CursorMan.pushCursorPalette(_screen->getPalette(), 0, kNumColours);
	CursorMan.pushCursor(sp._data, sp._width, sp._height, sp._width / 2, sp._height / 2);
	CursorMan.showMouse(true);

	Common::Event event;
	bool quit = false;
	while (!quit) {
		while (_eventMan->pollEvent(event)) {
			switch (event.type) {
			case Common::EVENT_QUIT:
				quit = true;
			case Common::EVENT_MOUSEMOVE:
				_system->warpMouse(event.mouse.x, event.mouse.y);
			default:
				break;
			}
		}
		_screen->copyToScreen();
		_system->delayMillis(20);
	}

	return 0;
}

DraciEngine::~DraciEngine() {
	// Dispose your resources here
 
	delete _screen;

	// Remove all of our debug levels here
	Common::clearAllDebugChannels();
}

Common::Error DraciEngine::run() {
	init();
	go();
	return Common::kNoError;
}

} // End of namespace Draci
