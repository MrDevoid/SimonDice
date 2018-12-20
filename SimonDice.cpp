#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <Windows.h>
CONSOLE_SCREEN_BUFFER_INFO	csbi;
using namespace std;
const int  MAX_COLORES = 4, MAX_COLORES_DIFICIL = 7, TAM_VEC_FAC = 12, TAM_VEC_DIF = 17, MAX_JUGADORES = 10, MAX_AYUDAS = 3, NUM_COLORES = 3;
enum tColores{ Rojo, Verde, Azul, Dorado, Blanco, Marron, Naranja };
enum tModo { Facil, Dificil };
typedef	unsigned long	DWORD;
const	 DWORD	doo = 523, re = 587, mi = 659, fa = 698, sol = 783, la =
880, si = 987, tiempo = 500;
const WORD negro = 0, azul = 1, verde = 2, cian = 3, rojo = 4, magenta = 6, amarillo = 14, gris = 7, blanco = 15;

struct tJugador {
	string nombre;
	float puntuacion;
};

struct tVector {
	vector <tJugador> puntuaciones;
	int cont = 0;
};

string mayusculas(string &repetir){
	for (int i = 0; i < repetir.size(); ++i){
		repetir[i] = toupper(repetir[i]);
	}
	return repetir;
}


string fallo(string &repetir){
	cout << "Por favor introduzca si o no:\n";
	cin >> repetir;
	return mayusculas(repetir);
}




//Sobrecarga del insertor para que muestre por pantalla el nombre correspondiente a cada elemento de tColores
ostream & operator <<(ostream & devolver, tColores color){
	switch (color){
	case Rojo:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rojo | FOREGROUND_INTENSITY); devolver << "Rojo"; Beep(doo, tiempo); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gris);  break;
	case Verde:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), verde | FOREGROUND_INTENSITY); devolver << "Verde"; Beep(re, tiempo); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gris); break;
	case Azul:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), azul | FOREGROUND_INTENSITY); devolver << "Azul"; Beep(mi, tiempo); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gris); break;
	case Dorado:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), amarillo | FOREGROUND_INTENSITY); devolver << "Dorado"; Beep(fa, tiempo); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gris); break;
	case Blanco:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blanco | FOREGROUND_INTENSITY); devolver << "Blanco"; Beep(sol, tiempo); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gris); break;
	case Marron:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), magenta | FOREGROUND_INTENSITY); devolver << "Marron"; Beep(la, tiempo); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gris); break;
	case Naranja:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cian | FOREGROUND_INTENSITY); devolver << "Naranja"; Beep(si, tiempo); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gris); break;
	}
	return devolver;
}

//Sobrecarga del insertor para el tipo vector <tJugador>; para que vaya mostrando todos los campos de cada uno de los elementos del vector
ostream & operator << (ostream & devolver, const tVector &contpuntuacion){
	if (contpuntuacion.cont != 0){
		for (unsigned int k = 0; k < contpuntuacion.cont - 1; ++k){
			devolver << contpuntuacion.puntuaciones.at(k).puntuacion << ' ' << contpuntuacion.puntuaciones.at(k).nombre << '\n';
		}
		devolver << contpuntuacion.puntuaciones.at(contpuntuacion.cont - 1).puntuacion << ' ' << contpuntuacion.puntuaciones.at(contpuntuacion.cont - 1).nombre;
	}
	return devolver;
}

//Función que abre el archivo "ranking" y almacena cada una de las puntuaciones en un vector
bool cargaranking(tVector &contpuntuacion){
	ifstream archivoranking; int i = 0;
	string aux = " ";
	contpuntuacion.puntuaciones.resize(MAX_JUGADORES);
	archivoranking.open("Ranking.txt");
	if (!archivoranking.is_open()) return false;
	else {
		archivoranking >> contpuntuacion.puntuaciones.at(i).puntuacion;
		getline(archivoranking, contpuntuacion.puntuaciones.at(i).nombre);
		if (contpuntuacion.puntuaciones.at(i).nombre != ""){
			++i;
			++contpuntuacion.cont;
			while (!archivoranking.eof()){
				archivoranking >> contpuntuacion.puntuaciones.at(i).puntuacion;
				getline(archivoranking, contpuntuacion.puntuaciones.at(i).nombre);
				++i;
				++contpuntuacion.cont;
			}
		}
	}
	archivoranking.close();
	return true;
}

//Función que pregunta el nombre al jugador
string nombre(){
	string text = " ";
	char aux = ' ';
	cout << "¿Cómo te llamas? ";
	getline(cin, text);
	cout << "Hola " << text << ", pulsa enter para empezar a jugar.";
	cin.get(aux);
	system("cls");
	return text;
}

//Función que muestra por pantalla el menú y verifica que se introducen valores correctos
int menu(){
	int opcion = 0;
	cout << "Bienvenido al juego de SIMON DICE\n";
	cout << "0. Salir\n";
	cout << "1. Jugar en modo facil\n";
	cout << "2. Jugar en modo dificil\n";
	cout << "3. Ver las  " << MAX_JUGADORES << " mejores puntuaciones\n";
	cout << "4. Ver jugador con la puntuacion mas alta\n";
	cout << "Elija una opcion para continuar: ";
	cin >> opcion;
	while (cin.fail() || opcion < 0 || opcion > 4){
		cin.sync(); cin.clear();
		cout << "Por favor, introduzca un valor valido: ";
		cin >> opcion;
	}
	return opcion;
}

