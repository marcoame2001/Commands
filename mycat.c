#include <stdio.h>			/* Header file for printf */
#include <sys/types.h>		/* Header file for system call  open */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>			/* Header file for system calls read, write y close */

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	
	/*Si el numero de argumentos es distinto a 2, arrojamos error de paso de parametros*/
	if(argc != 2)
	{
		write(STDOUT_FILENO,"Numeros de argumentos incorrecto\n",34); /*imprimimos el error mediante la llamada al sistema write*/
		return -1;
	}

	int fb = open(argv[1],O_RDONLY); /*llama f.open en modo lectura. Como arg el path del archivo. La f. devuelve id o -1, si no abre*/
	
	/*inicializamos variables y asignamos su valor*/
	char buffer[BUFFER_SIZE]; 
	ssize_t n_read = BUFFER_SIZE; 

	if (fb == -1) /*Si no se pudo abrir el archivo, imprime error y devuelve -1*/
	{
		write(STDOUT_FILENO,"Error al abrir el archivo\n",27); /*imprimimos el error mediante la llamada al sistema write*/
		return -1;
	} 

	while (n_read == BUFFER_SIZE) /*iteramos mientras los caracteres leidos sean igual al tamaño del buffer*/
	{
		n_read = read(fb,buffer,BUFFER_SIZE);

		/*Error de lectura*/
		if(n_read == -1)
		{
			write(STDOUT_FILENO,"Error de lectura\n",18); /*imprimimos el error mediante la llamada al sistema write*/
			return -1;
		}

		write(STDOUT_FILENO,buffer,n_read); /*imprimimos los caracteres leidos*/
	}	
		
	if (close(fb) == -1) /*cerramos el fichero. Si da error, devolvemos -1*/
	{
		printf("Error al cerrar el fichero\n");
		return -1;
	}

	return 0;
}
