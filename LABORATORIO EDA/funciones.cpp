#include<iostream>
#include<string.h>
#include<stdio_ext.h>
#include"prototipos.h"
#include"estructuras.h"
using namespace std;

bool es_vacio(archivo archivos){
	if(archivos == NULL){
		return true;
	}else{
		return false;
	}
}
	
bool es_vacioDir(directorio d){
	if(d == NULL){
		return true;
	}else{
		return false;
	}
}
	
bool es_raiz(directorio d){
	if(es_vacioDir(d->padre))
		return true;
	else
		return false;
}
	
Cadena juntoNombre(Cadena nombre, Cadena extension){
	Cadena nombreCompleto = new char[LARGO_NOMBRE+LARGO_EXTENSION + 1];
	strcpy(nombreCompleto, nombre);
	nombreCompleto = strcat(nombreCompleto, ".");
	nombreCompleto = strcat(nombreCompleto, extension);
	return nombreCompleto;
}
	
int buscoArchivo(archivo archivos, Cadena nombreArchivo, int pos){
	Cadena nombreAr = new char[LARGO_NOMBRE+LARGO_EXTENSION];
	strcpy(nombreAr, nombreArchivo);
	Cadena nombre = new char[LARGO_NOMBRE];
	Cadena extension = new char[LARGO_EXTENSION];
	nombre = strtok(nombreAr, "."); // Separo el nombre del archivo
	extension = strtok(NULL, "."); // Separo la extension del archivo
	
	// Existe por lo menos un nodo en el directorio actual
	if(!es_vacio(archivos)){
		// Si hay un unico nodo y ademas es distinto al nombre del archivo
		if( es_vacio(archivos->sig) && (strcmp(archivos->nombre, nombre) != 0 && strcmp(archivos->extension, extension) != 0) ){
			return 0;
		}else{
			pos++;
			/* Si el nombre del archivo es igual, retorna la posicion
			actual del archivo. Sino busca el siguiente */
			if(strcmp(archivos->nombre, nombre) == 0 && strcmp(archivos->extension, extension) == 0){
				return pos;
			}else{
				return buscoArchivo(archivos->sig, nombreArchivo, pos);
			}
		}
	}
	return 0; // En caso de que Archivos sea vacio
}
	
int buscoDirectorio(directorio directorioActual, directorio comparo, Cadena nombreDirectorio, int pos){
	
	// Existe por lo menos un directorio en el directorio actual
	if(!es_vacioDir(directorioActual->hijo)){
		// Si hay un unico directorio y ademas es distinto al nombre del directorio
		if( comparo->hermano == NULL && strcmp(comparo->nombre, nombreDirectorio) != 0 ){
			return 0;
		}else{
			pos++;
			/* Si el nombre del directorio es igual, retorna la posicion
			actual del directorio. Sino busca el siguiente */
			if(strcmp(comparo->nombre, nombreDirectorio) == 0){
				return pos;
			}else{
				return buscoDirectorio(directorioActual, comparo->hermano, nombreDirectorio, pos);
			}
		}
	}
	return 0; // En caso de que directorioActual sea vacio
}
	
Cadena devolverContenido(archivo archivos, int pos){
	if(pos == 1){
		if(strcmp(archivos->contenido, "") == 0){
			cout << "El archivo no posee contenido";
		}
		return archivos->contenido;
	}else{
		return devolverContenido(archivos->sig, pos-1);
	}
}
	
void cambioContenido(archivo archivos, Cadena texto, int pos){
	if(pos == 1){
		strcpy(archivos->contenido, texto);
	}else{
		cambioContenido(archivos->sig, texto, pos-1);
	}
}

Sistema crearsistema(Sistema &s){
	s = new _sistema;
	directorio raiz = new nodo_directorio;
	raiz->padre = NULL;
	raiz->hermano = NULL;
	s->directorioRaiz = raiz;
	strcpy(s->directorioRaiz->nombre, "RAIZ");
	s->directorioActual = s->directorioRaiz;
	return s;
}

