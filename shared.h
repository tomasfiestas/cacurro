#ifndef SHARED_H
#define SHARED_H

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<commons/string.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<assert.h>
#include <string.h>

typedef enum{
	NEW,
	READY,
	EXEC,
	BLOCK,
	FIN
} t_estado;

typedef struct{
	uint8_t AX;
	uint8_t BX;
	uint8_t CX;
	uint8_t DX;
	uint32_t EAX;
	uint32_t EBX;
	uint32_t ECX;
	uint32_t EDX;
	uint32_t SI;
	uint32_t DI;
} t_registros;

typedef struct{
	int pid;
	int program_counter;
	t_estado estado;
	t_registros registros;	
	//t_list* tabla_archivos;	
	int quantum;//USAR uint_32
	int ejecuto;
} t_pcb;



typedef enum{
	FIFO,
	VRR,
	RR
} algoritmos;

typedef enum {
	EJECUTAR_SCRIPT,
    INICIAR_PROCESO,
    FINALIZAR_PROCESO,
    DETENER_PLANIFICACION,
    INICIAR_PLANIFICACION,
    MULTIPROGRAMACION,
    PROCESO_ESTADO,
	ERROR,
	EXIT,
	CREAR
} t_mensajes_consola;

typedef enum
{
	MENSAJE,
	PAQUETE,	
	HANDSHAKE_KERNEL,
	HANDSHAKE_CPU,
	HANDSHAKE_MEMORIA,
	HANDSHAKE_ES,

	//KERNEL
	//Kernel le avisa a memoria que tiene que crear un proceso
	CREAR_PROCESO_KM,
	//Kernel manda contexto de ejecucion a CPU
	CONTEXTO_EJECUCION,
	// Kernel manda a CPU cuando termina el quantum
	FIN_DE_QUANTUM,
	PROCESO_DESALOJADO,

	// CPU
	SOLICITUD_INST,
	SOLICITUD_INST_OK,

	// motivos de desalojo enviados por cpu
	FINPROCESO,
	IO,

	//Entrada Saldia
	IO_GEN_SLEEP,
	IO_STDIN_READ,
	IO_STDOUT_WRITE,
	IO_FS_CREATE,
	IO_FS_DELETE,
	IO_FS_TRUNCATE,
	IO_FS_WRITE,
	IO_FS_READ,
	CREAR_NUEVA_INTERFAZ,
	SOLICITAR_LECTURA

	//


}op_code;

typedef struct {
	uint32_t longitud;
	char* parametro;
} t_parametro;

typedef struct {
	uint32_t instruccion_longitud;
    char* instruccion;
	uint32_t parametros_cantidad;
	t_parametro* parametros;
} t_instruccion;

typedef struct {
	int pid;
	int cantidad;
	t_instruccion* instrucciones;
} t_instrucciones;

// CLIENTE
typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;


int crear_conexion_cliente(char* ip, char* puerto);
void enviar_mensaje(char* mensaje, int socket_cliente);

void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket_cliente);
void liberar_conexion(int socket_cliente);
void eliminar_paquete(t_paquete* paquete);
void paquete(int conexion);
void iterator(char* value);
int iniciar_servidor(char* puerto);
int esperar_cliente(int socket_servidor);
t_list* recibir_paquete(int);
int recibir_operacion(int);
void realizar_handshake(op_code module, int server);
void recibir_mensaje(int socket_cliente);

//Agrego funciones de prueba para enviar y recibir paquetes
t_buffer* crear_buffer();
t_buffer* recibir_buffer(int conexion);
void destruir_buffer(t_buffer* buffer);
void cargar_a_buffer(t_buffer* buffer, void* valor, int tamanio);
void cargar_int_a_buffer(t_buffer* buffer, int valor);
void cargar_instrucciones_a_buffer(t_buffer* buffer, t_instrucciones instrucciones);
void cargar_string_a_buffer(t_buffer* buffer, char* valor);
void cargar_uint32_a_buffer(t_buffer* buffer, uint32_t valor);
void cargar_uint8_a_buffer(t_buffer* buffer, uint8_t valor);
void cargar_contexto_ejecucion_a_buffer(t_buffer* buffer, t_pcb* pcb);
void cargar_estado_a_buffer(t_buffer* buffer, t_estado estado);
void cargar_registros_a_buffer(t_buffer* buffer, t_registros registros);
void cargar_pcb_a_buffer(t_buffer* buffer, t_pcb* pcb);
void cargar_pcb_a_buffer2(t_buffer* buffer, t_pcb pcb);

t_registros extraer_registros_del_buffer(t_buffer* buffer);
t_pcb recibir_contexto_ejecucion(t_buffer* buffer);
t_estado extraer_estado_del_buffer(t_buffer* buffer);
void* extraer_de_buffer(t_buffer* buffer);
int extraer_int_del_buffer(t_buffer* buffer);
uint8_t extraer_uint8_del_buffer(t_buffer* buffer);
uint32_t extraer_uint32_del_buffer(t_buffer* buffer);
char* extraer_string_del_buffer(t_buffer* buffer);
t_instrucciones* extraer_instrucciones_del_buffer(t_buffer* buffer);
void* serializar_paquete(t_paquete* paquete);
//t_pcb extraer_pcb_del_buffer(t_buffer* buffer);
t_pcb* extraer_pcb_del_buffer(t_buffer* buffer);




t_paquete* crear_paquete(op_code cod_op, t_buffer* buffer);
void destruir_paquete(t_paquete* paquete);
void iniciar_proceso(t_buffer* buffer);


#endif