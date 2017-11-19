#include "funcionesDataNode.h"


void leerArchivoConfig(char* rutaArchivoConfig)
{
	data_DataNode = malloc(sizeof(t_DataNode));

	data_DataNode->IP_FILESYSTEM=strdup("");
	data_DataNode->NOMBRE_NODO=strdup("");
	data_DataNode->RUTA_DATABIN=strdup("");

	t_config *configuracion = config_create(rutaArchivoConfig);

	string_append(&data_DataNode->IP_FILESYSTEM,config_get_string_value(configuracion,"IP_FILESYSTEM"));
	string_append(&data_DataNode->NOMBRE_NODO,config_get_string_value(configuracion,"NOMBRE_NODO"));
	string_append(&data_DataNode->RUTA_DATABIN,config_get_string_value(configuracion,"RUTA_DATABIN"));
	data_DataNode->PUERTO_FILESYSTEM= config_get_int_value(configuracion,"PUERTO_FILESYSTEM");
	data_DataNode->PUERTO_WORKER=config_get_int_value(configuracion,"PUERTO_WORKER");

	config_destroy(configuracion);
}

void conectarConFS(void){

	//log_info(logger,"Conectandose a YAMA");
	printf("Conectandose a YAMA");

	int puerto = data_DataNode->PUERTO_FILESYSTEM;

	socketConexionFS = iniciar_socket_cliente(data_DataNode->IP_FILESYSTEM, puerto);

	//socketConexionFS = crearCliente(data_DataNode->IP_FILESYSTEM, puerto);

	if(socketConexionFS== -1){
		log_error(logger,"\n No se pudo establecer la conexion con YAMA, cerrando FS...");
		exit(1);
	}

	//puts("Me conecte a FS");
	//log_info(logger,"Me conecte a FS");

	//envia DTN|DTNAME|IP|PUERTO

	char * handshake = malloc(50);	memcpy(handshake,"DTN",3);
	memcpy(handshake+3,data_DataNode->NOMBRE_NODO,string_length(data_DataNode->NOMBRE_NODO));
	memcpy(handshake + 3 + string_length(data_DataNode->NOMBRE_NODO),data_DataNode->IP_FILESYSTEM,string_length(data_DataNode->IP_FILESYSTEM));
	memcpy(handshake + 3 + string_length(data_DataNode->NOMBRE_NODO)+string_length(data_DataNode->IP_FILESYSTEM), string_itoa(data_DataNode->PUERTO_FILESYSTEM),4);

	//puts(handshake);

	enviar(socketConexionFS,handshake,50);





	//log_info(logger,"Handshake enviado a YAMA");

}
