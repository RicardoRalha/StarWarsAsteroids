/******************************************************************************/
/**                                                    ,---------------.     **/
/**    COMPUTACAO GRAFICA                              |        .-.    |     **/
/**    MIEEC - FCTUC                                   |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTOR: -Ricardo Ralha                           |  `---'   `-'  |     **/
/**                                                    `---------------'     **/
/******************************************************************************/
/* DESCRICAO:																  */
/*O jogo Star Wars Asteroids inicia com um menu principal, onde temos         */
/*a opção de começar o jogo – “Start Game” ou sair - “Exit”. Podemos          */
/*ainda consultar a maior pontuação - “Highscore”.                            */
/*Para seleccionar entre as opções no menu, deve-se utilizar as teclas:       */
/*seta indicadora para cima (para andar para cima), e a seta para baixo       */
/*(para andar para baixo). Para confirmar a selecção, prime-se                */
/*“espaço”. A qualquer momento do jogo, para sair prima Escape “Esc”.         */
/*Seguidamente, ao iniciar o jogo, é possível observar do lado                */
/*esquerdo, em cima, a pontuação actual, o nível actual e o número de         */
/*vidas restantes. Quando é iniciado o jogo, nenhum asteróide estará          */
/*perto da nave principal!                                                    */
/*Para navegar a nave, deverá utilizar as teclas: seta indicadora para        */
/*cima (para andar para a frente), seta para a esquerda                       */
/*(rodar para a esquerda) e seta para a direita (rodar para a direita).       */
/*Para disparar, prima “espaço”.                                              */
/*Ao atingir um asteróide, este irá dividir-me em dois asteróides de um       */
/*tamanho mais pequeno, até desaparecerem. A cada nível avançado,             */
/*o número de asteróides aumenta por um.                                      */
/*Sempre que quiser fazer pausa, após o jogo ter sido iniciado, basta         */
/*premir a teca “P” para ficar o jogo pausado “Pause” e premir                */
/*novamente para continuar o jogo.                                            */
/*O utilizador terá sempre 3 vidas iniciais, e quando estas acabarem vai      */
/*surgir um menu onde será possívelcomeçar um novo jogo “New Game”            */
/* ou regressar ao menu principal “Main Menu”.                                */
/******************************************************************************/


// 
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//


#include "TP3.h"



//
//	Funcoes ////////////////////////////////////////////////////////////////////
//


//Adiciona um asteroide à lista
struct asteroides * adiciona_asteroides(){//struct que adiciona mais um asteroide à lista

	struct asteroides *ptr;

	ptr = (struct asteroides *) malloc(sizeof(*ptr));

	ptr->Anterior=NULL;
	ptr->Proxima=NULL;

	return(ptr);

}


//Adiciona um tiro à lista
struct tiros * adiciona_tiros(){//struct que adiciona mais um tiro à lista

	struct tiros *ptr;

	ptr = (struct tiros *) malloc(sizeof(*ptr));

	ptr->Proxima=NULL;
	ptr->Anterior=NULL;
	ptr->tiro_ciclos=0;

	return(ptr);

}


//Elimina as listas.
void elimina_estruturas(){
	Actual=Inicio;
	while(Actual!=NULL){
		Aux=Actual;
		Actual=Actual->Proxima;
		free(Aux);
	}
	Inicio=NULL;	//é necessario em alturas do programa
	Actual_tiro=Inicio_tiro;
	while(Actual_tiro!=NULL){
		Aux_tiro=Actual_tiro;
		Actual_tiro=Actual_tiro->Proxima;
		free(Aux_tiro);
	}
	Inicio_tiro=NULL;	//é necessario em alturas do programa
}


