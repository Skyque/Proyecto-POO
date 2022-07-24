#include "Selector.h"
#include "Model.h"
#include "Katana.h"
#include "Hacha.h"
#include "Lanza.h"

using namespace EDXFramework;

Skyque::Selector::Selector(Model* Modelo, float pX, float pY, float pZ, int Arma) {
	this->Modelo = Modelo;
	this->Posisción[0] = pX;
	this->Posisción[1] = pY;
	this->Posisción[2] = pZ;
	this->Elección = Arma;
}

Skyque::Armas* Skyque::Selector::SeleccionarArma(Armas* Arma, float Pos[3]) {
	if (Arma != NULL) {
		delete Arma;
	}
	switch (this->Elección) {
	case Espada:
		Arma = new Katana(this->Modelo, Pos);
		break;
	case Leviathan:
		Arma = new Hacha(this->Modelo, Pos);
		break;
	case Longinus:
		Arma = new Lanza(this->Modelo, Pos);
		break;
	}
	return Arma;
}