#include "Katana.h"
#include "Model.h"

using namespace EDXFramework;

Skyque::Katana::Katana(Model* Modelo, float PosInicial[3]) {
	this->Ataque = Preparacion;
	this->Daño = 1.5f;
	this->offsetY = 3;
	this->Escala = .25;
	this->RadioAtaque = 45;
	this->CooldownAtaque = 550;//cooldown entre cada ataque
	this->DejarDeAtacar = 2500;//tiempo sin atacar para pasar a idle
	this->Modelo = Modelo;
	for (int i = 0; i <= 2; i++) {
		this->Posición_Neutral[i] = PosInicial[i];
		this->Posición[i] = this->Posición_Neutral[i];
	}
	this->Rotación_Neutral[0] = 180;
	this->Rotación[0] = Rotación_Neutral[0];
	this->Rotación_Neutral[1] = 0; 
	this->Rotación[1] = Rotación_Neutral[1];
	this->Rotación_Neutral[2] = -20;
	this->Rotación[2] = Rotación_Neutral[2];
	glPushMatrix();
	glTranslatef(this->Posición_Neutral[0], this->Posición_Neutral[0], this->Posición_Neutral[0]);
	glRotatef(180, 1, 0, 0);
	glScalef(.35, .35, .35);
	this->Modelo->Draw();
	glPopMatrix();
}

Skyque::Katana::~Katana(){}

void Skyque::Katana::setRY(float angulo) {
	this->Rotación_Neutral[1] = angulo - 90;
}

void Skyque::Katana::resetAtaque() {
	this->Ataque = Preparacion;
}

void Skyque::Katana::Atacar() {
	glRotatef(180, 1, 0, 0);
	switch (this->Ataque) {
	case Preparacion: //regresamos a la posición inicial y de ahí comenzamos
		for (int i = 0; i <= 2; i++) {
			this->Posición[i] = this->Posición_Neutral[i];
			this->Rotación[i] = this->Rotación_Neutral[i];
		}
		cambio = 0;
		this->Ataque = Primero;
		break;
	case Primero:
		this->Rotación[0] = 135;
		if (this->Rotación[1] >= this->Rotación_Neutral[1] - 5) {
			cambio += 1.3;
			this->Rotación[1] = this->Rotación_Neutral[1] - cambio + 25;//rota a la izquierda
			this->Rotación[2] = this->Rotación_Neutral[2] + cambio * 2.5;//sube el arma
		}
		else {
			cambio = 0;
			this->Ataque = Segundo;
			this->Atacando = false;
			this->Rotación[0] = Rotación_Neutral[0];
			this->Rotación[1] = Rotación_Neutral[1];
			this->Rotación[2] = Rotación_Neutral[2];
		}
		break;
	case Segundo:
		this->Rotación[0] = -90;
		if (this->Rotación[1] < this->Rotación_Neutral[1] + 55) {
			cambio += 4;
			this->Rotación[1] = this->Rotación_Neutral[1] + cambio - 55;//rota a la derecha
		}
		else {
			cambio = 0;
			this->Ataque = Tercero;
			this->Atacando = false;
			this->Rotación[0] = Rotación_Neutral[0];
			this->Rotación[1] = Rotación_Neutral[1];
			this->Rotación[2] = Rotación_Neutral[2];
		}
		break;
	case Tercero:
		this->Rotación[1] = this->Rotación_Neutral[1];
		if (this->Rotación[2] > this->Rotación_Neutral[2] - 50) {
			cambio += 3.5;
			this->Rotación[2] = this->Rotación_Neutral[2] - cambio + 55;//baja el arma
		}
		else {
			cambio = 0;
			this->Ataque = Cuarto;
			this->Atacando = false;
			this->Rotación[0] = Rotación_Neutral[0];
			this->Rotación[1] = Rotación_Neutral[1];
			this->Rotación[2] = Rotación_Neutral[2];
		}
		break;
	case Cuarto:
		//Primer slash
		this->Rotación[0] = -135;
		this->Rotación[1] = this->Rotación_Neutral[1] + cambio - 25;//rota a la derecha
		if (this->Rotación[1] <= this->Rotación_Neutral[1] + 5) {
			cambio += 1.3;
			this->Rotación[2] = this->Rotación_Neutral[2] + cambio * 2.5;//sube el arma
		}
		else {
			cambio = 0;
			this->Ataque = Quinto;
			this->Rotación[0] = Rotación_Neutral[0];
			this->Rotación[1] = Rotación_Neutral[1];
			this->Rotación[2] = Rotación_Neutral[2];
		}
		break;
	case Quinto:
		//Segundo slash
		this->Rotación[0] = 135;
		if (this->Rotación[1] >= this->Rotación_Neutral[1] - 5) {
		cambio += 1.3;
		this->Rotación[1] = this->Rotación_Neutral[1] - cambio + 25;//rota a la izquierda
		this->Rotación[2] = this->Rotación_Neutral[2] + cambio * 2.5;//sube el arma
		}
		else {
		cambio = 0;
		this->Ataque = Preparacion;
		this->Atacando = false;
		this->Rotación[0] = Rotación_Neutral[0];
		this->Rotación[1] = Rotación_Neutral[1];
		this->Rotación[2] = Rotación_Neutral[2];
		}
		break;
	}
}

void Skyque::Katana::Idle() {
	switch (Estado_Idle) {
	case 0:
		if (this->Rotación[1] >= this->Rotación_Neutral[1] - 20) {
			cambio += .35;
			if (this->offsetY < 4) {
				this->offsetY += .7;
			}
			this->Rotación[1] = this->Rotación_Neutral[1] - cambio;//rota a la izquierda
			this->Rotación[2] = this->Rotación_Neutral[2] + cambio;//baja el arma
		}
		else {
			this->offsetY = 4;
			Estado_Idle++;
		}
		break;
	case 1:
		if (this->Rotación[1] < this->Rotación_Neutral[1]) {
			cambio -= .35;
			if (this->offsetY > 3) {
				this->offsetY -= .7;
			}
			this->Rotación[1] = this->Rotación_Neutral[1] - cambio;//rota a la derecha
			this->Rotación[2] = this->Rotación_Neutral[2] + cambio;//sube el arma
		}
		else {
			this->Rotación[1] = this->Rotación_Neutral[1];
			this->Rotación[2] = this->Rotación_Neutral[2];
			this->offsetY = 3;
			Estado_Idle++;
		}
		break;
	case 2:
		if (this->Rotación[1] <= this->Rotación_Neutral[1] + 20) {
			cambio += .35;
			if (this->offsetY < 4) {
				this->offsetY += .7;
			}
			this->Rotación[1] = this->Rotación_Neutral[1] + cambio;//rota a la derecha
			this->Rotación[2] = this->Rotación_Neutral[2] + cambio;//baja el arma
		}
		else {
			this->offsetY = 4;
			Estado_Idle++;
		}
		break;
	case 3:
		if (this->Rotación[1] > this->Rotación_Neutral[1]) {
			cambio -= .35;
			if (this->offsetY > 3) {
				this->offsetY -= .7;
			}
			this->Rotación[1] = this->Rotación_Neutral[1] + cambio;//rota a la izquierda
			this->Rotación[2] = this->Rotación_Neutral[2] + cambio;//sube el arma
		}
		else {
			this->Rotación[1] = this->Rotación_Neutral[1];
			this->Rotación[2] = this->Rotación_Neutral[2];
			this->offsetY = 3;
			Estado_Idle = 0;
		}
		break;
	}
}