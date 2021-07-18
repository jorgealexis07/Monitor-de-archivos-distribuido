# Monitor-de-archivos-distribuido
Monitor de archivos distribuido 

Descripción del problema 
Se ha solicitado la creación de un programa o conjunto de programas que cumplan con los siguientes requerimientos:
 • Mostrar la información de un archivo o conjunto de archivos: 
o Dispositivo en el que reside. 
o Número de inode. 
o Tipo de archivo. 
o Permisos. 
o Enlaces.
 	o User ID. 
o Group ID. 
o Longitud. 
o Último acceso. 
o Última modificación. 
• Se debe operar en un entorno distribuido. 
• Uso de sockets AF_INET. 
• Usar sockets orientados a conexión.
Descripción del diseño 
Más a detalle se presenta las funciones que llevara nuestro programa.
Cliente 
Para la lectura de los datos de los nodos se usaron:
• gethostname 
Para hacer la conexión: 
• socket
 	• connect 
Para leer el comando: 
• fgets 
Para escribir: 
• send 
Para leer la respuesta: 
• recv 

Servidor 
Para la lectura de los datos de los nodos se usaron:
 	• gethostbyname
 	• gethostname 
Para crear socket y esperar al cliente:
 	• socket 
• setsockopt
 	• bind 
• listen 
• accept 
Para leer el comando: 
• recv 
Para escribir: 
• send

Diseño de la solución 
En esta sección se presenta el diseño que se debe de realizar para cubrir los requerimientos, consulta en forma detallada el capítulo 11 de Programación Avanzada en UNIX; Se opta por usar un cliente y un servidor, los cuales usan sockets para comunicarse. A continuación, aparecen los diagramas de diseño del servidor y cliente. 

Cliente 
El cliente realiza el siguiente flujo: 
• Lee y valida los argumentos
• Crea una conexión con sockets. 
• Envía un nombre de archivo. 
• Recibe la descripción y la imprime.
 	• Cierra el socket. 
• Si hay más archivos vuelve a la creación del socket, de lo contrario termina. Ver la siguiente figura.
 

Código del cliente:
 
     







Servidor 
Para el servidor se tiene el siguiente flujo:
 	• Obtiene e imprime la información de su nodo. 
• Crea un socket por el que escucha las peticiones. 
• Si recibe una crea un hijo que la atiende y el sigue escuchando. 
• El hijo lee el nombre del archivo. 
• Recopila su información y la regresa por el socket. 
• Cierra la conexión.
 
Código del servidor: 
 
 






Ejecución:
   