//Funçao que vai criar os asteroides a ser visualizados e chama a funçao desenha_asteroides()
void cria_asteroides(int tamanho, int trans_x, int trans_y){

	if (controlo_asteroides==0){
		srand(time(NULL));
		controlo_asteroides=2;
		
		//vao ser criados asteroides grandes novos, para iniciar um novo nivel
		for(i=0;i<numero_asteroides;i++){
			
			if(Inicio==NULL){
				Inicio=adiciona_asteroides();
				Actual=Inicio;
			}
			else{
				Actual->Proxima=adiciona_asteroides();
				Actual->Proxima->Anterior=Actual;
				Actual=Actual->Proxima;
			}
			//condiçao aparecimento asteroides sem interferir com a nave
			if(ceil((float)(rand() % 2 +1))==1)
				Actual->trans_x=rand() % (tamanhox-(dist_aparecimento_asteroides-1)) +dist_aparecimento_asteroides;
			else
				Actual->trans_x=rand() % (tamanhox-(dist_aparecimento_asteroides-1)) -tamanhox;

			if(ceil((float)(rand() % 2 +1))==1)
				Actual->trans_y=(rand() % (tamanhoy-(dist_aparecimento_asteroides-1)) +dist_aparecimento_asteroides);
			else
				Actual->trans_y=(rand() % (tamanhoy-(dist_aparecimento_asteroides-1)) -tamanhoy);
			
			//condiçao velocidade dos asteroides, sem ser 0
			if(ceil((float)(rand() % 2 +1))==1)
				Actual->vel_x=(rand() % vel_max_asteroides +1);
			else
				Actual->vel_x=(rand() % vel_max_asteroides -vel_max_asteroides);

			if(ceil((float)(rand() % 2 +1))==1)
				Actual->vel_y=(rand() % vel_max_asteroides +1);
			else
				Actual->vel_y=(rand() % vel_max_asteroides -vel_max_asteroides);
			
			Actual->tipo=ceil((float)(rand() % 2 +1));
			Actual->tamanho=tamanho_ini_asteroides;
		}
	}
	else if(controlo_asteroides==1){
		srand(time(NULL));
		controlo_asteroides=2;
		for(i=0;i<2;i++){
			Actual->Proxima=adiciona_asteroides();
			Actual->Proxima->Anterior=Actual;
			Actual=Actual->Proxima;

			//condiçao aparecimento asteroides na zona onde o asteroide anterior foi destruido

				Actual->trans_x=trans_x;
				Actual->trans_y=trans_y;
			
			//condiçao velocidade dos asteroides, sem ser 0
			if(ceil((float)(rand() % 2 +1))==1)
				Actual->vel_x=(rand() % vel_max_asteroides +1);
			else
				Actual->vel_x=(rand() % vel_max_asteroides -vel_max_asteroides);

			if(ceil((float)(rand() % 2 +1))==1)
				Actual->vel_y=(rand() % vel_max_asteroides +1);
			else
				Actual->vel_y=(rand() % vel_max_asteroides -vel_max_asteroides);
			
			Actual->tipo=ceil((float)(rand() % 2 +1));
			Actual->tamanho=tamanho-1;
	
		}
	}
}


//Funçao que vai criar os tiros a ser visualizados 
void cria_tiros(){

	if(controlo_arma==1){
		if(controlo_criacao_arma==1){
			if(Inicio_tiro==NULL){
				Inicio_tiro=adiciona_tiros();
				Actual_tiro=Inicio_tiro;
			}
			else{
				Actual_tiro->Proxima=adiciona_tiros();
				Actual_tiro->Proxima->Anterior=Actual_tiro;
				Actual_tiro=Actual_tiro->Proxima;
			}
			Actual_tiro->trans_x=trans_x+cos(ang*(PI/180))*76.5;
			Actual_tiro->trans_y=trans_y+sin(ang*(PI/180))*76.5;
			Actual_tiro->ang=ang;
			Actual_tiro->vel_x=cos(ang*(PI/180))*velocidade_tiro;
			Actual_tiro->vel_y=sin(ang*(PI/180))*velocidade_tiro;

			controlo_criacao_arma=0;
		}

		Actual_tiro=Inicio_tiro;

		while(Inicio_tiro!=NULL){

			desenha_tiros(Actual_tiro->ang,Actual_tiro->trans_x,Actual_tiro->trans_y);
		
			if(Actual_tiro->Proxima==NULL)
				break;

			Actual_tiro=Actual_tiro->Proxima;
		}
		

	}

}


