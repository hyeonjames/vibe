#include "vibe_obj.h"
#include<stdio.h>
namespace vibe
{
	unsigned int object::_reference()
	{
		printf("reference! %d\n",_refc+1);
		return ++_refc;
	}
	unsigned int object::_release(){
		printf("release! %d\n",_refc-1);
		return --_refc;
	}

	
}