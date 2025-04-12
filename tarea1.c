#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define BAJO 0
#define MEDIO 1
#define ALTO 2

typedef struct {
  int ID;
  char descriProblema[100];
  int prioridad;
  time_t hora;
} ticketPersona;

ticketPersona* crearTicket(int id, const char *descripcion){
  ticketPersona *newTicket = (ticketPersona*)malloc(sizeof(ticketPersona));

  if(newTicket == NULL){
    return NULL;
  }

  newTicket->ID = id;
  strcpy(newTicket->descriProblema,descripcion);
  newTicket->prioridad = BAJO;
  newTicket->hora = time(NULL);

  return newTicket;
}
void registrar_paciente(List *pacientes) {
  int id;
  char descripcion[100];

  printf("Ingrese ID paciente: ");
  scanf("%d",&id);
  getchar();
  ticketPersona *paciente = list_first(pacientes);
  while(paciente != NULL){
    if(paciente->ID == id){
      printf("AVISO: Ya existe ID\n");
      return;
    }
    paciente = list_next(pacientes);
  }

  printf("Ingrese descripcion problema del paciente: ");
  scanf("%99[^\n]",descripcion);

  printf("Registrar nuevo paciente\n");

  ticketPersona *newTicket = crearTicket(id,descripcion);
  if(newTicket != NULL){
    list_pushBack(pacientes,newTicket);
  }
  // Aquí implementarías la lógica para registrar un nuevo paciente
}

void hacerMini(char *texto){
  for(int i = 0; texto[i]; i++){
    texto[i] = tolower(texto[i]);
  }
}

void asignarPaciente(List *pacientes){
  int id;
  char descripcion[100];

  printf("Ingrese ID paciente: ");
  scanf("%d",&id);
  getchar();

  printf("Ingrese prioridad paciente: ");
  scanf("%s",descripcion);
  hacerMini(descripcion);

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
        printf("No existe esa prioridad, intente de nuevo.");
      }
      return;
    }
    paciente = list_next(pacientes);
  }
  printf("AVISO: No se encontro paciente con ese ID.\n");
}

void mostrar_lista_pacientes(List *pacientes) {
  printf("Pacientes en espera ordenados por prioridad: \n");
  ticketPersona *paciente = list_first(pacientes);

  while(paciente != NULL){
    if(paciente->prioridad == ALTO){
      printf("ID: %d\n", paciente->ID);
      printf("Descripcion: %s\n",paciente->descriProblema);
    }
    paciente = list_next(pacientes);
  }

  paciente = list_first(pacientes);
  while(paciente != NULL){
    if(paciente->prioridad == MEDIO){
      printf("ID: %d\n", paciente->ID);
      printf("Descripcion: %s\n",paciente->descriProblema);
    }
    paciente = list_next(pacientes);
  }

  paciente = list_first(pacientes);
  while(paciente != NULL){
    if(paciente->prioridad == BAJO){
      printf("ID: %d\n", paciente->ID);
      printf("Descripcion: %s\n",paciente->descriProblema);
    }
    paciente = list_next(pacientes);
  }
}

void ProcesarSiguienteTicket(List *pacientes){
  ticketPersona *currentTicket = NULL;
  ticketPersona *paciente = list_first(pacientes);
  time_t horita = time(NULL);

  while(paciente != NULL){
    if(currentTicket == NULL ||
      (paciente->prioridad > currentTicket->prioridad) ||
      (paciente->prioridad == currentTicket->prioridad && paciente->hora < currentTicket->hora)){
      currentTicket = paciente;
    }
    paciente = list_next(pacientes);
  }

  if(currentTicket != NULL){
    printf("ID: %d\n",currentTicket->ID);
    printf("Descripcion: %s\n",currentTicket->descriProblema);
    printf("Prioridad: %d\n",currentTicket->prioridad);
    printf("Hora registrada: %s\n",ctime(&currentTicket->hora));
    paciente = list_first(pacientes);
    while(paciente != NULL){
      if(paciente == currentTicket){
        list_pushBack(pacientesAtendidos,currentTicket);
        list_popCurrent(pacientes);
        break;
      }
      paciente = list_next(pacientes);
    }
  }else {
    printf("AVISO: No hay tickets para procesar.\n");
  }

}

void BuscarticketporID(List *pacientes,List *pacientesAtendidos){
  int id;
  printf("Ingrese ID paciente: ");
  scanf("%d",&id);
  getchar();

  ticketPersona *paciente = list_first(pacientes);
  while(paciente != NULL){
    if(paciente->ID == id){
      printf("ID: %d\n",paciente->ID);
      printf("Descripcion: %s\n",paciente->descriProblema);
      printf("Prioridad: ");
      switch (paciente->prioridad){
        case ALTO:
          printf("Alto\n");
          break;
        case MEDIO:
          printf("Medio\n");
          break;
        case BAJO:
          printf("Bajo\n");
          break;
      }
      printf("Hora registrada: %s\n",ctime(&(paciente->hora)));
      return;
    }
    paciente = list_next(pacientes);
  }
  
  ticketPersona *paciente = list_first(pacientesAtendidos);
  while(paciente != NULL){
    if(paciente->ID == id){
      printf("ID: %d\n",paciente->ID);
      printf("Descripcion: %s\n",paciente->descriProblema);
      printf("Prioridad: ");
      switch (paciente->prioridad){
        case ALTO:
          printf("Alto\n");
          break;
        case MEDIO:
          printf("Medio\n");
          break;
        case BAJO:
          printf("Bajo\n");
          break;
      }
      printf("Hora registrada: %s\n",ctime(&(paciente->hora)));
      return;
    }
    paciente = list_next(pacientesAtendidos);
  }

  printf("AVISO: No se encontro ese ID.\n");
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
  List *pacientesAtendidos = list_create();

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
      asignarPaciente(pacientes);
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      ProcesarSiguienteTicket(pacientes);
      break;
    case '5':
      BuscarticketporID(pacientes,pacientesAtendidos);
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
