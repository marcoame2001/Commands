#include <stdio.h>		    /* Header file for system call printf */
#include <unistd.h>		    /* Header file for system call gtcwd */
#include <sys/types.h>		/* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
DIR *direccion;
struct dirent *direnst;
char buffer[PATH_MAX];

	/*Si el numero de argumentos es menor a 2, obtenemos la direccin de inicio del dir actual y lo almacenamos en argv[1]*/
	if(argc < 2)
	{
		argv[1] = getcwd(buffer,PATH_MAX);

		if (argv[1] == NULL) /*Error de obtencion de directorio actual*/
		{
			printf("Error al obtener el directorio actual"); 
		}
	}	
	
	/*Si el numero de argumentos es mayor a 2, arrojamos error de paso de parametros*/
	if(argc > 2)
	{
		printf("Numeros de argumentos incorrecto\n"); 
		return -1;
	}

    direccion = opendir(argv[1]); /*abrimos el directorio*/

	if (direccion == NULL) /*Si no se pudo abrir el dir, imprime error y devuelve -1*/
	{
		printf("Error al abrir el directorio\n");
		return -1;
	} 

    while ( ( direnst = readdir(direccion) ) != NULL) /*mientras la estructura != NULL*/
    {
        printf("%s\n", direnst -> d_name); /*imprimimos el nombre del fichero*/
    } 

    if (closedir(direccion) == -1) /*cerramos el directorio. Si da error, devolvemos -1*/
    {
        printf("Error al cerrar el directorio\n"); 
        return -1; 
    }
	
    return 0;
}   
