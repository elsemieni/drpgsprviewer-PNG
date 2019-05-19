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
#include "svViewMap.h"
#include "svViewRenderMap.h"
#include "../sprite/svSprite.h"
#include "../sprite/svSpriteImage.h"
#include "../map/svMap.h"
#include "../map/svMapField.h"
#include "../map/svMapLoader.h"
#include "../common/file/decDiscFileReader.h"
#include "../common/file/decDiscFileWriter.h"
#include "../common/file/decPath.h"
#include "../common/exceptions.h"



// events
///////////
FXDEFMAP( svViewRenderMap ) svViewRenderMapMap[]={
	FXMAPFUNC( SEL_CONFIGURE, 0, svViewRenderMap::onResize ),
	FXMAPFUNC( SEL_PAINT, 0, svViewRenderMap::onPaint ),
	FXMAPFUNC( SEL_LEFTBUTTONPRESS, 0, svViewRenderMap::onLButtonPress ),
	FXMAPFUNC( SEL_KEYPRESS, 0, svViewRenderMap::onKeyPress ),
};



// class svViewRenderMap
///////////////////////

FXIMPLEMENT( svViewRenderMap, FXFrame, svViewRenderMapMap, ARRAYNUMBER( svViewRenderMapMap ) )

svViewRenderMap::svViewRenderMap(){ }



// constructor, destructor
////////////////////////////

svViewRenderMap::svViewRenderMap( svViewMap *viewMap, FXComposite *parent ) : 
FXFrame( parent, FRAME_NORMAL | LAYOUT_FILL_X | LAYOUT_FILL_Y ){
	if( ! viewMap ) THROW( dueInvalidParam );
	// prepare
	pViewMap = viewMap;
	pMap = NULL;
	pImage = NULL;
	pFieldX = 0;
	pFieldY = 0;
	pPosX = 0;
	pPosY = 0;
	// set other stuff
	this->setBackColor( FXRGB( 0, 0, 0 ) );
}

svViewRenderMap::~svViewRenderMap(){
}

