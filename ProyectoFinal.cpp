#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

struct TiendaDeVideojuegos
{
	string nombre, videojuego, Ano, Clasificacion, descvideojuego, CT;
	float preciodevideojuego = 0, preciototal = 0;
	int ano = 0000, mes = 00;
	//Tuve que poner "ano" en vez de "año" por que el codigo salia con errores al poner una ñ
};

void alta();
void lectura();
void escribirauto();
void actualizarvideojuego();
void eliminarvideojuego();

TiendaDeVideojuegos NumeroDeArticulo[5];
bool jugador = true;
float IVA = 0;

int main() {
	bool menu = true;
	int opcion = 0;
	cout << "\t\t\t\t\tBienvenido a nuestra Tienda de Videojuegos" << endl;
	while (menu) {

		cout << "Ingrese 1 para registrar un nuevo videojuego\n \t2 para modificar un videojuego\n \t3 para Eliminar un videojuego\n \t4 para revisar la lista de videojuegos" << endl;
		cout << "\t5 para limpiar la pantalla\n \t6 para leer el archivo\n \t0 para salir" << endl;
		cin >> opcion;

		switch (opcion)
		{

		case 0:
			exit(0);
			break;
		case 1:
			alta();
			return main();
			break;
		case 2:
			actualizarvideojuego();
			return main();
			break;

		case 3:
			eliminarvideojuego();
			return main();
			break;

		case 4:
			lectura();
			return main();
			break;

		case 5:
			system("cls");
			break;
		case 6:
			lectura();
			system("cls");
			break;
		default:
			cout << "No se ingreso una opcion correcta" << endl;
			system("pause");
			break;

		}
	}
}
void alta() {
	int opcion = 0, CT = 0, num = 0, i, articulo = 0, op2 = 0;

	while (jugador) {
		for (i = 0; i < 5; i++)
		{
			cout << i << "\tNombre de videojuego: ";
			cin.ignore();
			getline(cin, NumeroDeArticulo[i].nombre);
			cout << i << "\tAno de Lanzamiento del Videojuego: ";
			cin >> NumeroDeArticulo[i].ano;
			cout << i << "\tMes: ";
			cin >> NumeroDeArticulo[i].mes;
			if (NumeroDeArticulo[i].ano >= 1995 && NumeroDeArticulo[i].ano <= 2023 && NumeroDeArticulo[i].mes >= 1 && NumeroDeArticulo[i].mes <= 12)
			{
				cout << "\tEl ano y mes son validos: " << NumeroDeArticulo[i].ano << "/" << NumeroDeArticulo[i].mes << endl;
			}
			else {
				cout << "Ano y mes no validos!" << endl;
				main();
			}
			cout << i << "\tClasificacion: ";
			cin.ignore();
			getline(cin, NumeroDeArticulo[i].Clasificacion);
			cout << i << "\tCaracteristicas del Videojuego: ";
			getline(cin, NumeroDeArticulo[i].videojuego);
			cout << i << "\tDescripcion del Videojuego: ";
			cin >> NumeroDeArticulo[i].descvideojuego;
			cout << i << "\tGenero del videojuego: ";
			cin >> NumeroDeArticulo[i].CT;
			cout << i << "\tPrecio del videojuego: ";
			cin >> NumeroDeArticulo[i].preciodevideojuego;
			cout << i << "\t" << "Total(Pesos mexicanos, IVA incluido): ";
			NumeroDeArticulo[i].preciototal = NumeroDeArticulo[i].preciodevideojuego;
			IVA = NumeroDeArticulo[i].preciototal * .16;
			NumeroDeArticulo[i].preciototal += IVA;
			cout << NumeroDeArticulo[i].preciototal << endl;
			cout << "para agregar otro juego ingrese un numero, para regresar al menu ingrese 6" << endl;
			cin >> num;
			escribirauto();

			if (num == 6)
			{
				i = 5;
				jugador = true;
			}
		}
		break;
	}
}
void lectura() {
	int i = 0;
	string linea;
	fstream videojuego;
	videojuego.open("TiendaDeVideojuegos.txt", ios::in | ios::app);
	if (!videojuego.is_open()) {
		cout << "No se pudo abrir el archivo" << endl;
	}
	while (getline(videojuego, linea, '\n')) {
		cout << "El videojuego que fue ingresada en la posicion     " << "[" << i << "]" << endl;
		cout << "Datos del videojuego:" << linea << endl;
		i++;
	}
	videojuego.close();
}
void escribirauto() {
	int i = 0;
	ofstream archivo;
	string nombrearchivo;

	nombrearchivo = "TiendaDeVideojuegos.txt";
	archivo.open(nombrearchivo.c_str(), ios::out);

	if (archivo.fail())
	{
		cout << "ERROR NO SE PUDO CREAR";
		exit(1);
	}
	else
	{
		archivo << "El juego fue ingresado en la posicion   " << i + 1 << "|" << NumeroDeArticulo[i].nombre
			<< "|" << NumeroDeArticulo[i].ano << "/" << NumeroDeArticulo[i].mes
			<< "|" << NumeroDeArticulo[i].Clasificacion
			<< "|" << NumeroDeArticulo[i].videojuego
			<< "|" << NumeroDeArticulo[i].descvideojuego
			<< "|" << NumeroDeArticulo[i].CT
			<< "|" << NumeroDeArticulo[i].preciodevideojuego
			<< "|" << NumeroDeArticulo[i].preciototal << endl;
		system("cls");
	}
}
void eliminarvideojuego() {
	int i = 0;
	int lineaBorrar = 0;
	string deleteline;
	string line;
	ifstream fin;
	fin.open("TiendaDeVideojuegos.txt");
	ofstream temp;
	temp.open("tienda.txt");
	cout << "Ingrese el numero del videojuego que quiera dar de baja";
	cin >> lineaBorrar;

	while (getline(fin, deleteline, '\n')) {

		if (i == lineaBorrar)
			break;
		i++;
	}
	fin.close();

	fin.open("videojuegos.txt");
	while (getline(fin, line)); {
		if (line != deleteline)
			temp << line << endl;
	}
	fin.close();
	temp.close();
	remove("TiendaDeVideojuegos.txt");
	rename("tienda.txt", "TiendaDeVideojuegos.txt");
}
void actualizarvideojuego() {
	fstream fin;
	ofstream temp;
	string linea, ref;
	string n, nombre, c, carac, clas, cl, desc, d, gen, g;
	int precio = 0, p = 0, ano = 0, a = 0, mes = 0, m = 0;
	int op = 0, lineacambiar, pase = 0, i = 0;
	fin.open("TiendaDeVideojuegos.txt", ios::in);
	temp.open("tienda.txt");
	cout << "Ingrese el numero del videojuego que quiera modificar" << endl;
	cin >> lineacambiar;

	while (getline(fin, ref, '\n')) {

		if (i == lineacambiar)
			break;
		i++;
	}
	fin.close();

	fin.open("TiendaDeVideojuegos.txt", ios::in);
	while (getline(fin, linea)) {
		if (linea != ref)
			temp << linea << endl;
	}
	fstream refe;
	refe.open("temp2", ios::out);
	refe << ref;
	refe.close();
	cin.ignore();
	cout << "Ingrese el nuevo nombre" << endl;
	getline(cin, nombre);
	cout << "Ingrese la nueva fecha" << endl;
	cout << "Ano: ";
	cin >> ano;
	cout << "    mes:  ";
	cin >> mes;
	cout << endl;
	cout << "Ingrese la nueva clasificacion" << endl;
	cin >> clas;
	cout << "Ingrese las nuevas caracteristicas" << endl;
	cin >> carac;
	cout << "Ingrese la nueva descripcion" << endl;
	cin >> desc;
	cout << "Ingrese el nuevo genero" << endl;
	cin >> gen;
	cout << "Ingrese el nuevo precio" << endl;
	cin >> precio;
	refe.open("temp2", ios::in);
	refe >> n >> a >> m >> cl >> c >> d >> g >> p;
	n = nombre;
	a = ano;
	m = mes;
	cl = clas;
	c = carac;
	d = desc;
	g = gen;
	p = precio;
	temp << n << ' ' << a << "/" << m << ' ' << cl << ' ' << c << ' ' << d << ' ' << g << ' ' << p << endl;
	fin.close();
	temp.close();
	refe.close();
	remove("temp2.txt");
	remove("TiendaDeVideojuegos.txt");
	rename("tienda.txt", "TiendaDeVideojuegos.txt");
}




