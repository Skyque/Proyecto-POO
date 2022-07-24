#ifndef _SPAWN_
#define _SPAWN_

#include "Enemigo.h"

namespace Skyque {
	class Spawn {
	public:
		Spawn(Enemigo* pEnemigo[35]);
		~Spawn();
		void Spawnea();
		float getIndice();
	private:
		Enemigo** Enemigos;
		int indiceEnemigo = 0;
	};
}

#endif
