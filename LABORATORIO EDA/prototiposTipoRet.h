#ifndef PROTOTIPOSTIPORET_H
#define PROTOTIPOSTIPORET_H

//Muestra el retorno de la funcion retorno.
void mostrarRetorno(TipoRet retorno);

/*  ###########################
	### TIPO 1: 1er Entrega ###
	###########################*/

//Este comando inicializa el sistema para que contenga unicamente al directorio RAIZ
TipoRet CREARSISTEMA(Sistema &s);

//Este comando muestra el contenido del directorio actual
TipoRet DIR(Sistema &s, Cadena parametro);

//Este comando crea un nuevo archivo en el directorio actual
TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo);

//Este comando agrega texto al final del archivo NombreArchivo
TipoRet IF(Sistema &s, Cadena nombreArchivo, Cadena texto);

//Este comando elimina los K ultimos caracteres del archivo parametro
TipoRet DF(Sistema &s, Cadena nombreArchivo, int k);

//Este comando imprime el contenido del archivo parametro
TipoRet TYPE(Sistema &s, Cadena nombreArchivo);

/*  ###########################
	### TIPO 2: 1er Entrega ###
	###########################*/

//Este comando elimina un archivo del directorio actual
TipoRet DELETE(Sistema &s, Cadena nombreArchivo);

//Este comando cambia los atributos de un archivo perteneciente al directorio actual
TipoRet ATTRIB(Sistema &s, Cadena nombreArchivo, Cadena parametro);

//Este comando agrega texto al comienzo del archivo NombreArchivo
TipoRet IC(Sistema &s, Cadena nombreArchivo, Cadena texto);

//Este comando elimina los K primeros caracteres del archivo parametro
TipoRet DC(Sistema &s, Cadena nombreArchivo, int k);

//Este comando destruye el sistema, liberando la memoria asignada a las estructuras de datos que constituyen el file system
TipoRet DESTRUIRSISTEMA(Sistema &s);

//Este comando busca dentro del archivo la existencia del texto
TipoRet SEARCH(Sistema &s, Cadena nombreArchivo, Cadena texto);

/*  ###########################
	### TIPO 1: 2da Entrega ###
	###########################*/

//Este comando nos permitira desplazarnos en la estructura de directorios
TipoRet CD(Sistema &s, Cadena nombreDirectorio);

//Este comando crea un nuevo subdirectorio vacio del directorio actual
TipoRet MKDIR(Sistema &s, Cadena nombreDirectorio);

/*  ###########################
	### TIPO 2: 2da Entrega ###
	###########################*/

//Este comando elimina un subdirectorio hijo del directorio actual
TipoRet RMDIR(Sistema &s, Cadena nombreDirectorio);

/*  ###########################
	####### OPCIONALES ########
	###########################*/

//Este comando mueve un directorio o archivo desde su directorio origen hasta un nuevo directorio destino
TipoRet MOVE(Sistema &s, Cadena nombre, Cadena directorioDestino); //NO_IMPLEMENTADA

//Este comando busca y remplaza dentro del archivo la existencia del texto1 por el texto 2
TipoRet REPLACE(Sistema &s, Cadena nombreArchivo, Cadena texto1, Cadena texto2); //NO_IMPLEMENTADA

#endif
