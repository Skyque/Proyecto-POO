#ifndef __Escena
#define __Escena

#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "Model.h"
#include "Water.h"
#include "Billboard.h"
#include "Fog.h"
#include "Camera.h"
#include <thread>
#include <vector>

#include "Decoraciones.h"
#include "Armas.h"
#include "Selector.h"
#include "Katana.h"
#include "Lanza.h"
#include "Hacha.h"
#include "Enemigo.h"
#include "Cucaracha.h"
#include "SilentHill.h"
#include "Golem.h"

#define BILLSIZE 50
#define ALTURA(A, B, C) terrain->Superficie(A, B) * 4 + C

//BIENVENIDO AL ARCHIVO MAS IMPORTANTE DE TU PROYECTO

class Scene : public Camera
{
public:

	HWND hWnd = 0;
	bool EstoyColisionando = false;
	bool Cerrar = false, Luna = false;
	short int skyIndex, lightIndex;
	float skyRotation;
	float PosiciónInicialArma [3], CooldownColisión;
	int indiceEnemigo = 0;
	int Cielo = 1;

	SkyDome *skyDome = new SkyDome(hWnd, 32, 32, 1400, L"Imagenes//skydome-hdri-sunset-clouds-vi-3d-model.jpg");
	SkyDome* Transición1 = new SkyDome(hWnd, 32, 32, 1400, L"Imagenes//Transición1.jpg");
	SkyDome* Transición2 = new SkyDome(hWnd, 32, 32, 1400, L"Imagenes//Transición2.jpg");
	SkyDome* LunaCarmesí = new SkyDome(hWnd, 16, 16, 1400, L"Imagenes//Crimson Moon.jpg");
	Terrain *terrain;
	EDXFramework::Model* Laptop;
	Water *lago;
	GLfloat AmbMat[4] = { 255, 255, 220, 1 };

	/*EDXFramework::Model  *Gun;
	EDXFramework::Model  *Gun2;
	EDXFramework::Model  *Guns[200];*/

	//EDXFramework::Model* Pejelagarto;//cierra el programa
	//EDXFramework::Model* Pejelagarto2;//Cierra el programa
	//EDXFramework::Model* CosoAlien;//cierra el programa
	EDXFramework::Model* KatanaPuntero;//listo, pero es grande
	EDXFramework::Model* LanzaLonginus;//listo, pero es gigantesca
	//EDXFramework::Model* Espada;//no carga textura bien
	EDXFramework::Model* HachaLeviathan;//listo
	//EDXFramework::Model* Hacha;//error al cargar (sale raro)
	//EDXFramework::Model* HachaDoble;//listo
	EDXFramework::Model* GolemPiedra;//listo
	//EDXFramework::Model* Dragón;//Error
	//EDXFramework::Model* CosoRojo;//error
	EDXFramework::Model* Cucaracha;//listo, pero es muy grande
	EDXFramework::Model* PareceDeSilentHill;//Listo, da asco y me encanta; pero está algo grande
	EDXFramework::Model* Casa1;//listo
	//EDXFramework::Model* Casa2;//cierra el programa :(
	//EDXFramework::Model* Casa3;
	//EDXFramework::Model* Casa4;
	//EDXFramework::Model* RelojPared;//cierra el programa
	//EDXFramework::Model* Jarrón1;//cierra el programa
	//EDXFramework::Model* Jarrón2;//cierra el programa
	//EDXFramework::Model* Despertador;//cierra el programa
	//EDXFramework::Model* GloboTerráqueo;//Error
	//EDXFramework::Model* Vela;//cierra el programa
	EDXFramework::Model* Mesa1;//listo, pero es muy grande
	EDXFramework::Model* Mesa2;//listo, pero es muuuy grande
	//EDXFramework::Model* Mesa3;//cierra el programa
	//EDXFramework::Model* Pino;//textura mal
	EDXFramework::Model* Árbol1;//listo, es enorme y hay que voltearlo
	//EDXFramework::Model* Árbol2;//problemas texturas, talvez se pueda incluir
	//EDXFramework::Model* Sillón1;//cierra el programa
	//EDXFramework::Model* Sillón2;//cierra el programa
	//EDXFramework::Model* Banco1;//Viene con escena, hay que modificarlo
	EDXFramework::Model* Maceta;//Listo, pero es enorme
	//EDXFramework::Model* Silla;//cierra el programa
	EDXFramework::Model* MuebleRetro;//Listo,pero está volteado
	EDXFramework::Model* Reloj1;//Listo
	//EDXFramework::Model* Papelera1;//cierra el programa
	//EDXFramework::Model* Papelera2;//cierra el programa
	//EDXFramework::Model* Papelera3;//cierra el programa
	EDXFramework::Model* Puerta1;//listo
	//EDXFramework::Model* Papelera4;
	//EDXFramework::Model* Papelera5;
	EDXFramework::Model* Papelera6;
	EDXFramework::Model* Silla2;