void svViewRenderMap::Update(){
	if( ! pMap || ! pImage ) return;
	int width = this->getWidth();
	int height = this->getHeight();
	if( width < 1 || height < 1 ) return;
	int fieldXCount = pMap->GetFieldXCount();
	int fieldYCount = pMap->GetFieldYCount();
	int fieldWidth = pMap->GetFieldWidth();
	int fieldHeight = pMap->GetFieldHeight();
	int fieldX1 = pPosX / fieldWidth;
	int fieldY1 = pPosY / fieldHeight;
	int fieldX2 = ( pPosX + width ) / fieldWidth;
	int fieldY2 = ( pPosY + height ) / fieldHeight;
	int offsetX = fieldX1 * fieldWidth - pPosX;
	int offsetY = fieldY1 * fieldHeight - pPosY;
	int tileFileIndex, tileIndex, objectIndex;
//printf( "[DEBUG] (%i,%i)-(%i,%i) %i %i %i %i\n", fieldX1, fieldY1, fieldX2, fieldY2,
//fieldWidth, fieldHeight, offsetX, offsetY );
	svMapField *field;
	svSprite *tile;
	svSpriteImage *tileImage;
	int fx, fy, pox, poy, x, y, rx, ry, sx, sy;
	svColor overlay, color, *pixelLine;
	bool hilight;
	bool flipX;
	// adjust the field values just for safety
	if( fieldX1 < 0 ) fieldX1 = 0;
	if( fieldY1 < 0 ) fieldY1 = 0;
	if( fieldX2 >= fieldXCount ) fieldX2 = fieldXCount - 1;
	if( fieldY2 >= fieldYCount ) fieldY2 = fieldYCount - 1;
	// loop over all visible tiles and draw them into the image
	for( fy=fieldY1; fy<=fieldY2; fy++){
		poy = offsetY + ( fy - fieldY1 ) * fieldHeight;
//		printf( "[DEBUG] poy %i %i : %i\n", fx, fy, poy );
		for( fx=fieldX1; fx<=fieldX2; fx++ ){
			pox = offsetX + ( fx - fieldX1 ) * fieldWidth;
//			printf( "[DEBUG] pox %i %i : %i\n", fx, fy, pox );
			field = pMap->GetFieldAt( fx, fy );
			flipX = ( field->GetFlags() & DRPG_MFF_FLIP_X ) == DRPG_MFF_FLIP_X;
			hilight = ( fx == pFieldX && fy == pFieldY );
			tileFileIndex = field->GetTileFileIndex();
			tileIndex = field->GetTileIndex();
//			printf( "[DEBUG] tile %i %i\n", tileFileIndex, tileIndex );
			if( tileFileIndex < 0 || tileFileIndex >= pMap->GetTileCount() ){
				tile = NULL;
				tileImage = NULL;
			}else{
				tile = pMap->GetTileAt( tileFileIndex );
				if( tileIndex < 0 || tileIndex >= tile->GetImageCount() ){
					tile = NULL;
					tileImage = NULL;
				}else{
					tileImage = tile->GetImageAt( tileIndex );
				}
			}
			objectIndex = field->GetObjectIndex();
			if( objectIndex == -1 ){
				overlay.red = 0;
				overlay.green = 0;
				overlay.blue = 0;
				overlay.alpha = 0;
			}else{
				overlay.red = 0;
				overlay.green = 0;
				overlay.blue = 255;
				overlay.alpha = 64;
			}
			for( y=0; y<fieldHeight; y++ ){
				ry = poy + y;
//				printf( "[DEBUG] ry %i\n", ry );
				if( ry < 0 || ry >= height ) continue;
				if( tileImage ){
					pixelLine = tileImage->GetLineAt( y );
				}else{
					pixelLine = NULL;
				}
				for( x=0; x<fieldWidth; x++ ){
					rx = pox + x;
//					printf( "[DEBUG] rx %i\n", rx );
					if( rx < 0 || rx >= width ) continue;
					if( hilight && ( x == 0 || x == fieldWidth - 1 || y == 0 || y == fieldHeight - 1 ) ){
						color.red = 255;
						color.green = 0;
						color.blue = 0;
					}else{
						if( pixelLine ){
							if( flipX ){
								sx = fieldWidth - 1 - x;
							}else{
								sx = x;
							}
							color.red = pixelLine[ sx ].red;
							color.green = pixelLine[ sx ].green;
							color.blue = pixelLine[ sx ].blue;
						}else{
							color.red = 0;
							color.green = 0;
							color.blue = 0;
						}
						color.red = ( unsigned char )( ( color.red * ( 255 - overlay.alpha ) + overlay.red * overlay.alpha ) / 255 );
						color.green = ( unsigned char )( ( color.green * ( 255 - overlay.alpha ) + overlay.green * overlay.alpha ) / 255 );
						color.blue = ( unsigned char )( ( color.blue * ( 255 - overlay.alpha ) + overlay.blue * overlay.alpha ) / 255 );
					}
					pImage->setPixel( rx, ry, FXRGB( color.red, color.green, color.blue ) );
				}
			}
		}
	}
	// update the image
	pImage->render();
	// request redrawing the map view
	this->update();
}



// management
///////////////

void svViewRenderMap::CleanUp(){
	if( pImage ) delete pImage;
}



// callbacks
//////////////

long svViewRenderMap::onResize( FXObject *sender, FXSelector selector, void *data ){
	int width = pViewMap->getWidth();
	int height = pViewMap->getHeight();
	FXImage *image = NULL;
	if( width > 0 && height > 0 ) image = pCreateImage( width, height );
	if( pImage ) delete pImage;
	pImage = image;
	pViewMap->UpdateRanges();
	Update();
	return 1;
}

long svViewRenderMap::onPaint( FXObject *sender, FXSelector selector, void *data ){
	if( pImage ){
		FXDCWindow dc( this, ( FXEvent* )data );
		dc.drawImage( pImage, 0, 0 );
	}
	return 1;
}

