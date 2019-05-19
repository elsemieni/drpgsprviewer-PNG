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
#ifndef _SVANIMATIONSET_H_
#define _SVANIMATIONSET_H_

// includes

// predefinitions
class svAnimation;



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Animation Set.
 * Manages a set of animations.
 */
class svAnimationSet{
private:
	svAnimation **pAnims;
	int pAnimCount, pAnimSize;
	char *pSpriteFile;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates a new animation set object. */
	svAnimationSet();
	/** Cleans up the animation set upon destruction. */
	~svAnimationSet();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/** Retrieves the assigned sprite file. */
	inline const char *GetSpriteFile() const{ return ( const char * )pSpriteFile; }
	/** Sets the assigned sprite file. */
	void SetSpriteFile( const char *filename );
	/** Retrieves the count of animations. */
	inline int GetAnimationCount() const{ return pAnimCount; }
	/** Retrieves the animation at the given index. */
	svAnimation *GetAnimationAt( int index ) const;
	/** Determines if the given animation is already part of the animation set. */
	bool HasAnimation( svAnimation *animation ) const;
	/**
	 * Adds the given animation to the sprite. The animation must not be
	 * part of the animation set.
	 */
	void AddAnimation( svAnimation *animation );
	/**
	 * Removes the given animation from the animation set. The animation is deleted
	 * after beeing removed from the animation set.
	 */
	void RemoveAnimation( svAnimation *animation );
	/** Removes all animations from the sprite and deletes them. */
	void RemoveAllAnimations();
	/*@}*/
private:
	void pCleanUp();
	int pFindAnimation( svAnimation *animation ) const;
};

// end of include only once
#endif
