#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BAJO 0
#define MEDIO 1
#define ALTO 2

typedef struct {
  int ID;
  char descriProblema[100];
  int prioridad;
} ticketPersona;

ticketPersona* crearTicket(int id, const char *descripcion){
  ticketPersona *newTicket = (ticketPersona*)malloc(sizeof(ticketPersona));

  if(newTicket == NULL){
    return NULL;
  }

  newTicket->ID = id;
  strcpy(newTicket->descriProblema,descripcion);
  newTicket->prioridad = BAJO;

  return newTicket;
}
void registrar_paciente(List *pacientes) {
  int id;
  char descripcion[100];

  printf("Ingrese ID paciente: ");
  scanf("%d",&id);
  getchar();

  printf("Ingrese descripcion paciente: ");
  scanf("99[^\n]",descripcion);

  //printf("Registrar nuevo paciente\n");

  ticketPersona *newTicket = crearTicket(id,descripcion);
  if(newTicket != NULL){
    list_pushBack(pacientes,newTicket);
  }
  // Aquí implementarías la lógica para registrar un nuevo paciente
}

void asignarPaciente(List *pacientes){
  int id;
  char descripcion[100];

  printf("Ingrese ID paciente: ");
  scanf("%d",&id);
  getchar();

  printf("Ingrese prioridad paciente con mayuscula la primera letra: ");
  scanf("%s",descripcion);

  ticketPersona *paciente = list_first(pacientes);

  while(paciente != NULL){
    if(paciente->ID == id){
      if(strcmp(descripcion,"alto") == 0) {
        paciente->prioridad = ALTO;
      } else if (strcmp(descripcion,"medio") == 0){
          paciente->prioridad = MEDIO;
      } else if (strcmp(descripcion,"bajo") == 0){
        paciente->prioridad = BAJO;
      } else {
        printf("No existe o no incluyo mayuscula en primera letra.");
      }
      return;
    }
    paciente = list_next(pacientes);
  }
  printf("No se encontro paciente con ese ID.\n");
}

void mostrar_lista_pacientes(List *pacientes) {
  // Mostrar pacientes en la cola de espera
  printf("Pacientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
  while(paciente != NULL){
    if(paciente->prioridad == ALTO){

    }
  }
}




// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

/*void registrar_paciente(List *pacientes) {
  printf("Registrar nuevo paciente\n");
  // Aquí implementarías la lógica para registrar un nuevo paciente
}*/



int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      // Lógica para asignar prioridad
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();


  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}