//Función que convierte los caracteres alfabéticos en su correspondiente mayúsculas
char mayusculas(char colorusuario){
	return toupper(colorusuario);
}

//Función que permite al usuario volver a insertar un caracter alfabético en caso de que el introducido no sea válido
char fallo(char colorusuario){
	cout << "Introduce uno de los caracteres validos(R,V,A,D,B,M,N):\n";
	cin >> colorusuario;
	return mayusculas(colorusuario);
}

//Función que convierte el carácter introducido por el usuario en su correspondiente elemento de tColores
tColores charaColor(char colorusuario){
	if (colorusuario == 'R'){
		Beep(doo, tiempo);
		return tColores(0);
	}
	else if (colorusuario == 'V'){
		Beep(re, tiempo);
		return tColores(1);
	}
	else if (colorusuario == 'A'){
		Beep(mi, tiempo);
		return tColores(2);
	}
	else if (colorusuario == 'D'){
		Beep(fa, tiempo);
		return tColores(3);
	}
	else if (colorusuario == 'B'){
		Beep(sol, tiempo);
		return tColores(4);
	}
	else if (colorusuario == 'M'){
		Beep(la, tiempo);
		return tColores(5);
	}
	else if (colorusuario == 'N') {
		Beep(si, tiempo);
		return tColores(6);
	}
}

//Función que genera un número al azar
int NumeroAzar(tModo modo){
	int numero = 0;
	if (modo == Facil) numero = rand() % MAX_COLORES;
	else numero = rand() % MAX_COLORES_DIFICIL;
	return numero;
}

//Función que convierte un número en su correspondiente elemento de tColores
tColores EnteroaColor(int numero){
	return tColores(numero);
}

//Función que genera un vector con la secuencia completa de colores tanto en una partida fácil como difícil
void generarSecuencia(vector <tColores>& secuencia, int numColores, tModo modo){
	secuencia.clear();
	for (int i = 0; i < TAM_VEC_FAC; ++i){
		secuencia.push_back(EnteroaColor(NumeroAzar(modo)));
	}
	if (modo == Dificil){
		for (int k = TAM_VEC_FAC; k < TAM_VEC_DIF; ++k) secuencia.push_back(EnteroaColor(NumeroAzar(modo)));
	}
}


//Función que va mostrando los elementos de la secuencia al jugador
void mostrarSecuencia(const vector <tColores> & secuencia, int numColores){
	tColores color;
	for (int k = 0; k < numColores - 1; ++k){
		color = secuencia[k];
		cout << color << " - ";
	}
	cout << secuencia[numColores - 1] << '\n';
	cout << "Memorice la secuencia y ";
	system("pause");
	system("cls");
}

//Función que muestra el color correspondiente en caso de que haya ayudas disponibles; y en caso contrario, devuelva false
bool utilizarayuda(const vector <tColores> &secuencia, int indice, int & ayudas){
	if (ayudas > 0){
		ayudas -= 1;

		cout << "El siguiente color es " << secuencia[indice] << '\n';
		cout << "Te quedan " << ayudas << " ayudas\n";
		return true;
	}
	else return false;
}


//Función que devuelve true en caso de que jugador acierte la secuencia; además, va calculando la puntuación cada vez que se acierta un color o se utiliza una ayuda
bool comprobacionrespuesta(char colorusuario, const vector <tColores> &secuencia, int numColores, string usuario, tModo modo, float &puntuacion, int & ayudas){
	tColores colores; int i = 0; bool c = true, ayudado;
	cout << usuario << " introduce la secuencia de " << numColores << " colores\n";
	while (i < numColores && c){
		cin >> colorusuario;
		colorusuario = mayusculas(colorusuario);
		while (colorusuario != 'A' && colorusuario != 'R' && colorusuario != 'V' &&colorusuario != 'D'&&colorusuario != 'M' &&colorusuario != 'N'&&colorusuario != 'B' && colorusuario != 'X'){
			colorusuario = fallo(colorusuario);
		}
		colores = charaColor(colorusuario);
		if (colorusuario == 'X'){
			ayudado = utilizarayuda(secuencia, i, ayudas);
			if (ayudado){
				puntuacion -= 7;
			}
			else cout << "No te quedan mas ayudas disponibles\n";

		}
		else if (colores == secuencia[i]){
			++i;
			puntuacion += 5;
		}

		else c = false;
	}

	if (!c) {
		cout << "Usted ha fallado la secuencia de colores.¿Quiere volver a intentarlo?\n";
		cin.sync();
	}
	else if (modo == Facil && i != TAM_VEC_FAC || modo == Dificil && i != TAM_VEC_DIF) {
		cout << "¡¡Correcto!! Podemos pasar a la siguiente secuencia\n";
		cin.sync();
	}
	return c;
}

