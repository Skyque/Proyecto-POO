#include "Cucaracha.h"
#include "Model.h"
#define TO_RAD(DEG) (DEG * 3.1416 / 180)
using namespace EDXFramework;

Skyque::Cucaracha::Cucaracha(float PosInicial[3]) {
	for (int i = 0; i <= 2; i++) {
		this->Posición_Neutral[i] = PosInicial[i];
		this->Posición[i] = this->Posición_Neutral[i];
		this->Rotación_Neutral[i] = 0;
		this->Rotación[i] = this->Rotación_Neutral[i];
	}
	this->DistanciaAtacar = 50;
	this->Escala = .2f;
	this->offsetY = 2;
	this->Vida = 1;
	this->Daño = 1;
	this->Velocidad = 3;
	this->Correr = new Model*[3];
	this->Correr[0] = new Model("Modelos//CucarachaRara//Correr1.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	this->Correr[1] = new Model("Modelos//CucarachaRara//Correr2.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	this->Correr[2] = new Model("Modelos//CucarachaRara//Correr3.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	this->Ataque = new Model*[7];
	this->Ataque[0] = new Model("Modelos//CucarachaRara//Ataque1.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	this->Ataque[1] = new Model("Modelos//CucarachaRara//Ataque2.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	this->Ataque[2] = new Model("Modelos//CucarachaRara//Ataque3.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	this->Ataque[3] = new Model("Modelos//CucarachaRara//Ataque4.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	this->Ataque[4] = new Model("Modelos//CucarachaRara//Ataque5.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	this->Ataque[5] = new Model("Modelos//CucarachaRara//Ataque6.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
	//this->Ataque[6] = new Model("Modelos//CucarachaRara//Ataque7.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);

	this->ModeloActual = Correr[0];
}

void Skyque::Cucaracha::Moverse(float X, float Z) {
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
		if (this->DelayAnimacion >= 12) {
			this->DelayAnimacion = 0;
			this->Frame++;
		}
		if (this->Frame == 2) {
			this->Loop = true;
		}
	}
	else {
		if (this->DelayAnimacion >= 12) {
			this->DelayAnimacion = 0;
			this->Frame--;
		}
		if (this->Frame == 0) {
			this->Loop = false;
		}
	}
}

void Skyque::Cucaracha::Atacar( float X, float Z) {
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
		if (CooldownAtaque >= 25) {
			this->AtaqueActual = Primero;
			this->CooldownAtaque = 0;
		}
		break;
	case Primero:
		this->CooldownAtaque++;
		this->ModeloActual = this->Ataque[1];
		if (this->CooldownAtaque >= 15) {
			this->AtaqueActual = Preparación2;
			this->CooldownAtaque = 0;
			this->Atacando = false;
		}
		break;
	case Preparación2:
		this->ModeloActual = this->Ataque[2];
		this->CooldownAtaque++;
		if (CooldownAtaque >= 25) {
			this->AtaqueActual = Segundo;
			this->CooldownAtaque = 0;
		}
		break;
	case Segundo:
		this->CooldownAtaque++;
		this->ModeloActual = this->Ataque[3];
		if (this->CooldownAtaque >= 15) {
			this->AtaqueActual = Preparación3;
			this->CooldownAtaque = 0;
			this->Atacando = false;
		}
		break;
	case Preparación3:
		this->ModeloActual = this->Ataque[4];
		this->CooldownAtaque++;
		if (CooldownAtaque >= 35) {
			this->AtaqueActual = Tercero;
			this->CooldownAtaque = 0;
		}
		break;
	case Tercero:
		this->CooldownAtaque++;
		this->ModeloActual = this->Ataque[5];
		if (this->CooldownAtaque >= 25) {
			this->AtaqueActual = Preparación1;
			this->CooldownAtaque = 0;
			this->Atacando = false;
		}
		break;
	}
}

Skyque::Cucaracha::~Cucaracha() {
	for (int i = 0; i <= 2; i++) {
		delete Correr[i];
	}
	for (int i = 0; i <= 5; i++) {
		delete Ataque[i];
	}
}