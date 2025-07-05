#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H
#include"estructuras.h"

//Devuelve Sistema s creado
Sistema crearsistema(Sistema &s);

//Devuelve 1 si el archivo fue creado, o 0 en caso contrario.
int createFile(Sistema s, Cadena nombreArchivo);

//Muestra la ruta del directorio actual.
void imprimo_ruta(directorio directorioActual);

//Muestra l contenido del directorio actual, con parametro /S muestra todo el contenido del sistema.
void dir(Sistema &s, Cadena parametro);

//Devuelve una cadena menos los k ultimos caracteres.
Cadena df(Cadena contenido, int k);

//Devuelve una cadena menos los k primeros caracteres.
Cadena dc(Cadena contenido, int k);

//Devuelve true si la lista de archivos es vacia, o false en caso contrario.
bool es_vacio(archivo archivos);

//Devuelve true si el directorio es vacio, o false en caso contrario.
bool es_vacioDir(directorio d);

//Devuelve true si el directorio d es raiz, o false en caso contrario.
bool es_raiz(directorio d);

//Devuelve el nombre del archivo (nombre + extension)
Cadena juntoNombre(Cadena nombre, Cadena extension);

//Devuelve la posicion del archivo (entre la lista simple de archivos) en caso de existir, o 0 en caso contrario.
int buscoArchivo(archivo archivos, Cadena nombreArchivo, int pos);

//Devuelve la posicion del directorio (entre la lista de hermanos) en caso de existir, o 0 en caso contrario.
int buscoDirectorio(directorio directorioActual, directorio comparo, Cadena nombreDirectorio, int pos);

//Devuelve el contenido del archivo buscado por la posicion pasada por parametro.
Cadena devolverContenido(archivo archivos, int pos);

//Cambia el contenido del archivo buscado por la posicion pasada por parametro.
void cambioContenido(archivo archivos, Cadena texto, int pos);

//Devuelve 1 si el directorio fue creado, o 0 en caso contrario.
int mkdir(directorio &directorioActual, directorio comparo, Cadena nombreDir);

//Muestra los archivos del directorio actual con su ruta.
void imprimoArchivos(directorio directorioActual);

//Muestra el arbol completo.
void imprimoArbolCompleto(directorio directorioRaiz);

//Elimina archivo en caso de existir en directorio actual
archivo eliminoArchivo(archivo aBorrar);

//Elimina directorio en caso de existir en directorio actual.
directorio rmdir(directorio D);

//Elimina arbol (subarbol de D).
directorio eliminoArbol(directorio D);

#endif
