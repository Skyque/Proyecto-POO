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
		bool Atacando = false, Dañado = false, Loop = false, Muerto = false;
		int AtaqueActual = 0, Frame = 0;
		float Vida, Daño, CooldownAtaque, DelayAnimacion, CooldownDaño = 0, Posición[3], Posición_Neutral[3], Rotación[3], Rotación_Neutral[3], offsetY, Escala, Velocidad, DistanciaAtacar;
	public:
		virtual void Moverse(float, float) = 0;
		virtual void Atacar(float, float) = 0;
		float getCooldownDaño(){ return this->CooldownDaño; }
		float getDistanciaAtacar() { return this->DistanciaAtacar; }
		bool getAtacando() { return this->Atacando; }
		bool getDañado() { return this->Dañado; }
		bool getMuerto() { return this->Muerto; }
		float getDaño() { return this->Daño; }
		void recibeDaño(float pDaño) { this->Vida -= pDaño; this->Dañado = true; }
		float getX() { return this->Posición[0]; }
		float getY() { return this->Posición[1]; }
		float getZ() { return this->Posición[2]; }
		float getRX() { return this->Rotación[0]; }
		float getRY() { return this->Rotación[1]; }
		float getRZ() { return this->Rotación[2]; }
		float getEscala() { return this->Escala; }
		float getVida() { return this->Vida; }
		float getoffsetY(){ return this->offsetY; }
		void setRY(float X, float Z) { 
			float ComponenteX = X - this->Posición[0];
			float ComponenteZ = Z - this->Posición[3];
			float Angulo = atan2(ComponenteZ, ComponenteX) * 180 / PI;
			this->Rotación[1] = Angulo; 
		}
		void setAtacando(bool pAtacando) { this->Atacando = pAtacando; }
		float DistanciaAJugador(float X, float Z) {
			return sqrt(pow(X - this->Posición[0], 2) + pow(Z - this->Posición[2], 2));
		}
		void Dibuja() { this->ModeloActual->Draw(); }
		void HabilitaDaño() {
			this->CooldownDaño++;
			if (this->CooldownDaño >= 60) {
				this->CooldownDaño = 0;
				this->Dañado = false;
			}
		}
		void Muere() { this->Muerto = true; }
		virtual ~Enemigo() {}
	};
}

#endif