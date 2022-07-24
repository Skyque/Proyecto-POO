#ifndef _DECORACIONES_
#define _DECORACIONES_
#include "Model.h"

using namespace EDXFramework;

namespace Skyque {
	class Decoraciones {
	public:
		Decoraciones(Model* pModelo, float Pos[3], float pEscala, bool pCircular, float radio) {
			for (int i = 0; i <= 2; i++) {
				this->Posici�n[i] = Pos[i];
			}
			this->Escala = pEscala;
			this->Modelo = pModelo;
			this->Circular = pCircular;
			if (Circular) {
				this->Colisi�n = radio;
			}
			else {
				this->Puntos[0][0] = 226.275;//XA
				this->Puntos[0][1] = 408.59;//ZA

				this->Puntos[1][0] = 78.99;//XB
				this->Puntos[1][1] = 408.59;//ZB

				this->Puntos[2][0] = 78.99;//XC
				this->Puntos[2][1] = 301.4;//ZC

				this->Puntos[3][0] = 78.99;//XD
				this->Puntos[3][1] = 270.89;//ZD

				this->Puntos[4][0] = 226.275;//XE
				this->Puntos[4][1] = 270.89;//ZE

				this->Puntos[5][0] = 226.275;//XF
				this->Puntos[5][1] = 301.4;//ZF

				this->Puntos[6][0] = 168.36;//XG
				this->Puntos[6][1] = 301.4;//ZG

				this->Puntos[7][0] = 150;//XH
				this->Puntos[7][1] = 301.4;//ZH

				this->Puntos[8][0] = 182.67;//XI
				this->Puntos[8][1] = 270.89;//ZI

				this->Puntos[9][0] = 126.78;//XJ
				this->Puntos[9][1] = 270.89;//ZJ
			}
		}
		~Decoraciones() {}
		float getX() { return this->Posici�n[0]; }
		float getY() { return this->Posici�n[1]; }
		float getZ() { return this->Posici�n[2]; }
		float getEscala() { return this->Escala; }
		float getRadio() { return this->Colisi�n; }
		void Dibuja() { this->Modelo->Draw(); }
		bool DetectaColisi�n(float X, float Z, float RadioJugador) {
			if (this->Circular) {
				float distancia = sqrt(pow(X - this->Posici�n[0], 2) + pow(Z - this->Posici�n[2], 2));
				if (distancia < this->Colisi�n + RadioJugador) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				float Distancia = abs(Z - this->Puntos[0][1]);
				if (X <= this->Puntos[0][0] && X >= this->Puntos[1][0] && Distancia <= 2) {
					return true;
				}
				Distancia = abs(X - this->Puntos[1][0]);
				if (Z <= this->Puntos[1][1] && Z >= this->Puntos[3][1] && Distancia <= 2) {
					return true;
				}
				Distancia = abs(X - this->Puntos[0][0]);
				if (Z <= this->Puntos[0][1] && Z >= this->Puntos[4][1] && Distancia <= 2) {
					return true;
				}
				Distancia = abs(Z - this->Puntos[5][1]);
				if (X <= this->Puntos[5][0] && X >= this->Puntos[6][0] && Distancia <= 2) {
					return true;
				}
				Distancia = abs(Z - this->Puntos[2][1]);
				if (X <= this->Puntos[7][0] && X >= this->Puntos[2][0] && Distancia <= 2) {
					return true;
				}
				Distancia = abs(Z - this->Puntos[4][1]);
				if (X <= this->Puntos[4][0] && X >= this->Puntos[8][0] && Distancia <= 2) {
					return true;
				}
				Distancia = abs(Z - this->Puntos[8][1]);
				if (X <= this->Puntos[9][0] && X >= this->Puntos[3][0] && Distancia <= 2) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	private:
		bool Circular;
		float Posici�n[3], Escala, Colisi�n;
		float Puntos[10][2];
		Model* Modelo;
	};
}

#endif