//Funçao que vai aplicar fisicas importantes ao programa. Aqui fazem-se os calculos para todos os objectos atravessarem
//os limites do ecra e aparecerem do outro lado, eliminam-se tiros, detectam-se colisoes e iteram-se variaveis necessarias ao correcto funcionamento do programa
void fisicas(){

	//Isto so corre se o jogo nao estiver em pausa
	if(controlo_pause==0){
		//controlo de todo o movimento da nave
		if (controlo_tecla_esquerda==1 && controlo_menus==1 && nave_destruida==0)
			ang+=rotacao_nave;
		if (controlo_tecla_direita==1 && controlo_menus==1 && nave_destruida==0)
			ang-=rotacao_nave;
		if(controlo_tecla_cima==1 && controlo_menus==1 && nave_destruida==0){
			trans_y+=sin(ang*(PI/180))*velocidade_nave;
			trans_x+=cos(ang*(PI/180))*velocidade_nave;
			ang_indep=ang;
			if(controlo_chama==0)
				controlo_chama=1;
			else 
				controlo_chama=0;
		}
		//movimento nave sem haver propulsao
		else if(controlo_tecla_cima==0 && controlo_menus==1 && nave_destruida==0){
			if(trans_x!=0 || trans_y!=0){
				trans_y+=sin(ang_indep*(PI/180))*vel_mov_indep;
				trans_x+=cos(ang_indep*(PI/180))*vel_mov_indep;
			}
		}
		//Movimento nave nos menus
		else if(controlo_tecla_cima==1 && (controlo_menus==0 || controlo_menus==2)){
			trans_x=-392;
			trans_y=-110;
		}
		if(controlo_tecla_baixo==1 && (controlo_menus==0 || controlo_menus==2)){
			trans_x=-392;
			trans_y=-230;
		}

	
		//So vai correr se estivermos em jogo e a nave nao estiver destruida
		if(nave_destruida==0 && controlo_menus==1){
			//condiçoes para saber se a nave e destruida pelos asteroides
			Actual=Inicio;
			while(Inicio!=NULL){
				for (i=0; i<360; i+=36){
					x=(tamanho_nave_x*cos(i*PI/180))+trans_x;
					y=(sin(i*PI/180)*tamanho_nave_y)+trans_y;
					//Em cada momento, faz-se o calculo da margem dos asteroides com todos os pontos da nave. Caso
					//algum dos pontos seja menor que o raio das asteroides, há colisao
					if(sqrt(powf(Actual->trans_x-x,2)+powf(Actual->trans_y-y,2))<=raio_asteroides*Actual->tamanho){
						controlo_destruicao=1;	//deixa que a nave seja destruida por um asteroide e seja detectado apenas uma vez
						vidas--;
						ang=0;
						controlo_chama=0;
						if(vidas==0){
							controlo_menus=2;
							trans_x=-392, trans_y=-110;
							sndPlaySoundA("imperial.wav", SND_LOOP | SND_ASYNC);
						}
						//Nave volta a posiçao inicial
						else{
							nave_destruida=1;
							trans_x=0;
							trans_y=0;
						}
					}
				}
				if(Actual->Proxima==NULL ||controlo_destruicao==1){
					controlo_destruicao=0;
					break;
				}
				Actual=Actual->Proxima;
			}

			//condiçoes para a nave atravessar a janela

			if((trans_x-tamanho_nave_x-tamanho_chama_y)>=tamanhox)
				trans_x=-(tamanhox+tamanho_nave_x);
			else if ((trans_x+tamanho_nave_x+tamanho_chama_y)<=-tamanhox)
				trans_x=(tamanhox+tamanho_nave_x);

			if((trans_y-tamanho_nave_x-tamanho_chama_y)>=tamanhoy)
				trans_y=-(tamanhoy+tamanho_nave_x);
			else if ((trans_y+tamanho_nave_x+tamanho_chama_y)<=-tamanhoy)
				trans_y=(tamanhoy+tamanho_nave_x);
		}
		else if(controlo_menus==1){
			//incrementa os ciclos em que a nave esta destruida
			ciclos_nave_destruida++;
			if(ciclos_nave_destruida==tempo_nave_destruida){
				controlo_aparecimento_nave=1;
				ciclos_nave_destruida=0;
			}
		}

	
		//Condiçoes para colisao entre os tiros e os asteroides

		if(controlo_arma==1){
			Actual_tiro=Inicio_tiro;
			while(Inicio_tiro!=NULL){
				Actual=Inicio;
				while(Inicio!=NULL){
					//Em cada momento, faz-se o calculo da margem dos asteroides com a translaçao dos tiros, mais o tamanho dos tiros. Caso
					//algum dos pontos seja menor que o raio das asteroides, há colisao
					if(sqrt(powf(Actual->trans_x-(Actual_tiro->trans_x+cos(ang*(PI/180))*36),2)+powf(Actual->trans_y-(Actual_tiro->trans_y+sin(ang*(PI/180))*36),2))<=raio_asteroides*Actual->tamanho){
						//elimina_tiro podia ser utilizado para a verificaçao do controlo_destruiçao, mas decidimos separar
						elimina_tiro=1;
						controlo_destruicao=1; //deixa que a nave seja destruida por um asteroide e seja detectado apenas uma vez
						//incrementa pontos em funçao do asteroide destruido
						if(Actual->tamanho==3)
							pontos+=pont_asteroides_grandes;
						else if(Actual->tamanho==2)
							pontos+=pont_asteroides_medios;
						else
							pontos+=pont_asteroides_pequenos;
						//cria asteroides descendentes do anterior excepto se o asteroide for de tamanho 1
						if(Actual->tamanho!=1){
							Aux=Actual;
							while(Actual->Proxima!=NULL)
								Actual=Actual->Proxima;
							controlo_asteroides=1;
							cria_asteroides(Aux->tamanho,Aux->trans_x,Aux->trans_y);
							Actual=Aux;
						}
						if(Inicio==Actual){
							if(Actual->Proxima==NULL){
								free(Inicio);
								Inicio=NULL;
								//Passa-se de nivel
								sndPlaySoundA("wookie1.wav", SND_ASYNC);
								nivel++;
								numero_asteroides++;
								controlo_asteroides=0;
							}
							else{
								Inicio=Actual->Proxima;
								Inicio->Anterior=NULL;
								free(Actual);
								Actual=Inicio;
							}
						}
						else if (Actual->Proxima!=NULL){
							Actual->Anterior->Proxima=Actual->Proxima;
							Actual->Proxima->Anterior=Actual->Anterior;
							Aux=Actual;
							Actual=Actual->Proxima;
							free(Aux);
						}
						else if(Actual->Proxima==NULL){
							Actual->Anterior->Proxima=NULL;
							Aux=Actual;
							Actual=Actual->Anterior;
							free(Aux);
							break;
						}
					
					}
					else{
						if(Actual->Proxima==NULL || controlo_destruicao==1){
							controlo_destruicao=0;
							break;
						}

						Actual=Actual->Proxima;
					}
				}
				//Caso exista um asteroide destruido, elimina_tiro fica a 1 e o tiro que destruiu é eliminado
				if(elimina_tiro==1){
					if(Inicio_tiro==Actual_tiro){
						if(Actual_tiro->Proxima==NULL){
							controlo_arma=0;
							free(Inicio_tiro);
							Inicio_tiro=NULL;
						}
						else{
							Inicio_tiro=Actual_tiro->Proxima;
							Inicio_tiro->Anterior=NULL;
							free(Actual_tiro);
							Actual_tiro=Inicio_tiro;
						}
					}
					else if (Actual_tiro->Proxima!=NULL){
						Actual_tiro->Anterior->Proxima=Actual_tiro->Proxima;
						Actual_tiro->Proxima->Anterior=Actual_tiro->Anterior;
						Aux_tiro=Actual_tiro;
						Actual_tiro=Actual_tiro->Proxima;
						free(Aux_tiro);
					}
					else if(Actual_tiro->Proxima==NULL){
						Actual_tiro->Anterior->Proxima=NULL;
						Aux_tiro=Actual_tiro;
						Actual_tiro=Actual_tiro->Anterior;
						free(Aux_tiro);
						numero_tiros--;
						elimina_tiro=0;
						break;
					}
					numero_tiros--;
					elimina_tiro=0;
				}

				else{
					if(Actual_tiro->Proxima==NULL)
						break;

					Actual_tiro=Actual_tiro->Proxima;
				}

			}
		}

		//condiçoes para o tiro atravessar a janela, existir movimento dos tiros e os tiros desaparecerem passado algum tempo

		//Corre so se houver tiros no ecra
		if(controlo_arma==1 && Inicio_tiro!=NULL){
			Actual_tiro=Inicio_tiro;

			if(Actual_tiro->tiro_ciclos==tempo_tiro){
				if(Actual_tiro->Proxima!=NULL){
					Inicio_tiro=Actual_tiro->Proxima;
					free(Actual_tiro);
					Actual_tiro=Inicio_tiro;
				}
				else{
					free(Actual_tiro);
					Inicio_tiro=NULL;
					controlo_arma=0;
				}
				numero_tiros--;		//aqui, diminui-se sempre um tiro ao ecra
			}

			while(Inicio_tiro!=NULL){
				if((Actual_tiro->trans_x)>tamanhox)
					Actual_tiro->trans_x=-(tamanhox);
				else if ((Actual_tiro->trans_x)<-(tamanhox))
					Actual_tiro->trans_x=(tamanhox);
				else
					Actual_tiro->trans_x+=Actual_tiro->vel_x;

				if((Actual_tiro->trans_y)>tamanhoy)
					Actual_tiro->trans_y=-(tamanhoy);
				else if ((Actual_tiro->trans_y)<-(tamanhoy))
					Actual_tiro->trans_y=(tamanhoy);
				else
					Actual_tiro->trans_y+=Actual_tiro->vel_y;

				Actual_tiro->tiro_ciclos++;


				if(Actual_tiro->Proxima==NULL)
					break;

				Actual_tiro=Actual_tiro->Proxima;
			}
		}



		//condiçoes para os asteroides atravessarem a janela e existir movimento dos asteroides
		//So aparecem quando passa o tempo inicial para o jogo começar
		if(tempo_jogo>=(tempo_inicio+inicio_jogo || controlo_menus!=1)){
				Actual=Inicio;
			while(Inicio!=NULL){

				if((Actual->trans_x-35*Actual->tamanho)>=tamanhox)
					Actual->trans_x=-(tamanhox+35*Actual->tamanho);
				else if ((Actual->trans_x+35*Actual->tamanho)<=-tamanhox)
					Actual->trans_x=(tamanhox+35*Actual->tamanho);

				if((Actual->trans_y-35*Actual->tamanho)>=tamanhoy)
					Actual->trans_y=-(tamanhoy+35*Actual->tamanho);
				else if ((Actual->trans_y+35*Actual->tamanho)<=-tamanhoy)
					Actual->trans_y=(tamanhoy+35*Actual->tamanho);

				Actual->trans_x+=Actual->vel_x;
				Actual->trans_y+=Actual->vel_y;

				if(Actual->Proxima==NULL)
					break;

				Actual=Actual->Proxima;
			}
		}

		//Condição para a nave, depois de destruida, nao aparecer antes de todos os asteroides estarem fora da dist_aparecimento_asteroides
		if (controlo_aparecimento_nave==1 && controlo_menus==1){
			nave_destruida=0;
			controlo_aparecimento_nave=0;
			Actual=Inicio;
			while(Inicio!=NULL){
				if(Actual->trans_x<=dist_aparecimento_asteroides && Actual->trans_x>=-dist_aparecimento_asteroides && Actual->trans_y<=dist_aparecimento_asteroides && Actual->trans_y>=-dist_aparecimento_asteroides){
					nave_destruida=1;
					controlo_aparecimento_nave=1;
					break;
				}

				if(Actual->Proxima==NULL)
						break;
				Actual=Actual->Proxima;
			}
		}
		//Calcula se há subida de nivel
		if(pontos>=valor_subida_nivel*pontos_suporte && pontos!=0 && controlo_menus==1){
			pontos_suporte++;
			if(vidas<numero_max_vidas){
				sndPlaySoundA("r2d2.wav", SND_ASYNC);
				vidas++;
			}
		}

		//quando se entra no jogo, todas estas variaveis vao sofrer um reset
		if(muda_dados_menu==1){
			controlo_pontuacao=0;
			controlo_ficheiro=0;
			controlo_som=0;
			elimina_estruturas();
			controlo_tecla_baixo=0;
			controlo_tecla_cima=0;
			controlo_tecla_esquerda=0;
			controlo_tecla_direita=0;
			trans_x=0;
			trans_y=0;
			controlo_asteroides=0;
			pontos=0;
			nivel=1;
			vidas=numero_ini_vidas;
			time(&inicio_jogo);
			controlo_menus=1;
			muda_dados_menu=0;
			numero_tiros=1;
			numero_asteroides=numero_inicial_asteroides;
		}
		//Quando se entra no menu principal, todas estas variaveis recebem um reset e a musica começa a tocar
		else if(muda_dados_menu==2){
			controlo_ficheiro=0;
			elimina_estruturas();
			trans_x=-392;
			trans_y=-110;
			controlo_asteroides=0;
			controlo_menus=0;
			muda_dados_menu=0;
			numero_asteroides=numero_inicial_asteroides;
			sndPlaySoundA("starwars.wav",SND_LOOP | SND_ASYNC);
		}


		time(&tempo_jogo);			//tempo de jogo é retirado
	}

}


