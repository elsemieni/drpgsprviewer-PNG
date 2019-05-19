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
#include "svSprite.h"
#include "svSpriteImage.h"
#include "../common/exceptions.h"



// class svSprite
///////////////////

// constructor, destructor
////////////////////////////

svSprite::svSprite(){
	pFilename = NULL;
	pImages = NULL;
	pImageCount = 0;
	pImageSize = 0;
	SetFilename( "sprite.spr" );
}

svSprite::~svSprite(){
	pCleanUp();
}



// Management
///////////////

void svSprite::SetFilename( const char *filename ){
	if( ! filename ) THROW( dueInvalidParam );
	char *newStr = new char[ strlen( filename ) + 1 ];
	if( ! newStr ) THROW( dueOutOfMemory );
	strcpy( newStr, filename );
	if( pFilename ) delete [] pFilename;
	pFilename = newStr;
}

svSpriteImage *svSprite::GetImageAt( int index ) const{
	if( index < 0 || index >= pImageCount ) THROW( dueInvalidParam );
	return pImages[ index ];
}

bool svSprite::HasImage( svSpriteImage *image ) const{
	return pFindImage( image ) != -1;
}

void svSprite::AddImage( svSpriteImage *image ){
	if( ! image ) THROW( dueInvalidParam );
	if( HasImage( image ) ) THROW( dueInvalidParam );
	if( pImageCount == pImageSize ){
		int i, newSize = pImageSize * 3 / 2 + 1;
		svSpriteImage **newArray = new svSpriteImage*[ newSize ];
		if( ! newArray ) THROW( dueOutOfMemory );
		if( pImages ){
			for( i=0; i<pImageCount; i++ ) newArray[ i ] = pImages[ i ];
			delete [] pImages;
		}
		pImages = newArray;
		pImageSize = newSize;
	}
	pImages[ pImageCount ] = image;
	pImageCount++;
}

void svSprite::RemoveImage( svSpriteImage *image ){
	int index = pFindImage( image );
	if( index == -1 ) THROW( dueInvalidParam );
	int i;
	for( i=index+1; i<pImageCount; i++ ) pImages[ i - 1 ] = pImages[ i ];
	pImages[ pImageCount - 1 ] = NULL;
	delete image;
}

void svSprite::RemoveAllImages(){
	int i;
	if( pImageCount > 0 ){
		for( i=0; i<pImageCount; i++ ){
			if( pImages[ i ] ){
				delete pImages[ i ];
				pImages[ i ] = NULL;
			}
		}
		pImageCount = 0;
	}
}



// Private Functions
//////////////////////

void svSprite::pCleanUp(){
	RemoveAllImages();
	if( pFilename ) delete [] pFilename;
}

int svSprite::pFindImage( svSpriteImage *image ) const{
	int i;
	if( image ){
		for( i=0; i<pImageCount; i++ ){
			if( pImages[ i ] == image ) return i;
		}
	}
	return -1;
}
