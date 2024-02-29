#include "PDoor.h"

CPDoor::CPDoor(int obj_width, int obj_height,int pas)
	:Object(pos, rad, angle) 
{

}

void CPDoor::Init(VECTOR pos, float obj_width, float obj_height, int pas) {
	position = pos;
	width = obj_width;
	height = obj_height;
	all_handle = pas;
}