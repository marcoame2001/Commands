#include <stdio.h>	    /*Header file for system call printf*/
#include <sys/types.h>	/*Header file for system call fstat*/
#include <sys/stat.h>
#include <fcntl.h>	    /*Header file for system call fcntl*/
#include <dirent.h> 	/*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>


int main(int argc, char *argv[])
{

DIR *direccion;
struct dirent *direnst;
char buffer[PATH_MAX];

	/*Si el numero de argumentos es mayor a 1, arrojamos error de paso de parametros*/
	if(argc > 1)
	{
		printf("Numeros de argumentos incorrecto\n"); 
		return -1;
	}

	/*Obtenemos la direccin de inicio del dir actual y lo almacenamos en argv[1]*/
    argv[1] = getcwd(buffer,PATH_MAX);	

    if (argv[1] == NULL) /*Error de obtencion de directorio actual*/
    {
        printf("Error al obtener el directorio actual"); /*imprimimos el error*/
    }

    direccion = opendir(argv[1]); /*abrimos el directorio*/

	if (direccion == NULL) /*Si no se pudo abrir el dir, imprime error y devuelve -1*/
	{
		printf("Error al abrir el directorio\n");
		return -1;
	} 	

    while ( ( direnst = readdir(direccion) ) != NULL) /*mientras la estructura != NULL*/
    {
        if(direnst -> d_type == DT_REG) /*comprobacion para verificar si el fichero es regular*/
        {
            int fb = open(direnst -> d_name,O_RDONLY); /*abrimos el fichero, solo lectura*/

            if (fb == -1) /*Si no se pudo abrir el archivo, imprime error y devuelve -1*/
            {
                printf("Error al abrir el archivo\n"); 
                return -1;
            } 

            int longitud = lseek(fb,0,SEEK_END); /*ponemos el puntero a 0 bytes luego del fin del fichero para obtener su tamaño*/

            if (longitud == -1) /*Si no se pudo posicionar el puntero, imprime error y devuelve -1*/
            {
                printf("Error al posicionar el puntero\n"); 
                return -1;
            }             
        
            if (close(fb) == -1) /*cerramos el fichero. Si da error, devolvemos -1*/
            {
                printf("Error al cerrar el fichero\n");
                return -1;
            }
            
            printf("%s\t%i\n", direnst -> d_name, longitud); /*imprimimos el nombre del fichero, un tabulador y su tamaño*/
        }
    } 
    
    if (closedir(direccion) == -1) /*cerramos el directorio. Si da error, devolvemos -1*/
    {
        printf("Error al cerrar el directorio\n"); 
        return -1; 
    }
    
	return 0;
}