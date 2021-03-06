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
#ifndef TEXT_H
#define TEXT_H

namespace Hugo {

class TextHandler {
public:
	TextHandler(HugoEngine *vm);
	~TextHandler();

	const char  *getNoun(int idx1, int idx2) const     { return _arrayNouns[idx1][idx2];   }
	const char  *getScreenNames(int screenIndex) const { return _screenNames[screenIndex]; }
	const char  *getStringtData(int stringIndex) const { return _stringtData[stringIndex]; }
	const char  *getTextData(int textIndex) const      { return _textData[textIndex];      }
	const char  *getTextEngine(int engineIndex) const  { return _textEngine[engineIndex];  }
	const char  *getTextIntro(int introIndex) const    { return _textIntro[introIndex];    }
	const char  *getTextMouse(int mouseIndex) const    { return _textMouse[mouseIndex];    }
	const char  *getTextParser(int parserIndex) const  { return _textParser[parserIndex];  }
	const char  *getTextUtil(int utilIndex) const      { return _textUtil[utilIndex];      }
	const char  *getVerb(int idx1, int idx2) const     { return _arrayVerbs[idx1][idx2];   }
	char **getNounArray(int idx1) { return _arrayNouns[idx1]; }
	char **getVerbArray(int idx1) { return _arrayVerbs[idx1]; }

	void loadAllTexts(Common::ReadStream &in);
	void freeAllTexts();

private:
	HugoEngine *_vm;

	char ***_arrayNouns;
	char ***_arrayVerbs;

	char  **_screenNames;
	char  **_stringtData;
	char  **_textData;
	char  **_textEngine;
	char  **_textIntro;
	char  **_textMouse;
	char  **_textParser;
	char  **_textUtil;

	char ***loadTextsArray(Common::ReadStream &in);
	char  **loadTextsVariante(Common::ReadStream &in, uint16 *arraySize);
	char  **loadTexts(Common::ReadStream &in);

	void    freeTexts(char **ptr);

};

} // End of namespace Hugo
#endif // TEXT_H
