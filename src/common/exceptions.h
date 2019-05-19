/* 
 * Drag[en]gine Library -- Game Engine
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
#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

// includes
#include "exceptions/decException.h"

// general exceptions
class deeAlreadyLoaded : public duException{
public: inline deeAlreadyLoaded(const char *Info, const char *File, int Line) :
	duException("AlreadyLoaded","Object is already loaded",Info,File,Line){}
};
class deeInvalidFormat : public duException{
public: inline deeInvalidFormat(const char *Info, const char *File, int Line) :
	duException("InvalidFormat","Invalid File Format",Info,File,Line){}
};

// model exceptions
class deeDupModelEntry : public duException{
public: inline deeDupModelEntry(const char *Info, const char *File, int Line) :
	duException("DupModelEntry","Duplicate Model Entry",Info,File,Line){}
};
class deeModelNotFound : public duException{
public: inline deeModelNotFound(const char *Info, const char *File, int Line) :
	duException("ModelNotFound","Model with the specified name could not be found",Info,File,Line){}
};

// animation exceptions
class deeDupAnimationEntry : public duException{
public: inline deeDupAnimationEntry(const char *Info, const char *File, int Line) :
	duException("DupAnimationEntry","Duplicate Animation Entry",Info,File,Line){}
};
class deeAnimationNotFound : public duException{
public: inline deeAnimationNotFound(const char *Info, const char *File, int Line) :
	duException("AnimationNotFound","Animation with the specified name could not be found",Info,File,Line){}
};

// skin exceptions
class deeDupSkinEntry : public duException{
public: inline deeDupSkinEntry(const char *Info, const char *File, int Line) :
	duException("DupSkinEntry","Duplicate Skin Entry",Info,File,Line){}
};
class deeSkinNotFound : public duException{
public: inline deeSkinNotFound(const char *Info, const char *File, int Line) :
	duException("SkinNotFound","Skin with the specified name could not be found",Info,File,Line){}
};

// Font exceptions
class deeDupFontEntry : public duException{
public: inline deeDupFontEntry(const char *Info, const char *File, int Line) :
	duException("DupFontEntry","Duplicate Font Entry",Info,File,Line){}
};
class deeFontNotFound : public duException{
public: inline deeFontNotFound(const char *Info, const char *File, int Line) :
	duException("FontNotFound","Font with the specified name could not be found",Info,File,Line){}
};

// map exceptions
class deeDupMapEntry : public duException{
public: inline deeDupMapEntry(const char *Info, const char *File, int Line) :
	duException("DupMapEntry","Duplicate Map Entry",Info,File,Line){}
};
class deeMapNotFound : public duException{
public: inline deeMapNotFound(const char *Info, const char *File, int Line) :
	duException("MapNotFound","Map with the specified name could not be found",Info,File,Line){}
};

// directory exceptions
class deeDirectoryNotFound : public duException{
public: inline deeDirectoryNotFound(const char *Info, const char *File, int Line) :
	duException("DirectoryNotFound","Directory does not exist",Info,File,Line){}
};
class deeDirectoryRead : public duException{
public: inline deeDirectoryRead(const char *Info, const char *File, int Line) :
	duException("DirectoryReadFailed","Directory read error",Info,File,Line){}
};

// script exceptions
class deeInvalidSyntax : public duException{
public: inline deeInvalidSyntax(const char *Info, const char *File, int Line) :
	duException("InvalidSyntax","Invalid Script Syntax",Info,File,Line){}
};
class deeScriptError : public duException{
public: inline deeScriptError(const char *Info, const char *File, int Line) :
	duException("ScriptError","Error in Script System",Info,File,Line){}
};

// module exceptions
class deeNoModuleFound : public duException{
public: inline deeNoModuleFound(const char *Info, const char *File, int Line) :
	duException("NoModuleFound","No Working Module could be found",Info,File,Line){}
};

// end of include only once
#endif
