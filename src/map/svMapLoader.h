/* 
 * Digimon RPG Map Viewer
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
#ifndef _SVMAPLOADER_H_
#define _SVMAPLOADER_H_

// includes

// predefinitions
class svMap;
class decBaseFileReader;

// definitions
#define SV_DEBUG_LEVEL_NONE				0
#define SV_DEBUG_LEVEL_MINIMAL			1
#define SV_DEBUG_LEVEL_MEDIUM			2
#define SV_DEBUG_LEVEL_HEAVY			3



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Map Loader.
 * Provides the ability to load a map from file.
 */
class svMapLoader{
private:
	int pDebugLevel;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates a new map loader object. */
	svMapLoader();
	/** Cleans up the map loader upon destruction. */
	~svMapLoader();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/**
	 * Loads the map from the given file and creates a new map
	 * object for it.
	 */
	svMap *LoadMap( decBaseFileReader *reader );
	/*@}*/
private:
	void pCleanUp();
	
};

// end of include only once
#endif
