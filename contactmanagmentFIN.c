#include <stdio.h> //standar input output (libreria para entrada y salida) (printf, scanf)
#include <string.h> //string (strcpy, strcmp) 

//STRUCT DEF
typedef struct { //crea estructura
    char nombre[50]; //cadena de caracteres
    char telefono[15];
    char email[50];
} Contacto; //nombre de la estructura

//VARIABLE GLOBALES
Contacto contactos[100]; //almacena 100 contactos
int total_contactos = 0; //entero con valor inicial 0

//DECLARO
void agregarContacto(); //void no retorna valor pero 
void listarContactos();
void modificarContacto();
void eliminarContacto();
void ordenarContactos();
void guardarContactos();
void cargarContactos()

//EST
void limpiarPantalla() {
    printf("\033[2J\033[1;1H"); //limpia pantalla (solo ANSI)
}

void imprimirLinea(char c, int longitud) {
    for (int i = 0; i < longitud; i++) { //dibuja linea de caracteres c por longitud 
        putchar(c); //imprime un caracter
    }
    putchar('\n'); 
}

void imprimirTitulo(const char* titulo) { //const char* es una cadena de caracteres
    imprimirLinea('=', 50);
    printf(" %s\n", titulo);
    imprimirLinea('=', 50);
}

// MAIN FUNC
int main() {
    cargarContactos();
    int opcion;

    do {
        limpiarPantalla();
        imprimirTitulo("Gestor de Contactos");
        printf("1. Agregar contacto\n");
        printf("2. Listar contactos\n");
        printf("3. Modificar contacto\n");
        printf("4. Eliminar contacto\n");
        printf("5. Ordenar contactos\n");
        printf("0. Salir\n");
        imprimirLinea('-', 50);
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        getchar();  //limpia salto de linea 
        
        limpiarPantalla();
        switch(opcion) { //switch sirve para comparar valores y ejecutar un bloque de codigo dependiendo de la opcion seleccionada 
            case 1: imprimirTitulo("Agregar Contacto"); agregarContacto(); break;
            case 2: imprimirTitulo("Lista de Contactos"); listarContactos(); break;
            case 3: imprimirTitulo("Modificar Contacto"); modificarContacto(); break;
            case 4: imprimirTitulo("Eliminar Contacto"); eliminarContacto(); break;
            case 5: imprimirTitulo("Ordenar Contactos"); ordenarContactos(); break;
            case 0: guardarContactos(); printf("Guardando y saliendo...\n"); break;
            default: printf("Opción no valida.\n");
        }
        printf("\nPresiona Enter para continuar...");
        getchar();  //pausa antes de volver al main

    } while(opcion != 0); //while opcion diferente de 0, entonces retorna al main

    return 0;
}

//CRUD (create, read, update, delete)
void agregarContacto() { 
    if (total_contactos >= 100) {
        printf("No se pueden agregar más contactos.\n");
        return;
    } //si total_contactos es mayor o igual a 100, no se puede agregar mas contactos

    printf("\nNombre y Apellido: ");
    fgets(contactos[total_contactos].nombre, 50, stdin); //fgets lee linea de texto y almacena en el arreglo de caracteres
    printf("Telefono: ");//printf imprime en pantalla
    fgets(contactos[total_contactos].telefono, 15, stdin); //fgets lee linea de texto y lo guarda en .telefono
    printf("Email: ");
    fgets(contactos[total_contactos].email, 50, stdin); //fgets asegura que no se lean mas caracteres de los que el tamaño del array permite

    contactos[total_contactos].nombre[strcspn(contactos[total_contactos].nombre, "\n")] = 0; //strcspn es un string que devuelve la longitud de la cadena de caracteres
    contactos[total_contactos].telefono[strcspn(contactos[total_contactos].telefono, "\n")] = 0;
    contactos[total_contactos].email[strcspn(contactos[total_contactos].email, "\n")] = 0;

    total_contactos++; //incrementa el total de contactos
    printf("Contacto agregado con exito\n");
}

void listarContactos() {
    if (total_contactos == 0) {
        printf("No hay contactos para mostrar\n");
        return;
    }
    for (int i = 0; i < total_contactos; i++) { //recorre el arreglo de contactos    
        printf("%d. %s - %s - %s\n", i + 1, contactos[i].nombre, contactos[i].telefono, contactos[i].email); //printf %d (decimal) %s (string) - (menos para separar), i + 1 (incrementa indice)
    } //imprime los contactos con nombre, telefono y email
}//[i] indice de contactos

