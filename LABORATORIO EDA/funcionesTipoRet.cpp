#include<iostream>
#include<string.h>
#include"estructuras.h"
#include"prototipos.h"
using namespace std;

void mostrarRetorno(TipoRet retorno){
	switch (retorno){
	case OK:
		cout << "OK"<< endl;
		break;
	case ERROR:
		cout << "ERROR" << endl;
		break;
	case NO_IMPLEMENTADA:
		cout << "NO IMPLEMENTADA"<<endl;
	}
}

TipoRet CREARSISTEMA(Sistema &s){
	s = crearsistema(s);
	return OK;
}
	
TipoRet DIR(Sistema &s, Cadena parametro){
	dir(s, parametro);
	return OK;
}

TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo){
	int retorno = createFile(s, nombreArchivo);
	if(retorno != 1){
		return ERROR;
	}else{
		return OK;
	}
}
	
TipoRet TYPE(Sistema &s, Cadena nombreArchivo){
	if(s->directorioActual->archivos == NULL){ // No existen archivos en directorio actual
		cout << "No existen archivos en el directorio actual" << endl;
		return ERROR;
	}else{
		int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
		if(pos > 0){ // Existe archivo con ese nombre en directorio actual
			cout << devolverContenido(s->directorioActual->archivos, pos) << endl;
			return OK;
		}
		cout << "No existe un archivo con ese nombre en el directorio actual" << endl;
		return ERROR;
	}
}
	
TipoRet IF(Sistema &s, Cadena nombreArchivo, Cadena texto){
	int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
	int pos_aux = pos;
	archivo aux = s->directorioActual->archivos;
	
	if(pos > 0){
		/* Recorre el directorio hasta el archivo deseado */
		while(pos_aux > 1){
			aux = aux->sig;
			pos_aux--;
		}
		/* Si archivo es de Lectura/Escritura */
		if(strcmp(aux->atributo, "Lectura/Escritura") == 0){
			strcat(aux->contenido, texto); // Concateno texto al contenido (Ingreso al final)
			
			Cadena contenido_aux = new char[TEXTO_MAX];
			strncpy(contenido_aux, aux->contenido, TEXTO_MAX); // Copio en "contenido_aux" el contenido hasta TEXTO_MAX caracteres
			
			cambioContenido(s->directorioActual->archivos, contenido_aux, pos); // Modifico contenido del archivo
			return OK;
		}else{
			cout << "Archivo es de sólo lectura" << endl;
			return ERROR;
		}
	}
	cout << "No existe un archivo con ese nombre en el directorio actual" << endl;
	return ERROR;
}
	
TipoRet DF(Sistema &s, Cadena nombreArchivo, int k){
	int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
	int pos_aux = pos;
	archivo aux = s->directorioActual->archivos;
	
	if(pos > 0){
		/* Recorre el directorio hasta el archivo deseado */
		while(pos_aux > 1){
			aux = aux->sig;
			pos_aux--;
		}
		/* Si archivo es de Lectura/Escritura */
		if(strcmp(aux->atributo, "Lectura/Escritura") == 0){
			/* Cambio el contenido del archivo raiz quitandole los k ultimos caracteres */
			cambioContenido(s->directorioActual->archivos, df(aux->contenido, k), pos);
			return OK;
		}else{
			cout << "Archivo es de sólo lectura" << endl;
			return ERROR;
		}
	}
	cout << "No existe un archivo con ese nombre en el directorio actual" << endl;
	return ERROR;
}
	
TipoRet DELETE(Sistema &s, Cadena nombreArchivo){
	int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
	int pos_aux = pos - 1;
	archivo aux = s->directorioActual->archivos;
	
	if(pos != 0){
		/* Recorre el directorio hasta el archivo deseado */
		while(pos_aux > 1){
			aux = aux->sig;
			pos_aux--;
		}
		/* Unico nodo, primer posicion */
		if(pos == 1 && aux->sig == NULL){ 
			if(strcmp(aux->atributo, "Lectura") != 0){
				delete aux;
				s->directorioActual->archivos = NULL;
				return OK;
			}
		}
		/* Primer nodo, existe mas de un nodo */
		if(pos == 1 && aux->sig != NULL){ 
			if(strcmp(aux->atributo, "Lectura") != 0){
				archivo aBorrar = aux;
				s->directorioActual->archivos = s->directorioActual->archivos->sig;
				delete aBorrar;
				return OK;
			}
		}
		/* Posicion mayor a 1, mas de un nodo */
		if(pos > 1){ 
			if(strcmp(aux->sig->atributo, "Lectura") != 0){
				archivo aBorrar = aux->sig;
				aux->sig = aBorrar->sig;
				delete aBorrar;
				return OK;
			}
		}
		cout << "Archivo solo de Lectura" << endl;
		return ERROR;
	}
	cout << "No existe un archivo con ese nombre en el directorio actual" << endl;
	return ERROR;
}

TipoRet ATTRIB(Sistema &s, Cadena nombreArchivo, Cadena parametro){
	int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
	int pos_aux = pos;
	archivo aux = s->directorioActual->archivos;
	
	if(pos != 0){
		/* Recorre el directorio hasta el archivo deseado */
		while(pos_aux > 1){
			aux = aux->sig;
			pos_aux--;
		}
		// Parametro -W
		if(strcmp(parametro, "-W") == 0){
			// Archivo Lectura/Escritura
			if(strcmp(aux->atributo, "Lectura/Escritura") == 0){
				strcpy(aux->atributo, "Lectura");
			}
		}else{
			// Parametro +W
			if(strcmp(parametro, "+W") == 0){
				// Archivo Lectura
				if(strcmp(aux->atributo, "Lectura") == 0){
					strcpy(aux->atributo, "Lectura/Escritura");
				}
			}
		}
		return OK;
	}else{
		cout << "No existe un archivo con ese nombre en el directorio actual" << endl;
		return ERROR;
	}
}
	