//funçao init, vai inicializar as propriedades iniciais do programa
void init(){

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluOrtho2D(-tamanhox,tamanhox,-tamanhoy,tamanhoy);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPointSize(1);
}


//Funçao display, vai escrever no ecra todos os objectos do jogo
void display(void){

	glLoadIdentity();

	gluOrtho2D(-tamanhox,tamanhox,-tamanhoy,tamanhoy);

	glClear(GL_COLOR_BUFFER_BIT);


	//Desenho das estrelas

	if (controlo_estrelas==0){
		sndPlaySoundA("starwars.wav",SND_LOOP | SND_ASYNC);//Quando o jogo inicio, utiliza-se esta condiçao, que so e corrida uma unica vez, para tocar a musica pela 1a vez
		time(&rand_estrelas);		//Este valor, rand_estrelas, vamos utiliza lo para desenhar as estrelas sempre no mesmo sitio e para temporizar o jogo
		controlo_estrelas=1;
	}
	srand(rand_estrelas);
	for (i=0;i<n_estrelas;i++){
		x=ceil((float)(rand() % tamanhox) );
		y=ceil((float)(rand() % tamanhoy) );
		for(j=0;j<3;j++)
			tab[x][y][j]=1.0;
	}
	glDrawPixels( tamanhox, tamanhoy, GL_RGB, GL_FLOAT, tab);

	//Menu principal, desenho asteroides, nave, e palavras do menu
	if(controlo_menus==0){
		cria_asteroides(0,0,0);

		Actual=Inicio;
		while(Inicio!=NULL){
			desenha_asteroides(Actual->tipo,Actual->tamanho,Actual->trans_x,Actual->trans_y);

			if(Actual->Proxima==NULL)
				break;

			Actual=Actual->Proxima;
		}
		//Leitura(ou criaçao) do ficheiro para ler o highscore
		if(controlo_ficheiro==0){
			descriptor = fopen("Highscore.txt", "r");

			if(descriptor==NULL){
				descriptor = fopen("Highscore.txt", "w");
				fprintf(descriptor,"0");
				fclose(descriptor);
				descriptor = fopen("Highscore.txt", "r");
			}
			fgets(char_pontos_vidas_nivel,30,descriptor);
			fclose(descriptor);
			controlo_ficheiro=1;
	}

		Desenhar_Texto();
	

		desenha_nave();
		
	}

	//Quando de joga
	else if(controlo_menus==1){

		//Desenho asteroides
		if(tempo_jogo>=(tempo_inicio+inicio_jogo)){
			cria_asteroides(0,0,0);

			Actual=Inicio;
			while(Inicio!=NULL){
				desenha_asteroides(Actual->tipo,Actual->tamanho,Actual->trans_x,Actual->trans_y);

				if(Actual->Proxima==NULL)
					break;

				Actual=Actual->Proxima;
			}
		}

		//Desenho tiros
		cria_tiros();

			//Desenho nave,chama
		if(nave_destruida==0)
			desenha_nave();
		

		//Desenho pontos, nivel e vidas
		sprintf(char_pontos_vidas_nivel,"POINTS: %d ",pontos);
		renderBitmapString(-1000,550, GLUT_BITMAP_HELVETICA_18, char_pontos_vidas_nivel);

		sprintf(char_pontos_vidas_nivel,"LEVEL: %d ",nivel);
		renderBitmapString(-1000,500, GLUT_BITMAP_HELVETICA_18, char_pontos_vidas_nivel);

		sprintf(char_pontos_vidas_nivel,"LIFES: %d ",vidas);
		renderBitmapString(-1000,450, GLUT_BITMAP_HELVETICA_18, char_pontos_vidas_nivel);

		//Desenha Pause quando activa
		if(controlo_pause==1)
			pause();


	}

	//Menu game over
	else if(controlo_menus==2){
		Actual=Inicio;
			while(Inicio!=NULL){
				desenha_asteroides(Actual->tipo,Actual->tamanho,Actual->trans_x,Actual->trans_y);

				if(Actual->Proxima==NULL)
					break;

				Actual=Actual->Proxima;
			}
		//Verificaçao se ha novo highscore
		if(controlo_ficheiro==0){
			descriptor = fopen("Highscore.txt", "r");
			fscanf(descriptor,"%d",&i);
			sprintf(char_pontos_vidas_nivel, "%d", pontos);
			if(pontos>i){
				fclose(descriptor);
				descriptor = fopen("Highscore.txt", "w");
				controlo_pontuacao=1;
				fputs(char_pontos_vidas_nivel,descriptor);
			}
			fclose(descriptor);
			controlo_ficheiro=1;
		}
		

		Desenhar_Texto_2();

		desenha_nave();

		sprintf(char_pontos_vidas_nivel,"POINTS: %d ",pontos);
		renderBitmapString(-1000,550, GLUT_BITMAP_HELVETICA_18, char_pontos_vidas_nivel);

		sprintf(char_pontos_vidas_nivel,"LEVEL: %d ",nivel);
		renderBitmapString(-1000,500, GLUT_BITMAP_HELVETICA_18, char_pontos_vidas_nivel);

	}

	glutSwapBuffers();
}


