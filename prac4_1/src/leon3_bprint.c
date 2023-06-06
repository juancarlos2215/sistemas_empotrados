#include "leon3_uart.h"
#include "leon3_uart.h"
#include "leon3_bprint.h"
#include <stdio.h>

int8_t leon3_print_string(char* str)
{
	int i = 0;
	while(str[i] != '\0'){			//Hasta llegar al final de cadena
		leon3_putchar(str[i]);		//Lo mandamos a ejecutar
		i++;
	}
	return 0;
}


/**Sacamos cada uno de los numeros del integer y los almacenamos en un array.
 * Se almacenan de forma inversa, por eso luego hacemos un bucle para ordenarlos en un array auxiliar
*/
int8_t leon3_print_uint8(uint8_t i)
{
    int contador = 0, x = 0, j = 0;
    int numeros[10], aux[10];
    char c;

    while(i>0){
        numeros[contador] = i%10; 	//Almacenamos el ultimo digito del numero, en un array
        i = i/10;					//Borramos el ultimo digito del numero
        contador++;
    }

    x = contador-1;					//Variable que usamos para contar posiciones, restamos 1
    								//ya que el array empieza en 0


    /**En este bucle rellenamos las primeras posiciones del vector auxiliar, con las ultimas
     * posiciones del otro vector (que tiene el numero al reves). De esta forma ordenamos los
     * numeros, en el array auxiliar, por cada iteracion.
     */
    for (j = 0; j < contador; j++)
    {
        aux[j] = numeros [x];	//A medida que aumentan las posiciones de aux, decrecen las de
        x--;					//numeros
        c = aux[j] +'0';		//Pasamos el numero a char
        leon3_putchar(c);		//Lo mandamos a ejecutar
    }

    return 0;
}

/**Sacamos cada uno de los numeros del integer y los almacenamos en un array.
 * Se almacenan de forma inversa, por eso luego hacemos un bucle para ordenarlos en un array auxiliar
*/
int8_t leon3_print_uint32(uint32_t i)
{
    int contador = 0, x = 0, j = 0;
    int numeros[10], aux[10];
    char c;

    while(i>0){
        numeros[contador] = i%10; 	//Almacenamos el ultimo digito del numero, en un array
        i = i/10;					//Borramos el ultimo digito del numero
        contador++;
    }

    x = contador-1;					//Variable que usamos para contar posiciones, restamos 1
    								//ya que el array empieza en 0


    /**En este bucle rellenamos las primeras posiciones del vector auxiliar, con las ultimas
     * posiciones del otro vector (que tiene el numero al reves). De esta forma ordenamos los
     * numeros, en el array auxiliar, por cada iteracion.
     */
    for (j = 0; j < contador; j++)
    {
        aux[j] = numeros [x];	//A medida que aumentan las posiciones de aux, decrecen las de
        x--;					//numeros
        c = aux[j] +'0';		//Pasamos el numero a char
        leon3_putchar(c);		//Lo mandamos a ejecutar
    }

    return 0;
}





