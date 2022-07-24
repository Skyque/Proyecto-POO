#include "Lanza.h"
#include "Model.h"
#define TO_RAD(DEG) (DEG * 3.1416 / 180)

using namespace EDXFramework;

Skyque::Lanza::Lanza(Model* Modelo, float PosInicial[3]) {
	this->Daño = .8f;
	this->offsetY = 5;
	this->Escala = 1;
	this->RadioAtaque = 65;
	this->CooldownAtaque = 700;//cooldown entre cada ataque
	this->DejarDeAtacar = 15000;//tiempo sin atacar para pasar a idle
	this->Modelo = Modelo;
	for (int i = 0; i <= 2; i++) {
		this->Posición_Neutral[i] = PosInicial[i];
		this->Posición[i] = this->Posición_Neutral[i];
	}
	this->Rotación_Neutral[0] = 0;
	this->Rotación[0] = Rotación_Neutral[0];
	this->Rotación_Neutral[1] = 0;
	this->Rotación[1] = Rotación_Neutral[1];
	this->Rotación_Neutral[2] = -90;
	this->Rotación[2] = Rotación_Neutral[2];
	glPushMatrix();
	glTranslatef(this->Posición_Neutral[0], this->Posición_Neutral[0], this->Posición_Neutral[0]);
	glScalef(1.5, 1.5, 1.5);
	this->Modelo->Draw();
	glPopMatrix();
}

Skyque::Lanza::~Lanza(){}

void Skyque::Lanza::Idle() {
	switch (this->Estado_Idle) {
	case 0:
		this->Rotación[1] = this->Rotación_Neutral[1] - cambio;
		if (this->Rotación[2] < -80) {
			this->Rotación[2] = this->Rotación_Neutral[2] + cambio;
		}
		if (this->Rotación[1] > this->Rotación_Neutral[1] - 15) {
			cambio += .3;
		}
		else {
			this->Rotación[1] = this->Rotación_Neutral[1] - 15;
			this->Rotación[2] = -80;
			cambio = 0;
			Estado_Idle++;
		}
		break;
	case 1:
		this->Rotación[1] = this->Rotación_Neutral[1] + cambio - 15;
		if (this->Rotación[2] < -70) {
			this->Rotación[2] = this->Rotación_Neutral[2] + cambio + 10;
		}
		if (this->Rotación[1] < this->Rotación_Neutral[1]) {
			cambio += .3;
		}
		else {
			cambio = 0;
			Estado_Idle++;
			this->Rotación[1] = this->Rotación_Neutral[1];
			this->Rotación[2] = -70;
		}
		break;
	case 2:
		this->Rotación[1] = this->Rotación_Neutral[1] + cambio;
		if (this->Rotación[2] > -80) {
			this->Rotación[2] = this->Rotación_Neutral[2] - cambio + 20;
		}
		if (this->Rotación[1] < this->Rotación_Neutral[1] + 15) {
			cambio += .3;
		}
		else {
			cambio = 0;
			Estado_Idle++; 
			this->Rotación[1] = this->Rotación_Neutral[1] + 15;
			this->Rotación[2] = -80;
		}
		break;
	case 3:
		this->Rotación[1] = this->Rotación_Neutral[1] - cambio + 15;
		if (this->Rotación[2] > -90) {
			this->Rotación[2] = this->Rotación_Neutral[2] - cambio + 10;
		}
		if (this->Rotación[1] > this->Rotación_Neutral[1]) {
			cambio += .3;
		}
		else {
			this->Rotación[1] = this->Rotación_Neutral[1];
			this->Rotación[2] = -90;
			cambio = 0;
			Estado_Idle = 0;
		}
		break;
	}
}

