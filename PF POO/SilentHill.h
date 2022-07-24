#ifndef _SILENTHIL_
#define _SILENTHILL_

#include "Enemigo.h"
#include "Model.h"
using namespace EDXFramework;

namespace Skyque {
	class SilentHill : public Skyque::Enemigo {
	public:
		SilentHill(float PosInicial[3]);
		~SilentHill();
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