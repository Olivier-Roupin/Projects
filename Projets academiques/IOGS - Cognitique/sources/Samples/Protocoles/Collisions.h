/************************************************************************************
 Filename    :   Collisions.h
 Content     :   
 Created     :   November 6th, 2018
 Author      :   Olivier Roupin
 Copyright   :   
 *************************************************************************************/

#ifndef Collisions_h
#define Collisions_h

#include "GL/CAPI_GLE.h"
#include "Extras/OVR_Math.h"
#include "OVR_CAPI_GL.h"
#include <assert.h>

using namespace OVR;

#ifndef VALIDATE
    #define VALIDATE(x, msg) if (!(x)) { MessageBoxA(NULL, (msg), "OculusRoomTiny", MB_ICONERROR | MB_OK); exit(-1); }
#endif

#ifndef OVR_DEBUG_LOG
    #define OVR_DEBUG_LOG(x)
#endif

bool CollisionDroiteSeg(Vector2f A, Vector2f B, Vector2f O, Vector2f P)
{
	Vector2f AO(O - A), AP(P - A), AB(B - A);
	if ((AB.x*AP.y - AB.y*AP.x)*(AB.x*AO.y - AB.y*AO.x) < 0)
		return true;
	else
		return false;
}

bool CollisionSegSeg(Vector2f A, Vector2f B, Vector2f O, Vector2f P)
{
	if (CollisionDroiteSeg(A, B, O, P) == false)
		return false;  // inutile d'aller plus loin si le segment [OP] ne touche pas la droite (AB)
	Vector2f OP(P - O), AB(B - A);

	float k = -(A.x*OP.y - O.x*OP.y - OP.x*A.y + OP.x*O.y) / (AB.x*OP.y - AB.y*OP.x);
	if (k < 0 || k>1)
		return false;
	else
		return true;
}

bool CollisionPointCercle(Vector2f A, Vector2f C, float rayon)
{
	float d2 = A.DistanceSq(C);
	if (d2 > rayon*rayon)
		return false;
	else
		return true;
}

bool CollisionDroite(Vector2f A, Vector2f B, Vector2f C, float rayon)
{
	Vector2f u(B - A), AC(C - A);
	float numerateur = u.x*AC.y - u.y*AC.x;   // norme du vecteur v
	if (numerateur < 0)
		numerateur = -numerateur;   // valeur absolue ; si c'est négatif, on prend l'opposé.
	float denominateur = u.Length();  // norme de u
	float CI = numerateur / denominateur;
	if (CI < rayon)
		return true;
	else
		return false;
}

bool CollisionSegment(Vector2f A, Vector2f B, Vector2f C, float rayon)
{
	if (CollisionDroite(A, B, C, rayon) == false)
		return false;  // si on ne touche pas la droite, on ne touchera jamais le segment
	Vector2f AB(B - A), AC(C - A), CB(B - C);
	float pscal1 = AB.Dot(AC);  // produit scalaire
	float pscal2 = AB.Dot(CB);  // produit scalaire
	if (pscal1 >= 0 && pscal2 >= 0)
		return true;   // I entre A et B, ok.
					   // dernière possibilité, A ou B dans le cercle
	if (CollisionPointCercle(A, C, rayon))
		return true;
	if (CollisionPointCercle(B, C, rayon))
		return true;
	return false;
}

Vector2f ProjectionI(Vector2f A, Vector2f B, Vector2f C)
{
	Vector2f u(B - A), AC(C - A);
	float ti = u.Dot(AC) / u.LengthSq();
	Vector2f I(A + u * ti);
	return I;
}

Vector2f Normale(Vector2f AB)
{
	Vector2f N;
	N.x = -AB.y;
	N.y = AB.x;
	N.Normalize();
	return N;
}

Vector2f Normale(Vector2f A, Vector2f B)
{
	return Normale(B - A);
}

Vector2f Projeter(Vector2f A, Vector2f B, Vector2f T)
{
	Vector2f F;
	Vector2f I = ProjectionI(A, B, T);
	float it = (T - I).Length();
	Vector2f AB = B - A;
	Vector2f N = Normale(AB);
	if ((I - A).Dot(AB) >= 0 && (I - B).Dot(AB) <= 0) // Si la projection du centre du cercle est sur le segment
	{
		F = T + N * (0.75f - it); // IT < R car collision
	}
	else if ((I - A).Dot(AB) < 0) // La projection sort du cercle mais A est dans le cercle
	{
		if (0.75f*0.75f > A.DistanceSq(I))
			F = T + N * (sqrtf(0.75f*0.75f - A.DistanceSq(I)) - it);
		else
			F = T;
	}
	else // La projection sort du cercle mais B est dans le cercle
	{
		if (0.75f*0.75f > B.DistanceSq(I))
			F = T + N * (sqrtf(0.75f*0.75f - B.DistanceSq(I)) - it);
		else
			F = T;
	}
	return F;
}

#endif // Collisions_h
