#ifndef _LANZA_
#define _LANZA_

#include "Armas.h"

namespace Skyque {
	class Lanza : public Skyque::Armas {
	public:
		Lanza(Model* Modelo, float PosInicial[3]);
		void Atacar();
		void Idle();
		void setRY(float angulo);
		void resetAtaque();
		enum Slash {
			Preparacion,
			Primero,
			Segundo,
			Tercero,
			Cuarto,
			Quinto,
			Sexto,
			Septimo
		};
	private:
		~Lanza();
	};
}

#endif