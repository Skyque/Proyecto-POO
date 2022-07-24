#ifndef _KATANA_
#define _KATANA_

#include "Armas.h"
#include "Model.h"
using namespace EDXFramework;

namespace Skyque {
	class Katana : public Skyque::Armas {
	public:
		Katana(Model* Modelo, float PosInicial[3]);
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
			Quinto
		};
	private:
		~Katana();
	};
}

#endif