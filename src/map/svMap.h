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
#ifndef _SVMAP_H_
#define _SVMAP_H_

// includes

// predefinitions
class svMapField;
class svMap;
class svSprite;



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Map.
 * Manages a map. Each map composes of one or more map tiles.
 */
class svMap{
private:
	char *pMapName;
	svSprite **pTiles;
	int pTileCount, pTileSize;
	svSprite **pObjects;
	int pObjectCount, pObjectSize;
	svMapField *pFields;
	int pFieldCount;
	int pFieldXCount;
	int pFieldYCount;
	int pFieldWidth;
	int pFieldHeight;
	int pMapWidth;
	int pMapHeight;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates a new map object. */
	svMap( int fieldXCount, int fieldYCount, int fieldWidth, int fieldHeight );
	/** Cleans up the map upon destruction. */
	~svMap();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/** Retrieves the name of the map. */
	inline const char *GetMapName() const{ return ( const char * )pMapName; }
	/** Sets the name of the map. */
	void SetMapName( const char *name );
	/** Retrieves the width of the map in pixels. */
	inline int GetMapWidth() const{ return pMapWidth; }
	/** Retrieves the height of the map in pixels. */
	inline int GetMapHeight() const{ return pMapHeight; }
	/*@}*/
	
	/** @name Tile  Management */
	/*@{*/
	/** Retrieves the count of tile files. */
	inline int GetTileCount() const{ return pTileCount; }
	/** Retrieves the tile at the given index. */
	svSprite *GetTileAt( int index ) const;
	/** Determines if the given tile is already part of the map. */
	bool HasTile( svSprite *tile ) const;
	/**
	 * Adds the given tile to the sprite. The tile must not be
	 * part of the map.
	 */
	void AddTile( svSprite *tile );
	/*@}*/
	
	/** @name Object  Management */
	/*@{*/
	/** Retrieves the count of object files. */
	inline int GetObjectCount() const{ return pObjectCount; }
	/** Retrieves the object at the given index. */
	svSprite *GetObjectAt( int index ) const;
	/** Determines if the given object is already part of the map. */
	bool HasObject( svSprite *object ) const;
	/**
	 * Adds the given object to the sprite. The object must not be
	 * part of the map.
	 */
	void AddObject( svSprite *object );
	/*@}*/
	
	/** @name Field Management */
	/*@{*/
	/** Retrieves field count in X direction. */
	inline int GetFieldXCount() const{ return pFieldXCount; }
	/** Retrieves field count in Y direction. */
	inline int GetFieldYCount() const{ return pFieldYCount; }
	/** Retrieves field width. */
	inline int GetFieldWidth() const{ return pFieldWidth; }
	/** Retrieves field height. */
	inline int GetFieldHeight() const{ return pFieldHeight; }
	/** Retrieves the field at the given position. */
	svMapField *GetFieldAt( int x, int y ) const;
	/*@}*/
private:
	void pCleanUp();
	int pFindTile( svSprite *tile ) const;
	int pFindObject( svSprite *object ) const;
};

// end of include only once
#endif
