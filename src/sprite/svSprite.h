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
#ifndef _SVSPRITE_H_
#define _SVSPRITE_H_

// includes

// predefinitions
class svSpriteImage;



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Sprite.
 * Manages a sprite. Each sprite composes of one or more
 * sprite images. The images are stored as 24-bit RGB.
 */
class svSprite{
private:
	svSpriteImage **pImages;
	int pImageCount, pImageSize;
	char *pFilename;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates a new sprite object. */
	svSprite();
	/** Cleans up the sprite upon destruction. */
	~svSprite();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/** Retrieves the filename of the sprite if any. */
	inline const char *GetFilename() const{ return ( const char * )pFilename; }
	/** Sets the filename of the sprite if any. */
	void SetFilename( const char *filename );
	/** Retrieves the count of images. */
	inline int GetImageCount() const{ return pImageCount; }
	/** Retrieves the image at the given index. */
	svSpriteImage *GetImageAt( int index ) const;
	/** Determines if the given image is already part of the sprite. */
	bool HasImage( svSpriteImage *image ) const;
	/**
	 * Adds the given image to the sprite. The image must not be
	 * part of the sprite.
	 */
	void AddImage( svSpriteImage *image );
	/**
	 * Removes the given image from the sprite. The image is deleted
	 * after beeing removed from the sprite.
	 */
	void RemoveImage( svSpriteImage *image );
	/** Removes all images from the sprite and deletes them. */
	void RemoveAllImages();
	/*@}*/
private:
	void pCleanUp();
	int pFindImage( svSpriteImage *image ) const;
};

// end of include only once
#endif