	Skyque::Armas* Arma;
	Skyque::Selector* SelectorKatana;
	Skyque::Selector* SelectorHacha;
	Skyque::Selector* SelectorLanza;
	Skyque::Enemigo* enemigo[20];

	Skyque::Decoraciones* Construcción;
	Skyque::Decoraciones* Banco;
	Skyque::Decoraciones* Mesita;
	Skyque::Decoraciones* Pino1;
	Skyque::Decoraciones* Pino2;
	Skyque::Decoraciones* Pino3;
	Skyque::Decoraciones* Pino4;
	Skyque::Decoraciones* Pino5;
	Skyque::Decoraciones* Pino6;
	Skyque::Decoraciones* Pino7;
	Skyque::Decoraciones* Pino8;
	Skyque::Decoraciones* Pino9;
	Skyque::Decoraciones* Pino10;
	Skyque::Decoraciones* MacetaExterior;
	Skyque::Decoraciones* RadioRetro;
	Skyque::Decoraciones* RelojPared;
	Skyque::Decoraciones* PuertaCaída;
	Skyque::Decoraciones* PapeleraLondinense;
	Skyque::Decoraciones* SillaInterior;

	Billboard *billBoard[BILLSIZE];

	static int loadModel(EDXFramework::Model* Gun) {
		Gun = new EDXFramework::Model("Modelos//Arma//Cyborg_Riffle.obj", "Modelos//Arma//Cyborg_Riffle_D.bmp", 1);
		return 1;
	}

	Scene(HWND hWnd)
	{
		srand(time(NULL));
		this->hWnd = hWnd;
		skyIndex = lightIndex, skyRotation = 0;

		GLfloat AmbPos[] = { 0, 400, 400, 1 };


		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);

		//lago = Pista, busca en sus constructores para poder crear un lago.

		Laptop = new EDXFramework::Model("Modelos//Laptop//laptop1.obj", "Modelos//Laptop//laptop.bmp", 1);

		terrain = new Terrain(hWnd, L"Imagenes//descarga3.jpg", L"Imagenes//Pasto.jpg", L"Imagenes//Pasto.jpg", 2600, 2600);

		lago = new Water(hWnd, L"Imagenes//Agua2.jpg", L"Imagenes//Agua2.jpg", 2000, 2000);

		//Gun = new EDXFramework::Model("Modelos//Arma//Cyborg_Riffle.obj", "Modelos//Arma//Cyborg_Riffle_D.bmp", 1);
		//Gun2 = new EDXFramework::Model("Modelos//Arma//Cyborg_Riffle.obj", "Modelos//Arma//Cyborg_Riffle_D.bmp", 1);

