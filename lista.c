#include <stdio.h>
#include <stdlib.h>

/* ==============================================================================
 * UNIDAD 6: ASIGNACIÓN DINÁMICA DE MEMORIA - TAD LISTA SIMPLEMENTE ENLAZADA
 * Cátedra: Programación I - Ingeniería en Informática
 * ==============================================================================
 * Una lista enlazada es una estructura de datos dinámica (TAD) donde cada nodo
 * contiene información (dato) y un puntero de enlace ('sig' o 'ps') hacia el 
 * siguiente nodo en memoria (Heap).
 * ============================================================================== */

// Definición de la estructura de un Nodo
typedef struct Nodo
{
    int dato;               // Campo de información / valor
    struct Nodo *sig;       // Puntero de enlace al siguiente nodo (ps)
} Nodo;

// Prototipos de funciones
int empty(Nodo *lista);
void insertarPrincipio(Nodo **lista, int dato);
void insertarFinal(Nodo **lista, int dato);
void insertarDespues(Nodo *lista, int buscado, int dato);
void insertarAntes(Nodo **lista, int buscado, int dato);
Nodo *buscar(Nodo *lista, int buscado);
void eliminarPrincipio(Nodo **lista);
void eliminarPorClave(Nodo **lista, int buscado);
void recorrer(Nodo *lista);
void vaciarLista(Nodo **lista);

int main()
{
    Nodo *lista = NULL; // Inicialización: lista vacía (cabeza = NULL)

    int opcion;
    int dato;
    int buscado;

    do
    {
        printf("\n================ MENU TAD LISTA ================\n");
        printf("1. Insertar al principio (en la cabeza)\n");
        printf("2. Insertar al final\n");
        printf("3. Insertar antes de un nodo\n");
        printf("4. Insertar despues de un nodo\n");
        printf("5. Buscar un nodo\n");
        printf("6. Eliminar primer nodo (cabeza)\n");
        printf("7. Eliminar nodo por clave (ejemplo de catedra)\n");
        printf("8. Recorrer lista\n");
        printf("9. Verificar si esta vacia\n");
        printf("0. Salir\n");
        printf("================================================\n");

        printf("Ingrese una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            break;
        }

        switch (opcion)
        {
            case 1:
                printf("Ingrese el dato a insertar al principio: ");
                scanf("%d", &dato);
                insertarPrincipio(&lista, dato);
                break;

            case 2:
                printf("Ingrese el dato a insertar al final: ");
                scanf("%d", &dato);
                insertarFinal(&lista, dato);
                break;

            case 3:
                printf("Ingrese el nodo ANTES del cual insertar: ");
                scanf("%d", &buscado);
                printf("Ingrese el nuevo dato: ");
                scanf("%d", &dato);
                insertarAntes(&lista, buscado, dato);
                break;

            case 4:
                printf("Ingrese el nodo DESPUES del cual insertar: ");
                scanf("%d", &buscado);
                printf("Ingrese el nuevo dato: ");
                scanf("%d", &dato);
                insertarDespues(lista, buscado, dato);
                break;

            case 5:
                printf("Ingrese el dato a buscar: ");
                scanf("%d", &buscado);
                if (buscar(lista, buscado) != NULL)
                {
                    printf("El dato %d se encuentra en la lista.\n", buscado);
                }
                else
                {
                    printf("El dato %d no se encuentra en la lista.\n", buscado);
                }
                break;

            case 6:
                eliminarPrincipio(&lista);
                break;

            case 7:
                printf("Ingrese el dato del nodo a eliminar: ");
                scanf("%d", &buscado);
                eliminarPorClave(&lista, buscado);
                break;

            case 8:
                recorrer(lista);
                break;

            case 9:
                if (empty(lista))
                {
                    printf("La lista ESTA vacia.\n");
                }
                else
                {
                    printf("La lista NO esta vacia.\n");
                }
                break;

            case 0:
                printf("Programa finalizado.\n");
                break;

            default:
                printf("Opcion incorrecta.\n");
        }

    } while (opcion != 0);

    // Liberar toda la memoria dinámica asignada antes de finalizar el programa
    vaciarLista(&lista);

    return 0;
}

