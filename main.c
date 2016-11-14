/*Compilar en sistemas tipo UNIX(linux, bsd)
 * Usar comando de compilacion gcc -Wall -std=c99
 * Usar codificacion UTF-8                      */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "biblio.h"//biblioteca de funciones en carpeta del codigo fuente del programa
//aqui empieza la macros del preprocesador
#define FILA 6
#define NUMASIENTO 20
#define SALA 6
#define MAXAFORO 120
#define NUM boletos[cont].numeroAsiento //macros para simplificar el indice
#define NFILA boletos[cont].Fila //macros para simplificar el indice
#define NSALA boletos[cont].sala //macros para simplificar el indice
//estructura del boleto
struct boleto{
	char asiento[SALA][FILA][NUMASIENTO][5];
	int Fila;
	int numeroAsiento;
	int sala;
	char pelicula[40];
	float precio;
}boletos[MAXAFORO];
//estructura del ticket
struct ticket{
	int IdVenta;
	struct boleto boletos[10];
	char combo[5][40];
	float precioCombo[5], precioTotal;
}tickette;
//punteros a archivos de texto
static FILE *cartelera; 
static FILE *combos;
static FILE *ticketto;
static FILE *preciosAsientos;
static FILE *asientos;
int main(int argc, char **argv)//incio de funcion principal o main
{
	tickette.precioTotal=0;//inicializa el precio total del ticket en 0
	char FilaCar[4]/*variable con la direccion de memoria valida para el apuntador *cFila*/, nAsiento[2], AsientoTemp[5],*aptcombo, combo;
	char *cFila;//apuntador para argumento a funcion
	char rec;//variable que recibe el valor de fin para los menus recursivos
	char afirm;//variable que recibe el valor de afirmacion para imprimir el ticket
	int menu, numBoletos, cont, sala, nCombos=0, Asiento[6][6][20], AsientosComprados=0, tempo;
	InicializarAsientos(Asiento);
	do{
		system("clear");//limpia la pantalla de la consola de linux
		printf("\n******************************************************");
		printf("\n* Bienvenido al sistema de venta de boletos cineplux *");
		printf("\n*                                                    *");
		printf("\n* selecciona una opcion                              *");
		printf("\n*                                                    *");
		printf("\n* 1.-ver cartelera                                   *");
		printf("\n* 2.-ver precios de asientos                         *");
		printf("\n* 3.-ver menu de combos                              *");
		printf("\n* 4.-comprar                                         *");
		printf("\n* 5.-Ver compra e imprimir ticket                    *");
		printf("\n* 6.-salir                                           *");
		printf("\n******************************************************\n");
		scanf("%d",&menu);
		switch(menu)
		{
			case 1:
			system("clear");
			Consultar(&cartelera,"Cartelera.txt");//muestra en pantalla el contenido de la cartelera directo del fichero
			break;
			case 2:
			system("clear");
			Consultar(&preciosAsientos,"PreciosAsientos.txt");
			break;
			case 3:
			system("clear");
			Consultar(&combos,"Combo.txt");
			
			break;
			case 4:
			do{
				system("clear");
				printf("\n******************************************************");
				printf("\n* 1.Comprar boletos                                  *");
				printf("\n* 2.Comprar combos                                   *");
				printf("\n* 3.regresar al menu anterior                        *");
				printf("\n******************************************************");
				scanf("%d",&menu);
				switch(menu)//menu principal
				{
					case 1://1.comprar boletos
					system("clear");//limpiar pantalla
					printf("\n¿Cuantos boletos desea comprar?");
					scanf("%d",&numBoletos);//recibe el numero de boletos para ingresar datos hasta (maximo 10)
					
					if(numBoletos>=1&&numBoletos<=MAXAFORO)//condicional que asegura el rango de boletos a comprar entre 1 y 10
					{
						printf("\nEscoja la pelicula de la cartelera\n");
						Consultar(&cartelera,"Cartelera.txt");//imprime en pantalla el contenido de la cartelera
						scanf("%d",&sala);//recibe el numero de la sala en la que se proyecta la pelicula
						if(sala>=1 && sala<=5)//condicional que asegura la seleccion valida de la cartelera entre 1 y 5
						{
							tempo=AsientosComprados;
							system("clear");
							for(cont=AsientosComprados;cont<numBoletos+tempo;cont++){//bucle que recibira los datos de los boletos
								boletos[cont].sala=sala;//guarda el numero de sala en la estructura 
								switch(sala)//este switch dependiendo del numero de la sala guarda el titulo de la pelicula en la estructura
								{
									case 1:
									strcpy(boletos[cont].pelicula,"fantasmas del espacio");
									break;
									case 2:
									strcpy(boletos[cont].pelicula,"batman VS Hulk");
									break;
									case 3:
									strcpy(boletos[cont].pelicula,"Mr satan");
									break;
									case 4:
									strcpy(boletos[cont].pelicula,"LincesTroesmas");
									break;
									case 5: 
									strcpy(boletos[cont].pelicula,"Chuck Norris Inmortal");
									break;
									default://en caso de error saldra esta opcion(es poco probable que pase por la condicional)
									printf("\nSi ves esto contacta al administrador ya que algo no funciono bien");
									break;
								}
								Consultar(&asientos,"asientos.txt");
								printf("\nescoja el asiento del boleto %d\n",(cont+1));
								cFila=&FilaCar[0];//incializa el puntero en una direccion de memoria valida
								boletos[cont].Fila=FilaANum(cFila);//asigna la letra de la fila(convertida a numero) en la estructura
								boletos[cont].numeroAsiento=numAsiento();//asigna el numero de asiento ingresado en la estructura
								if(Asiento[sala-1][NFILA][NUM-1]!=0){
									system("clear");
									printf("\nlugar ya ocupado");
									cont--;
								}else{
									sprintf(nAsiento,"%d",(boletos[cont].numeroAsiento));//Convierte el entero de la estructura y la pasa a cadena en la variable nAsiento 
									strcpy(boletos[cont].asiento[sala-1][NFILA][NUM-1],cFila);//copia la cadena de caracteres del apuntador con la letra de fila a la estructura
									strncat(boletos[cont].asiento[sala-1][NFILA][NUM-1],nAsiento,4);//genera la cadena para impresion ejemplo fila=A numeroAsiento=13 lo generado seria "A13"
									boletos[cont].precio=PrecioFila(boletos[cont].Fila);
									tickette.boletos[cont]=boletos[cont];//asigna la estructura a la estructura dentro de la estructura ticket
									tickette.precioTotal+=boletos[cont].precio;//suma el precio de la fila del boleto al precio total
									Asiento[NSALA-1][NFILA][NUM-1]=1;
									printf("\nsala %d, fila %c, asiento %d Precio $%.2f",sala,*cFila, boletos[cont].numeroAsiento, boletos[cont].precio);//imprime los datos referentes al boleto
									AsientosComprados++;
								}
							}//fin de for
						}else{//condicional negativa en caso de no seleccionar una pelicula valida
							system("clear");
							printf("\npelicula invalida sigue participando");
							stoppy();
							break;
						}
					}else{//condicional negativa en caso de no seleccionar numero dentro del rango 
						system("clear");
						printf("\n Solo se pueden comprar entre 1 y %d boletos",(MAXAFORO-AsientosComprados));
						stoppy();
						break;
					}
					break;
					case 2:
					aptcombo=&combo;
					system("clear");
					rec='s';
					if(nCombos<5){
						while(nCombos<5 && rec=='s'){//bucle que funcionara en caso de que se compre maximo 5 combos
							printf("\n escoje el combo que deseas comprar\n");
							Consultar(&combos,"Combo.txt");
							printf("\n0.Salir\n");
							scanf("%c",aptcombo);
							if(*aptcombo>='1' && *aptcombo<='5'){
								tickette.precioCombo[nCombos]=PrecioCombos(atoi(aptcombo));//recibe valor devuelto de la funcion en la estructura
								switch(*aptcombo)
								{
									case '1':
									strcpy(tickette.combo[nCombos],"Combo individual");
									break;
									case '2':
									strcpy(tickette.combo[nCombos],"Combo pareja");
									break;
									case '3':
									strcpy(tickette.combo[nCombos],"Combo Cuates");
									break;
									case '4':
									strcpy(tickette.combo[nCombos],"Combo Familiar");
									break;
									case '5': 
									strcpy(tickette.combo[nCombos],"Combo Diabetico");
									break;
									default://poco probable que esta opcion se visualice por la condicional
									printf("\n combo invalido Vuelve a intentarlo\n");
									break;
								}
								tickette.precioTotal+=tickette.precioCombo[nCombos];//se le suma al precio total el precio del combo
								printf("\n¿desea agregar otro combo? pulse S\n");
								scanf("%s",&rec);
								rec=tolower(rec);
								nCombos++;
							}else
							system("clear");
							printf("\nok");
							stoppy();
							break;
						}//fin de while
					}else{
						system("clear");
						printf("\nya compraste el maximo de 5 combos permitidos por tu cartilla de racionacion del partido popular chavista");
						stoppy();
						break;
					}
					break;
					case 3://en este caso hace que la condicional recursiva se acabe dandole el valor
					rec='e';
					break;
					default:
					system("clear");
					printf("esta opcion no es valida vuelve a intentarlo");
					stoppy();
					break;
				}
			}while(rec!='E'&&rec!='e');
			break;
			case 5:
			system("clear");
			if(tickette.precioTotal>0){
				printf("\n******************************************************");
				for(cont=0;cont<AsientosComprados;cont++){//imprime en pantalla los datos de los boletos que se compraron
					printf("\n boleto: %d pelicula: %s",(cont+1),boletos[cont].pelicula);
					printf("\n sala: %d, asiento: %s       $%.2f",boletos[cont].sala,boletos[cont].asiento[NSALA-1][NFILA][NUM-1],boletos[cont].precio);
				}
				for(cont=0;cont<nCombos;cont++){//imprime en pantalla los datos de los combos que se compraron
					printf("\n Combo: %s $ %.2f",tickette.combo[cont],tickette.precioCombo[cont]);
				}
				printf("\n      total a pagar $%.2f",tickette.precioTotal);
				printf("\n******************************************************");
				printf("\n¿esta seguro de su compra?, si es asi pulse \"S\" para imprimir el ticket\n");
				scanf("%s",&afirm);
				afirm=toupper(afirm);//funcion que hace que el caracter afirm sea mayuscula siempre
				if(afirm=='S'){//condicional si se pulsa "S" o "s" se inicia el proceso de creacion del fichero del ticket.txt
					AperturaSegura(&ticketto, "ticket.txt");//abre en modo lectura el fichero
					fprintf(ticketto,"\n******************************************************");
					fprintf(ticketto,"\n                CINEMAS CINEPLUX");
					for(cont=0;cont<AsientosComprados;cont++){//for que escribira en el ticket el numero comprado de boletos con sus datos
						strcpy(AsientoTemp, *boletos[cont].asiento[NFILA][NUM]);
						fprintf(ticketto,"\n boleto: %d pelicula: %s",(cont+1),boletos[cont].pelicula);
						fprintf(ticketto,"\n sala: %d, asiento: %s    $%.2f",boletos[cont].sala, boletos[cont].asiento[NSALA-1][NFILA][NUM-1], boletos[cont].precio);
					}
					for(cont=0;cont<nCombos;cont++){//for que escribira en el ticket el numero de combos que se compraron
						fprintf(ticketto,"\n   %s $ %.2f",tickette.combo[cont],tickette.precioCombo[cont]);
					}
					fprintf(ticketto,"\n      total a pagar $%.2f",tickette.precioTotal);
					fprintf(ticketto,"\n              GRACIAS POR SU COMPRA                   ");
					fprintf(ticketto,"\n******************************************************");
					fclose(ticketto);
					printf("\nticket creado con exito");
					stoppy();				
				}//fin de condicional if
			}else{
				printf("\nAun se ha comprado nada");
			}
				stoppy();//estas funciones solo reciben un caracter para detener la consola momentaneamente
			break;
			case 6:
			system("clear");
			printf("\n Usted esta saliendo del programa\n");
			rec='S';
			break;
			default:
			system("clear");
			printf("esta opcion no es valida vuelve a intentarlo");
			stoppy();
			break;
		}
		stoppy();
	}while(rec!='S'); 
	return 0;
}
