/*
** This file exists merely to produce the typeinfo-function for BDirectWindow
** (i.e. the symbol __tf13BDirectWindow).
** It seems that the version of this function included in the Be-libs isn't
** working (it crashes GLTeapot, for instance). So we use this file to
** generate a working version of this function which will be linked into any
** application automatically, fixing the problem.
** TODO: check if this applies to Dano/Zeta and deactivate this if it doesn't.
**/

#include <typeinfo>
#include <DirectWindow.h>

void 
dummy() 
{
	typeid(BDirectWindow); 
}