void dir(Sistema &s, Cadena parametro){
	archivo auxA = s->directorioActual->archivos;
	if(strcmp(parametro, "/S") != 0){ /* SIN PARAMETRO */
		imprimo_ruta(s->directorioActual);
		cout << endl;
		while(auxA != NULL){
			cout << auxA->nombre << "." << auxA->extension << "     " << auxA->atributo << endl;
			auxA = auxA->sig;
		}
		directorio aux = s->directorioActual->hijo;
		while(aux != NULL){
			cout << aux->nombre << endl;
			aux = aux->hermano;
		}
	}else{ /* PARAMETRO /S */
		imprimoArbolCompleto(s->directorioRaiz);
	}
}
	
int createFile(Sistema s, Cadena nombreArchivo){
	int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
	if(pos > 0){ /* Archivo ya existe */
		cout << "Ya existe archivo con ese nombre en directorio Actual" << endl;
		return 0;
	}else{
		
		archivo nuevoArchivo = new nodo_archivo;
		
		Cadena nom = new char[LARGO_NOMBRE];
		nom = strtok(nombreArchivo, "."); // Separo el nombre del archivo
		strncpy(nuevoArchivo->nombre, nom, LARGO_NOMBRE);
		
		Cadena ext = new char[LARGO_EXTENSION];
		ext = strtok(NULL, "."); // Separo la extension del archivo
		strncpy(nuevoArchivo->extension, ext, LARGO_EXTENSION);
		
		strcpy(nuevoArchivo->atributo, "Lectura/Escritura"); // Asigno el atributo default 
		strcpy(nuevoArchivo->contenido, ""); // Contenido vacio
		nuevoArchivo->sig = NULL;
		
		if(es_vacio(s->directorioActual->archivos)){ /* Si no existen archivos en directorioActual */
			s->directorioActual->archivos = nuevoArchivo;
		}else{
			archivo act = s->directorioActual->archivos;
			archivo ant = s->directorioActual->archivos;
			while(act != NULL && strcmp(act->nombre, nom) <= 0){
				if(strcmp(act->nombre, nom) == 0 && strcmp(act->extension, ext) < 0){
					ant = act;
					act = act->sig;
				}else{
					if(strcmp(act->nombre, nom) != 0){
						ant = act;
						act = act->sig;
					}else{
						if(ant == act){
							s->directorioActual->archivos = nuevoArchivo;
							nuevoArchivo->sig = act;
						}else{
							ant->sig = nuevoArchivo;
							nuevoArchivo->sig = act;
						}
						break;
					}
				}
			}
			if(ant == act){
				s->directorioActual->archivos = nuevoArchivo;
				nuevoArchivo->sig = act;
			}else{
				ant->sig = nuevoArchivo;
				nuevoArchivo->sig = act;
			}
		}
		return 1;
	}
}

Cadena df(Cadena contenido, int k){
	Cadena aux = new char[TEXTO_MAX];
	int kCont = strlen(contenido); // Largo del archivo (raiz->contenido)
	if(k >= kCont){
		/* Si la cantidad de caracteres a borrar es 
		mayor o igual a los carecteres del archivo */
		strcpy(contenido, "");
	}
	
	int tam = kCont - k; // tam = Cant caracteres del archivo - Cant caracteres a borrar
	int i = 0;
	while(i < tam){
		/* Mientras i sea menor a tam, copie la 
		direccion de memoria de contenido+i en aux+i */
		*(aux+i) = *(contenido+i);
		i++;
	}
	
	return aux;
}
	
Cadena dc(Cadena contenido, int k){
	
	/* Invierte cadena contenido */
	Cadena invertida = new char[strlen(contenido)];
	int x = 0;
	for(int i = strlen(contenido)-1; i >= 0; i--){
		*(invertida+x) = *(contenido+i);
		x++;
	}
	
	Cadena aux = new char[strlen(invertida)];
	aux = df(invertida, k); /* Elimina los k ultimos caracteres */
	
	/* Vuelve a invertir cadena contenido */
	Cadena dobleInvertida = new char[strlen(aux)];
	int y = 0;
	for(int i = strlen(aux)-1; i >= 0; i--){
		*(dobleInvertida+y) = *(aux+i);
		y++;
	}
	*(dobleInvertida+y) = '\0';
	
	return dobleInvertida;
	
}

