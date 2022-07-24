#ifndef _CUCARACHA_
#define _CUCARACHA_

#include "Enemigo.h"
#include "Model.h"
using namespace EDXFramework;

namespace Skyque {
	class Cucaracha : public Skyque::Enemigo {
	public:
		Cucaracha(float PosInicial[3]);
		~Cucaracha();
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
