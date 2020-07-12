#include <iostream>
#include <string>
#include <string.h> 
#include <windows.h>  
#include <stdlib.h>

const int longCad = 20; //Se le asigna una constante para la cadena que seran los nombres de los productos//

using namespace std;

void gotoxy(int x,int y){  
/*Se utiliza la funcion gotoxy, para dar mas elegancia a la presentacion del programa, centrando todo el contenido como 
comunmente estan alineados los recibos de los supermercados, restaurantes y otros lugares*/
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
} 
struct costoporarticulo{ /*se utiliza una estructura, la cual contiene en su interior variables de diferentes tipos para lograr presentar correctamente el recibo,
esto es algo que los arreglos por si solos no nos permiten*/
char nombrearti[longCad + 1];
int cantidad;
float precio;
float costoPorArticulo;
};

void leerdatos (costoporarticulo p[], int n, string cad){ /*esta funcion se encarga de pedir al usuario cada uno de los datos deseados, ademas de asignarlos en un arreglo 
que maneja toda la estructura, colocando los datos de la estructura en cada una de las posiciones del arreglo de acuerdo al numero de productos ingresados por el usuario*/
    int i;
    cout << "Ingrese el nombre del producto, la cantidad y su precio por unidad" << "\n";
    for (i=0; i<n; i++){
        cout << "Nombre del producto: " << "\n";
        getline (cin, cad, '\n'); //se utiliza getline por si existiera la utilizacion de la barra espaciadora para el nombre del producto//
        strncpy(p[i].nombrearti, cad.c_str(), longCad); //se utiliza la funcion strncpy para copiar lo que se acaba de llenar en la variable string cad hacia la variable de la estructura//
        p[i].nombrearti[longCad]='\0';
        cout << "Unidades que lleva de este producto: " << "\n";
        cin >> p[i].cantidad;
        cout << "Precio por unidad: $";
        cin >> p[i].precio;
        cin.ignore(100, '\n');
    }
}
void calcularcosto (costoporarticulo p[],int n){ /*esta funcion calcula el costo de cada articulo, multiplicando su precio 
por la cantidad de productos del mismo que el usuario ha comprado, y se le asigna el valor en la variable previamente declarada en la estructura */
    int i;
    for (i=0; i<n; i++){
        p[i].costoPorArticulo = p[i].cantidad * p[i].precio;
    }
}
void imprimirenpantalla (costoporarticulo p[],int n){ /*esta funcion recorre todo el arreglo que contiene a la estructura, permitiendo mostrar en pantalla los datos ingresados por el usuario, 
notese que es aqui donde se utiliza la funcion gotoxy, asignando las coordenadas, que pueden variar dependiendo de la magnitud del monitor donde sea visualizado, 
y se le asigna el +i en Y para que se vaya posicionando correctamente en cada recorrido*/
    int i;
        gotoxy(80,1);
        cout <<"||Nombre del Producto||";
        cout << "||Unidades||";
        cout << "||Precio por unidad||" ;
        cout << "||Costo total del producto||" << "\n";

    for (i=0; i<n; i++){
         gotoxy(80,2+i);
        cout <<p[i].nombrearti;
        gotoxy(108,2+i);
        cout << p[i].cantidad;
        gotoxy(120,2+i);
        cout << "  $"<< p[i].precio;
        gotoxy(145,2+i);
        cout << "  $" << p[i].costoPorArticulo;
    }
}
int calculartotal (costoporarticulo p[],int n, float *total){ 
/*Esta funcion calcula el precio total de todos los articulos que ha comprado el usuario, la variable total es declarada 
como un puntero para que luego se pueda pasar al main el valor modificado*/
    
    int i;
    for (i=0; i<n; i++){
        *total = *total + p[i].costoPorArticulo;
    }
  
    return *total;
}

int main (){
    string cadena; //se declara una variable cadena que corresponde a la funcion leerdatos para que en esta se ingresen los nombres de los productos*/
    int n;
    cout << "Ingrese la cantidad de productos comprados" << "\n"; //en esta pregunta, se supone que el usuario ingresara la cantidad de tipos de productos, sin contar si llevan 2 o mas del mismo tipo//
    cin >> n;
    cin.ignore(100, '\n'); //se utiliza esta funcion para eliminar toda la "basura" del buffer y continuar con la ejecucion correcta del programa ya que se manejaran varios tipos de datos//
    costoporarticulo productos[n]; /*se declara una variable de tipo costoporarticulo que corresponde a la estructura, en este caso un arreglo 
    que contendra en cada posicion N que es el numero de productos que ingresara el usuario, los datos de cada variable declarada en la estructura*/
    leerdatos (productos, n,cadena); //a continuacion se comienzan a llamar las funciones mandando las variables contenidas en la main para que se usen en dichas funciones//
    calcularcosto (productos,n);
    system("CLS"); //esta funcion permite limpiar la pantalla y asi mostrar solamente la factura luego de haber ingresado los datos//
    cout << "************************************************************************************RECIBO SUPER SELECTOS UCA***********************************************************************************************************************" << "\n"<< endl;
    imprimirenpantalla (productos,n);
    float t=0;
    calculartotal (productos,n,&t); //la variable t que corresponde al total se pasa por referencia para que pueda ser modificada en la funcion//
    gotoxy(80,n+3); //Se utiliza N en y ya que no se conoce cuantos productos querra el usuario, y se le suman 3 unidades para que quede mas ordenado y mas legible para el usuario el precio final//
    cout << "El precio total de sus compras es: $" << t << "\n";
    return 0;
}