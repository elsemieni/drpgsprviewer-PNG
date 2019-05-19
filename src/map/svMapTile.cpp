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
#include "svSpriteImage.h"
#include "../common/exceptions.h"



// class svSpriteImage
////////////////////////

// constructor, destructor
////////////////////////////

svSpriteImage::svSpriteImage( int width, int height ){
	if( width < 1 || height < 1 ) THROW( dueInvalidParam );
	pWidth = width;
	pHeight = height;
	pData = NULL;
	pBlocking = false;
	try{
		pData = new svColor[ pWidth * pHeight ];
		if( ! pData ) THROW( dueOutOfMemory );
	}catch( duException ){
		pCleanUp();
		throw;
	}
}

svSpriteImage::~svSpriteImage(){
	pCleanUp();
}



// Management
///////////////

void svSpriteImage::SetBlocking( bool blocking ){
	pBlocking = blocking;
}

svColor *svSpriteImage::GetLineAt( int line ) const{
	if( line < 0 || line >= pHeight ) THROW( dueInvalidParam );
	return pData + pWidth * line;
}



// Private Functions
//////////////////////

void svSpriteImage::pCleanUp(){
	if( pData ) delete [] pData;
}
