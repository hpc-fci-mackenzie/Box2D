/*
* Copyright (c) 2007-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Box2D/Common/b2Math.h"

const b2Vec2 b2Vec2_zero(0.0f, 0.0f);

/// Solve A * x = b, where b is a column vector. This is more efficient
/// than computing the inverse in one-shot cases.
b2Vec3 b2Mat33::Solve33(const b2Vec3& b) const
{
	float32 det = b2Dot(ex, b2Cross(ey, ez));
	if (det != 0.0f)
	{
		det = 1.0f / det;
	}
	b2Vec3 x;
	x.vector[0] = det * b2Dot(b, b2Cross(ey, ez));
	x.vector[1] = det * b2Dot(ex, b2Cross(b, ez));
	x.vector[2] = det * b2Dot(ex, b2Cross(ey, b));
	return x;
}

/// Solve A * x = b, where b is a column vector. This is more efficient
/// than computing the inverse in one-shot cases.
b2Vec2 b2Mat33::Solve22(const b2Vec2& b) const
{
	float32 a11 = ex.vector[0], a12 = ey.vector[0], a21 = ex.vector[1], a22 = ey.vector[1];
	float32 det = a11 * a22 - a12 * a21;
	if (det != 0.0f)
	{
		det = 1.0f / det;
	}
	b2Vec2 x;
	x.vector[0] = det * (a22 * b.vector[0] - a12 * b.vector[1]);
	x.vector[1] = det * (a11 * b.vector[1] - a21 * b.vector[0]);
	return x;
}

///
void b2Mat33::GetInverse22(b2Mat33* M) const
{
	float32 a = ex.vector[0], b = ey.vector[0], c = ex.vector[1], d = ey.vector[1];
	float32 det = a * d - b * c;
	if (det != 0.0f)
	{
		det = 1.0f / det;
	}

	M->ex.vector[0] =  det * d;	M->ey.vector[0] = -det * b; M->ex.vector[2] = 0.0f;
	M->ex.vector[1] = -det * c;	M->ey.vector[1] =  det * a; M->ey.vector[2] = 0.0f;
	M->ez.vector[0] = 0.0f; M->ez.vector[1] = 0.0f; M->ez.vector[2] = 0.0f;
}

/// Returns the zero matrix if singular.
void b2Mat33::GetSymInverse33(b2Mat33* M) const
{
	float32 det = b2Dot(ex, b2Cross(ey, ez));
	if (det != 0.0f)
	{
		det = 1.0f / det;
	}

	float32 a11 = ex.vector[0], a12 = ey.vector[0], a13 = ez.vector[0];
	float32 a22 = ey.vector[1], a23 = ez.vector[1];
	float32 a33 = ez.vector[2];

	M->ex.vector[0] = det * (a22 * a33 - a23 * a23);
	M->ex.vector[1] = det * (a13 * a23 - a12 * a33);
	M->ex.vector[2] = det * (a12 * a23 - a13 * a22);

	M->ey.vector[0] = M->ex.vector[1];
	M->ey.vector[1] = det * (a11 * a33 - a13 * a13);
	M->ey.vector[2] = det * (a13 * a12 - a11 * a23);

	M->ez.vector[0] = M->ex.vector[2];
	M->ez.vector[1] = M->ey.vector[2];
	M->ez.vector[2] = det * (a11 * a22 - a12 * a12);
}