/**
 * Comprueba si la lista está vacía.
 * Retorna 1 si está vacía (cabeza == NULL), 0 en caso contrario.
 */
int empty(Nodo *lista)
{
    return (lista == NULL);
}

/**
 * Inserta un nuevo elemento al principio (cabeza) de la lista.
 * Algoritmo de cátedra:
 * 1. Asignar memoria para el nuevo nodo con malloc.
 * 2. Guardar el dato.
 * 3. Hacer que nuevo->sig apunte a la cabeza actual.
 * 4. Actualizar la cabeza para que apunte al nuevo nodo.
 */
void insertarPrincipio(Nodo **lista, int dato)
{
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));

    if (nuevo != NULL)
    {
        nuevo->dato = dato;
        nuevo->sig = *lista; // Enlaza con el antiguo primer elemento
        *lista = nuevo;      // La cabeza ahora es el nuevo nodo
        printf("Elemento %d insertado al principio.\n", dato);
    }
    else
    {
        printf("Error: Insuficiente espacio de memoria.\n");
    }
}

/**
 * Inserta un nuevo elemento al final de la lista.
 * Algoritmo de cátedra:
 * 1. Asignar memoria para el nuevo nodo con malloc.
 * 2. Guardar el dato y poner nuevo->sig en NULL.
 * 3. Si la lista está vacía, la cabeza apunta al nuevo nodo.
 * 4. Si no, recorrer hasta el último nodo (aux->sig == NULL) y enlazar aux->sig = nuevo.
 */
void insertarFinal(Nodo **lista, int dato)
{
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));

    if (nuevo != NULL)
    {
        nuevo->dato = dato;
        nuevo->sig = NULL;

        if (empty(*lista))
        {
            *lista = nuevo; // Si está vacía, es el primer nodo
        }
        else
        {
            Nodo *aux = *lista;
            while (aux->sig != NULL) // Recorrido hasta el último nodo
            {
                aux = aux->sig;
            }
            aux->sig = nuevo; // Se desengancha el NULL y se engancha al nuevo
        }
        printf("Elemento %d insertado al final.\n", dato);
    }
    else
    {
        printf("Error: Insuficiente espacio de memoria.\n");
    }
}

/**
 * Inserta un nuevo elemento DESPUÉS de un nodo especificado por clave.
 * Algoritmo de cátedra:
 * 1. Recorrer la lista buscando el nodo con el valor buscado.
 * 2. Si se encuentra, reservar memoria para el nuevo nodo.
 * 3. nuevo->sig = aux->sig;
 * 4. aux->sig = nuevo;
 */
void insertarDespues(Nodo *lista, int buscado, int dato)
{
    Nodo *aux = lista;

    // Búsqueda del nodo de referencia
    while (aux != NULL && aux->dato != buscado)
    {
        aux = aux->sig;
    }

    if (aux != NULL)
    {
        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
        if (nuevo != NULL)
        {
            nuevo->dato = dato;
            nuevo->sig = aux->sig; // El nuevo nodo apunta al siguiente del actual
            aux->sig = nuevo;      // El nodo actual apunta al nuevo nodo
            printf("Elemento %d insertado despues de %d.\n", dato, buscado);
        }
        else
        {
            printf("Error: Insuficiente espacio de memoria.\n");
        }
    }
    else
    {
        printf("No se encontro el nodo con valor %d.\n", buscado);
    }
}

/**
 * Inserta un nuevo elemento ANTES de un nodo especificado por clave.
 * Algoritmo de cátedra:
 * 1. Mantener punteros: aux (para recorrer) y anterior (nodo previo).
 * 2. Si coincide con el primer nodo, se inserta al principio modificando la cabeza.
 * 3. Si es intermedio: nuevo->sig = aux; anterior->sig = nuevo;
 */
