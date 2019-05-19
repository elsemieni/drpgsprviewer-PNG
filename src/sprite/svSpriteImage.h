/* 
 * Digimon RPG Sprite Viewer
 *
 * Copyright (C) 2004, Plüss Roland ( rptd@gmx.net )
 * 
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later 
 * version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

// include only once
#ifndef _SVSPRITEIMAGE_H_
#define _SVSPRITEIMAGE_H_

// includes
#include "../drpgsprviewer.h"

// predefinitions



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Sprite Image.
 * Manages a sprite image. The image is stored as 32-bit RGBA.
 */
class svSpriteImage{
private:
	int pWidth;
	int pHeight;
	svColor *pData;
	bool pBlocking;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates a new sprite image object with the given dimensions. */
	svSpriteImage( int width, int height );
	/** Cleans up the sprite image upon destruction. */
	~svSpriteImage();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/** Retrieves the width of the image. */
	inline int GetWidth() const{ return pWidth; }
	/** Retrieves the height of the image. */
	inline int GetHeight() const{ return pHeight; }
	/** Retrieves the blocking value used only by tiles. */
	inline bool GetBlocking() const{ return pBlocking; }
	/** Sets the blocking value used only by tiles. */
	void SetBlocking( bool blocking );
	/** Retrieves the pointer to the start of the given line. */
	svColor *GetLineAt( int line ) const;
	/*@}*/
private:
	void pCleanUp();
};

// end of include only once
#endif
