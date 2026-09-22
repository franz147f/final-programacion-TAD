#include <stdio.h>
#include <stdlib.h>

/* ==============================================================================
 * UNIDAD 6: ASIGNACIÓN DINÁMICA DE MEMORIA - TAD PILA (STACK)
 * Cátedra: Programación I - Ingeniería en Informática
 * ==============================================================================
 * Concepto:
 * - Una Pila es una colección homogénea y ordenada de elementos con acceso LIFO
 *   (Last-In, First-Out: "Último en entrar, primero en salir").
 * - Todas las inserciones (push / apilar) y extracciones (pop / desapilar) 
 *   se realizan por un único extremo denominado CIMA o TOPE.
 * - En implementación dinámica (con punteros y malloc), no hay límite de tamaño
 *   fijo (salvo la memoria física disponible en el Heap).
 * ============================================================================== */

// Definición de la estructura de un Nodo típico para construir Pilas
typedef struct nodo
{
    int valor;              // Información / dato almacenado
    struct nodo* siguiente; // Puntero al siguiente elemento (hacia la base)
} nodo;

// Prototipos de funciones del TAD Pila
int push(nodo **cima, int valor);
int pop(nodo **cima, int *valor_eliminado);
int isEmpty(nodo *cima);
void top_pila(nodo *cima);
void vaciar_pila(nodo **cima);

int main() {
    nodo *cima = NULL; // Pila inicialmente vacía (cima apunta a NULL)
    int opc = -1, val;
    int intentos = 0;

    while (opc != 0 && intentos < 25)
    {
        printf("\n=== TAD PILA (LIFO) ===\n");
        printf("1. Apilar (Push)\n");
        printf("2. Desapilar (Pop)\n");
        printf("3. Mostrar el tope (Top / Peek)\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        
        if (scanf("%d", &opc) != 1) {
            break;
        }

        if (opc == 1)
        {
            printf("Ingrese el valor a agregar a la pila: ");
            scanf("%d", &val);
            if (push(&cima, val)) {
                printf("Elemento %d apilado correctamente.\n", val);
            } else {
                printf("Error: No se pudo asignar memoria (Overflow / Memoria insuficiente).\n");
            }
        }
        else if (opc == 2)
        {
            int valor_desapilado;
            if (pop(&cima, &valor_desapilado))
            {
                printf("El elemento desapilado es: %d \n", valor_desapilado);
            }
            else
            {
                printf("Error: La pila esta vacia (Underflow / Desbordamiento negativo).\n");
            }
        }
        else if (opc == 3)
        {
            top_pila(cima);
        }
        
        intentos++;
    }

    // Liberar memoria restante en el Heap al salir
    vaciar_pila(&cima);
    printf("Memoria liberada. Fin del programa.\n");
    
    return 0;
}

/**
 * Operación Apilar (Push):
 * Algoritmo de la cátedra:
 * 1. Asignar memoria para el nuevo nodo con malloc().
 * 2. Guardar el dato en nuevo_nodo->valor.
 * 3. Enlazar nuevo_nodo->siguiente a la cima actual (*cima).
 * 4. Actualizar la cima (*cima) para que apunte al nuevo nodo.
 * Retorna 1 si fue exitoso, 0 si hubo error de memoria (Overflow).
 */
int push(nodo **cima, int valor) {
    nodo *nuevo_nodo = (nodo*)malloc(sizeof(nodo));
    if (nuevo_nodo != NULL) {
        nuevo_nodo->valor = valor;
        nuevo_nodo->siguiente = *cima; // nuevo apunta a la anterior cima
        *cima = nuevo_nodo;            // la cima ahora es el nuevo nodo
        return 1; // Éxito
    } else {
        return 0; // Error de asignación de memoria
    }
}

/**
 * Operación Desapilar (Pop):
 * Algoritmo de la cátedra:
 * 1. Verificar si la pila está vacía (evita Underflow).
 * 2. Usar un puntero auxiliar (aux) que apunte al nodo en la cima (*cima).
 * 3. Guardar el valor contenido para retornarlo.
 * 4. Avanzar la cima al siguiente nodo: *cima = aux->siguiente.
 * 5. Liberar la memoria del nodo eliminado con free(aux).
 * Retorna 1 si se desapiló correctamente, 0 si la pila estaba vacía.
 */
int pop(nodo **cima, int *valor_eliminado) {
    if (isEmpty(*cima)) {
        return 0; // Pila vacía (Underflow)
    }
    nodo *aux = *cima;
    *valor_eliminado = aux->valor; // Se recupera el dato
    *cima = aux->siguiente;        // La cima baja al nodo anterior
    free(aux);                     // Se libera la memoria en el Heap
    return 1; // Éxito
}

/**
 * Operación Comprobar si la pila está vacía (isEmpty):
 * Retorna 1 si cima es NULL, 0 en caso contrario.
 */
int isEmpty(nodo *cima) {
    return (cima == NULL);
}

/**
 * Operación Consultar Tope (Top / Peek):
 * Permite visualizar el dato en la cima sin modificar la estructura ni eliminarlo.
 */
void top_pila(nodo *cima) {
    if (isEmpty(cima)) {
        printf("Error: La pila esta vacia. No hay elementos para mostrar.\n");
    } else {
        printf("El valor del tope es: %d\n", cima->valor);
    }
}

/**
 * Libera toda la memoria dinámica de los nodos restantes en la pila.
 */
void vaciar_pila(nodo **cima) {
    int dummy;
    while (pop(cima, &dummy));
}