void modificarContacto() { //identifica el contacto a modificar en base al id
    listarContactos();
    printf("Selecciona el numero del contacto a modificar: ");
    int indice; //declaro variable entera 
    scanf("%d", &indice); //
    getchar();

    if (indice > 0 && indice <= total_contactos) { //si indice es mayor o igual a 1 y menor o igual a total_contactos
        printf("Nuevo nombre (pulse enter para no modificar): ");
        char nuevoNombre[50];
        fgets(nuevoNombre, 50, stdin);
        if (strcmp(nuevoNombre, "\n") != 0) { //strcmp compara dos cadenas de caracteres
            strcpy(contactos[indice - 1].nombre, nuevoNombre); //strcpy copia una cadena y la guarda en la otra
            contactos[indice - 1].nombre[strcspn(contactos[indice - 1].nombre, "\n")] = 0; //strcspn devuelve la longitud de la cadena
        }

        printf("Nuevo teléfono (pulse enter para no modificar): ");
        char nuevoTelefono[15];
        fgets(nuevoTelefono, 15, stdin);
        if (strcmp(nuevoTelefono, "\n") != 0) {
            strcpy(contactos[indice - 1].telefono, nuevoTelefono);
            contactos[indice - 1].telefono[strcspn(contactos[indice - 1].telefono, "\n")] = 0; 
        }

        printf("Nuevo email (pulse enter para no modificar): ");
        char nuevoEmail[50];
        fgets(nuevoEmail, 50, stdin);
        if (strcmp(nuevoEmail, "\n") != 0) {
            strcpy(contactos[indice - 1].email, nuevoEmail);
            contactos[indice - 1].email[strcspn(contactos[indice - 1].email, "\n")] = 0;
        }

        printf("Contacto modificado con exito\n");
    } else {
        printf("Indice no valido.\n");
    }
}

void eliminarContacto() {
    listarContactos();
    printf("Selecciona el numero del contacto a eliminar: ");
    int indice;
    scanf("%d", &indice);
    getchar();

    if (indice > 0 && indice <= total_contactos) { //si el indice es mayor o igual a 1 y menor o igual a total_contactos
        for (int i = indice - 1; i < total_contactos - 1; i++) { //entonces recorre el arreglo de contactos
            contactos[i] = contactos[i + 1]; //copia el contacto actual al anterior
        }
        total_contactos--; //decrementa el total de contactos
        printf("Contacto eliminado con éxito.\n");
    } else { //si no es asi entonces printf indice no valido
        printf("Índice no válido.\n");
    }
}

//BURBLE SORT
void ordenarContactos() {
    if (total_contactos < 2) { //si total_contactos es menor a 2
        printf("No hay suficientes contactos para ordenar.\n");//entonces printf no hay suficientes contactos para ordenar
        return; //vuelve a main
    }

    for (int i = 0; i < total_contactos - 1; i++) { //for recorre el arreglo de contactos si i es menor a total_contactos - 1 ; i se incrementa
        for (int j = 0; j < total_contactos - i - 1; j++) { //for recorre el arreglo de contactos si j es menor a total_contactos - i - 1 ; j se incrementa
            if (strcmp(contactos[j].nombre, contactos[j + 1].nombre) > 0) { //si contactos[j].nombre es mayor que contactos[j + 1].nombre
                Contacto temp = contactos[j]; //contacto se almacena en temp
                contactos[j] = contactos[j + 1]; //contactos[j] se iguala a contactos[j + 1]
                contactos[j + 1] = temp; //contactos[j + 1] se iguala a temp porque se almaceno en temp
            }
        }
    }
    printf("Contactos ordenados por nombre\n"); 
}

void guardarContactos() {//llamada sin retorno de valor a guardarContactos
    FILE *archivo = fopen("contactos.dat", "wb");//FILE (puntero a archivo) = fopen abre un archivo binario a ("contactos.dat", "wb") wb es para escritura binaria
    if (archivo == NULL) { //si el archivo es nulo
        printf("Error al guardar los contactos\n"); //entonces printf error al guardar los contactos
        return; //retorna a main
    }
    fwrite(contactos, sizeof(Contacto), total_contactos, archivo); //fwrite escribe en un archivo binario (en contacos, sizeof sirve para tamaño de contactos, de total_contactos, archivo)
    fclose(archivo); //cierra el archivo binario
}

void cargarContactos() {
    FILE *archivo = fopen("contactos.dat", "rb"); //FILE * (puntero a archivo) = abrir un archivo binario a ("contactos.dat", "rb") rb es para lectura binaria
    if (archivo == NULL) {//si el archivo es nulo (nulo es cuando no existe el archivo)
        printf("No hay contactos guardados.\n");//
        return; //retorna a main
    }
    total_contactos = fread(contactos, sizeof(Contacto), 100, archivo); //si total_contactos es igual a fread (osea leer de un archivo binario) (struct de contactos, sizeof(contacto), 100, archivo)
    fclose(archivo); //cerrar el archivo binario

}
