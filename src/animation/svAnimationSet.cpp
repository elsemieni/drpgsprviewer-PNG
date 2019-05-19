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
#include "svAnimationSet.h"
#include "svAnimation.h"
#include "../common/exceptions.h"



// class svAnimationSet
/////////////////////////

// constructor, destructor
////////////////////////////

svAnimationSet::svAnimationSet(){
	pAnims = NULL;
	pAnimCount = 0;
	pAnimSize = 0;
	pSpriteFile = NULL;
	SetSpriteFile( "sprite.spr" );
}

svAnimationSet::~svAnimationSet(){
	pCleanUp();
}



// Management
///////////////

void svAnimationSet::SetSpriteFile( const char *filename ){
	if( ! filename ) THROW( dueInvalidParam );
	char *newStr = new char[ strlen( filename ) + 1 ];
	if( ! newStr ) THROW( dueOutOfMemory );
	strcpy( newStr, filename );
	if( pSpriteFile ) delete [] pSpriteFile;
	pSpriteFile = newStr;
}

svAnimation *svAnimationSet::GetAnimationAt( int index ) const{
	if( index < 0 || index >= pAnimCount ) THROW( dueInvalidParam );
	return pAnims[ index ];
}

bool svAnimationSet::HasAnimation( svAnimation *animation ) const{
	return pFindAnimation( animation ) != -1;
}

void svAnimationSet::AddAnimation( svAnimation *animation ){
	if( ! animation ) THROW( dueInvalidParam );
	if( HasAnimation( animation ) ) THROW( dueInvalidParam );
	if( pAnimCount == pAnimSize ){
		int i, newSize = pAnimSize * 3 / 2 + 1;
		svAnimation **newArray = new svAnimation*[ newSize ];
		if( ! newArray ) THROW( dueOutOfMemory );
		if( pAnims ){
			for( i=0; i<pAnimCount; i++ ) newArray[ i ] = pAnims[ i ];
			delete [] pAnims;
		}
		pAnims = newArray;
		pAnimSize = newSize;
	}
	pAnims[ pAnimCount ] = animation;
	pAnimCount++;
}

void svAnimationSet::RemoveAnimation( svAnimation *animation ){
	int index = pFindAnimation( animation );
	if( index == -1 ) THROW( dueInvalidParam );
	int i;
	for( i=index+1; i<pAnimCount; i++ ) pAnims[ i - 1 ] = pAnims[ i ];
	pAnims[ pAnimCount - 1 ] = NULL;
	delete animation;
}

void svAnimationSet::RemoveAllAnimations(){
	int i;
	if( pAnimCount > 0 ){
		for( i=0; i<pAnimCount; i++ ){
			if( pAnims[ i ] ){
				delete pAnims[ i ];
				pAnims[ i ] = NULL;
			}
		}
		pAnimCount = 0;
	}
}



// Private Functions
//////////////////////

void svAnimationSet::pCleanUp(){
	RemoveAllAnimations();
	if( pSpriteFile ) delete [] pSpriteFile;
}

int svAnimationSet::pFindAnimation( svAnimation *animation ) const{
	int i;
	if( animation ){
		for( i=0; i<pAnimCount; i++ ){
			if( pAnims[ i ] == animation ) return i;
		}
	}
	return -1;
}
