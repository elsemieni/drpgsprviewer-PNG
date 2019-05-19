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
#ifndef _SVVIEWRENDERMAP_H_
#define _SVVIEWRENDERMAP_H_

// includes
#include "../drpgsprviewer.h"
#include "../foxtoolkit.h"

// predefinitions
class svMap;
class svSprite;
class svViewMap;



// class svViewRenderMap
class svViewRenderMap : public FXFrame{
	FXDECLARE( svViewRenderMap )
protected:
	svViewRenderMap();
public:
	enum eFoxIDs{
		ID_CANVAS=FXFrame::ID_LAST,
		ID_LAST
	};
private:
	svViewMap *pViewMap;
	FXImage *pImage;
	int pFieldX, pFieldY;
	int pPosX, pPosY;
	svMap *pMap;
public:
	// constructor, destructor
	svViewRenderMap( svViewMap *viewMap, FXComposite *parent );
	~svViewRenderMap();
	// management
	void Show( bool show );
	void CleanUp();
	void Update();
	// callbacks
	long onResize( FXObject *sender, FXSelector selector, void *data );
	long onPaint( FXObject *sender, FXSelector selector, void *data );
	long onLButtonPress( FXObject *sender, FXSelector selector, void *data );
	long onKeyPress( FXObject *sender, FXSelector selector, void *data );
	// map
	inline svMap *GetMap() const{ return pMap; }
	void SetMap( svMap *map );
	inline int GetFieldX() const{ return pFieldX; }
	inline int GetFieldY() const{ return pFieldY; }
	void SetField( int fieldX, int fieldY );
	inline int GetPositionX() const{ return pPosX; }
	inline int GetPositionY() const{ return pPosY; }
	void SetPositionX( int posX );
	void SetPositionY( int posY );
	void UpdateRanges();
private:
	FXImage *pCreateImage( int width, int height );
};

// end of include only once
#endif
