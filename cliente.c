// Ficheros de cabecera y librerias
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
//netbd.h es necesitada por la estructura hostent usando la funcion stat de C POXIS.

int main(int argc, char *argv[])
{
	//hacemos la declaracion de variables para nuestro programa 
	struct stat datos;
	struct tm *fecha;
	char tipofich;
	char *fichero2;
 
	if(argc > 2)
	{
 		//Primer paso, definir variables
 		char *ip;
 		int fd, numbytes,puerto;
 		char buf[100];
 		puerto=atoi(argv[2]);
 		ip=argv[1];
 
		struct hostent *he;
 		/*==Lee y valida argumentos==*/
 		/* estructura que recibira informacion sobre el nodo remoto */
 		struct sockaddr_in server;
 	/* informacion sobre la direccion del servidor */
	if ((he=gethostbyname(ip))==NULL){
 		/* llamada a gethostbyname() */
 		printf("gethostbyname() error\n");
 		exit(-1);
 	}
 
	//Paso 2, Definicion de socket y creacion de la conexion con el servidor
 	if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
 		/* llamada a socket() */
 		printf("socket() error\n");
 		exit(-1);
 	}
	//Datos del servidor
 	server.sin_family = AF_INET;
 	server.sin_port = htons(puerto);
 	server.sin_addr = *((struct in_addr *)he->h_addr);
 	/*he->h_addr pasa la informaciÃ³n de ``*he'' a "h_addr" */
 	bzero(&(server.sin_zero),8);
 
 	//Paso 3, conectarnos al servidor
 	if(connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1){
 		/* llamada a connect() */
 		printf("connect() error\n");
 		exit(-1);
 	}
 
	if ((numbytes=recv(fd,buf,100,0)) == -1){
 		/* llamada a recv() */
 		printf("Error en recv() \n");
 		exit(-1);
 	}
 
	buf[numbytes]='\0';
	//Se envia el nombre del archivo asi como el host y direccion.
	 printf("Nombre de este host cliente: %s\n",argv[1]);
	 printf("Direccion de internet de este host cliente: %s\n",argv[1]);
	 printf("El puerto del servidor es: %s\n",argv[2]);
	 printf("Nombre de este host servidor: %s\n",argv[1]);
	 printf("Direccion de internet de este host servidor: %s\n",argv[1]);
	 /*Recibe la conexion y la imprime*/ 
	 printf("Se ha iniciado el Servidor: %s\n",buf);
	 /* muestra el mensaje de bienvenida del servidor =) */
	 printf("================================================================\n");
	 printf("================================================================\n");
	 if (argc != 4)
	{       /*si no se han ingresado parametros nos lanzara un error*/
		perror("Necesario fichero o directorio como parámetro\n");
		exit (-1);
	}
	if (stat(argv[3],&datos) != 0)
	{ 	
		perror("Error en el stat");
		exit (-1);
	}
	//nos muestra el nombre del archivo o fichero.
	printf("Nombre del fichero: %s\n",argv[3]);
	//nos muestra la informacion del fichero pedida.
	printf("Recide en el dispositivo = %ld \n", (long) datos.st_dev);
	printf("Numero de inode = %ld \n", (long) datos.st_ino);
	printf("Tamaño(longitud) en bytes: %d\n",datos.st_size);
	switch(datos.st_mode & S_IFMT)
	{
	case S_IFREG: 
		tipofich='R';
		printf("Tipo de fichero: Parametro (%c)\n",tipofich);
		break;
	case S_IFLNK:
		tipofich='L';
		printf("Tipo de fichero: Fichero: (%c)\n",tipofich);
		break;
	case S_IFDIR:
		tipofich='D';
		printf("Tipo de fichero: Directorio: (%c)\n",tipofich);
		break;
	}
	//printf("Tipo de fichero: %c\n",tipofich);
	printf("Permisos: \t");
    	printf( (S_ISDIR(datos.st_mode)) ? "d" : "-");
    	printf( (datos.st_mode & S_IRUSR) ? "r" : "-");
    	printf( (datos.st_mode & S_IWUSR) ? "w" : "-");
    	printf( (datos.st_mode & S_IXUSR) ? "x" : "-");
    	printf( (datos.st_mode & S_IRGRP) ? "r" : "-");
    	printf( (datos.st_mode & S_IWGRP) ? "w" : "-");
    	printf( (datos.st_mode & S_IXGRP) ? "x" : "-");
    	printf( (datos.st_mode & S_IROTH) ? "r" : "-");
    	printf( (datos.st_mode & S_IWOTH) ? "w" : "-");
    	printf( (datos.st_mode & S_IXOTH) ? "x" : "-");
    	printf("\n");
	printf("Número de enlaces: %d\n",datos.st_nlink);
	printf("User ID= %ld (alexis)\n", (long) datos.st_uid);
 	printf("Group ID= %ld (alexis) \n", (long) datos.st_gid);
	printf("Fecha Último acceso: ");
	printf("%s \n",ctime(&datos.st_atime));
	printf("Fecha Última modificación: ");
	printf("%s \n",asctime(localtime(&datos.st_mtime)));
	 
 
	close(fd);
	}
	else{
		printf("No se ingreso el ip y puerto por parametro\n");
	}
}
