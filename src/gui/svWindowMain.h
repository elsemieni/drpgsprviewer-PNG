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
#ifndef _SVWINDOWMAIN_H_
#define _SVWINDOWMAIN_H_

// includes
#include "../drpgsprviewer.h"
#include "../foxtoolkit.h"

// predefinitions
class deCmdLineArgs;
class svSprite;
class svAnimationSet;
class svViewSprite;
class svViewMap;



// class svWindowMain
class svWindowMain : public FXMainWindow{
	FXDECLARE( svWindowMain )
protected:
	svWindowMain();
public:
	enum eFoxIDs{
		ID_CANVAS=FXMainWindow::ID_LAST,
		ID_FILEOPEN,
		ID_FILEQUIT,
		ID_INFOABOUT,
		ID_TABVIEWS,
		ID_LAST
	};
	enum eFileTypes{
		eftSprite,
		eftAnimation,
		eftTile,
		eftMap,
		EFT_COUNT
	};
private:
	FXMenuPane *pMenuFile;
	FXMenuPane *pMenuInfos;
	FXTabItem *pTabItemSprite;
	FXTabBook *pTabViews;
	svViewSprite *pViewSprite;
	svViewMap *pViewMap;
	deCmdLineArgs *pCmdArgs;
	char *pFilename;
	int pLastFileType;
public:
	// constructor, destructor
	svWindowMain( FXApp* app, deCmdLineArgs *args );
	~svWindowMain();
	virtual void create();
	// management
	void Show( bool show );
	void CleanUp();
	bool QuitRequest();
	void Update();
	void UpdateWindowTitle();
	// callbacks
	long onFileOpen( FXObject *sender, FXSelector selector, void *data );
	long onFileQuit( FXObject *sender, FXSelector selector, void *data );
	long onInfoAbout( FXObject *sender, FXSelector selector, void *data );
	// general management
	inline const char *GetFilename() const{ return pFilename; }
	void SetFilename( const char *filename, int type );
private:
};

// end of include only once
#endif
