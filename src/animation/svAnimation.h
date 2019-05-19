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
#ifndef _SVANIMATION_H_
#define _SVANIMATION_H_

// includes

// predefinitions



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Animation.
 * Manages an animation.
 */
class svAnimation{
private:
	char *pName;
	int pStartFrame;
	int pEndFrame;
	int pPlaybackSpeed;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates a new animation object. */
	svAnimation();
	/** Creates a new animation object with the given frame range. */
	svAnimation( int startFrame, int endFrame );
	/** Cleans up the animation upon destruction. */
	~svAnimation();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	inline const char *GetName() const{ return ( const char * )pName; }
	/** Retrieves the start frame index. */
	inline int GetStartFrame() const{ return pStartFrame; }
	/** Retrieves the end frame index. */
	inline int GetEndFrame() const{ return pEndFrame; }
	/** Retrieves the count of frames. */
	inline int GetFrameCount() const{ return pEndFrame - pStartFrame + 1; }
	/** Retrieves the playback speed. */
	inline int GetPlaybackSpeed() const{ return pPlaybackSpeed; }
	/**
	 * Sets the start and end frame. The end frame has to be equal or
	 * greater than the start frame. Both have to be 0 or greater.
	 */
	void SetFrameRange( int startFrame, int endFrame );
	/**
	 * Sets the playback speed.
	 */
	void SetPlaybackSpeed( int playbackSpeed );
	/** Sets the name of the animation. */
	void SetName( const char *name );
	/*@}*/
private:
};

// end of include only once
#endif
