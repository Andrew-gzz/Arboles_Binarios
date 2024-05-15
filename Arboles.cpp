#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string.h>
#include <Windows.h>


using namespace std;

// Arboles
enum GENDER{
	MASCULINO,
	FEMENINO,
	OTRO,
};
struct nodo_usuario {  //ARBOL

	int num;	
	bool isActive = true;	
	char nombre[30];		
	int genero = OTRO;  
	nodo_usuario* izq;
	nodo_usuario* der;

} *raiz_usuario = 0, * aux_usuario;

struct nodo_usuario2 {
	int num;
	nodo_usuario* izq;
	nodo_usuario* der;
};


class CNombres {
private:
	char Nombres[50];
	char ApellidoP[25];
	char ApellidoM[25];

public:
	// Constructor
	CNombres() {}

	// Método para concatenar nombres y apellidos
	void concatenarNombres(char NombreCompleto[100]) {
		strcpy(NombreCompleto, Nombres);
		strcat(NombreCompleto, " ");
		strcat(NombreCompleto, ApellidoP);
		strcat(NombreCompleto, " ");
		strcat(NombreCompleto, ApellidoM);
	}

	// Setter para establecer los nombres y apellidos
	void setNombres(const char* nombres) {
		strcpy(Nombres, nombres);
	}

	void setApellidoP(const char* apellidoP) {
		strcpy(ApellidoP, apellidoP);
	}

	void setApellidoM(const char* apellidoM) {
		strcpy(ApellidoM, apellidoM);
	}
};



//arboles
void agrega_user_arbol(nodo_usuario** arbol, nodo_usuario* dato) {

	if (*arbol != 0) {
		if (dato->num < (*arbol)->num) {
			agrega_user_arbol(&(*arbol)->izq, dato);
		}
		else {
			if (dato->num > (*arbol)->num) {
				agrega_user_arbol(&(*arbol)->der, dato);
			}
			else {
				printf("El num de usuario ya existe \n");
			}
		}
	}
	else{	
		dato->izq = 0;
		dato->der = 0;
		*arbol = dato;
	}

}

void printArbol(nodo_usuario* arbol) { //ARBOL

	if (arbol != nullptr) {
		printf("ID de Usuario: %d\n", arbol->num);
		cout <<"Nombre del Usuario: " << arbol->nombre << endl;
		cout << "Genero del Usuario: " << arbol->genero << endl;
	}
	else {
		cout << "El árbol está vacío." << endl;
	}
}


void inOrder_Vuelo(nodo_usuario* arbol, int c) {  //ARBOL
	//Este creo que era otro método para imprimir los árboles (Lo sacó de internet)
	if (arbol != 0) {
		inOrder_Vuelo(arbol->izq, c + 1);
		for (short i = 0; i < c; i++) {
			cout << "    ";
		}
		printArbol(arbol);
		inOrder_Vuelo(arbol->der, c + 1);
	}
}
//Este es el que viene en las diapositivas, ya si quieres usar ese para el post y el inorder, solo le cambias el orden xd
void preOrder_Vuelo(nodo_usuario* arbol) {

	if (arbol != 0){                           	
		printArbol(arbol);
		preOrder_Vuelo(arbol->izq);
		preOrder_Vuelo(arbol->der);
	}	
}
void Buscar_Nodo(nodo_usuario* arbol, int ID) { 
//:::::::Busqueda realizada con pre-orden::::::::::://
	if (arbol != 0) {
		if (arbol->num == ID) { 
			printArbol(arbol);
		}
		Buscar_Nodo(arbol->izq,ID);
		Buscar_Nodo(arbol->der,ID);  	
		cout << "El ID no existe" << endl;		
	}
	
}
void postOrder_Vuelo(nodo_usuario* arbol) { 

	if (arbol != 0)                           
	{
		preOrder_Vuelo(arbol->izq);
		preOrder_Vuelo(arbol->der);
		printArbol(arbol);
	}
}

void Captura_Usuarios(nodo_usuario*datos) { 
	cout << "ID: "; cin >> datos->num;
	cin.ignore(); 
	cout << "Nombre: "; cin >> datos->nombre;
	cin.ignore();  
}

/*
void leer_arch_pas(char archivo[]) {
	ifstream archivaldo;
	archivaldo.open(archivo, ios::binary);
	if (archivaldo.is_open()) {
		arbol = preOrder_Read(archivaldo); // Llama a la función para leer el árbol en preorden
		archivaldo.close();
	}
	else {
		printf("Archivo no se pudo abrir\n");
	}
}

void preOrder_Write(nodo_usuario* nodo, ofstream& archivaldo) {
	if (nodo != nullptr) {
		// Escribe el nodo actual en el archivo
		archivaldo.write((char*)nodo, sizeof(nodo_usuario));

		// Llama recursivamente a preOrder_Write para los nodos izquierdo y derecho
		preOrder_Write(nodo->izq, archivaldo);
		preOrder_Write(nodo->der, archivaldo);
	}
}

nodo_usuario* preOrder_Read(ifstream& archivaldo) {
	nodo_usuario* nodo = nullptr;
	if (!archivaldo.eof()) {
		nodo = new nodo_usuario;
		archivaldo.read((char*)nodo, sizeof(nodo_usuario));

		// Lee recursivamente los nodos izquierdo y derecho
		nodo->izq = preOrder_Read(archivaldo);
		nodo->der = preOrder_Read(archivaldo);
	}
	return nodo;
}
*/



nodo_usuario* arbol = nullptr;

int main() {
	CNombres nombres;
	

	short opc = 0, _opc = 0;
	char mensaje[40];
	int _pasa;

	do
	{
		system("cls");
		printf("  SISTEMA DE USUARIOS\n");
		printf("1. Agregar usuario\n");
		printf("2. Recorrido Preorden\n");
		printf("3. Recorrido Entreorden\n");
		printf("4. Recorrido Postorden\n");
		printf("5. Buscar nodo\n");
		printf("6. Modificar nodo\n");
		printf("7. Salir\n");
		cin >> opc;
		cin.ignore(); 

		switch (opc)
		{
		case 1: {						
			nodo_usuario* nuevo_usuario = new nodo_usuario;		
			nuevo_usuario->izq = nullptr;
			nuevo_usuario->der = nullptr;			
			// Llamar a la función para agregar al árbol
			Captura_Usuarios(nuevo_usuario);
			agrega_user_arbol(&arbol, nuevo_usuario);					
			system("pause"); 
			break;
		}
		case 2:
			preOrder_Vuelo(arbol);
			system("pause");
			break;
		case 3:
			inOrder_Vuelo(arbol, 0);
			system("pause");
			break;
		case 4:
			postOrder_Vuelo(arbol);
			system("pause");
			break;
		case 5: {
			int x;
			cout << "Ingresa el ID del Usuario: ";
			cin >> x;
			Buscar_Nodo(arbol, x);
			system("pause");
		}break;
		case 6: {
			int x; 
			cout << "Ingresa el ID del Usuario: "; 
			cin >> x;
			Buscar_Nodo(arbol, x);
			cout << "Deseas modificar el usuario? 1) Si 2) NO" << endl;
			cin >> x; 
			if (x==1) {
				Captura_Usuarios(arbol); 
				cout << "Usuario modificado" << endl;
				system("PAUSE");
			}
			system("pause");
		}break;
		default:
			break;
		}
		printf("%s\n", mensaje);

	} while (opc < 7);

	system("pause");
}