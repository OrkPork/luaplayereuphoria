/*
 * LuaPlayer Euphoria
 * ------------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE for details.
 *
 * Copyright (c) 2005 Frank Buss <fb@frank-buss.de> (aka Shine)
 * Copyright (c) 2009 Danny Glover <danny86@live.ie> (aka Zack) 
 *
 * Official Forum : http://www.retroemu.com/forum/forumdisplay.php?f=148
 * For help using LuaPlayer, code help, tutorials etc please visit the official site : http://www.retroemu.com/forum/forumdisplay.php?f=148
 *
 * Credits:
 * 
 * (from Shine/Zack) 
 *
 *   many thanks to the authors of the PSPSDK from http://forums.ps2dev.org
 *   and to the hints and discussions from #pspdev on freenode.net
 *
 * (from Zack Only)
 *
 * Thanks to Brunni for the Swizzle/UnSwizzle code (taken from oslib). 
 * Thanks to Arshia001 for AALIB. It is the sound engine used in LuaPlayer Euphoria. 
 * Thanks to HardHat for being a supportive friend and advisor.
 * Thanks to Benhur for IntraFont.
 * Thanks to Jono for the moveToVram code.
 * Thanks to Raphael for the Vram manager code.
 * Thanks to Osgeld, Dan369 & Cmbeke for testing LuaPlayer Euphoria for me and coming up with some neat ideas for it.
 * Thanks to the entire LuaPlayer Euphoria userbase, for using it and for supporting it's development. You guys rock!
 *
 *
 */

#include "include/luaplayer.h"
#include "libs/vfpu/pspmath.h"

//Set vfpu random generator seed
static int lua_VfpuSrand(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.srand(no) takes one argument (a number)");
	}
	
	unsigned int x = luaL_checkint(L, 1);
	
	vfpu_srand(x);
	
	return 0;
}

//Return random float value
static int lua_VfpuRandFloat(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
	{
		return luaL_error(L, "Vfpu.randfloat(min, max) takes two arguments (min, max)");
	}
	
	float min = luaL_checknumber(L, 1);	
	float max = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, vfpu_randf(min, max));

	return 1;
}

//Return random color value in 8888 format
static int lua_VfpuRandColor(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
	{
		return luaL_error(L, "Vfpu.randColor(min,max) takes two arguments (min, maxß)");
	}
	
	float min = luaL_checknumber(L, 1);	
	float max = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, vfpu_rand_8888(min, max));

	return 1;
}

//Generate an identity matrix -//NOT IMPLEMENTED YET
static int lua_VfpuIdentityMatrix(lua_State *L)
{
	return 0;
}

//Generate a translation matrix -//NOT IMPLEMENTED YET
static int lua_VfpuTranslateMatrix(lua_State *L)
{
	return 0;
}

//Generate a perspective projection matrix -//NOT IMPLEMENTED YET
static int lua_VfpuPerspectiveMatrix(lua_State *L)
{
	return 0;
}

//Generate an orthogonal  projection matrix -//NOT IMPLEMENTED YET
static int lua_VfpuOrthoMatrix(lua_State *L)
{
	return 0;
}

//Returns an integer no greater than or no less than the given value
static int lua_VfpuFloor(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.floor(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_floor(x));

	return 1;
}

//Returns an integer no greater than or no less than the given value
static int lua_VfpuCeil(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.ceil(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_ceil(x));

	return 1;
}

//Return the absolute, or non-negative value, of a given value
static int lua_VfpuAbs(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.abs(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_abs(x));

	return 1;
}

//Calculates the square root
static int lua_VfpuSqrt(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.sqrt(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_sqrtf(x));

	return 1;
}

//Calculate maximum numeric value
static int lua_VfpuFmaxf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
	{
		return luaL_error(L, "Vfpu.fmax(x, y) takes two arguments (x, y)");
	}
	
	float x = luaL_checknumber(L, 1);	
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, vfpu_fmaxf(x, y));

	return 1;
}

//Calculate minimum numeric value
static int lua_VfpuFminf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
	{
		return luaL_error(L, "Vfpu.fmin(x, y) takes two arguments (x, y)");
	}
	
	float x = luaL_checknumber(L, 1);	
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, vfpu_fminf(x, y));

	return 1;
}

//Calculate sine
static int lua_VfpuSinf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.sin(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_sinf(x));

	return 1;
}

//Calculate cosine
static int lua_VfpuCosf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.cos(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_cosf(x));

	return 1;
}

//Calculate tangent
static int lua_VfpuTanf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.tan(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_tanf(x));

	return 1;
}

