#ifndef __Camera
#define __Camera
#define TO_RAD(DEG) (DEG * 3.1416 / 180)
#define TO_DEG(RAD) (RAD / 3.1416 * 180.0)
#define ANGLE_INC 3.5
#define POSITION_INC 1


#include "VectorRR.h"
#include <math.h>

class Camera : public VectorRR
{
private:
	float Velocidad_Movimiento = 1.6, Velocidad_Cámara = .85f;
public:
	VectorRR posc, dirc;
	GLdouble px, py, pz, dx, dy, dz, ux, uy, uz;

	float RadioColisón = 3;
	float angle = 0, dir = 0;
	float viewVectorMag = 0, magX = 0, magZ = 0;

	bool ableToMove;

	Camera()
	{
	}

	void cameraInitialize()
	{
		px = 180, py = 30, pz = 330, dx = 0, dy = 23, dz = -25;
		ux = 0, uy = 1, uz = 0;
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
		viewVectorMag = sqrt(pow(dx - px, 2) + pow(dz - pz, 2));
		ableToMove = true;
	}

	void cameraUpdate()
	{
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
	}

	void move(char movDir)
	{
		dir = 0;

		magX = dx - px;
		magZ = dz - pz;

		switch (movDir)
		{
		case 'f':
			dir = TO_DEG(atan2(magZ, magX));
			break;
		case 'b':
			dir = TO_DEG(atan2(magZ, magX)) - 180;
			break;
		case 'l':
			dir = TO_DEG(atan2(magZ, magX)) - 90;
			break;
		case 'r':
			dir = TO_DEG(atan2(magZ, magX)) + 90;
			break;
		}
		if (ableToMove)
		{
			pz += POSITION_INC * sin(TO_RAD(dir)) * Velocidad_Movimiento;
			dz += POSITION_INC * sin(TO_RAD(dir)) * Velocidad_Movimiento;
			px += POSITION_INC * cos(TO_RAD(dir)) * Velocidad_Movimiento;
			dx += POSITION_INC * cos(TO_RAD(dir)) * Velocidad_Movimiento;
		}
	}

	void turnRight()
	{
		angle = angle + ANGLE_INC * Velocidad_Cámara;
		dx = sin(TO_RAD(angle)) * viewVectorMag + px;
		dz = -cos(TO_RAD(angle)) * viewVectorMag + pz;
	}

	void turnLeft()
	{
		angle = angle - ANGLE_INC * Velocidad_Cámara;
		dx = sin(TO_RAD(angle)) * viewVectorMag + px;
		dz = -cos(TO_RAD(angle)) * viewVectorMag + pz;
	}

	void turnUp()
	{
		if (dy < 50 + py)
			dy += 1 * Velocidad_Cámara;
	}

	void turnDown()
	{
		if (dy > -50 + py)
			dy -= 1 * Velocidad_Cámara;
	}
};
#endif