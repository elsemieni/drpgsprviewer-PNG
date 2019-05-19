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
#ifndef _DECMDLINEARGS_H_
#define _DECMDLINEARGS_H_



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Manages command line arguments.
 *
 * @todo - Adding function to remove arguments
 */
class deCmdLineArgs{
private:
	char **pArgs;
	int pCount;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/** Creates a new empty command line object. */
	deCmdLineArgs();
	~deCmdLineArgs();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/** Retrieves the count of arguments. */
	inline int GetCount() const{ return pCount; }
	/** Retrieves the argument at the given index. */
	const char *GetArgument( int index ) const;
	/** Adds an argument to the end of the list. */
	void AddArgument( const char *arg );
	/**
	 * Parses command line passed into arguments which are then added
	 * to the end of the list. Arguments are considered separated by
	 * a white space. Quoted text strings are considered one argument.
	 * This function is present for operating systems not providing
	 * an entry point function which already splits up the arguments.
	 */
	void AddArgsSplit( const char *argLine );
	/*@}*/
};

// end of include only once
#endif
