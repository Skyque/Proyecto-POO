#include <Windows.h>
#include "glew.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Scene.h"
#include <time.h>
#include "GamePadRR.h"
#include "resource.h"
#include "Enemigo.h"
#include <thread>
#pragma comment (lib, "glew32.lib") 
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 

#define Timer1 100
#define CooldownAtaque 101
#define SinAtacar 102
#define CooldownDa�oJugador 103
#define CooldownSpawn 104
#define LunaCarmes� 105
#define CambiarImagen 106
#define DesactivaLuna 107

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DefPixelFormat(HDC hDC);

HWND hInfo = 0;
HWND hText = 0;
bool ableToCheck = false;
HDC hContextoVentana;
Scene *scene;
GamePadRR *gamPad;
bool renderiza = false, SiguienteAtaque = true, Da�oJugador = true, Spawnea = true, Iniciado = false, CieloCambiado = false, Luna = false;
unsigned int dayTimer = 0;
int EnemigosDerrotados = 0;
int EnemigosCreados = 0;
int Cambios = 0;
int Vueltas = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndVentana;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX); //Tama�o en bytes de la estructura.
	wc.style = CS_HREDRAW | CS_VREDRAW; //Entero de 16 bits que codifica el estilo de la clase de ventana.
	wc.lpfnWndProc = WindowProc;//Apunta al procedimiento de ventana.
	wc.hInstance = hInstance;//Identifica la instancia de la ventana a la que esta clase pertenece.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Identificador del curso de la clase. Debe ser un manipulador de un recurso de tipo icono. Si es Null, la aplicaci�n mostrar� un icono cuando el usuario minice la ventana de la aplicaci�n.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //Identificador del pincel para la clase.
	wc.lpszClassName = "SkyqueWindow"; //Especifica el nombre de la clase ventana.
	RegisterClassEx(&wc);//Registra una clase de ventana para su uso subsecuente en llamadas a las funciones CreateWindow o CreateWindowEx
	RECT wr = { 0, 0, 1080, 720 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);//Calcula el tama�o necesario del rect�ngulo de la ventana.

	//Se crea la ventana definida previamente.
	hwndVentana = CreateWindowEx(NULL,//estilo extendido de ventana
		"SkyqueWindow",//puntero al nombre de la clase registrada *visto arriba*
		"Arena de Skyque",//puntero al nombre de la ventana
		WS_OVERLAPPEDWINDOW,//estilo de ventana
		0,//posici�n horizontal de la ventana
		0,//posici�n vertical de la ventana
		wr.right - wr.left,//ancho de la ventana
		wr.bottom - wr.top,//alto de la ventana
		NULL,//manejador de la ventana padre o propietaria
		NULL,//manejador del menu o identificador de ventana hija
		hInstance,//manejador de la instancia de la aplicaci�n
		NULL);//puntero a los datos de creaci�n de la ventana

	ShowWindow(hwndVentana, nCmdShow);//Muestra la ventana creada

	
	ShowWindow(hInfo, SW_SHOW);
	
	glewInit();//Inicializa glew

	//Instancia de la escena
	scene = new Scene(hwndVentana);

	gamPad = new GamePadRR(1);
	ableToCheck = true;

	//Crear un timer con el valor especificado de time-out
	SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
		Timer1,//identificador del timer
		5,//valor de time-out
		NULL);//direcci�n del procedimiento de timer

	MSG msg = { 0 };
	while (TRUE)
	{
		if (Iniciado) {
			if (!Luna) {
				SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
					LunaCarmes�,//identificador del timer
					40000,//valor de time-out
					NULL);//direcci�n del procedimiento de timer
				Luna = true;
				CieloCambiado = true;
			}
			else if (!CieloCambiado && Cambios < 3) {
				SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
					CambiarImagen,//identificador del timer
					2000,//valor de time-out
					NULL);//direcci�n del procedimiento de timer
				CieloCambiado = true;
				Cambios++;
				if (Cambios == 3) {
					Vueltas++;
					if (Vueltas == 2) {
						Vueltas = 0;
						Luna = false;
					}
				}
			}
			if (Spawnea && EnemigosCreados < 20) {
				scene->Spawnea();
				EnemigosCreados++;
				Spawnea = false;
				KillTimer(hwndVentana, CooldownSpawn);
				SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
					CooldownSpawn,//identificador del timer
					10000,//valor de time-out
					NULL);//direcci�n del procedimiento de timer
			}
			for (Skyque::Enemigo* enemigo : scene->enemigo) {//todo lo que tengo que checar por cada enemigo
				if (enemigo != NULL) {
					if (enemigo->DistanciaAJugador(scene->px, scene->pz) < enemigo->getDistanciaAtacar() && !enemigo->getMuerto()) {
						enemigo->setAtacando(true);
					}
					if (enemigo->DistanciaAJugador(scene->px, scene->pz) < 20 && Da�oJugador && !enemigo->getMuerto()) {
						Da�oJugador = false;
						KillTimer(hwndVentana, CooldownDa�oJugador);
						SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
							CooldownDa�oJugador,//identificador del timer
							scene->Arma->getCooldownDa�o(),//valor de time-out
							NULL);//direcci�n del procedimiento de timer
						if (scene->Luna) {
							scene->Arma->RecibeDa�o(enemigo->getDa�o() * 1.7); //con la luna hacen 70% m�s de da�o
						}
						else {
							scene->Arma->RecibeDa�o(enemigo->getDa�o());
						}
						if (scene->Arma->getVida() <= 0) {
							MessageBox(hwndVentana, "Fin del juego", "Has muerto", MB_OK);
							exit(0);
						}
					}
					if (scene->Arma->getAtacando() && enemigo->DistanciaAJugador(scene->px, scene->pz) < scene->Arma->getDistanciaAtaque() && !enemigo->getDa�ado() && !enemigo->getMuerto()) {
						enemigo->recibeDa�o(scene->Arma->getDa�o());
					}
					if (enemigo->getDa�ado() && !enemigo->getMuerto()) {
						enemigo->HabilitaDa�o();
					}
					if (enemigo->getVida() <= 0 && !enemigo->getMuerto()) {
						enemigo->Muere();
						EnemigosDerrotados++;
					}
				}
			}
			if (EnemigosDerrotados == 20) {
				MessageBox(hwndVentana, "Fin del juego", "Has ganado", MB_OK);
				exit(0);
			}
		}
		else {
			float distanciaDeCasa = sqrt(pow(scene->px - scene->Construcci�n->getX(), 2) + pow(scene->pz - scene->Construcci�n->getZ(), 2));
			if (distanciaDeCasa >= 100) {
				Iniciado = true;
			}
		}
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else{
			if (renderiza){			
				scene->render(hContextoVentana);
				renderiza = false;
				if (gamPad->IsConnected()){
					/*Las colisiones tienen cuatro veces la funci�n move porque si s�lo era una quedabas directamente en la zona de colisi�n
					por lo que al mover el stick en una direcci�n distitnta para alejarte, detectaba la colisi�n y te mov�a a la direcci�n contraria.
					Al poner dos quedas fuera de la colisi�n y puedes moverte libremente sin entorpecer/confundir el movimiento del jugador.*/
					if (gamPad->GetState().Gamepad.sThumbLX > 0) {
						if (!scene->EstoyColisionando) {
							scene->move('r');
						}
						else {
							scene->move('l');
							scene->move('l');
							scene->move('l');
							scene->move('l');
						}
						renderiza = true;
					}
					else if (gamPad->GetState().Gamepad.sThumbLX < 0) {
						if (!scene->EstoyColisionando) {
							scene->move('l');
						}
						else {
							scene->move('r');
							scene->move('r');
							scene->move('r');
							scene->move('r');
						}
						renderiza = true;
					}
					if (gamPad->GetState().Gamepad.sThumbLY > 0) {
						if (!scene->EstoyColisionando) {
							scene->move('f');
						}
						else {
							scene->move('b');
							scene->move('b');
							scene->move('b');
							scene->move('b');
						}
						renderiza = true;
					}
					else if (gamPad->GetState().Gamepad.sThumbLY < 0) {
						if (!scene->EstoyColisionando) {
							scene->move('b');
						}
						else {
							scene->move('f');
							scene->move('f');
							scene->move('f');
							scene->move('f');
						}
						renderiza = true;
					}
					if (gamPad->GetState().Gamepad.sThumbRX > 0) {
						scene->turnRight();
						renderiza = true;
					}
					else if (gamPad->GetState().Gamepad.sThumbRX < 0) {
						scene->turnLeft();
						renderiza = true;
					}
					if (gamPad->GetState().Gamepad.bRightTrigger) {
						if (SiguienteAtaque && !scene->Arma->getAtacando()) {
							SiguienteAtaque = false;
							KillTimer(hwndVentana, CooldownAtaque);
							KillTimer(hwndVentana, SinAtacar);
							SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
								CooldownAtaque,//identificador del timer
								scene->Arma->getCooldownAtaque(),//valor de time-out
								NULL);//direcci�n del procedimiento de timer
							SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
								SinAtacar,//identificador del timer
								scene->Arma->getDejardeAtacar(),//valor de time-out
								NULL);//direcci�n del procedimiento de timer
							scene->Arma->setAtacando(true);
						}
						else {//si no se suelta el bot�n de ataque el cooldown no se reinicia y no puede seguir atacando, tampoco puedes spamear el bot�n (balance)
							KillTimer(hwndVentana, CooldownAtaque);
							SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
								CooldownAtaque,//identificador del timer
								scene->Arma->getCooldownAtaque(),//valor de time-out
								NULL);//direcci�n del procedimiento de timer
						}
					}
					float DistanciaAKatana = sqrt(pow(scene->px - scene->SelectorKatana->getX(), 2) + pow(scene->pz - scene->SelectorKatana->getZ(), 2));
					float DistanciaALanza = sqrt(pow(scene->px - scene->SelectorLanza->getX(), 2) + pow(scene->pz - scene->SelectorLanza->getZ(), 2));
					float DistanciaHacha = sqrt(pow(scene->px - scene->SelectorHacha->getX(), 2) + pow(scene->pz - scene->SelectorHacha->getZ(), 2));
					float Posici�n[3] = { scene->px,scene->py,scene->pz };
					if (DistanciaAKatana <= 13 && gamPad->GetState().Gamepad.bLeftTrigger) {
						scene->Arma = scene->SelectorKatana->SeleccionarArma(scene->Arma, Posici�n);
					}
					else if (DistanciaALanza <= 13 && gamPad->GetState().Gamepad.bLeftTrigger) {
						scene->Arma = scene->SelectorLanza->SeleccionarArma(scene->Arma, Posici�n);
					}
					else if (DistanciaHacha <= 13 && gamPad->GetState().Gamepad.bLeftTrigger) {
						scene->Arma = scene->SelectorHacha->SeleccionarArma(scene->Arma, Posici�n);
					}
				}
			}
		}
	}

	return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hContextoGL;
	static HDC hContextoAux;
	int ancho, alto;
	char epx[6] = "";
	char epz[6] = "";
	char epy[6] = "";
	char edx[6] = "";
	char edz[6] = "";
	char edy[6] = "";
	char ec[80] = "";

	switch (message)
	{
	case WM_CREATE:
		hContextoAux = GetDC(hWnd);
		hContextoVentana = hContextoAux;
		DefPixelFormat(hContextoVentana);
		hContextoGL = wglCreateContext(hContextoVentana);
		wglMakeCurrent(hContextoVentana, hContextoGL);
		srand(time(NULL));
		break;
	case WM_CLOSE:
		exit(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F1:
		{
			string info = "X: " + to_string(scene->px) + " Y: " + to_string(scene->py)+ " Z: " +to_string(scene->pz);
			MessageBox(hWnd,info.c_str(),"INFO",MB_OK);
		}
			break;
		case VK_UP:
			scene->turnUp();
			renderiza = true;
			return 0;
		case VK_DOWN:
			scene->turnDown();
			renderiza = true;
			return 0;
		case VK_LEFT:
			scene->turnLeft();
			renderiza = true;
			return 0;
		case VK_RIGHT:
			scene->turnRight();
			renderiza = true;
			return 0;
		case 0x44: //D
			scene->move('r');
			renderiza = true;
			return 0;
		case 0x41: //A
			scene->move('l');
			renderiza = true;
			return 0;
		case 0x57: //W
			scene->move('f');
			renderiza = true;
			return 0;
		case 0x53: //S
			scene->move('b');
			renderiza = true;
			return 0;
		}
		break;
	case WM_TIMER:
	{
		switch (wParam) {
		case Timer1:
			renderiza = true;
			break;
		case CooldownAtaque:
			SiguienteAtaque = true;
			KillTimer(hWnd, CooldownAtaque);
			break;
		case SinAtacar:
			scene->Arma->resetAtaque();
			KillTimer(hWnd, SinAtacar);
			break;
		case CooldownDa�oJugador:
			Da�oJugador = true;
			KillTimer(hWnd, CooldownDa�oJugador);
			break;
		case CooldownSpawn:
			Spawnea = true;
			KillTimer(hWnd, CooldownSpawn);
			break;
		case LunaCarmes�:
			scene->ActivaLunaCarmes�();
			if (!scene->Luna) {
				Luna = false;
			}
			else {
				CieloCambiado = false;
				Cambios = 0;
				SetTimer(hWnd,//Manejador de ventana que recibir� los mensajes del timer
					DesactivaLuna,//identificador del timer
					60000,//valor de time-out
					NULL);//direcci�n del procedimiento de timer
			}
			KillTimer(hWnd, LunaCarmes�);
			break;
		case CambiarImagen:
			scene->Cielo++;
			CieloCambiado = false;
			KillTimer(hWnd, CambiarImagen);
			break;
		case DesactivaLuna:
			CieloCambiado = false;
			Cambios = 0;
			scene->Luna = false;
			KillTimer(hWnd, DesactivaLuna);
			break;
		}
	}
		break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, Timer1);
		delete scene;
		wglMakeCurrent(hContextoVentana, NULL);
		wglDeleteContext(hContextoGL);
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_SIZE:
	{
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DefPixelFormat(HDC hDC)
{
	int bestmatch;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), //tama�o de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tama�o del color en 32 bits
		0, 0, 0, 0, 0, 0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0, 0, 0, 0, //no hay bits de acumulacion
		16, //tama�o del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0, 0, 0 //mascaras de capas ignoradas
	};

	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}