long svViewRenderMap::onLButtonPress( FXObject *sender, FXSelector selector, void *data ){
	if( ! pMap ) return 1;
	FXEvent *event = ( FXEvent* )data;
	int fieldXCount = pMap->GetFieldXCount();
	int fieldYCount = pMap->GetFieldYCount();
	int fieldWidth = pMap->GetFieldWidth();
	int fieldHeight = pMap->GetFieldHeight();
	int fieldX = ( pPosX + event->click_x ) / fieldWidth;
	int fieldY = ( pPosY + event->click_y ) / fieldHeight;
	// adjust the field values just for safety
	if( fieldX < 0 ) fieldX = 0;
	if( fieldY < 0 ) fieldY = 0;
	if( fieldX >= fieldXCount ) fieldX = fieldXCount - 1;
	if( fieldY >= fieldYCount ) fieldY = fieldYCount - 1;
	// set field and update
	SetField( fieldX, fieldY );
	pViewMap->UpdateFieldInfo( pFieldX, pFieldY );
	Update();
	setFocus();
	return 1;
}

long svViewRenderMap::onKeyPress( FXObject *sender, FXSelector selector, void *data ){
	if( ! pMap ) return 1;
	FXEvent *event = ( FXEvent* )data;
	int fieldXCount = pMap->GetFieldXCount();
	int fieldYCount = pMap->GetFieldYCount();
	// check where to move
	if( event->code == 65362 ){ // Up Arrow
		if( pFieldY > 0 ){
			SetField( pFieldX, pFieldY - 1 );
			pViewMap->UpdateFieldInfo( pFieldX, pFieldY );
			Update();
		}	
	}else if( event->code == 65364 ){ // Down Arrow
		if( pFieldY < pMap->GetFieldYCount() - 1 ){
			SetField( pFieldX, pFieldY + 1 );
			pViewMap->UpdateFieldInfo( pFieldX, pFieldY );
			Update();
		}
	}else if( event->code == 65361 ){ // Left Arrow
		if( pFieldX > 0 ){
			SetField( pFieldX - 1, pFieldY );
			pViewMap->UpdateFieldInfo( pFieldX, pFieldY );
			Update();
		}	
	}else if( event->code == 65363 ){ // Right Arrow
		if( pFieldX < pMap->GetFieldXCount() - 1 ){
			SetField( pFieldX + 1, pFieldY );
			pViewMap->UpdateFieldInfo( pFieldX, pFieldY );
			Update();
		}
	}
	printf( "[KEY] %i\n", event->code );
	return 1;
}



// Map
////////

void svViewRenderMap::SetMap( svMap *map ){
	pMap = map;
}

void svViewRenderMap::SetField( int fieldX, int fieldY ){
	if( ! pMap ) THROW( dueInvalidParam );
	if( fieldX < 0 || fieldX >= pMap->GetFieldXCount() ) THROW( dueInvalidParam );
	if( fieldY < 0 || fieldY >= pMap->GetFieldYCount() ) THROW( dueInvalidParam );
	pFieldX = fieldX;
	pFieldY = fieldY;
}

void svViewRenderMap::SetPositionX( int posX ){
	if( ! pMap ) THROW( dueInvalidParam );
	pPosX = posX;
}

void svViewRenderMap::SetPositionY( int posY ){
	if( ! pMap ) THROW( dueInvalidParam );
	pPosY = posY;
}



// Private Functions
//////////////////////

FXImage *svViewRenderMap::pCreateImage( int width, int height ){
	if( width < 1 || height < 1 ) THROW( dueInvalidParam );
	FXImage *image = NULL;
	int x, y;
	// create a new image
	printf( "[DEBUG] Create Image %i x %i\n", width, height );
	image = new FXImage( this->getApp(), NULL, IMAGE_KEEP | IMAGE_OWNED
		| IMAGE_SHMI | IMAGE_SHMP, width, height );
	if( ! image ) THROW( dueOutOfMemory );
	// update the image
	image->create();
	// finished
	printf( "[DEBUG] Done\n" );
	return image;
}
