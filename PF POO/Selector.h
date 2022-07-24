#ifndef _SELECTOR_
#define _SELECTOR

#include "Armas.h"
#include "Model.h"

using namespace EDXFramework;

namespace Skyque {
	class Selector {
	private:
		Model * Modelo;
		float Posisción[3];
		enum ArmaElegida {
			Espada=1,
			Leviathan,
			Longinus
		};
		int Elección;
	public:
		Selector(Model*, float, float, float, int);
		~Selector() { delete this; }
		Armas* SeleccionarArma(Armas*, float[3]);
		void Dibujar() { this->Modelo->Draw(); }
		float getX() { return this->Posisción[0]; }
		float getY() { return this->Posisción[1]; }
		float getZ() { return this->Posisción[2]; }
	};
}

#endif
