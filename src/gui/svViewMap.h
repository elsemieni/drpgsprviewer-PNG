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
#ifndef _SVVIEWMAP_H_
#define _SVVIEWMAP_H_

// includes
#include "../drpgsprviewer.h"
#include "../foxtoolkit.h"

// predefinitions
class deCmdLineArgs;
class svMap;
class svSprite;
class svWindowMain;
class svViewRenderMap;



// class svViewMap
class svViewMap : public FXVerticalFrame{
	FXDECLARE( svViewMap )
protected:
	svViewMap();
public:
	enum eFoxIDs{
		ID_CANVAS=FXWindow::ID_LAST,
		ID_SCROLLX,
		ID_SCROLLY,
		ID_EDITFLAGS,
		ID_LAST
	};
private:
	svWindowMain *pWndMain;
	svViewRenderMap *pViewRenderMap;
	FXScrollBar *pScrollX;
	FXScrollBar *pScrollY;
	FXTextField *pEditFieldCount;
	FXTextField *pEditFieldSize;
	FXTextField *pEditTileCount;
	FXTextField *pEditObjectCount;
	FXTextField *pEditField;
	FXTextField *pEditFlags;
	FXTextField *pEditTile;
	FXTextField *pEditObject;
	FXTextField *pEditTileFile;
	FXTextField *pEditObjectFile;
	svMap *pMap;
public:
	// constructor, destructor
	svViewMap( svWindowMain *wndMain, FXComposite *parent );
	~svViewMap();
	// management
	void Show( bool show );
	void CleanUp();
	void Update();
	// callbacks
	long onScrollXChanged( FXObject *sender, FXSelector selector, void *data );
	long onScrollYChanged( FXObject *sender, FXSelector selector, void *data );
	// map
	inline svMap *GetMap() const{ return pMap; }
	void NewMap();
	void LoadMap( const char *filename );
	void UpdateRanges();
	void UpdateFieldInfo( int fieldX, int fieldY );
	void UpdateMapInfos();
private:
	svSprite *pNewTile();
	svMap *pNewMap();
};

// end of include only once
#endif
