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
#ifndef _SVMAPFIELD_H_
#define _SVMAPFIELD_H_

// includes
#include "../drpgsprviewer.h"

// predefinitions

// definitions
#define DRPG_MFF_FLIP_X		0x100



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Map Field.
 * Manages one field in a map. A field contains an optional tile and object.
 */
class svMapField{
private:
	int pTileFile;
	int pTile;
	int pObject;
	int pFlags;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates a new map field object. */
	svMapField();
	/** Cleans up the map field upon destruction. */
	~svMapField();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/**
	 * Retrieves the index of the tile file to use. Can be -1 if there
	 * is no tile to be drawn.
	 */
	inline int GetTileFileIndex() const{ return pTileFile; }
	/**
	 * Retrieve the index of the tile inside the tile file. Can be -1 if
	 * there is no tile to be drawn.
	 */
	inline int GetTileIndex() const{ return pTile; }
	/**
	 * Sets the index of the tile file and the index of the tile inside
	 * this file to use. Can be -1 if there is no tile to be drawn.
	 */
	void SetTileIndex( int tileFileIndex, int tileIndex );
	/**
	 * Retrieves the index of the object file to use. Can be -1 if there
	 * is no object to be used.
	 */
	inline int GetObjectIndex() const{ return pObject; }
	/**
	 * Sets the index of the object file to use. Can be -1 if there
	 * is no object to be used.
	 */
	void SetObjectIndex( int objectIndex );
	/**
	 * Retrieves the flags of the field.
	 */
	inline int GetFlags() const{ return pFlags; }
	/**
	 * Sets the flags of the field.
	 */
	void SetFlags( int flags );
	/*@}*/
};

// end of include only once
#endif
