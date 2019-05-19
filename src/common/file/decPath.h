/* 
 * Drag[en]gine Library -- Game Engine
 *
 * Copyright (C) 2004, Plüss Roland ( roland@rptd.dnsalias.net )
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
#ifndef _DECPATH_H_
#define _DECPATH_H_

// includes

// predefinitions



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Describes a file path.
 * This class provides an abstraction over file systems. A path
 * is represented as an optional prefix followed by 0 or more
 * path components. A string path can be parsed from a unix file
 * system used by the engine or native file system used by the
 * operating system below.
 */
class decPath{
private:
	char **pComponents;
	int pComponentCount, pComponentSize;
	char *pPrefix;
	char *pPath;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates an empty path. */
	decPath();
	/** Creates a new path from the given path. */
	decPath( const decPath &path );
	/** Cleans up the path object. */
	~decPath();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/** Retrieves the prefix of the path. */
	inline const char *GetPrefix() const{ return ( const char * )pPrefix; }
	/** Sets the prefix of the path. */
	void SetPrefix( const char *prefix );
	/** Sets the path from the given string path in unix form. */
	void SetFromUnix( const char *path );
	/** Sets the path from the given string path in native form. */
	void SetFromNative( const char *path );
	/** Sets the path to the empty path. */
	void SetEmpty();
	/**
	 * Retrieves the path as string in unix form.
	 * The string is allocated using new.
	 */
	const char *GetPathUnix();
	/**
	 * Retrieves the path as string in native form.
	 * The string is allocated using new.
	 */
	const char *GetPathNative();
	/** Determines if the path is empty. */
	bool IsEmpty() const;
	/**
	 * Determines if this path is an aboslute path.
	 * A path is absolute if it does have a prefix.
	 */
	bool IsAbsolute() const;
	/**
	 * Determines if this path is an relative path.
	 * A path is absolute if it does have a prefix.
	 */
	bool IsRelative() const;
	/** Sets the path from another path. */
	void SetFrom( const decPath &path );
	/** Adds a path to this path. */
	void AddPath( const decPath &path );
	/** Adds a unix string path to this path. */
	void AddUnixPath( const char *path );
	/** Adds a native string path to this path. */
	void AddNativePath( const char *path );
	/*@}*/
	
	/** @name Component Management */
	/*@{*/
	/** Retrieves the number of path components. */
	inline int GetComponentCount() const{ return pComponentCount; }
	/** Retrieves the component at the given index. */
	const char *GetComponent( int index ) const;
	/** Retrieves the last component ( aka the filename ). */
	const char *GetLastComponent() const;
	/** Adds a component to the path. */
	void AddComponent( const char *component );
	/** Removes the component at the given index from the path. */
	void RemoveComponent( int index );
	/** Removes the last component. */
	void RemoveLastComponent();
	/** Removes all components from the path. */
	void RemoveAllComponents();
	/** Determines if there are components in this path. */
	inline bool HasComponents() const{ return pComponentCount > 0; }
	/*@}*/
	
	/** @name String Path Testing */
	/*@{*/
	/** Determines if the given unix style string path is absolute. */
	static bool IsUnixPathAbsolute( const char *path );
	/** Determines if the given native style string path is absolute. */
	static bool IsNativePathAbsolute( const char *path );
	/*@}*/

private:
	void pParseRelativePath( const char *filename, int separator );
	int pGetPrefixLength( const char *path ) const;
	void pSetPrefix( const char *path, int prefixLength );
	char *pBuildPath( const char *separator ) const;
	void pUpdatePath();
	void pCleanUp();
};

// end of include only once
#endif
