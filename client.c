#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, const char * argv[] )
{
        if ( argc > 2 ) {
                const char *ip;
                int client_socket, numbytes, puerto;
                char buff[100];
                puerto = atoi( argv[2] );
                ip = argv[1];

                struct sockaddr_in server;

                if ( inet_pton( AF_INET, argv[1], &server.sin_addr ) <= 0  ) { 
                        printf( "la ip %s no es valida\n", ip );

                        return -1;
                }
                printf( "abrir el socket\n" );

                if ( ( client_socket = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 ){
                        printf("no pude abrir el socket\n");

                        return -2;
                }
                
                server.sin_family = AF_INET;
                server.sin_port = htons( puerto );
                bzero( &(server.sin_zero ), 8);

                printf( "coenctando a %s:%s\n", argv[1], argv[2]  );

                if (connect( client_socket, (struct sockaddr *)&server, sizeof( struct sockaddr) ) == -1) { 
                        printf ( "No pude conectarme al servidor\n" );

                        return -3;
                } 

                printf("recibiendo...\n");

                if ( ( numbytes = recv( client_socket, buff, 100, 0 )  ) == -1 ) {
                        printf( "Error en la lectura\n" );

                        return -4;
               }
                
                buff[numbytes] = '\0';

                printf( "el servidor envio el mensaje '%s'\n", buff );

                shutdown( client_socket, 2);
                
        } else { 
                printf( "por favor indique ip del servidor y puerto\n" );
        }
}           
