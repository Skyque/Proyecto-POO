#include "Hacha.h"
#include "Model.h"

using namespace EDXFramework;

Skyque::Hacha::Hacha(Model* Modelo, float PosInicial[3]) {
	this->Ataque = Preparacion;
	this->Da�o = 3.5;
	this->offsetY = 4;
	this->Escala = .45;
	this->RadioAtaque = 35;
	this->CooldownAtaque = 1500;//cooldown entre cada ataque
	this->DejarDeAtacar = 2500;//tiempo sin atacar para pasar a idle
	this->Modelo = Modelo;
	for (int i = 0; i <= 2; i++) {
		this->Posici�n_Neutral[i] = PosInicial[i];
		this->Posici�n[i] = this->Posici�n_Neutral[i];
	}
	this->Rotaci�n_Neutral[0] = 0;
	this->Rotaci�n[0] = Rotaci�n_Neutral[0];
	this->Rotaci�n_Neutral[1] = 0;
	this->Rotaci�n[1] = Rotaci�n_Neutral[1];
	this->Rotaci�n_Neutral[2] = 0;
	this->Rotaci�n[2] = Rotaci�n_Neutral[2];
	glPushMatrix();
	glTranslatef(this->Posici�n_Neutral[0], this->Posici�n_Neutral[0], this->Posici�n_Neutral[0]);
	glRotatef(90, 1, 0, 0);
	glScalef(.65, .65, .65);
	this->Modelo->Draw();
	glPopMatrix();
}

Skyque::Hacha::~Hacha() {}


void Skyque::Hacha::Idle() {
	switch (Estado_Idle) {
	case 0:
		this->Rotaci�n[2] = this->Rotaci�n_Neutral[2] - 120;
		this->Rotaci�n[1] = this->Rotaci�n_Neutral[1] - cambio;
		if (this->Rotaci�n[1] > this->Rotaci�n_Neutral[1] - 25) {
			cambio += .5;
			this->offsetY -= .05;
		}
		else {
			Estado_Idle++;
		}
		break;
	case 1:
		this->Rotaci�n[1] = this->Rotaci�n_Neutral[1] - 25;
		if (this->Rotaci�n[2] < this->Rotaci�n_Neutral[2] + 240) {
			this->Rotaci�n[2] += 23;
		}
		else {
			Estado_Idle++;
		}
		break;
	case 2:
		this->Rotaci�n[2] = this->Rotaci�n_Neutral[2] - 120;
		this->Rotaci�n[1] = this->Rotaci�n_Neutral[1] - cambio;
		if (this->Rotaci�n[1] < this->Rotaci�n_Neutral[1]) {
			cambio -= .5;
			this->offsetY += .05;
		}
		else {
			Estado_Idle = 0;
			offsetY = 4;
			cambio = 0;
		}
		break;
	}
}

void Skyque::Hacha::Atacar() {
	switch (this->Ataque) {
	case Preparacion:
		cambio = 0;
		this->offsetY = 4;
		this->Ataque = Primero;
		break;
	case Primero:
		this->Rotaci�n[2] = this->Rotaci�n_Neutral[2] + 25;
		this->Rotaci�n[1] = this->Rotaci�n_Neutral[1] - cambio + 30;
		if (this->Rotaci�n[1] > this->Rotaci�n_Neutral[1] - 30) {
			cambio += 2;
			this->offsetY -= .06;
		}
		else {
			this->Ataque = Segundo;
			cambio = 0;
			this->offsetY = 4;
			this->Estado_Idle = 0;
			this->Atacando = false;
		}
		break;
	case Segundo:
		this->Rotaci�n[2] = this->Rotaci�n_Neutral[2] - 90;
		this->Rotaci�n[1] = this->Rotaci�n_Neutral[1];
		this->Rotaci�n[0] = this->Rotaci�n_Neutral[0] - cambio + 55;
		if (this->Rotaci�n[0] > this->Rotaci�n_Neutral[0] - 60) {
			cambio += 2;
		}
		else {
			this->Ataque = Tercero;
			cambio = 0;
			this->offsetY = 4;
			this->Estado_Idle = 0;
			this->Rotaci�n[0] = this->Rotaci�n_Neutral[0];
			this->Atacando = false;
		}
		break;
	case Tercero:
		this->Rotaci�n[2] = this->Rotaci�n_Neutral[2] + 180;
		this->offsetY = 2;
		this->Rotaci�n[1] = this->Rotaci�n_Neutral[1] - 50 + cambio;
		if (this->Rotaci�n[1] < this->Rotaci�n_Neutral[1] + 50) {
			cambio += 2.5;
		}
		else {
			this->Ataque = Cuarto;
			cambio = 0;
			this->Estado_Idle = 0;
			this->Atacando = false;
			this->offsetY = 4;
		}
		break;
	case Cuarto:
		if (!this->Cambiado) {
			this->offsetY = 1;
			Cambiado = true;
		}
		this->Rotaci�n[2] = this->Rotaci�n_Neutral[2] - 25;
		this->Rotaci�n[1] = this->Rotaci�n_Neutral[1] - cambio + 50;
		if (this->Rotaci�n[1] > this->Rotaci�n_Neutral[1] - 60) {
			cambio += 2;
			this->offsetY += .1;
		}
		else {
			this->Ataque = Preparacion;
			cambio = 0;
			this->offsetY = 4;
			this->Estado_Idle = 0;
			this->Atacando = false;
			this->Cambiado = false;
		}
		break;
	}
}

void Skyque::Hacha::resetAtaque() {
	this->Ataque = Preparacion;
}

void Skyque::Hacha::setRY(float angulo) {
	this->Rotaci�n_Neutral[1] = -angulo;
}
/*
* 	switch (Estado_Idle) {
	case 0:
		this->Rotaci�n[0] = -30;
		if (this->Rotaci�n[2] < this->Rotaci�n_Neutral[2] + 40) {
			cambio += .5;
			this->Rotaci�n[2] = this->Rotaci�n_Neutral[2] + cambio;
		}
		else {
			cambio = 0;
			this->Rotaci�n[2] = this->Rotaci�n_Neutral[2] + cambio;
		}
		break;
	}
*/