void Skyque::Lanza::Atacar() {
	switch (this->Ataque) {
	case Preparacion:
		this->Rotación[0] = this->Rotación_Neutral[0];
		this->Rotación[1] = this->Rotación_Neutral[1];
		this->Rotación[2] = this->Rotación_Neutral[2];
		cambio = 0;
		this->Ataque = Primero;
		break;
	case Primero:
		this->Rotación[1] = this->Rotación_Neutral[1] + cambio;
		this->Rotación[2] = this->Rotación_Neutral[2] + cambio;
		glTranslatef(cambio * cos(TO_RAD(this->Rotación[1])), 0, cambio * -sin(TO_RAD(this->Rotación[1])));
		if (cambio < 15) {
			cambio += .8;
		}
		else {
			this->Ataque = Segundo;
			cambio = 0;
		}
		break;
	case Segundo:
		this->Rotación[1] = this->Rotación_Neutral[1] - cambio;
		this->Rotación[2] = this->Rotación_Neutral[2] + cambio;
		glTranslatef(cambio * cos(TO_RAD(this->Rotación[1])), 0, cambio * -sin(TO_RAD(this->Rotación[1])));
		if (cambio < 15) {
			cambio += .8;
		}
		else {
			this->Ataque = Tercero;
			this->Atacando = false;
		}
		break;
	case Tercero:
		this->Rotación[1] = this->Rotación_Neutral[1];
		this->Rotación[2] = this->Rotación_Neutral[2] + cambio - 20;
		if (cambio < 10) {
			glTranslatef(cambio * cos(TO_RAD(this->Rotación[1])), 0, cambio * -sin(TO_RAD(this->Rotación[1])));
		}
		else {
			glTranslatef(10 * cos(TO_RAD(this->Rotación[1])), 0, 10 * -sin(TO_RAD(this->Rotación[1])));
		}
		if (this->Rotación[2] < this->Rotación_Neutral[2] + 20) {
			cambio += 1;
		}
		else {
			this->Ataque = Cuarto;
			this->Atacando = false;
		}
		break;
	case Cuarto:
		this->Rotación[1] = this->Rotación_Neutral[1];
		this->Rotación[2] = this->Rotación_Neutral[2] + cambio;
		glTranslatef(cambio * cos(TO_RAD(this->Rotación[1])), 0, cambio * -sin(TO_RAD(this->Rotación[1])));
		if (cambio < 20) {
			cambio += 1.2;
		}
		else {
			this->Ataque = Quinto;
			cambio = 0;
		}
		break;
	case Quinto:
		this->Rotación[1] = this->Rotación_Neutral[1] - cambio;
		this->Rotación[2] = this->Rotación_Neutral[2] + cambio;
		glTranslatef(cambio * cos(TO_RAD(this->Rotación[1])), 0, cambio * -sin(TO_RAD(this->Rotación[1])));
		if (cambio < 20) {
			cambio += 1.2;
		}
		else {
			this->Ataque = Sexto;
			cambio = 0;
		}
		break;
	case Sexto:
		this->Rotación[1] = this->Rotación_Neutral[1] + cambio;
		this->Rotación[2] = this->Rotación_Neutral[2] + cambio;
		glTranslatef(cambio * cos(TO_RAD(this->Rotación[1])), 0, cambio * -sin(TO_RAD(this->Rotación[1])));
		if (cambio < 20) {
			cambio += 1.2;
		}
		else {
			this->Ataque = Septimo;
			cambio = 0;
			this->Atacando = false;
		}
		break;
	case Septimo:
		this->Rotación[1] = this->Rotación_Neutral[1] + cambio - 30;
		this->Rotación[2] = -80;
		if (cambio < 10) {
			glTranslatef(cambio * cos(TO_RAD(this->Rotación[1])), 0, cambio * -sin(TO_RAD(this->Rotación[1])));
		}
		else {
			glTranslatef(10 * cos(TO_RAD(this->Rotación[1])), 0, 10 * -sin(TO_RAD(this->Rotación[1])));
		}
		if (this->Rotación[1] < this->Rotación_Neutral[1] + 30) {
			cambio += 1.5;
		}
		else {
			this->Ataque = Preparacion;
			cambio = 0;
			this->Atacando = false;
		}
		break;
	}
}

void Skyque::Lanza::resetAtaque() {
	this->Ataque = Preparacion;
}

void Skyque::Lanza::setRY(float angulo) {
	this->Rotación_Neutral[1] = -angulo + 90;
}