int mkdir(directorio &directorioActual, directorio comparo, Cadena nombreDir){
	int pos = buscoDirectorio(directorioActual, comparo, nombreDir, 0);
	int aux;
	if(strcmp(nombreDir, "RAIZ") == 0){
		cout << "Nombre no valido" << endl;
		aux = 0;
	}else{
		if(pos > 0){
			cout << "Ya existe un subdirectorio con ese nombre en directorio actual" << endl;
			aux = 0;
		}else{
			if(es_vacioDir(directorioActual->hijo)){ // NO EXISTEN DIRECTORIOS
				directorio nuevoDir = new nodo_directorio;
				strncpy(nuevoDir->nombre, nombreDir, LARGO_NOMBRE);
				nuevoDir->padre = directorioActual;
				nuevoDir->hijo = NULL; // Hijo del nuevoDir = NULL
				nuevoDir->hermano = NULL;
				directorioActual->hijo = nuevoDir;
				aux = 1;
			}else{
				
				/* MIENTRAS QUE NOMBREDIR SEA MAYOR A COMPARO, AVANZA AL SIGUIENTE HERMANO */
				directorio ant = comparo;
				
				while(comparo != NULL && strcmp(comparo->nombre, nombreDir) < 0){
					ant = comparo;
					comparo = comparo->hermano;
				}
				
				directorio nuevoDir = new nodo_directorio;
				strncpy(nuevoDir->nombre, nombreDir, LARGO_NOMBRE);
				nuevoDir->padre = directorioActual;
				nuevoDir->hijo = NULL; /* Hijo del nuevoDir = NULL */
				nuevoDir->hermano = comparo;
				if(ant != comparo){
					ant->hermano = nuevoDir;
				}else{
					directorioActual->hijo = nuevoDir;
				}
				aux = 1;
			}
		}
	}
	return aux;
}
	
void imprimoArchivos(directorio directorioActual){
	archivo auxA = directorioActual->archivos;
	while(!es_vacio(auxA)){
		imprimo_ruta(directorioActual); 
		cout << "/" << auxA->nombre << "." << auxA->extension << endl;
		auxA = auxA->sig;
	}
}

void imprimo_ruta(directorio directorioActual){
	if(strcmp(directorioActual->nombre, "RAIZ") == 0){
		cout << directorioActual->nombre;
	}else{
		imprimo_ruta(directorioActual->padre);
		cout << "/" << directorioActual->nombre;
	}
}
	
void imprimoArbolCompleto(directorio directorioRaiz){
	imprimo_ruta(directorioRaiz);
	cout << endl;
	imprimoArchivos(directorioRaiz);
	if(!es_vacioDir(directorioRaiz->hijo)){
		imprimoArbolCompleto(directorioRaiz->hijo);
	}
	if(!es_vacioDir(directorioRaiz->hermano)){
		imprimoArbolCompleto(directorioRaiz->hermano);
	}
}

archivo eliminoArchivo(archivo aBorrar){
	if(aBorrar != NULL){
		if(aBorrar->sig == NULL){
			delete aBorrar;
		}else{
			return eliminoArchivo(aBorrar->sig);
		}
	}
	return aBorrar;
}
	
directorio rmdir(directorio D){
	directorio aBorrar = D;
	D->hijo = eliminoArbol(D->hijo);
	/* Nodo a borrar es primer hijo */
	if(aBorrar->padre->hijo == aBorrar){
		aBorrar->padre->hijo = aBorrar->hermano;
		delete aBorrar;
	}else{
		directorio ant = aBorrar->padre->hijo; /* ant apunta al primer hijo de D */
		D = aBorrar->padre->hijo;
		while(D != NULL && D->hermano != aBorrar){ /* Busco el anterior del nodo aBorrar */
			ant = D;
			D = D->hermano;
		}
		ant = D;
		ant->hermano = aBorrar->hermano;
		delete aBorrar;
	}
	return D->padre->hijo; /* Retorna el primero hijo del padre de D */
}

directorio eliminoArbol(directorio D){
	if(!es_vacioDir(D)){
		archivo A = D->archivos;
		A = eliminoArchivo(D->archivos);
		D->archivos = A;
		return eliminoArbol(D->hijo);
		return eliminoArbol(D->hermano);
		delete D;
	}
	return D;
}