//Calculate inverse sine (arcsin)
static int lua_VfpuAsinf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.asin(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_asinf(x));

	return 1;
}

//Calculate inverse cosine (arccos)
static int lua_VfpuAcosf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.acos(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_acosf(x));

	return 1;
}

//Calculate inverse tangent (arctan)
static int lua_VfpuAtanf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.atan(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_atanf(x));

	return 1;
}

//Calculate inverse tangent, with proper quadrant fixup
static int lua_VfpuAtan2f(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
	{
		return luaL_error(L, "Vfpu.atan2f(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, vfpu_atan2f(x, y));

	return 1;
}

//Calculate hyperbolic sine
static int lua_VfpuSinhf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.sinh(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_sinhf(x));

	return 1;
}

//Calculate hyperbolic cosine
static int lua_VfpuCoshf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.cosh(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_coshf(x));

	return 1;
}

// Calculate hyperbolic tangent
static int lua_VfpuTanhf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.tanh(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_tanhf(x));

	return 1;
}

//Calculate sine and cosine
static int lua_VfpuSinCos(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.sincos(radian) takes one argument (radians)");
	}
	
	float rad = luaL_checknumber(L, 1);
	float sin = 0.0f;
	float cos = 0.0f;
	
	vfpu_sincos(rad, &sin, &cos);
	lua_pushnumber(L, sin);	
	lua_pushnumber(L, cos);
	
	return 2;
}

//Calculate exponent of x
static int lua_VfpuExpf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.exp(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_expf(x));

	return 1;
}

//Calculate logarithm of x
static int lua_VfpuLogf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.log(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_logf(x));

	return 1;
}

//Calculate x raised to the power of y
static int lua_VfpuPowf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
	{
		return luaL_error(L, "Vfpu.pow(x, y) takes two arguments (x, y)");
	}
	
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, vfpu_powf(x, y));

	return 1;
}

///Calculate floating point remainder of x/y
static int lua_VfpuFmodf(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 2)
	{
		return luaL_error(L, "Vfpu.fmod(x, y) takes two arguments (x, y)");
	}
	
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	
	lua_pushnumber(L, vfpu_fmodf(x, y));

	return 1;
}

//Perform a smooth acceleration/deceleration curve based on the input time value
static int lua_VfpuEaseInOut(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if(argc != 1)
	{
		return luaL_error(L, "Vfpu.inout(no) takes one argument (a number)");
	}
	
	float x = luaL_checknumber(L, 1);	
	
	lua_pushnumber(L, vfpu_ease_in_out(x));

	return 1;
}

//Normalize a 3d vector, returning a unit vector of length = 1 -//NOT IMPLEMENTED YET
static int lua_VfpuNormalizeVector(lua_State *L)
{
	return 0;
}

//Zero a 3d vector -//NOT IMPLEMENTED YET
static int lua_VfpuZeroVector(lua_State *L) 
{
	return 0;
}

//Scale a 3d vector  -//NOT IMPLEMENTED YET
static int luaVfpuScaleVector(lua_State *L) 
{
	return 0;
}

//Add 2 3d vectors  -//NOT IMPLEMENTED YET
static int lua_VfpuAddVector(lua_State *L)
{
	return 0;
}

//Generate rotation matrix for environment map. -//NOT IMPLEMENTED YET
static int lua_VfpuEnvmapMatrix(lua_State *L)
{
	return 0;
}

//Transform 3d vector by 4x4 matrix -//NOT IMPLEMENTED YET
static int lua_VfpuTransformVector(lua_State *L)
{
	return 0;
}

//Convert input sphere coordinates to cartesian coordinates -//NOT IMPLEMENTED YET
static int lua_VfpuSphereToCartesian(lua_State *L)
{
	return 0;
}

//Generate an identity quaternion -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionIdentity(lua_State *L)
{
	return 0;
}

//Copy a quaternion -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionCopy(lua_State *L)
{
	return 0;
}

//Normalize a quaternion -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionNormalize(lua_State *L)
{
	return 0;
}

//Multiply 2 quaternions -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionMultiply(lua_State *L)
{
	return 0;
}

//Make a quaternion from euler angles -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionFromEuler(lua_State *L)
{
	return 0;
}

//Calculate exponent of a quaternion -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionExp(lua_State *L)
{
	return 0;
}

//Calculate logarithm of a quaternion -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionLn(lua_State *L)
{
	return 0;
}

