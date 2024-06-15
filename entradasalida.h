#ifndef ENTRADASALIDA_H
#define ENTRADASALIDA_H

#include <stdlib.h>
#include <stdio.h>
#include <utils/hello.h>
#include <utils/logging.h>
#include <utils/shared.h>

/*
void crear_interfaz(char* nombre, char* tipo){
    t_paquete* paquete = crear_paquete();
    crear_buffer();
    cargar_string_a_buffer(paquete->buffer, nombre);
    cargar_string_a_buffer(paquete->buffer, tipo);

    log_info(logger, "Interfaz Generica creada");
}
*/

int conexion_kernel;
int conexion_memoria;


int crear_conexion_cliente(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	// Ahora vamos a crear el socket.
	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	// Ahora que tenemos el socket, vamos a conectarlo
	freeaddrinfo(server_info);

	return socket_cliente;
} 

void conectar(socket_cliente, server_info){
    struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);
    freeaddrinfo(server_info);
    connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);
}





typedef struct{
    char* nombre;
    char* tipo;
} t_interfaz;

void crear_interfaz(char* nombre, char* tipo){
    
    interfaz->nombre = nombre;
    interfaz->tipo = tipo;
    log_info(logger, "Interfaz Generica creada");
}




/*
 case GENERICA:
                    crear_interfaz(mensaje_consola, argumentos[1]);
                    t_buffer* buffer = crear_buffer();
                    cargar_string_a_buffer(buffer, argumentos[1]); //PATH     
                    iniciar_proceso(buffer);
                    break;
                    
                case STDIN:
                    crear_interfaz(mensaje_consola, argumentos[1]);
                    t_buffer* buffer = crear_buffer();
                    cargar_string_a_buffer(buffer, argumentos[1]); //PATH     
                    iniciar_proceso(buffer);
                    break;

                case STDOUT:
                    crear_interfaz(mensaje_consola, argumentos[1]);
                    t_buffer* buffer = crear_buffer();
                    cargar_string_a_buffer(buffer, argumentos[1]); //PATH     
                    iniciar_proceso(buffer);
                    break;

                case DIALFS:
                    crear_interfaz(mensaje_consola, argumentos[1]);
                    t_buffer* buffer = crear_buffer();
                    cargar_string_a_buffer(buffer, argumentos[1]); //PATH     
                    iniciar_proceso(buffer);
                    break;
*/

void mandar_paquete_a_KERNEL(t_pcb* pcb){
	t_buffer* buffer_io = crear_buffer();    
    cargar_pcb_a_buffer(buffer_cpu,pcb);    
	t_paquete* paquete_io = crear_paquete(PAQUETE, buffer_io);
    enviar_paquete(paquete_io, PUERTO_ESCUCHA);

}


t_log* entradasalida_logger;
t_config* entradasalida_config;
char* TIPO_INTERFAZ;
char* TIEMPO_UNIDAD_TRABAJO;
char* IP_KERNEL;
char* PUERTO_KERNEL;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PATH_BASE_DIALFS;
char* BLOCK_SIZE;
char* BLOCK_COUNT;

typedef enum{
    GENERICA,
    STDIN,
    STDOUT,
    DIALFS
} t_tipo_interfaz;


void atender_mensajes_memoria(void* socket_cliente_ptr);

#endif