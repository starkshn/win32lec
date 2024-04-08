#include "pch.h"
#include "WMath.h"

float WLerp(float A, float B, float Alpha)
{
	return ((1.f - Alpha) * A) + (Alpha * B);
}

void CameraShake(Vec2 pos)
{
	
}