TipoRet IC(Sistema &s, Cadena nombreArchivo, Cadena texto){
	int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
	int pos_aux = pos;
	archivo aux = s->directorioActual->archivos;
	
	if(pos > 0){
		/* Recorre el directorio hasta el archivo deseado */
		while(pos_aux > 1){
			aux = aux->sig;
			pos_aux--;
		}
		if(strcmp(aux->atributo, "Lectura/Escritura") == 0){
			strcat(texto, aux->contenido); // Concateno el contenido al texto (Ingreso al comienzo)
			
			Cadena contenido_aux = new char[TEXTO_MAX];
			strncpy(contenido_aux, texto, TEXTO_MAX); // Copio en "contenido_aux" el contenido hasta TEXTO_MAX caracteres
			
			cambioContenido(s->directorioActual->archivos, contenido_aux, pos); // Modifico contenido del archivo
			return OK;
		}else{
			cout << "Archivo es solo de lectura" << endl;
			return ERROR;
		}
	}
	cout << "No existe un archivo con ese nombre en el directorio actual" << endl;
	return ERROR;
}
	
TipoRet DC(Sistema &s, Cadena nombreArchivo, int k){
	int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
	int pos_aux = pos;
	archivo aux = s->directorioActual->archivos;
	
	if(pos > 0){
		/* Recorre el directorio hasta el archivo deseado */
		while(pos_aux > 1){
			aux = aux->sig;
			pos_aux--;
		}
		/* Si archivo es de Lectura/Escritura */
		if(strcmp(aux->atributo, "Lectura/Escritura") == 0){
			/* Cambio el contenido del archivo raiz quitandole los k primeros caracteres */
			cambioContenido(s->directorioActual->archivos, dc(aux->contenido, k), pos);
			return OK;
		}else{
			cout << "Archivo es de sólo lectura" << endl;
			return ERROR;
		}
	}
	cout << "No existe un archivo con ese nombre en el directorio actual" << endl;
	return ERROR;
}

TipoRet SEARCH(Sistema &s, Cadena nombreArchivo, Cadena texto){
	int pos = buscoArchivo(s->directorioActual->archivos, nombreArchivo, 0);
	int pos_aux = pos;
	archivo aux = s->directorioActual->archivos;
	
	if(pos > 0){
		/* Recorre el directorio hasta el archivo deseado */
		while(pos_aux > 1){
			aux = aux->sig;
			pos_aux--;
		}
		if(strstr(aux->contenido, texto) != NULL){
			cout << "Se encontro el texto dentro del archivo" << endl;
			return OK;
		}else{
			cout << "No se encontro el texto dentro del archivo" << endl;
			return ERROR;
		}
	}
	cout << "No existe un archivo con ese nombre en el directorio actual" << endl;
	return ERROR;
}

TipoRet MKDIR(Sistema &s, Cadena nombreDirectorio){
	int retorno = mkdir(s->directorioActual, s->directorioActual->hijo, nombreDirectorio);
	if(retorno != 1){
		return ERROR;
	}
	return OK;
}
	
TipoRet CD(Sistema &s, Cadena nombreDirectorio){
	if(strcmp(nombreDirectorio, "..") != 0){
		/* CD RAIZ */
		if(strcmp(nombreDirectorio, "RAIZ") == 0){
			s->directorioActual = s->directorioRaiz;
			return OK;
		}
		
		/* CD nombreDirectorio */
		int pos = buscoDirectorio(s->directorioActual, s->directorioActual->hijo, nombreDirectorio, 0);
		int pos_aux = pos;
		directorio auxDir = s->directorioActual->hijo;
		
		if(pos > 0){
			/* Recorre el directorioActual hasta el directorio deseado */
			while(pos_aux > 1){
				auxDir = auxDir->hermano;
				pos_aux--;
			}
			s->directorioActual = auxDir;
			return OK;
		}else{
			cout << "No existe el subdirectorio destino" << endl;
			return ERROR;
		}
	}else{
		/* CD .. */
		if(es_raiz(s->directorioActual)){
			cout << "El directorio actual es el directorio RAIZ" << endl;
			return ERROR;
		}else{
			s->directorioActual = s->directorioActual->padre;
			return OK;
		}
	}
}
	
TipoRet RMDIR(Sistema &s, Cadena nombreDirectorio){
	int pos = buscoDirectorio(s->directorioActual, s->directorioActual->hijo, nombreDirectorio, 0);
	int pos_aux = pos;
	directorio auxDir = s->directorioActual->hijo;
	if(pos > 0){
		/* Recorre el directorioActual hasta el directorio deseado */
		while(pos_aux > 1){
			auxDir = auxDir->hermano;
			pos_aux--;
		}
		
		s->directorioActual->hijo = rmdir(auxDir);
		return OK;
	}else{
		cout << "No existe el subdirectorio a eliminar" << endl;
		return ERROR;
	}
}

TipoRet DESTRUIRSISTEMA(Sistema &s){
	s->directorioRaiz = eliminoArbol(s->directorioRaiz);
	s->directorioActual = s->directorioRaiz; //Igualo a diectorioActual, el directorioRaiz
	cout << "SISTEMA DESTRUIDO" << endl;
	return OK;
}
