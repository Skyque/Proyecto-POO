#ifndef _ENEMIGO_
#define _ENEMIGO_
#include "Model.h"
#define PI 3.1416
using namespace EDXFramework;

namespace Skyque {
	class Enemigo {
	protected:
		Model** Correr; //Modelos de movimiento
		Model** Ataque; //Modelos de ataque
		Model* ModeloActual; //Modelo desplegado en pantalla
		bool Atacando = false, Da�ado = false, Loop = false, Muerto = false;
		int AtaqueActual = 0, Frame = 0;
		float Vida, Da�o, CooldownAtaque, DelayAnimacion, CooldownDa�o = 0, Posici�n[3], Posici�n_Neutral[3], Rotaci�n[3], Rotaci�n_Neutral[3], offsetY, Escala, Velocidad, DistanciaAtacar;
	public:
		virtual void Moverse(float, float) = 0;
		virtual void Atacar(float, float) = 0;
		float getCooldownDa�o(){ return this->CooldownDa�o; }
		float getDistanciaAtacar() { return this->DistanciaAtacar; }
		bool getAtacando() { return this->Atacando; }
		bool getDa�ado() { return this->Da�ado; }
		bool getMuerto() { return this->Muerto; }
		float getDa�o() { return this->Da�o; }
		void recibeDa�o(float pDa�o) { this->Vida -= pDa�o; this->Da�ado = true; }
		float getX() { return this->Posici�n[0]; }
		float getY() { return this->Posici�n[1]; }
		float getZ() { return this->Posici�n[2]; }
		float getRX() { return this->Rotaci�n[0]; }
		float getRY() { return this->Rotaci�n[1]; }
		float getRZ() { return this->Rotaci�n[2]; }
		float getEscala() { return this->Escala; }
		float getVida() { return this->Vida; }
		float getoffsetY(){ return this->offsetY; }
		void setRY(float X, float Z) { 
			float ComponenteX = X - this->Posici�n[0];
			float ComponenteZ = Z - this->Posici�n[3];
			float Angulo = atan2(ComponenteZ, ComponenteX) * 180 / PI;
			this->Rotaci�n[1] = Angulo; 
		}
		void setAtacando(bool pAtacando) { this->Atacando = pAtacando; }
		float DistanciaAJugador(float X, float Z) {
			return sqrt(pow(X - this->Posici�n[0], 2) + pow(Z - this->Posici�n[2], 2));
		}
		void Dibuja() { this->ModeloActual->Draw(); }
		void HabilitaDa�o() {
			this->CooldownDa�o++;
			if (this->CooldownDa�o >= 60) {
				this->CooldownDa�o = 0;
				this->Da�ado = false;
			}
		}
		void Muere() { this->Muerto = true; }
		virtual ~Enemigo() {}
	};
}

#endif