		//Pejelagarto = new EDXFramework::Model("Modelos//Pejelagarto//uploads_files_2023745_LOW_POLY.OBJ", "Modelos//Pejelagarto//Texutres//Diffuse.bmp", 1);
		//Pejelagarto2 = new EDXFramework::Model("Modelos//Pejelagarto2//Green Miner//Green.obj", "Modelos//Pejelagarto2//Green Miner//Green_base_color.bmp", 1);
		//CosoAlien = new EDXFramework::Model("Modelos//Coso//Alien Animal.obj", "Modelos//Coso//textures//Base Color.bmp", 1);
		KatanaPuntero = new EDXFramework::Model("Modelos//Katana2//katana4.obj", "Modelos//Katana2//katana.bmp", 1);
		LanzaLonginus = new EDXFramework::Model("Modelos//Lanza Longinus//Longinus2.obj", "Modelos//Lanza Longinus//Longinus.bmp", 1);//gigante no, lo siguiente
		//Espada = new EDXFramework::Model("Modelos//Espada//lowpolysword//Models and Textures//sword.obj", "Modelos//Espada//lowpolysword//Models and Textures//1_BaseColor.bmp", 1);
		HachaLeviathan = new EDXFramework::Model("Modelos//Hacha Leviatán//untitled3.obj", "Modelos//Hacha Leviatán//Axe.bmp", 1);//un poco más pequeña
		//Hacha = new EDXFramework::Model("Modelos//Hacha//Axe//Axe.obj", "Modelos//Hacha//Axe//Texture2.bmp", 1);
		//HachaDoble = new EDXFramework::Model("Modelos//Hacha doble//Axe.obj", "Modelos//Hacha doble//maps//Axe Texture.bmp", 1); //carga pero es muuuuy grande
		GolemPiedra = new EDXFramework::Model("Modelos//Golem de piedra//Stone.obj", "Modelos//Golem de piedra//diffuso.bmp", 1);
		//Dragón = new EDXFramework::Model("Modelos//Dragón//aca.obj", "Modelos//Dragón//Texture//body.bmp", 1);
		//CosoRojo = new EDXFramework::Model("Modelos//CosoRojo//creature.obj", "Modelos//CosoRojo//creature.BMP", 1);
		Cucaracha = new EDXFramework::Model("Modelos//CucarachaRara//Umber_Hulk_1.obj", "Modelos//CucarachaRara//Umber Hulk1Diffuse1f.bmp", 1);
		PareceDeSilentHill = new EDXFramework::Model("Modelos//PareceDeSilentHill//flesh_creature.obj", "Modelos//PareceDeSilentHill//flesh_diffuse_1024.bmp", 1);
		Casa1 = new EDXFramework::Model("Modelos//Casa1//Cottage_FREE4.obj", "Modelos//Casa1//Cottage_Dirt//Cottage_Dirt_Base_Color.bmp", 1);
		//Casa2 = new EDXFramework::Model("Modelos//Casa2(esta puede ser la buena)//Medieval House 2//Medieval house 2.obj", "Modelos//Casa2(esta puede ser la buena)//Medieval House 2//Texture 1//Texture 1.bmp", 1);
		//Casa3 = new EDXFramework::Model("Modelos//Casa4//farmhouse_obj.obj", "Modelos//Casa4//Farmhouse Texture Bump Map .jpg", 1);
		//Casa4 = new EDXFramework::Model("Modelos//Casa5//house//Farm_house.obj", "Modelos//Casa5//house//textures//Farm_house_D.jpg", 1);
		//RelojPared = new EDXFramework::Model("Modelos//RelojPared//Clock 01.obj", "Modelos//RelojPared//Clock 01 bp.bmp", 1);
		//Jarrón1 = new EDXFramework::Model("Modelos//Jarrón//vasee.obj", "Modelos//Jarrón//varillnew_low_lambert1_BaseColor.bmp", 1);
		//Jarrón2 = new EDXFramework::Model("Modelos//Jarrón2//Ancient_Vase.obj", "Modelos//Jarrón2//Ancient_Vase_CM.bmp", 1);
		//Despertador = new EDXFramework::Model("Modelos//Despertador//ALARM_CLOCK.obj", "Modelos//Despertador//1_STEREO.png", 1);
		//GloboTerráqueo = new EDXFramework::Model("Modelos//GloboTerráqueo//Old_Antique_Standing_Globe_.obj", "Modelos//GloboTerráqueo//Textures//Diffuse.bmp", 1);
		//Vela = new EDXFramework::Model("Modelos//Vela//candle.obj", "Modelos//Vela//metal//3 (4).bmp", 1);
		Mesa1 = new EDXFramework::Model("Modelos//Mesa1//Simja_side_table3.obj", "Modelos//Mesa1//Textures//eucalyptus_wood_ALBEDO.bmp", 1);
		Mesa2 = new EDXFramework::Model("Modelos//Mesa2//Vintage_Furniture_Coffee_Table_OBJ4.obj", "Modelos//Mesa2//VF_Coffee_Table_Textures//VF_Coffee_Table_Textures_BaseColor.bmp", 1);
		//Mesa3 = new EDXFramework::Model("Modelos//Mesa3//Nikari side table.obj", "Modelos//Mesa3//Nikari side table_wood.bmp", 1);
		//Pino = new EDXFramework::Model("Modelos//Pino//Fir.obj", "Modelos//Pino//FirBranches_Df.bmp", 1);
		Árbol1 = new EDXFramework::Model("Modelos//Árbol1//White_Ash_Tree_v1_L3.123cb9916c2a-d762-485a-872c-b7210bc5f34a//10459_White_Ash_Tree_v1_L4.obj", "Modelos//Árbol1//White_Ash_Tree_v1_L3.123cb9916c2a-d762-485a-872c-b7210bc5f34a//10459_White_Ash_Tree_v1_Diffuse.bmp", 1);
		//Árbol2 = new EDXFramework::Model("Modelos//Árbol2//ItalianCypress.obj", "Modelos//Árbol2//ItalianCypress_Color.bmp", 1);
		//Banco1 = new EDXFramework::Model("Modelos//Banco//Obj//Chair.obj", "Modelos//Banco//Obj//wood 1.bmp", 1);
		Maceta = new EDXFramework::Model("Modelos//Maceta3//Pot3.obj", "Modelos//Maceta3//Pot.bmp", 1);
		MuebleRetro = new EDXFramework::Model("Modelos//MuebleRetro//Radiogram_furniture_V2_L1.123ca1f684d5-0f8b-47c6-a8e3-a01fd624ee14//20347_Radiogram_(furniture)_V2_Texture3.obj", "Modelos//MuebleRetro//Radiogram_furniture_V2_L1.123ca1f684d5-0f8b-47c6-a8e3-a01fd624ee14//20347_Radiogram_(furniture)_V2_Diff.bmp", 1);
		Reloj1 = new EDXFramework::Model("Modelos//Reloj1//Clock_Constraints_for_Animations//Clock_obj3.obj", "Modelos//Reloj1//Clock_Constraints_for_Animations//textures//Uhr_ohne_Zeiger.bmp", 1);
		Puerta1 = new EDXFramework::Model("Modelos//Puerta1//10057_wooden_door_v3_L3.123c1d67cf02-d520-4cbb-bc8d-b74529055cdd//10057_wooden_door_v3_iterations-4.obj", "Modelos//Puerta1//10057_wooden_door_v3_L3.123c1d67cf02-d520-4cbb-bc8d-b74529055cdd//10057_wooden_door_v1_diffuse.bmp", 1);
		Papelera6 = new EDXFramework::Model("Modelos//Papelera6//FREE_TRASHCAN_1_OBJ3.obj", "Modelos//Papelera6//Metal.bmp", 1);
		Silla2 = new EDXFramework::Model("Modelos//Silla2//chair_03.obj", "Modelos//Silla2//Textures//chair_01_Base_Color.bmp", 1);