//Return a sample from a linear interpolation of 2 quaternions -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionSampleLinear(lua_State *L)
{
	return 0;
}

//Return a sample from a hermite spline interpolation -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionSampleHermite(lua_State *L)
{
	return 0;
}

//Return a tangent point for hermite spline interpolation -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionHermiteTangent(lua_State *L)
{
	return 0;
}

//Convert quaternion to rotation matrix -//NOT IMPLEMENTED YET
static int lua_VfpuQuaternionToMatrix(lua_State *L)
{
	return 0;
}

//Register VFPU Functions
static const luaL_reg VFPU_functions[] = {
	{"srand",						lua_VfpuSrand},
	{"randFloat",					lua_VfpuRandFloat},
	{"randColor", 					lua_VfpuRandColor},
	//{"identityMatrix", 				lua_VfpuIdentityMatrix}, 		-//NOT IMPLEMENTED YET
	//{"translateMatrix", 			lua_VfpuTranslateMatrix},    		-//NOT IMPLEMENTED YET
	//{"perspectiveMatrix", 			lua_VfpuPerspectiveMatrix},  	-//NOT IMPLEMENTED YET
	//{"orthoMatrix",					lua_VfpuOrthoMatrix}, 			-//NOT IMPLEMENTED YET
	{"floor",						lua_VfpuFloor},
	{"ceil", 						lua_VfpuCeil},
	{"abs",							lua_VfpuAbs},
	{"sqrt",						lua_VfpuSqrt},
	{"fmax",						lua_VfpuFmaxf},
	{"fmin",						lua_VfpuFminf},
	{"sin", 						lua_VfpuSinf},
	{"cos", 						lua_VfpuCosf},
	{"tan", 						lua_VfpuTanf},
	{"asin", 						lua_VfpuAsinf},
	{"acos", 						lua_VfpuAcosf},
	{"atan",						lua_VfpuAtanf},
	{"atan2",						lua_VfpuAtan2f},
	{"sinh",						lua_VfpuSinhf},
	{"cosh",						lua_VfpuCoshf},
	{"tanh",						lua_VfpuTanhf},
	{"sincos",						lua_VfpuSinCos},
	{"exp",							lua_VfpuExpf},
	{"log",							lua_VfpuLogf},
	{"pow",							lua_VfpuPowf},
	{"fmod",						lua_VfpuFmodf},
	{"inout",						lua_VfpuEaseInOut},
	//{"normalizeVector",				lua_VfpuNormalizeVector}, 		-//NOT IMPLEMENTED YET
	//{"zeroVector",					lua_VfpuZeroVector}, 			-//NOT IMPLEMENTED YET
	//{"scaleVector",					lua_VfpuScaleVector}, 			-//NOT IMPLEMENTED YET
	//{"addVector",						lua_VfpuAddVector},	 			-//NOT IMPLEMENTED YET
	//{"envmapMatrix",					lua_VfpuEnvmapMatrix},			-//NOT IMPLEMENTED YET
	//{'transformVector",				lua_VfpuTransformVector},		-//NOT IMPLEMENTED YET
	//{"sphereToCartesian",				lua_VfpuSphereToCartesian},		-//NOT IMPLEMENTED YET
	//{"quaternionIdentity",			lua_VfpuQuaternionIdentity},	-//NOT IMPLEMENTED YET
	//{"quaternionCopy",				lua_VfpuQuaternionCopy},		-//NOT IMPLEMENTED YET
	//{"quaternionNormalize",			lua_VfpuQuaternionNormalize},	-//NOT IMPLEMENTED YET
	//{"quaternionMultiply",			lua_VfpuQuaternionMultiply},	-//NOT IMPLEMENTED YET
	//{"quaternionFromEuler",			lua_VfpuQuaternionFromEuler},	-//NOT IMPLEMENTED YET
	//{"quaternionExp",					lua_VfpuQuaternionExp},			-//NOT IMPLEMENTED YET
	//{"quaternionLn",					lua_VfpuQuaternionLn},			-//NOT IMPLEMENTED YET
	//{"quaternionSampleLinear",		lua_VfpuQuaternionSampleLinear},-//NOT IMPLEMENTED YET
	//{"quaternionSampleHermite",		lua_VfpuQuaternionSampleHermite},-//NOT IMPLEMENTED YET
	//{"quaternionHermiteTangent",		lua_VfpuQuaternionHermiteTangent},-//NOT IMPLEMENTED YET
	{0,0}
};

void luaMath_init(lua_State *L) {
	luaL_openlib(L, "Vfpu", VFPU_functions, 0);
}
