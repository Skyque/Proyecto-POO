#include"Spawn.h"
#include "Cucaracha.h"
#include "SilentHill.h"
#include "Golem.h"
#include <stdlib.h>
#include <time.h> 

Skyque::Spawn::Spawn(Enemigo* pEnemigo[35]) {
	this->Enemigos = pEnemigo;
}

void Skyque::Spawn::Spawnea() {
	
}

float Skyque::Spawn::getIndice() {
	return this->indiceEnemigo;
}

Skyque::Spawn::~Spawn() {

}