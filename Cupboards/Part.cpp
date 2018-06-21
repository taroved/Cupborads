#include "Part.h"

float Part::fit(float coordinate, float size)
{
	size /= 2;
	return coordinate - size;
}