void insertarAntes(Nodo **lista, int buscado, int dato)
{
    if (empty(*lista))
    {
        printf("La lista esta vacia.\n");
        return;
    }

    // Caso particular: insertar antes del primer nodo (cabeza)
    if ((*lista)->dato == buscado)
    {
        insertarPrincipio(lista, dato);
        return;
    }

    Nodo *aux = *lista;
    Nodo *anterior = NULL;

    // Búsqueda manteniendo el puntero anterior
    while (aux != NULL && aux->dato != buscado)
    {
        anterior = aux;
        aux = aux->sig;
    }

    if (aux != NULL)
    {
        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
        if (nuevo != NULL)
        {
            nuevo->dato = dato;
            nuevo->sig = aux;       // El nuevo apunta al nodo encontrado
            anterior->sig = nuevo;  // El anterior apunta al nuevo
            printf("Elemento %d insertado antes de %d.\n", dato, buscado);
        }
        else
        {
            printf("Error: Insuficiente espacio de memoria.\n");
        }
    }
    else
    {
        printf("No se encontro el nodo con valor %d.\n", buscado);
    }
}

/**
 * Recorre y muestra los elementos de la lista enlazada de principio a fin.
 */
void recorrer(Nodo *lista)
{
    if (empty(lista))
    {
        printf("Lista vacia (NULL)\n");
        return;
    }

    printf("Lista: ");
    Nodo *aux = lista;
    while (aux != NULL)
    {
        printf("[%d] -> ", aux->dato);
        aux = aux->sig;
    }
    printf("NULL\n");
}

/**
 * Busca un elemento por valor y retorna el puntero al nodo si existe, o NULL si no.
 */
Nodo *buscar(Nodo *lista, int buscado)
{
    Nodo *aux = lista;
    while (aux != NULL)
    {
        if (aux->dato == buscado)
        {
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}

/**
 * Elimina el primer nodo (cabeza) de la lista y libera su memoria.
 */
void eliminarPrincipio(Nodo **lista)
{
    if (!empty(*lista))
    {
        Nodo *aux = *lista;
        *lista = (*lista)->sig; // La cabeza pasa a ser el segundo nodo
        free(aux);              // Se libera la memoria del primer nodo
        printf("Primer nodo eliminado correctamente.\n");
    }
    else
    {
        printf("Error: La lista esta vacia. No hay elementos para eliminar.\n");
    }
}

/**
 * Elimina un nodo por su clave/valor en cualquier posición de la lista.
 * Implementación basada directamente en el ejemplo de la cátedra (Diapositiva 66).
 * Pasos:
 * 1. Buscar con punteros 'actual' y 'anterior'.
 * 2. Si es el primer nodo (actual == *cabeza), *cabeza = actual->sig.
 * 3. Si es intermedio, anterior->sig = actual->sig.
 * 4. Liberar memoria con free(actual).
 */
void eliminarPorClave(Nodo **lista, int buscado)
{
    if (empty(*lista))
    {
        printf("Error: La lista esta vacia.\n");
        return;
    }

    Nodo *actual = *lista;
    Nodo *anterior = NULL;
    int encontrado = 0;

    // Búsqueda del nodo a eliminar
    while (actual != NULL && !encontrado)
    {
        encontrado = (actual->dato == buscado);
        if (!encontrado)
        {
            anterior = actual;
            actual = actual->sig;
        }
    }

    if (actual != NULL)
    {
        // Caso 1: El nodo a eliminar es la cabeza
        if (actual == *lista)
        {
            *lista = actual->sig;
        }
        // Caso 2: El nodo a eliminar está en una posición intermedia o final
        else
        {
            anterior->sig = actual->sig;
        }

        free(actual); // Liberar memoria del nodo eliminado
        printf("Elemento %d eliminado correctamente.\n", buscado);
    }
    else
    {
        printf("No se encontro el nodo con valor %d para eliminar.\n", buscado);
    }
}

/**
 * Libera toda la memoria dinámica asignada a la lista.
 */
void vaciarLista(Nodo **lista)
{
    Nodo *aux;
    while (*lista != NULL)
    {
        aux = *lista;
        *lista = (*lista)->sig;
        free(aux);
    }
}