//Activa variaveis necessarias ao movimento da nave
void teclado_especial(int key, int x, int y){

	if(key==GLUT_KEY_RIGHT && controlo_pause==0)
		controlo_tecla_direita=1;
		
	if(key==GLUT_KEY_LEFT && controlo_pause==0)
		controlo_tecla_esquerda=1;

	if(key==GLUT_KEY_UP && controlo_pause==0)
		controlo_tecla_cima=1;
	
	if(key==GLUT_KEY_DOWN && controlo_pause==0)
		controlo_tecla_baixo=1;
	


}


//Activa quando a tecla pressionada é largada
void teclado_especial_2(int key,int x, int y){
	if(key==GLUT_KEY_RIGHT )
		controlo_tecla_direita=0;
		
	if(key==GLUT_KEY_LEFT )
		controlo_tecla_esquerda=0;

	if(key==GLUT_KEY_UP ){
		controlo_tecla_cima=0;
		controlo_chama=0;
	}
	if(key==GLUT_KEY_DOWN)
		controlo_tecla_baixo=0;

}


//Condiçoes de escape, pause(com P) e enter
void teclado(unsigned char key,int x, int y){

	if(key==27){
		elimina_estruturas();
		exit(0);
	}
	
	if((key==112 || key==80) && controlo_menus==1){
		if(controlo_pause==0){
			controlo_chama=0;
			controlo_pause=1;
		}
		else if(controlo_pause==1)
			controlo_pause=0;
	}

	//O enter vai agir em funçao do menu onde estivermos e se estamos ou nao em jogo
	//Aqui há disparo
	if(key==32 && nave_destruida==0 && controlo_menus==1 && controlo_pause==0){
		if(numero_tiros<=max_tiros){
			//sndPlaySoundA("blaster.wav", SND_ASYNC);		//este som traz breaks ao jogo
			numero_tiros++;
			controlo_criacao_arma=1;
		}
		controlo_arma=1;
	}
	//Selecçao dos menus
	else if(key==32 && controlo_menus==0){
		if(trans_y==-110){
			muda_dados_menu=1;
			sndPlaySoundA("blaster.wav", SND_ASYNC);		//este som traz breaks ao jogo
		}
		else if(trans_y==-230){
			elimina_estruturas();
			exit(0);
		}
	}
	else if(key==32 && controlo_menus==2 && controlo_som==0){
		if(trans_y==-110){
			muda_dados_menu=1;
			sndPlaySoundA("dontfailvader.wav", SND_SYNC);
		}
		else if(trans_y==-230){
			muda_dados_menu=2;
			sndPlaySoundA("faith.wav", SND_SYNC);		
		}
		controlo_som=1;
	}


}


void timer(int value){
glutPostRedisplay();

fisicas();


glutTimerFunc(tempo,timer,1);
}

//Função reshape para janela voltar a posiçao original
void reshape( GLint w, GLint h){

	if( w != tamanhox || h != tamanhoy )
		glutReshapeWindow( tamanhox, tamanhoy);

}

////////////////////////////////////////////////////////////////////////////////
//	Programa Principal /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int main( int argc, char *argv[]){

	
	//Inicializar o GLUT e processar qualquer argumento de comando
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize(tamanhox,tamanhoy);
	glutInitWindowPosition(0,0);

	//Criar a janela de saida
	glutCreateWindow("Star Wars Asteroids");

	init();

	//Registar uma "callback function". é obrigatorio
	glutDisplayFunc(display);

	glutSpecialFunc(teclado_especial);
	glutKeyboardFunc(teclado);
	glutSpecialUpFunc(teclado_especial_2);
	glutReshapeFunc(reshape);
	
	glutTimerFunc(tempo,timer,1);
	//a espera de eventos
	glutMainLoop();

	return EXIT_SUCCESS;
}
