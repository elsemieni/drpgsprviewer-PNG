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

 
// includes
/////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "svMapField.h"
#include "../common/exceptions.h"



// class svMapField
/////////////////////

// constructor, destructor
////////////////////////////

svMapField::svMapField(){
	pTileFile = -1;
	pTile = -1;
	pObject = -1;
	pFlags = 0;
}

svMapField::~svMapField(){
}



// Management
///////////////

void svMapField::SetTileIndex( int tileFileIndex, int tileIndex ){
	if( tileFileIndex < -1 || tileIndex < -1 ) THROW( dueInvalidParam );
	pTileFile = tileFileIndex;
	pTile = tileIndex;
}

void svMapField::SetObjectIndex( int objectIndex ){
	if( objectIndex < -1 ) THROW( dueInvalidParam );
	pObject = objectIndex;
}

void svMapField::SetFlags( int flags ){
	pFlags = flags;
}
