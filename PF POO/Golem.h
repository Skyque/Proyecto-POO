#ifndef _GOLEM_
#define _GOLEM_

#include "Enemigo.h"
#include "Model.h"
using namespace EDXFramework;

namespace Skyque {
	class Golem : public Skyque::Enemigo {
	public:
		Golem(float PosInicial[3]);
		~Golem();
		void Moverse(float X, float Z);
		void Atacar(float X, float Z);
		enum Ataques {
			Preparación1,
			Primero,
			Preparación2,
			Segundo,
			Preparación3,
			Tercero
		};
	};
}

#endif
