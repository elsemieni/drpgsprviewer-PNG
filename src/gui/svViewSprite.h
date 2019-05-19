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
#ifndef _SVVIEWSPRITE_H_
#define _SVVIEWSPRITE_H_

// includes
#include "../drpgsprviewer.h"
#include "../foxtoolkit.h"

// predefinitions
class deCmdLineArgs;
class svSprite;
class svAnimationSet;
class svWindowMain;



// class svViewSprite
class svViewSprite : public FXVerticalFrame{
	FXDECLARE( svViewSprite )
protected:
	svViewSprite();
public:
	enum eFoxIDs{
		ID_CANVAS=FXWindow::ID_LAST,
		ID_SCROLLINDEX,
		ID_CBANIM,
		ID_LAST
	};
private:
	svWindowMain *pWndMain;
	FXImageView *pViewImage;
	FXScrollBar *pScrollIndex;
	FXTextField *pEditIndex;
	FXTextField *pEditWidth;
	FXTextField *pEditHeight;
	FXTextField *pEditAnim;
	FXComboBox *pComboAnim;
	FXTextField *pEditStartFrame;
	FXTextField *pEditEndFrame;
	FXImage *pImage;
	int pImageIndex;
	int pAnimIndex;
	svSprite *pSprite;
	svAnimationSet *pAnimSet;
public:
	// constructor, destructor
	svViewSprite( svWindowMain *wndMain, FXComposite *parent );
	~svViewSprite();
	// management
	void Show( bool show );
	void CleanUp();
	void Update();
	// callbacks
	long onScrollIndexChanged( FXObject *sender, FXSelector selector, void *data );
	long onCBAnimChanged( FXObject *sender, FXSelector selector, void *data );
	// sprite
	inline svSprite *GetSprite() const{ return pSprite; }
	inline svAnimationSet *GetAnimationSet() const{ return pAnimSet; }
	inline FXImage *GetImage() const{ return pImage; }
	inline int GetImageIndex() const{ return pImageIndex; }
	inline int GetAnimationIndex() const{ return pAnimIndex; }
	void NewAnimation();
	void LoadSprite( const char *filename );
	void LoadAnimation( const char *filename );
	void LoadTile( const char *filename );
	void SetImageIndex( int index );
	void SetAnimationIndex( int index );
	void UpdateRanges();
private:
	svSprite *pNewSprite();
	svAnimationSet *pNewAnimationSet();
};

// end of include only once
#endif