		float PosInicial[3] = { 150, ALTURA(150, 350, 0), 350 };
		Construcción = new Skyque::Decoraciones(Casa1, PosInicial, 13.5, 0 , 0);
		PosInicial[0] = 105;
		PosInicial[1] = ALTURA(98, 323, 0);
		PosInicial[2] = 330;
		Banco = new Skyque::Decoraciones(Mesa1, PosInicial, 13.5, 1 , 9);
		PosInicial[0] = 156.75;
		PosInicial[1] = ALTURA(156.75, 377, 0);
		PosInicial[2] = 377;
		Mesita = new Skyque::Decoraciones(Mesa2, PosInicial, 13.5, 1, 9);
		PosInicial[0] = 210.345;
		PosInicial[1] = ALTURA(210.345, 237.95, 0);
		PosInicial[2] = 237.95;
		MacetaExterior = new Skyque::Decoraciones(Maceta, PosInicial, 13.5, 1, 6);
		PosInicial[0] = 123;
		PosInicial[1] = ALTURA(123, 390.5, 0);
		PosInicial[2] = 390.5;
		RadioRetro = new Skyque::Decoraciones(MuebleRetro, PosInicial, 13.5, 1, 3);
		PosInicial[0] = 78.45;
		PosInicial[1] = ALTURA(78.45, 352, 0);
		PosInicial[2] = 352;
		RelojPared = new Skyque::Decoraciones(Reloj1, PosInicial, 13.5, 1, 3);
		PosInicial[0] = 109.5;
		PosInicial[1] = ALTURA(109.5, 231.2, 0);
		PosInicial[2] = 231.2;
		PuertaCaída = new Skyque::Decoraciones(Puerta1, PosInicial, 13.5, 1, 3);
		PosInicial[0] = 220.2;
		PosInicial[1] = ALTURA(220.2, 306.8, 0);
		PosInicial[2] = 306.8;
		PapeleraLondinense = new Skyque::Decoraciones(Papelera6, PosInicial, 13.5, 1, 3);
		PosInicial[0] = 156.75;
		PosInicial[1] = ALTURA(156.75, 372.95, 0);
		PosInicial[2] = 372.95;
		SillaInterior = new Skyque::Decoraciones(Silla2, PosInicial, 13.5, 1, 3);
		float PosPino[3] = { 302.55, ALTURA(302.55, 177.2, 0), 177.2 };
		Pino1 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = 241.395;
		PosPino[1] = ALTURA(241.395, 485, 0);
		PosPino[2] = 485;
		Pino2 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = 422.7;
		PosPino[1] = ALTURA(422.7, 431, 0);
		PosPino[2] = 431;
		Pino3 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = 120.3;
		PosPino[1] = ALTURA(120.3, 633.5, 0);
		PosPino[2] = 633.5;
		Pino4 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = -229.35;
		PosPino[1] = ALTURA(229.35, 161, 0);
		PosPino[2] = 161;
		Pino5 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = -144.3;
		PosPino[1] = ALTURA(144.3, 325.7, 0);
		PosPino[2] = 325.7;
		Pino6 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = -4;
		PosPino[1] = ALTURA(-4, 42.875, 0);
		PosPino[2] = 42.875;
		Pino7 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = -234.75;
		PosPino[1] = ALTURA(-234.75, 566, 0);
		PosPino[2] = 566;
		Pino8 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = -66;
		PosPino[1] = ALTURA(-66, 479.6, 0);
		PosPino[2] = 479.6;
		Pino9 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);
		PosPino[0] = 320;
		PosPino[1] = ALTURA(320, 626.75, 0);
		PosPino[2] = 626.75;
		Pino10 = new Skyque::Decoraciones(Árbol1, PosPino, .15, 1, 17);

		PosiciónInicialArma[0] = px;
		PosiciónInicialArma[1] = ALTURA(px, pz, 1);
		PosiciónInicialArma[2] = pz;
		Arma = new Skyque::Katana(KatanaPuntero, PosiciónInicialArma);
		SelectorKatana = new Skyque::Selector(KatanaPuntero, 215, ALTURA(230, 326, 5), 326, 1);
		SelectorHacha = new Skyque::Selector(HachaLeviathan, 215, ALTURA(-10, -10, 7), 346, 2);
		SelectorLanza = new Skyque::Selector(LanzaLonginus, 215, ALTURA(-20, -20, 15), 366, 3);

		vector<thread> threads;

		/*for (int i = 0; i < 199; i++) {

			//threads.push_back(thread(&Scene::loadModel,Guns[i]));
			loadModel(Guns[i]);

		}*/

		//for (int j = 0; j < 199; j++) { threads[j].join(); }

		Billboards(billBoard, hWnd);

		cameraInitialize();
	}

	void Billboards(Billboard *bills[], HWND hWnd) //inicializa billboards
	{
		//Aqui puedes crear algo util con un FOR quiza.
	}


	void render(HDC hDC)
	{
		if (!Cerrar) {
			if (Cielo == 7) {
				Cielo = 1;
			}
			EstoyColisionando = false; //sólo detecta una colisión por vuelta o si no no detcta bien las colisioenes
			skyRotation < 360 ? skyRotation += 0.03f : skyRotation = 0;

			//gunRotation < 360 ? gunRotation += 0.7f : gunRotation = 0;


			glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0, 0);
			glLoadIdentity();

			GLfloat AmbInt[] = { 0.1, 0.1, 0.1, 1 };
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
			py = ALTURA(px, pz, 20);

			cameraUpdate();

			//Skydome
			switch (Cielo) {
			case 1:
				glPushMatrix();
				glTranslatef(0, 8, 0);
				glRotatef(skyRotation, 0, 1, 0);
				skyDome->Draw();
				glPopMatrix();
				break;
			case 2:
				glPushMatrix();
				glTranslatef(0, 8, 0);
				glRotatef(skyRotation, 0, 1, 0);
				Transición1->Draw();
				glPopMatrix();
				break;
			case 3:
				glPushMatrix();
				glTranslatef(0, 8, 0);
				glRotatef(skyRotation, 0, 1, 0);
				Transición2->Draw();
				glPopMatrix();
				break;
			case 4:
				glPushMatrix();
				glTranslatef(0, 8, 0);
				glRotatef(skyRotation, 0, 1, 0);
				LunaCarmesí->Draw();
				glPopMatrix();
				break;
			case 5:
				glPushMatrix();
				glTranslatef(0, 8, 0);
				glRotatef(skyRotation, 0, 1, 0);
				Transición2->Draw();
				glPopMatrix();
				break;
			case 6:
				glPushMatrix();
				glTranslatef(0, 8, 0);
				glRotatef(skyRotation, 0, 1, 0);
				Transición1->Draw();
				glPopMatrix();
				break;
			}

			//Sleeción de armas
			//Katana
			glPushMatrix();
			glTranslatef(SelectorKatana->getX(), SelectorKatana->getY(), SelectorKatana->getZ());
			glRotatef(180, 1, 0, 0);
			glRotatef(-90, 0, 0, 1);
			glScalef(.25, .25, .25);
			SelectorKatana->Dibujar();
			glPopMatrix();

			//Lanza
			glPushMatrix();
			glTranslatef(SelectorLanza->getX(), SelectorLanza->getY(), SelectorLanza->getZ());
			glScalef(1.5, 1.5, 1.5);
			SelectorLanza->Dibujar();
			glPopMatrix();

			//Hacha
			glPushMatrix();
			glTranslatef(SelectorHacha->getX(), SelectorHacha->getY(), SelectorHacha->getZ());
			glRotatef(90, 1, 0, 0);
			glScalef(.65, .65, .65);
			SelectorHacha->Dibujar();
			glPopMatrix();


			//Arma
			if (Arma != NULL) {
				glPushMatrix();
				//todavía tengo que hacer bien el seguimiento, update: no sé qué hice, si quiera si hice algo, pero ya funciona :)
				if (!Arma->getAtacando()) {
					Arma->setX(px);
					Arma->setZ(pz);
					Arma->setY(py);
					glTranslatef(Arma->getX(), Arma->getY(), Arma->getZ());
					Arma->setRY(angle);
					Arma->Idle();
					glRotatef(Arma->getRX(), 1, 0, 0);
					glRotatef(Arma->getRY(), 0, 1, 0);
					glRotatef(Arma->getRZ(), 0, 0, 1);
					glScalef(Arma->getEscala(), Arma->getEscala(), Arma->getEscala());
				}
				else {
					Arma->setX(px);
					Arma->setZ(pz);
					Arma->setY(py);
					glTranslatef(Arma->getX(), Arma->getY(), Arma->getZ());
					Arma->setRY(angle);
					Arma->Atacar();
					glRotatef(Arma->getRY(), 0, 1, 0);
					glRotatef(Arma->getRX(), 1, 0, 0);
					glRotatef(Arma->getRZ(), 0, 0, 1);
					glScalef(Arma->getEscala(), Arma->getEscala(), Arma->getEscala());
				}
				Arma->Dibuja();
				glPopMatrix();
			}

			for (Skyque::Enemigo* enemigos : enemigo) {
				if (enemigos != NULL) {
					if (!enemigos->getMuerto()) {
						glPushMatrix();
						if (enemigos->getAtacando()) {
							enemigos->Atacar(px, pz);
						}
						else {
							enemigos->Moverse(px, pz);
						}
						glTranslatef(enemigos->getX(), ALTURA(enemigos->getX(), enemigos->getZ(), enemigos->getoffsetY()), enemigos->getZ());
						enemigos->setRY(px, pz);
						glRotatef(-enemigos->getRY() + 180, 0, 1, 0);
						glScalef(enemigos->getEscala(), enemigos->getEscala(), enemigos->getEscala());
						enemigos->Dibuja();
						glPopMatrix();
					}
				}
			}

			/*Golem
			glPushMatrix();
			glTranslatef(6, ALTURA(6, 6, 2), 6);
			glScalef(4.3, 4.3, 4.3);
			GolemPiedra->Draw();
			glPopMatrix();

			//cucaracha
			glPushMatrix();
			glTranslatef(20, ALTURA(20, 20, 2), 20);
			glScalef(.2, .2, .2);
			Cucaracha->Draw();
			glPopMatrix();

			//coso de silent hill que no es de silent hill, o tal vez sí
			glPushMatrix();
			glTranslatef(30, ALTURA(30, 30, 13), 30);
			glScalef(.6, .6, .6);
			PareceDeSilentHill->Draw();
			glPopMatrix();
			*/
			//casa
			glPushMatrix();
			glTranslatef(Construcción->getX(), Construcción->getY(), Construcción->getZ());
			glScalef(Construcción->getEscala(), Construcción->getEscala(), Construcción->getEscala());
			Construcción->Dibuja();
			EstoyColisionando = Construcción->DetectaColisión(px, pz, RadioColisón);
			glPopMatrix();

			//Mesa 1
			glPushMatrix();
			glTranslatef(Banco->getX(), Banco->getY(), Banco->getZ());
			glScalef(Banco->getEscala(), Banco->getEscala(), Banco->getEscala());
			Banco->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Banco->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			//Mesa 2
			glPushMatrix();
			glTranslatef(Mesita->getX(), Mesita->getY(), Mesita->getZ());
			glScalef(Mesita->getEscala(), Mesita->getEscala(), Mesita->getEscala());
			Mesita->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Mesita->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			//Arboles
			glPushMatrix();
			glTranslatef(Pino1->getX(), Pino1->getY(), Pino1->getZ());
			glScalef(Pino1->getEscala(), Pino1->getEscala(), Pino1->getEscala());
			Pino1->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino1->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino2->getX(), Pino2->getY(), Pino2->getZ());
			glScalef(Pino2->getEscala(), Pino2->getEscala(), Pino2->getEscala());
			Pino2->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino2->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino3->getX(), Pino3->getY(), Pino3->getZ());
			glScalef(Pino3->getEscala(), Pino3->getEscala(), Pino3->getEscala());
			Pino3->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino3->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino4->getX(), Pino4->getY(), Pino4->getZ());
			glScalef(Pino4->getEscala(), Pino4->getEscala(), Pino4->getEscala());
			Pino4->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino4->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino5->getX(), Pino5->getY(), Pino5->getZ());
			glScalef(Pino5->getEscala(), Pino5->getEscala(), Pino5->getEscala());
			Pino5->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino5->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino6->getX(), Pino6->getY(), Pino6->getZ());
			glScalef(Pino6->getEscala(), Pino6->getEscala(), Pino6->getEscala());
			Pino6->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino6->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino7->getX(), Pino7->getY(), Pino7->getZ());
			glScalef(Pino7->getEscala(), Pino7->getEscala(), Pino7->getEscala());
			Pino7->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino7->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino8->getX(), Pino8->getY(), Pino8->getZ());
			glScalef(Pino8->getEscala(), Pino8->getEscala(), Pino8->getEscala());
			Pino8->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino8->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino9->getX(), Pino9->getY(), Pino9->getZ());
			glScalef(Pino9->getEscala(), Pino9->getEscala(), Pino9->getEscala());
			Pino9->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino9->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(Pino10->getX(), Pino10->getY(), Pino10->getZ());
			glScalef(Pino10->getEscala(), Pino10->getEscala(), Pino10->getEscala());
			Pino10->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = Pino10->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			//Silla 
			glPushMatrix();
			glTranslatef(SillaInterior->getX(), SillaInterior->getY(), SillaInterior->getZ());
			glScalef(SillaInterior->getEscala(), SillaInterior->getEscala(), SillaInterior->getEscala());
			SillaInterior->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = SillaInterior->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			//Maceta
			glPushMatrix();
			glTranslatef(MacetaExterior->getX(), MacetaExterior->getY(), MacetaExterior->getZ());
			glScalef(MacetaExterior->getEscala(), MacetaExterior->getEscala(), MacetaExterior->getEscala());
			MacetaExterior->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = MacetaExterior->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			//Mueble retro
			glPushMatrix();
			glTranslatef(RadioRetro->getX(), RadioRetro->getY(), RadioRetro->getZ());
			glScalef(RadioRetro->getEscala(), RadioRetro->getEscala(), RadioRetro->getEscala());
			RadioRetro->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = RadioRetro->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			//Puerta
			glPushMatrix();
			glTranslatef(PuertaCaída->getX(), PuertaCaída->getY(), PuertaCaída->getZ());
			glScalef(PuertaCaída->getEscala(), PuertaCaída->getEscala(), PuertaCaída->getEscala());
			PuertaCaída->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = PuertaCaída->DetectaColisión(px, pz, RadioColisón);
			}
			glPopMatrix();

			//Papelera
			glPushMatrix();
			glTranslatef(PapeleraLondinense->getX(), PapeleraLondinense->getY(), PapeleraLondinense->getZ());
			glScalef(PapeleraLondinense->getEscala(), PapeleraLondinense->getEscala(), PapeleraLondinense->getEscala());
			PapeleraLondinense->Dibuja();
			if (!EstoyColisionando) {
				EstoyColisionando = PapeleraLondinense->DetectaColisión(px, pz, RadioColisón);
			}

			glPopMatrix();

			//Reloj
			glPushMatrix();
			glTranslatef(RelojPared->getX(), RelojPared->getY(), RelojPared->getZ());
			glScalef(RelojPared->getEscala(), RelojPared->getEscala(), RelojPared->getEscala());
			RelojPared->Dibuja();
			//El reloj está en la pared y arria, no necesota colisiones
			glPopMatrix();

			//Terreno
			glPushMatrix();
			glScalef(1, 4, 1);
			terrain->Draw();
			glPopMatrix();

			//Lago
			glPushMatrix();
			glTranslatef(-610, 30, -360);
			//glTranslatef(-172, 10, -140);
			glScalef(2, 1, 2);
			lago->Draw();
			glPopMatrix();

			glPushMatrix();
			for (int i = 0; i < BILLSIZE; i++) //dibuja billboards
				//Aqui puede ir algo en especial, en tu carpeta de HEADER_FILES, el primer archivo es la respuesta.
				glPopMatrix();


			SwapBuffers(hDC);

		}
	}

	void Spawnea() {
		int decideSpawn = rand() % 4 + 1; //decide en cuál spawnpoint genera al enemigo
		int decideEnemigo = rand() % 3 + 1; //decide en cuál spawnpoint genera al enemigo
		float Posición[3];
		switch (decideSpawn) {
		case 1:
			Posición[0] = -188;
			Posición[1] = 1;
			Posición[2] = 253;
			break;
		case 2:
			Posición[0] = 16.5;
			Posición[1] = 1;
			Posición[2] = -30;
			break;
		case 3:
			Posición[0] = 330;
			Posición[1] = 1;
			Posición[2] = -366;
			break;
		case 4:
			Posición[0] = 773;
			Posición[1] = 1;
			Posición[2] = 232;
			break;
		}
		switch (decideEnemigo) {
		case 1:
			enemigo[indiceEnemigo] = new Skyque::Cucaracha(Posición);
			break;
		case 2:
			enemigo[indiceEnemigo] = new Skyque::SilentHill(Posición);
			break;
		case 3:
			enemigo[indiceEnemigo] = new Skyque::Golem(Posición);
			break;
		}
		enemigo[indiceEnemigo]->setRY(px, pz);
		indiceEnemigo++;
	}

	void ActivaLunaCarmesí() {
		int decide = rand() % 10 + 1;
		if (decide <= 5) {
			Luna = true;
		}
	}

	~Scene()
	{
		//NO OLVIDES PONER AQUI TODOS TUS PUNTEROS
		delete skyDome;
		delete Transición1;
		delete Transición2;
		delete LunaCarmesí;
		delete Laptop;
		//delete Gun;
		delete terrain;
		delete KatanaPuntero;
		//delete Espada;
		delete LanzaLonginus;
		delete HachaLeviathan;
		//delete Hacha;
		//delete HachaDoble;
		delete GolemPiedra;
		delete Cucaracha;
		delete PareceDeSilentHill;
		delete Construcción;
		delete Casa1;
		delete Banco;
		delete Mesa1;
		delete Mesita;
		delete Mesa2;
		//delete Mesa3;
		delete Pino1;
		delete Pino2;
		delete Pino3;
		delete Pino4;
		delete Pino5;
		delete Pino6;
		delete Pino7;
		delete Pino8;
		delete Pino9;
		delete Pino10;
		delete Árbol1;
		delete SillaInterior;
		delete Silla2;
		delete MacetaExterior;
		delete Maceta;
		delete RadioRetro;
		delete MuebleRetro;
		delete RelojPared;
		delete Reloj1;
		//delete Maceta1;
		delete PuertaCaída;
		delete Puerta1;
		delete PapeleraLondinense;
		delete Papelera6;
		delete Arma;
		for (Skyque::Enemigo* enemigos : enemigo) {
			if (enemigos != NULL) {
				delete enemigos;
				enemigos = NULL;
			}
		}
	}
};
#endif
