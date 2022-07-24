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
			Preparaci�n1,
			Primero,
			Preparaci�n2,
			Segundo,
			Preparaci�n3,
			Tercero
		};
	};
}

#endif