#ifndef _ARMAS_
#define _ARMAS_
#include "Model.h"

using namespace EDXFramework;

namespace Skyque {
	class Armas {
	protected:
		Model* Modelo;
		bool Atacando = false;
		int Estado_Idle = 0, CooldownAtaque, DejarDeAtacar;
		int Ataque = 0;
		float cambio = 0;
		float Daño, Posición[3], Posición_Neutral[3], Rotación[3], Rotación_Neutral[3], offsetY, Escala;
		float Vida = 7, CooldownDaño = 2000, RadioAtaque;
	public:
		virtual ~Armas(){}
		virtual void Atacar() = 0;
		virtual void Idle() = 0;
		virtual void resetAtaque() = 0;
		bool getAtacando() { return this->Atacando; }
		int getCooldownAtaque() { return this->CooldownAtaque; }
		int getDejardeAtacar() { return this->DejarDeAtacar; }
		float getVida() { return this->Vida; }
		float getDaño() { return this->Daño; }
		float getDistanciaAtaque() { return this->RadioAtaque; }
		float getCooldownDaño(){ return this->CooldownDaño; }
		float getX() { return this->Posición[0]; }
		float getY() { return this->Posición[1]; }
		float getZ() { return this->Posición[2]; }
		float getRX() { return this->Rotación[0]; }
		float getRY() { return this->Rotación[1]; }
		float getRZ() { return this->Rotación[2]; }
		float getEscala() { return this->Escala; }
		void setAtacando(bool pAtacando) { this->Atacando = pAtacando; }
		void setX(double pX) { this->Posición_Neutral[0] = pX; this->Posición[0] = this->Posición_Neutral[0]; }
		void setY(double pY) { this->Posición_Neutral[1] = pY - this->offsetY; this->Posición[1] = this->Posición_Neutral[1]; }
		void setZ(double pZ) { this->Posición_Neutral[2] = pZ; this->Posición[2] = this->Posición_Neutral[2]; }
		virtual void setRY(float angulo) = 0;
		void Dibuja() { this->Modelo->Draw(); }
		void RecibeDaño(float pDaño) { this->Vida -= pDaño;}
	};
}

#endif