#include "SilentHill.h"
#include "Model.h"
#define TO_RAD(DEG) (DEG * 3.1416 / 180)
using namespace EDXFramework;

Skyque::SilentHill::SilentHill(float PosInicial[3]) {
	for (int i = 0; i <= 2; i++) {
		this->Posición_Neutral[i] = PosInicial[i];
		this->Posición[i] = this->Posición_Neutral[i];
		this->Rotación_Neutral[i] = 0;
		this->Rotación[i] = this->Rotación_Neutral[i];
	}
	this->DistanciaAtacar = 60;
	this->Escala = .6f;
	this->offsetY = 13;
	this->Vida = 6;
	this->Daño = .5;
	this->Velocidad = 4;
	this->Correr = new Model * [3];
	this->Correr[0] = new Model("Modelos//PareceDeSilentHill//Correr1.obj", "Modelos//PareceDeSilentHill//flesh_diffuse_1024.bmp", 1);
	this->Correr[1] = new Model("Modelos//PareceDeSilentHill//Correr2.obj", "Modelos//PareceDeSilentHill//flesh_diffuse_1024.bmp", 1);
	this->Correr[2] = new Model("Modelos//PareceDeSilentHill//Correr3.obj", "Modelos//PareceDeSilentHill//flesh_diffuse_1024.bmp", 1);
	this->Ataque = new Model * [4];
	this->Ataque[0]= new Model("Modelos//PareceDeSilentHill//Ataque1.obj", "Modelos//PareceDeSilentHill//flesh_diffuse_1024.bmp", 1);
	this->Ataque[1] = new Model("Modelos//PareceDeSilentHill//Ataque2.obj", "Modelos//PareceDeSilentHill//flesh_diffuse_1024.bmp", 1);
	this->Ataque[2] = new Model("Modelos//PareceDeSilentHill//Ataque3.obj", "Modelos//PareceDeSilentHill//flesh_diffuse_1024.bmp", 1);
	this->Ataque[3] = new Model("Modelos//PareceDeSilentHill//Ataque4.obj", "Modelos//PareceDeSilentHill//flesh_diffuse_1024.bmp", 1);

	this->ModeloActual = Correr[0];
}

void Skyque::SilentHill::Moverse(float X, float Z) {
	//Movimiento
	if (this->Posición[0] < X) {
		this->Posición[0] += .3 * Velocidad;
	}
	else {
		this->Posición[0] -= .3 * Velocidad;
	}
	if (this->Posición[2] < Z) {
		this->Posición[2] += .3 * Velocidad;
	}
	else {
		this->Posición[2] -= .3 * Velocidad;
	}
	//Animaciones
	this->ModeloActual = Correr[Frame];
	this->DelayAnimacion++;
	if (!this->Loop) {
		if (this->DelayAnimacion >= 17) {
			this->DelayAnimacion = 0;
			this->Frame++;
		}
		if (this->Frame == 2) {
			this->Loop = true;
		}
	}
	else {
		if (this->DelayAnimacion >= 17) {
			this->DelayAnimacion = 0;
			this->Frame--;
		}
		if (this->Frame == 0) {
			this->Loop = false;
		}
	}
}

void Skyque::SilentHill::Atacar(float X, float Z) {
	//Movimiento
	if (this->Posición[0] < X) {
		this->Posición[0] += .3 * Velocidad;
	}
	else {
		this->Posición[0] -= .3 * Velocidad;
	}
	if (this->Posición[2] < Z) {
		this->Posición[2] += .3 * Velocidad;
	}
	else {
		this->Posición[2] -= .3 * Velocidad;
	}
	//Animaciones
	switch (this->AtaqueActual) {
	case Preparación1:
		this->ModeloActual = this->Ataque[0];
		this->CooldownAtaque++;
		if (CooldownAtaque >= 35) {
			this->AtaqueActual = Primero;
			this->CooldownAtaque = 0;
		}
		break;
	case Primero:
		this->CooldownAtaque++;
		this->ModeloActual = this->Ataque[1];
		if (this->CooldownAtaque >= 25) {
			this->AtaqueActual = Preparación2;
			this->CooldownAtaque = 0;
			this->Atacando = false;
		}
		break;
	case Preparación2:
		this->ModeloActual = this->Ataque[2];
		this->CooldownAtaque++;
		if (CooldownAtaque >= 15) {
			this->AtaqueActual = Segundo;
			this->CooldownAtaque = 0;
		}
		break;
	case Segundo:
		this->CooldownAtaque++;
		this->ModeloActual = this->Ataque[3];
		if (this->CooldownAtaque >= 20) {
			this->AtaqueActual = Preparación3;
			this->CooldownAtaque = 0;
			this->Atacando = false;
		}
		break;
	case Preparación3:
		this->ModeloActual = this->Ataque[3];
		this->CooldownAtaque++;
		if (CooldownAtaque >= 15) {
			this->AtaqueActual = Tercero;
			this->CooldownAtaque = 0;
		}
		break;
	case Tercero:
		this->CooldownAtaque++;
		this->ModeloActual = this->Ataque[2];
		if (this->CooldownAtaque >= 20) {
			this->AtaqueActual = Preparación1;
			this->CooldownAtaque = 0;
			this->Atacando = false;
		}
		break;
	}
}

Skyque::SilentHill::~SilentHill() {
	for (int i = 0; i <= 2; i++) {
		delete Correr[i];
	}
	for (int i = 0; i <= 3; i++) {
		delete Ataque[i];
	}
}