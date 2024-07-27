#include <stdio.h>
#include <string.h>


int comparaRam(char ram[80][5], char nom[5], int indice){
			int val=0, cont=0;
			for(int j=0; j<5; j++){
				if(ram[indice][j]==nom[j]){
					cont++;
				}
			}
			if(cont==5){
				val=1;
			}
			return val;
		}

void agrega(char ram[80][5], char nom[5], int indice){
			for(int j=0; j<5; j++){
				ram[indice][j]=nom[j];
			}
		}

char hdd[80][5];

int main(){
				int opc, flag=0, tam_p, metodo=-1, opc_rep, cont_huecos=0, espacio=80, indice=-1, band=0, contPoH=0, indicePoH=0;
				char nombre[5], ram[80][5], borrar[5], PoH[5], vacio[5]="     ";
				for(int i=0; i<80; i++){
					for(int j=0; j<5; j++){
						ram[i][j]=32;//Inicializa RAM con espacios vacios
					}
				}
				do{
					printf("Seleccione una opcion del menu:\n1-Crear Procesos.\n2-Eliminar Procesos.\n3-Visualizar RAM.");
					printf("\n4-Representacion \"RAM disponible\"\n5-Intercambio.\n6.-Salir\n");
					scanf("%d",&opc);
					switch(opc){
						case 1://Agregar Proceso
								do{
									band=0;
									printf("Escriba el nombre del proceso (max. 5 caracteres):\n");
									scanf("%s",nombre);
									for(int i=0; i<80; i++){
										if(comparaRam(ram, nombre, i)==1){
											printf("\nERROR: El proceso ya existe.\nOpciones:\n1.Cambiar nombre del Proceso.\n2.No colocar Proceso.\nSeleccione su opcion: ");
											scanf("%d",&band);
											break;
										}
									}
								}while(band==1);
								if(band==2){
									break;
								}
								do{
									printf("Escriba el tamano del proceso:\n");
									scanf("%d",&tam_p);
								}while(tam_p<=0);
								if(espacio<tam_p){
									printf("\nERROR: Memoria RAM Saturada\n\n");
								}
								//Buscador de huecos
								cont_huecos=0;
								for(int i=0; i<80; i++){
									if(comparaRam(ram, vacio, i)==1){
										cont_huecos++;
										if(cont_huecos==tam_p){
											indice=(i-tam_p)+1;
											cont_huecos=0;
											break;
										}
									}else{
										cont_huecos=0;
									}
								}
								if(indice>=0){
									for(int j=indice; j<(indice+tam_p); j++){
										agrega(ram, nombre, j);
									}
									espacio=espacio-tam_p;
									indice=-1;
								}else{
									int error=0;
									printf("\nERROR: No hay espacio disponible en la memoria RAM\nOpciones:\n1.Eliminar un Proceso\n2.No Crear Proceso.\nSeleccione su opcion:\n");
									scanf("%d",&error);
									switch (error) {
									case 1:
										for(int i=79;i>=0; i--){
											if(comparaRam(ram, vacio, i)==0){
												for(int a=0; a<5; a++){
													borrar[a]=ram[i][a];
												}

												for(int j=i; j>=0; j--){
													if(comparaRam(ram, borrar, j)==1){
														agrega(ram, vacio, j);
														espacio++;
													}
												}
												break;
											}
										}
										break;
									case 2:
										break;
									}
								}
							break;
					case 2:
						printf("Escriba el nombre del proceso (max. 5 caracteres):\n");//Eliminar Proceso
						scanf("%s",nombre);
						band=0;
						for(int i=0; i<80; i++){
							if(comparaRam(ram, nombre, i)==1){
								agrega(ram, vacio, i);
								band=1;
								espacio++;
							}
						}
						//IF-ELSE
						if(band==0){
							printf("\nWARNING: El proceso no fue encontrado o no existe.\n\n");
						}else{
							printf("Proceso eliminado de la RAM.\n");
						}
						break;
						case 3:
									printf("Visualizacion de la memoria RAM:\n");
									for(int i=0; i<80; i++){
										printf("[ ");
										for(int j=0; j<5; j++){
											if (ram[i][j] != -96)
												printf("%c",ram[i][j]);
										}
										printf(" ] ");
										if(i==7 || i==15 || i==23 || i==31 || i==39 || i==47 || i==55 || i==63 || i==71 || i==79){
											printf("\n");
										}
									}
									break;
						case 4:
								printf("Seleccione una representacion usando los numeros:\n1.Mapa de Bits.\n2.Listas Libres.\n");
								scanf("%d",&metodo);
								switch(metodo){
													case 1:
														printf("Usted ha seleccionado: Mapa de Bits.\n");
														printf("Visualizando en Mapa de Bits:\n");
														for(int i=0; i<80; i++){
															if(comparaRam(ram, vacio, i)==0){
																printf(" [1]");
															}else{
																printf(" [0]");
															}
															if(i==7 || i==15 || i==23 || i==31 || i==39 || i==47 || i==55 || i==63 || i==71 || i==79){
																printf("\n");
															}
														}
														printf("\n");
														break;
												case 2:
																printf("Usted ha seleccionado: Listas Libres.\n");
																printf("Visualizando en Listas Libres:\n\n");
																		contPoH=0, indicePoH=0;
																		for(int a=0; a<5; a++){
																				PoH[a]=ram[0][a];
																		}

																		for(int i=0; i<=80; i++){
																				if(comparaRam(ram, PoH, i)==1){
																						contPoH++;
																				}
																				if(comparaRam(ram, PoH, i)==0){
																						for(int a=0; a<5; a++){
																								PoH[a]=ram[i][a];
																						}

																						if(comparaRam(ram, vacio, i-1)==1){
																								printf("[H | %d | %d ] -> ",indicePoH,contPoH);
																								contPoH=1;
																								indicePoH=i;
																						}else{
																								printf("[P | %d | %d ] -> ",indicePoH,contPoH);
																								contPoH=1;
																								indicePoH=i;
																						}
																				}
																		}printf("\n\n");
																		break;
						case 5:
								if(flag==0){
									for(int i=0; i<80; i++){
										for(int j=0; j<5; j++){
											hdd[i][j]=32;//Inicializa RAM con espacios vacios
										}
									}
								}
								flag=1;
								printf("Escriba el número del intercambio que desea realizar:\n1.De RAM a HDD.\n2.De HDD a RAM.\n");//Intercambio
								scanf("%d",&opc_rep);
								switch(opc_rep){
								case 1:

									printf("Escriba el nombre del proceso en RAM para guardarlo en HDD:\n");//Modificado de: Eliminar Proceso
									scanf("%s",nombre);
									band=0;
									tam_p=0;
									cont_huecos=0;
									indice=-1;

									for(int i=0; i<80; i++){
										if(comparaRam(ram, nombre, i)==1){
											tam_p++;
										}
									}

									for(int i=0; i<80; i++){
										if(comparaRam(ram, nombre, i)==1){

											for(int j=0; j<80; j++){//Modificado de: Crear Proceso
												if(comparaRam(hdd, vacio, j)==1){
													cont_huecos++;
													if(cont_huecos==tam_p){
														indice=(j-tam_p)+1;
														cont_huecos=0;
														break;
													}
												}else{
													cont_huecos=0;
												}
											}
											if(indice>=0){
												for(int j=indice; j<(indice+tam_p); j++){
													agrega(hdd, nombre, j);//Agrega el Proceso a HDD
													agrega(ram, vacio, i);//Elimina proceso de RAM
													i++;
												}
												espacio=espacio+tam_p;
												indice=-1;
											}else{
												printf("\nERROR: No hay espacio disponible en HDD.\nIntercambie un proceso de HDD a la RAM.\n");
											}
											band=1;
											break;
										}
									}
									//Este IF-ELSE
									if(band==0){
										printf("\nWARNING: El proceso no fue encontrado o no existe.\n\n");
									}else{
										printf("Proceso guardado en HDD y liberado de RAM.\n");
									}
									break;

								case 2:
									printf("Escriba el nombre del proceso en HDD para guardarlo en RAM:\n");
									scanf("%s",nombre);
									band=0;
									tam_p=0;
									cont_huecos=0;
									indice=-1;

									for(int i=0; i<80; i++){
										if(comparaRam(hdd, nombre, i)==1){
											tam_p++;
										}
									}

									for(int i=0; i<80; i++){
										if(comparaRam(hdd, nombre, i)==1){

											for(int j=0; j<80; j++){//Modificado de: Crear Proceso
												if(comparaRam(ram, vacio, j)==1){
													cont_huecos++;
													if(cont_huecos==tam_p){
														indice=(j-tam_p)+1;
														cont_huecos=0;
														break;
													}
												}else{
													cont_huecos=0;
												}
											}
											if(indice>=0){
												for(int j=indice; j<(indice+tam_p); j++){
													agrega(ram, nombre, j);//Agrega el Proceso a HDD
													agrega(hdd, vacio, i);//Elimina proceso de RAM
													i++;
												}
												espacio=espacio-tam_p;
												indice=-1;
											}else{
												printf("\nERROR: No hay espacio disponible en RAM.\nLibere espacio de la RAM o intercambie un proceso de RAM a HDD.\n");
											}
											band=1;
											break;
										}
									}
									//Este IF-ELSE
									if(band==0){
										printf("\nWARNING: El proceso no fue encontrado o no existe.\n\n");
									}else{
										printf("Proceso guardado en RAM y liberado de HDD.\n");
									}
									break;
								}
								break;
				}
			}	
				}while(opc!=6);
				printf("Hasta Luego!\n");
				return 0;
			}
