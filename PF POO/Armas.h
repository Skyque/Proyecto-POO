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
		float Da�o, Posici�n[3], Posici�n_Neutral[3], Rotaci�n[3], Rotaci�n_Neutral[3], offsetY, Escala;
		float Vida = 7, CooldownDa�o = 2000, RadioAtaque;
	public:
		virtual ~Armas(){}
		virtual void Atacar() = 0;
		virtual void Idle() = 0;
		virtual void resetAtaque() = 0;
		bool getAtacando() { return this->Atacando; }
		int getCooldownAtaque() { return this->CooldownAtaque; }
		int getDejardeAtacar() { return this->DejarDeAtacar; }
		float getVida() { return this->Vida; }
		float getDa�o() { return this->Da�o; }
		float getDistanciaAtaque() { return this->RadioAtaque; }
		float getCooldownDa�o(){ return this->CooldownDa�o; }
		float getX() { return this->Posici�n[0]; }
		float getY() { return this->Posici�n[1]; }
		float getZ() { return this->Posici�n[2]; }
		float getRX() { return this->Rotaci�n[0]; }
		float getRY() { return this->Rotaci�n[1]; }
		float getRZ() { return this->Rotaci�n[2]; }
		float getEscala() { return this->Escala; }
		void setAtacando(bool pAtacando) { this->Atacando = pAtacando; }
		void setX(double pX) { this->Posici�n_Neutral[0] = pX; this->Posici�n[0] = this->Posici�n_Neutral[0]; }
		void setY(double pY) { this->Posici�n_Neutral[1] = pY - this->offsetY; this->Posici�n[1] = this->Posici�n_Neutral[1]; }
		void setZ(double pZ) { this->Posici�n_Neutral[2] = pZ; this->Posici�n[2] = this->Posici�n_Neutral[2]; }
		virtual void setRY(float angulo) = 0;
		void Dibuja() { this->Modelo->Draw(); }
		void RecibeDa�o(float pDa�o) { this->Vida -= pDa�o;}
	};
}

#endif