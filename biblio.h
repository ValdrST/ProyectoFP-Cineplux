//prototipos
void stoppy(void);
void Consultar(FILE **archivo, char fichero[]);
void CrearTicket(FILE **archivo, char fichero[]);
int FilaANum(char*);
int numAsiento(void);
void mostrarTiempo(char output[128]);
float PrecioCombos(int combo);
void InicializarAsientos(int Asiento[6][6][20]);
//inicio de funciones
void Consultar(FILE **archivo, char fichero[])
{
	char printo;
				*archivo = fopen(fichero,"r");
			if (*archivo == NULL){
		printf("\nError de apertura del archivo. \n\n");
			}else{
				while((printo=getc(*archivo))!=EOF){
					if(printo!='/' && printo!='*' && printo!='#')
						printf("%c",printo);
					}
			}
			fclose(*archivo);
			stoppy();
}

void stoppy(void)
{
    char stoppy;
    scanf("%c",&stoppy);
}

int FilaANum(char *aptFila)
{
	printf("\nfila: ");
	scanf("%c",aptFila);
	*aptFila=toupper(*aptFila);
		switch(*aptFila)
		{
				case 'A':
				return 0;
				break;
				case 'B':
				return 1;
				break;
				case 'C':
				return 2;
				break;
				case 'D':
				return 3;
				break;
				case 'E':
				return 4;
				break;
				case 'F':
				return 5;
				break;
				default:
				printf("\nFila no existente vuelva a escojer letra valida\n");
				break;
		}
		return FilaANum(aptFila);
}

int numAsiento(void)
{
	int nAsiento;
	printf("\nnumero de asiento: ");
	scanf("%d",&nAsiento);
	if(nAsiento>=1 && nAsiento<=20)
		return nAsiento;
	else{
		printf("\nrango no valido vuelve a intentar \n");
		return numAsiento();
	}
}

float PrecioFila(int fila)
{
	switch(fila)
	{
		case 0:
		return 15.00;
		break;
		case 1:
		return 17.00;
		break;
		case 2:
		return 19.00;
		break;
		case 3:
		return 21.00;
		break;
		case 4:
		return 23.00;
		break;
		case 5:
		return 25.00;
		break;
		default:
		printf("\nops aqui hubo error contacte al administrador");
		return 0;
		break;
	}
}

float PrecioCombos(int combo)
{
	switch(combo)
	{
		case 1:
		return 70.00;
		break;
		case 2:
		return 90.00;
		break;
		case 3:
		return 120.00;
		break;
		case 4:
		return 140.00;
		break;
		case 5:
		return 100.00;
		break;
		default:
		return 0;
		break;
	}
}

void AperturaSegura(FILE **archivo, char fichero[])
{
	*archivo = fopen(fichero,"w");
	if (*archivo == NULL)
		printf("\nError de apertura del archivo. \n\n");
}
void InicializarAsientos(int Asiento[6][6][20]){
	int x,y, z;
	for(x=0;x<5;x++){
		for(y=0;y<6;y++){
			for(z=0;z<20;z++){
				Asiento[x][y][z]=0;
			}
		}
	}
}
void mostrarTiempo(char fechaHora[128])
{
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(fechaHora,128,"%d/%m/%y %H:%M:%S",tlocal);
}
