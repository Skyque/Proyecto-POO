#ifndef _SELECTOR_
#define _SELECTOR

#include "Armas.h"
#include "Model.h"

using namespace EDXFramework;

namespace Skyque {
	class Selector {
	private:
		Model * Modelo;
		float Posisci�n[3];
		enum ArmaElegida {
			Espada=1,
			Leviathan,
			Longinus
		};
		int Elecci�n;
	public:
		Selector(Model*, float, float, float, int);
		~Selector() { delete this; }
		Armas* SeleccionarArma(Armas*, float[3]);
		void Dibujar() { this->Modelo->Draw(); }
		float getX() { return this->Posisci�n[0]; }
		float getY() { return this->Posisci�n[1]; }
		float getZ() { return this->Posisci�n[2]; }
	};
}

#endif
