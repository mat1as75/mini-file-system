/* Integrantes: Mateo Silva - Brisa Kuster - Matias Alfaro */

#include<iostream>
#include<string.h>
#include<stdio_ext.h>
#include"estructuras.h"
#include"prototipos.h"
#include"prototiposTipoRet.h"
using namespace std;

int main (int argc, char *argv[]) {
	
	Sistema s = crearsistema(s);
	bool finaliza = false;
	cout << "COMANDOS: DIR - CREATEFILE - IF - DF - TYPE - DELETE - ATTRIB - IC - DC - SEARCH - MKDIR - CD - RMDIR - DESTRUIRSISTEMA - CLEAR." << endl;
	do{
		string consola;
		cout << "> ";
		getline(cin, consola);
		__fpurge(stdin);
		
		Cadena parametro1 = new char[LARGO_NOMBRE];
		Cadena parametro2 = new char[LARGO_NOMBRE+LARGO_EXTENSION+TEXTO_MAX];
		Cadena parametro3 = new char[TEXTO_MAX];
		Cadena token = new char[TEXTO_MAX];
		
		//Convertir el string consola en una cadena consolaC
		Cadena consolaC = new char[consola.length() + 1];
		strcpy(consolaC, consola.c_str());
		
		if(consola.length() > 0){ //Si se ingreso algo por consola
			Cadena consolaAux = new  char[consola.length()];
			strcpy(consolaAux, consolaC);
			
			//Separo lo ingresado por consola
			token = strtok(consolaC, " ");
			parametro1 = token; // COMANDO
			
			if(strcmp(parametro1, "DIR") == 0){
				if(strlen(consolaAux) > 3){
					token = strtok(NULL, " ");
					parametro2 = token; // PARAMETRO /S
					mostrarRetorno(DIR(s, parametro2));
				}else{
					strcpy(parametro2, "");
					mostrarRetorno(DIR(s, parametro2));
				}
			}
			if(strcmp(parametro1, "C") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION (archivo.txt)
				mostrarRetorno(CREATEFILE(s, parametro2));
			}
			if(strcmp(parametro1, "IF") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION (archivo.txt)
				token = strtok(NULL, "\"");
				parametro3 = token; // CONTENIDO A INGRESAR AL FINAL DEL ARCHIVO
				mostrarRetorno(IF(s, parametro2, parametro3));
			}
			if(strcmp(parametro1, "DF") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION (archivo.txt)
				token = strtok(NULL, "");
				parametro3 = token; // K CARACTERES A BORRAR DEL FINAL
				int p3 = atoi(parametro3);
				mostrarRetorno(DF(s, parametro2, p3));
			}
			if(strcmp(parametro1, "TYPE") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION DEL ARCHIVO (archivo.txt)
				mostrarRetorno(TYPE(s, parametro2));
			}
			if(strcmp(parametro1, "DELETE") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION DEL ARCHIVO (archivo.txt)
				mostrarRetorno(DELETE(s, parametro2));
			}
			if(strcmp(parametro1, "ATTRIB") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION DEL ARCHIVO (archivo.txt)
				token = strtok(NULL, "");
				parametro3 = token; // PARAMETRO DE ATRIBUTO (-W / +W)
				mostrarRetorno(ATTRIB(s, parametro2, parametro3));
			}
			if(strcmp(parametro1, "IC") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION DEL ARCHIVO (archivo.txt)
				token = strtok(NULL, "\"");
				parametro3 = token; // CONTENIDO A INGRESAR AL COMIENZO DEL ARCHIVO
				mostrarRetorno(IC(s, parametro2, parametro3));
			}
			if(strcmp(parametro1, "DC") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION DEL ARCHIVO (archivo.txt)
				token = strtok(NULL, "");
				parametro3 = token; // K CARACTERES A BORRAR DEL COMIENZO
				int p3 = atoi(parametro3);
				mostrarRetorno(DC(s, parametro2, p3));
			}
			if(strcmp(parametro1, "SEARCH") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE + EXTENSION DEL ARCHIVO (archivo.txt)
				token = strtok(NULL, "\"");
				parametro3 = token; // CADENA A BUSCAR EN ARCHIVO
				mostrarRetorno(SEARCH(s, parametro2, parametro3));
			}
			if(strcmp(parametro1, "MKDIR") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE DEL DIRECTORIO A CREAR
				mostrarRetorno(MKDIR(s, parametro2));
			}
			if(strcmp(parametro1, "CD") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // SEGUNDO PARAMETRO (NOMBRE DE SUBDIRECTORIO / .. / CD)
				mostrarRetorno(CD(s, parametro2));
			}
			if(strcmp(parametro1, "RMDIR") == 0){
				token = strtok(NULL, " ");
				parametro2 = token; // NOMBRE DEL DIRECTORIO A ELIMINAR
				mostrarRetorno(RMDIR(s, parametro2));
			}
			if(strcmp(parametro1, "DESTRUIRSISTEMA") == 0){
				mostrarRetorno(DESTRUIRSISTEMA(s));
				cout << endl << "Gracias por utilizar Mini File System!";
				finaliza = true;
			}
			if(strcmp(parametro1, "CLEAR") == 0){
				system("clear");
				cout << "COMANDOS: DIR - CREATEFILE - IF - DF - TYPE - DELETE - ATTRIB - IC - DC - SEARCH - MKDIR - CD - RMDIR - DESTRUIRSISTEMA - CLEAR." << endl;
			}
		}
	} while(!finaliza);
	
	return 0;
}