void controljuego(int & numColores, vector <tColores> & secuencia, string usuario, tModo modo, float & puntuacion, int ayudas, bool & c){
	char colorusuario = ' '; string repetir = " ";
	mostrarSecuencia(secuencia, numColores);
	if (comprobacionrespuesta(colorusuario, secuencia, numColores, usuario, modo, puntuacion, ayudas)){
		++numColores;
		puntuacion += 10;
	}
	else {
		c = false;
		numColores = NUM_COLORES;
		cin >> repetir;
		repetir = mayusculas(repetir);
		while (repetir != "SI" && repetir != "NO"){
			repetir = fallo(repetir);
		}
		if (repetir == "SI"){
			c = true;
			puntuacion = 0;
			ayudas = 3;
			generarSecuencia(secuencia, numColores, modo);
		}
		else;
	}
}

//Funcion que lleva a cabo la conducción del juego y devuelve la puntuación total del jugador
float juego(string &usuario, tModo modo){
	bool c = true;
	int numColores = NUM_COLORES;
	float puntuacion = 0;
	int ayudas = MAX_AYUDAS;
	vector <tColores> secuencia;
	generarSecuencia(secuencia, numColores, modo);
	if (modo == Facil){
		while (numColores <= TAM_VEC_FAC && c){
			controljuego(numColores, secuencia, usuario, modo, puntuacion, ayudas, c);
		}
	}
	if (modo == Dificil){
		while (numColores <= TAM_VEC_DIF && c){
			controljuego(numColores, secuencia, usuario, modo, puntuacion, ayudas, c);
			puntuacion *= 1.5;
		}
	}
	if (c == true) cout << "¡Genial! Ganaste.";
	else if (puntuacion < 0) puntuacion = 0;
	return puntuacion;

}

//Función que modifica el vector de puntuaciones una vez se termina una partida, añadiendo el nombre y la puntuación en caso de que se clasifique en el ranking
void modificarpuntuaciones(tVector &contpuntuacion, float puntuacion, string &nombre){
	if (contpuntuacion.cont != 0){
		if (puntuacion < contpuntuacion.puntuaciones.at(contpuntuacion.cont - 1).puntuacion){
			cout << "Lo siento pero tu puntuacion no esta entre las 10 mejores\n";
		}

		else{
			int i = contpuntuacion.cont - 1;
			while (i > -1 && puntuacion >= contpuntuacion.puntuaciones[i].puntuacion){
				--i;
			}
			for (int k = contpuntuacion.cont - 1; k > i + 1; --k){
				contpuntuacion.puntuaciones[k] = contpuntuacion.puntuaciones[k - 1];
				++contpuntuacion.cont;
			}
			contpuntuacion.puntuaciones[i + 1].nombre = nombre;
			contpuntuacion.puntuaciones[i + 1].puntuacion = puntuacion;
			++contpuntuacion.cont;
		}
	}
}

void visualizarranking(const tVector &contpuntuacion){
	cout << contpuntuacion;
	cout << '\n';
}

//Función que muestra los jugadores que han logrado la mayor puntuación (varios en caso de empate)
void bestPlayers(const tVector & contpuntuacion){
	bool cond = false; unsigned int i = 2;
	if (contpuntuacion.cont != 0){
		cout << contpuntuacion.puntuaciones.at(0).nombre;
		if (contpuntuacion.puntuaciones[0].puntuacion == contpuntuacion.puntuaciones[1].puntuacion)cout << ", " << contpuntuacion.puntuaciones[1].nombre;
		while (i < contpuntuacion.cont && !cond){

			if (contpuntuacion.puntuaciones.at(i - 1).puntuacion == contpuntuacion.puntuaciones.at(i).puntuacion) cout << ", " << contpuntuacion.puntuaciones.at(i).nombre;
			else cond = true;
			++i;
		}
		cout << '\n';
	}
	else cout << "Aun no hay record obtenidos\n";
}

//Función que guarda en el documento Ranking las 10 mejores puntuaciones
bool escribirranking(tVector & contpuntuacion){
	ofstream archivo;
	archivo.open("Ranking.txt");
	if (!archivo.is_open())return false;
	else{
		archivo << contpuntuacion;
		archivo.close();
		return true;
	}
}

int main(){
	system("chcp 1252");
	srand(time(NULL)); int nummenu = 0; string usuario = ""; tModo modo = Dificil; float puntuacion;
	tVector contpuntuacion;
	if (!cargaranking(contpuntuacion)) cout << "No se pudo abrir el archivo\n";
	usuario = nombre();
	nummenu = menu();
	while (nummenu != 0){
		switch (nummenu){
		case 1: modo = Facil;
		case 2: puntuacion = juego(usuario, modo); modificarpuntuaciones(contpuntuacion, puntuacion, usuario); break;
		case 3: visualizarranking(contpuntuacion); break;
		case 4: bestPlayers(contpuntuacion); break;
		}
		system("PAUSE");
		system("cls");
		nummenu = menu();
	}
	if (!escribirranking(contpuntuacion)) cout << "No se han podido guardar las puntuaciones obtenidas\n";
	return 0;
}
