#include <stdio.h>
#include <stdlib.h>

/* ==============================================================================
 * UNIDAD 6: ASIGNACIÓN DINÁMICA DE MEMORIA - TAD COLA (QUEUE)
 * Cátedra: Programación I - Ingeniería en Informática
 * ==============================================================================
 * Concepto:
 * - Una Cola es una estructura de datos homogénea y ordenada de acceso FIFO
 *   (First-In, First-Out: "Primero en entrar, primero en salir").
 * - Las inserciones (encolar / queue) se realizan por el extremo FINAL.
 * - Las extracciones (desencolar / dequeue) se realizan por el extremo FRENTE / PRIMERO.
 * - Se manejan habitualmente dos punteros: 'primero' (frente) y 'ultimo' (final).
 * ============================================================================== */

// Definición de la estructura de un Nodo típico para construir Colas
typedef struct nodo
{
    int valor;              // Información / dato almacenado
    struct nodo* siguiente; // Puntero al siguiente elemento en la fila
} nodo;

// Prototipos de funciones del TAD Cola
int encolar(nodo **pp_primero, nodo **pp_ultimo, int valor);
int desencolar(nodo **pp_primero, nodo **pp_ultimo, int *valor_eliminado);
int isEmpty(nodo *primero);
void mostrar_elementos(nodo *primero);
void vaciar_cola(nodo **pp_primero, nodo **pp_ultimo);

int main() {
    nodo *primero = NULL; // Puntero al frente de la cola (inicialmente NULL)
    nodo *ultimo = NULL;  // Puntero al final de la cola (inicialmente NULL)
    int opc = -1, val;
    int intentos = 0;

    printf("=== SIMULADOR DE UNA COLA (FIFO) ===\n");

    while (opc != 0 && intentos < 25)
    {
        printf("\n=== TAD COLA (FIFO) ===\n");
        printf("1. Encolar (Insertar al final)\n");
        printf("2. Desencolar (Eliminar del frente)\n");
        printf("3. Consultar si esta vacia\n");
        printf("4. Mostrar elementos (Recorrido)\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        
        if (scanf("%d", &opc) != 1) {
            break;
        }

        if (opc == 1)
        {
            printf("Ingrese el valor a encolar: ");
            scanf("%d", &val);
            if (encolar(&primero, &ultimo, val)) {
                printf("Elemento %d encolado correctamente.\n", val);
            } else {
                printf("Error: No se pudo asignar memoria (Overflow / Insuficiente espacio).\n");
            }
        }
        else if (opc == 2)
        {
            int valor_desencolado;
            if (desencolar(&primero, &ultimo, &valor_desencolado)) {
                printf("El elemento desencolado es: %d\n", valor_desencolado);
            } else {
                printf("Error: La cola esta vacia (Underflow). No hay elementos para desencolar.\n");
            }
        }
        else if (opc == 3)
        {
            if (isEmpty(primero)) {
                printf("La cola ESTA vacia.\n");
            } else {
                printf("La cola NO esta vacia.\n");
            }
        }
        else if (opc == 4)
        {
            mostrar_elementos(primero);
        }

        intentos++;
    }

    // Liberar toda la memoria restante en el Heap al salir
    vaciar_cola(&primero, &ultimo);
    printf("\nMemoria liberada. Fin del programa.\n");

    return 0;
}

/**
 * Operación Encolar (Insertar un elemento en la cola):
 * Algoritmo de la cátedra:
 * 1. Asignar memoria para el nuevo nodo con malloc().
 * 2. Asignar nuevo->valor = valor y nuevo->siguiente = NULL.
 * 3. Caso Cola Vacía (*pp_primero == NULL):
 *      Hacer que *pp_primero = nuevo y *pp_ultimo = nuevo.
 * 4. Caso Cola No Vacía:
 *      Hacer que (*pp_ultimo)->siguiente = nuevo y actualizar *pp_ultimo = nuevo.
 * Retorna 1 si fue exitoso, 0 si falló la asignación de memoria.
 */
int encolar(nodo **pp_primero, nodo **pp_ultimo, int valor) {
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    if (nuevo != NULL)
    {
        nuevo->valor = valor;
        nuevo->siguiente = NULL;

        if (*pp_primero == NULL) {
            /* Caso 1: Cola vacía -> el nuevo nodo es el primero y el último */
            *pp_primero = nuevo;
            *pp_ultimo = nuevo;
        }
        else {
            /* Caso 2: Cola con elementos -> se enlaza al final y se mueve 'ultimo' */
            (*pp_ultimo)->siguiente = nuevo;
            *pp_ultimo = nuevo;
        }
        return 1; // Éxito
    }
    else
    {
        return 0; // Error de memoria
    }
}

/**
 * Operación Desencolar (Eliminar un elemento del frente de la cola):
 * Algoritmo de la cátedra:
 * 1. Verificar si la cola está vacía (evita Underflow).
 * 2. Usar un puntero auxiliar (aux) apuntando al primer nodo (*pp_primero).
 * 3. Guardar el valor a retornar (*valor_eliminado = aux->valor).
 * 4. Avanzar el puntero primero al siguiente nodo (*pp_primero = aux->siguiente).
 * 5. Si la cola quedó vacía (*pp_primero == NULL), poner también *pp_ultimo = NULL.
 * 6. Liberar la memoria con free(aux).
 * Retorna 1 si se desencoló con éxito, 0 si la cola estaba vacía.
 */
int desencolar(nodo **pp_primero, nodo **pp_ultimo, int *valor_eliminado) {
    if (isEmpty(*pp_primero)) {
        return 0; // Cola vacía
    }

    nodo *aux = *pp_primero;
    *valor_eliminado = aux->valor;
    *pp_primero = aux->siguiente;

    // Caso particular cátedra: Si al desencolar el único elemento la cola queda vacía,
    // el puntero 'ultimo' también debe actualizarse a NULL.
    if (*pp_primero == NULL) {
        *pp_ultimo = NULL;
    }

    free(aux);
    return 1; // Éxito
}

/**
 * Operación Comprobar si la cola está vacía:
 * Retorna 1 si el puntero 'primero' es NULL, 0 en caso contrario.
 */
int isEmpty(nodo *primero) {
    return (primero == NULL);
}

/**
 * Recorrido y visualización de la cola desde el Frente (primero) hasta el Final (último).
 */
void mostrar_elementos(nodo *primero) {
    if (isEmpty(primero)) {
        printf("La cola esta vacia.\n");
        return;
    }

    printf("Elementos en la cola (Frente/Primero -> Final/Ultimo): ");
    nodo *actual = primero;
    while (actual != NULL) {
        printf("[%d]", actual->valor);
        if (actual->siguiente != NULL) {
            printf(" -> ");
        }
        actual = actual->siguiente;
    }
    printf("\n");
}

/**
 * Libera toda la memoria dinámica de los nodos restantes en la cola.
 */
void vaciar_cola(nodo **pp_primero, nodo **pp_ultimo) {
    int dummy;
    while (desencolar(pp_primero, pp_ultimo, &dummy));
}