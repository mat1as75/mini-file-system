#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#define LARGO_NOMBRE 15 // Caracteres maximo del nombre del archivo o directorio
#define LARGO_EXTENSION 3 // Caracteres maximo de la extension del archivo
#define LARGO_ATRIBUTO 20 // Caracteres maximos de los atributos del archivo
#define TEXTO_MAX 50 // Caracteres maximo en contenido del archivo

typedef char* Cadena;

typedef enum _retorno{
	OK, ERROR, NO_IMPLEMENTADA
}TipoRet;

/* Estructura Archivo */
typedef struct nodo_archivo{
	Cadena nombre = new char[LARGO_NOMBRE];
	Cadena extension = new char[LARGO_EXTENSION];
	Cadena atributo = new char[LARGO_ATRIBUTO];
	Cadena contenido = new char[TEXTO_MAX];
	nodo_archivo *sig;
}*archivo;

/* Estructura Directorio */
typedef struct nodo_directorio{
	Cadena nombre = new char[LARGO_NOMBRE];
	archivo archivos = NULL;
	nodo_directorio *padre;
	nodo_directorio *hijo;
	nodo_directorio *hermano;
}*directorio;

/* Estructura Sistema */
typedef struct _sistema{
	directorio directorioRaiz;
	directorio directorioActual;
}*Sistema;

#endif









