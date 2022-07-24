#ifndef _HACHA_
#define _HACHA_

#include "Armas.h"

namespace Skyque {
	class Hacha : public Skyque::Armas {
	public:
		Hacha(Model* Modelo, float PosInicial[3]);
		void Atacar();
		void Idle();
		void setRY(float angulo);
		void resetAtaque();
		enum Slash {
			Preparacion,
			Primero,
			Segundo,
			Tercero,
			Cuarto
		};
	private:
		bool Cambiado = false;
		~Hacha();
	};
}

#endif