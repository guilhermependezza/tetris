#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>

#define FALSE           0     // Valor usado nas fun��es que deveriam retornar true ou false
#define TRUE            1     // Valor usado nas fun��es que deveriam retornar true ou false
#define TEMPO_ESPERA  900     // Tempo em milissegundos para a pe�a se mover na tela.
#define BLOCO_PREENCHIDO "@"  // Caracter que aparece no bloco preenchido
#define BLOCO_VAZIO      " "  // Caracter que aparece no bloco vazio
#define NUMERO_PECAS 7        // Numero de pe�as do jogo
#define LARGURA_GRADE   10   
#define ALTURA_GRADE    20
#define QTD_BLOCOS_PECA 5 // Largura e altura da matriz que guarda a pe�a: 5x5
#define POS_PREENCHIDA  1 // Valor da posicao na grade quando est� preenchida
#define POS_VAZIA       0 // Valor da posicao na grade quando est� vazia

struct record //struct usada para a grava��o dos recordes
{
	char nome[20];
	int  pontuacao;
};

struct jogoSalvo //struct usada para a grava��o dos jogos
{
	//dados para salvar o estado do jogo
	int grade[LARGURA_GRADE][ALTURA_GRADE];
	int tempoEspera;
	int pontuacaoMudancaNivel;
	int pontuacao;
};

//Prototipos das Fun��es
void DesenhaTela();
void CriaNovaPeca();
int GeraNumeroAleatorio(int inicio, int fim);
void InicializaJogo();
void carregarJogo();
void carregaJogo(int pos);
void mostraRecordes();
void carregaRecordes();
void gravaRecordesArquivo();
void gravaRecorde();
void DesenhaGrade();
void inicializaGrade();
void colocaPecaNaGrade(int x, int y, int peca, int rotacao);
int GameOver();
void deletaLinha(int numLinha);
int deletaLinhasPossiveis();
int BlocoLivre(int x, int y);
int MovimentoPossivel(int x, int y, int peca, int rotacao);
void DesenhaGrade();
int TipoBloco(int peca, int rotacao, int x, int y);
int PosicaoXInicial(int peca, int rotacao);
int PosicaoYInicial(int peca, int rotacao);
void gravaJogo();
void menu();


//Variaveis do jogo
int grade[LARGURA_GRADE][ALTURA_GRADE]; //Tabuleiro
int posicaoX;                           // Posi��o horizontal da pe�a atual.
int posicaoY;                           // Posi��o vertical da pe�a atual.
int tipoPeca;                           // Tipo da pe�a atual
int rotacao;                            // Rota��o da pe�a atual
int tempoEspera = TEMPO_ESPERA;         // Tempo de espera inicial
int pontos = 0;                         // Pontos ganhos
int pontuacaoMudancaNivel = 10000;      // Pontua��o inicial para que o nivel aumente.
record recordes[11];

/*
A variavel pecas armazena as 7 pecas e cada rota��o possivel para cada uma delas.
As pe�as s�o armazendas em uma matriz 5x5.
*/
int pecas[NUMERO_PECAS]
         [4] // numero de rota��es
	     [5] //largura do bloco que cont�m a pe�a
		 [5] //altura do bloco que cont�m a pe�a
		  = {
			  //Peca O
			  {
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,0,2,1,0},
					  {0,0,1,1,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,0,2,1,0},
					  {0,0,1,1,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,0,2,1,0},
					  {0,0,1,1,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,0,2,1,0},
					  {0,0,1,1,0},
					  {0,0,0,0,0}
				  }
			  },
			  //Pe�a I
			  {
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,1,2,1,1},
					  {0,0,0,0,0},
					  {0,0,0,0,0}

				  },
				  {
					  {0,0,0,0,0},
					  {0,0,1,0,0},
					  {0,0,2,0,0},
					  {0,0,1,0,0},
					  {0,0,1,0,0}

				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {1,1,2,1,0},
					  {0,0,0,0,0},
					  {0,0,0,0,0}

				  },
				  {
					  {0,0,1,0,0},
					  {0,0,1,0,0},
					  {0,0,2,0,0},
					  {0,0,1,0,0},
					  {0,0,0,0,0}

				  }
		      },
			  //Pe�a L
			  {
				  {
					  {0,0,0,0,0},
					  {0,0,1,0,0},
					  {0,0,2,0,0},
					  {0,0,1,1,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,1,2,1,0},
					  {0,1,0,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,1,1,0,0},
					  {0,0,2,0,0},
					  {0,0,1,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,1,0},
					  {0,1,2,1,0},
					  {0,0,0,0,0},
					  {0,0,0,0,0}
				  }
			  },
			  //Pe�a J
			  {
				  {
					  {0,0,0,0,0},
					  {0,0,1,0,0},
					  {0,0,2,0,0},
					  {0,1,1,0,0},
					  {0,0,0,0,0}
				  },
			      {
					  {0,0,0,0,0},
					  {0,1,0,0,0},
					  {0,1,2,1,0},
					  {0,0,0,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,1,1,0},
					  {0,0,2,0,0},
					  {0,0,1,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,1,2,1,0},
					  {0,0,0,1,0},
					  {0,0,0,0,0}
				  }
			  },
			  //Pe�a Z
			  {
				  {
					  {0,0,0,0,0},
					  {0,0,0,1,0},
					  {0,0,2,1,0},
					  {0,0,1,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,1,2,0,0},
					  {0,0,1,1,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,1,0,0},
					  {0,1,2,0,0},
					  {0,1,0,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,1,1,0,0},
					  {0,0,2,1,0},
					  {0,0,0,0,0},
					  {0,0,0,0,0}
				  }
			  },
			  //Pe�a S
			  {
				  {
					  {0,0,0,0,0},
					  {0,0,1,0,0},
					  {0,0,2,1,0},
					  {0,0,0,1,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,0,2,1,0},
					  {0,1,1,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,1,0,0,0},
					  {0,1,2,0,0},
					  {0,0,1,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,1,1,0},
					  {0,1,2,0,0},
					  {0,0,0,0,0},
					  {0,0,0,0,0}
				  }
			  },
			  //Pe�a T
			  {
				  {
					  {0,0,0,0,0},
					  {0,0,1,0,0},
					  {0,0,2,1,0},
					  {0,0,1,0,0},
					  {0,0,0,0,0}
				  },
			      {
					  {0,0,0,0,0},
					  {0,0,0,0,0},
					  {0,1,2,1,0},
					  {0,0,1,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,1,0,0},
					  {0,1,2,0,0},
					  {0,0,1,0,0},
					  {0,0,0,0,0}
				  },
				  {
					  {0,0,0,0,0},
					  {0,0,1,0,0},
					  {0,1,2,1,0},
					  {0,0,0,0,0},
					  {0,0,0,0,0}
				  }
			  }

		    };

/*A variavel pecasOffSet guarda o deslocamento necess�rio de cada pe�a para que ela apare�a no lugar correto na tela.
    EX: a pe�a I � representada assim na sua 1� rota��o
		00000
		00000
		01211
		00000
		00000
	Sem o offSet ela j� apareceria na 3� linha da grade do jogo.
*/
int pecasOffSet[NUMERO_PECAS]
               [4] // numero de rota��es
			   [2] // deslocamento x, y das pecas
			   =
				   {
					   // Pe�a O
					   {
						   {-2,-3},
						   {-2,-3},
						   {-2,-3},
						   {-2,-3}
					   },
					   // Pe�a I
					   {
						   {-2,-2},
						   {-2,-3},
						   {-2,-2},
						   {-2,-3}
					   },
					   // Pe�a L
					   {
						   {-2,-3},
						   {-2,-3},
						   {-2,-3},
						   {-2,-2}
					   },
					   // Pe�a J
					   {
						   {-2,-3},
						   {-2,-2},
						   {-2,-3},
						   {-2,-3}
						   
					   },
					   // Pe�a Z
					   {
						   {-2,-3},
						   {-2,-3},
						   {-2,-3},
						   {-2,-2}
					   },
				       // Pe�a S
					   {
						   {-2,-3},
						   {-2,-3},
						   {-2,-3},
						   {-2,-2}
					   },
					   // Pe�a T
					   {
						   {-2,-3},
						   {-2,-3},
						   {-2,-3},
						   {-2,-2}
					   }
				   };

// Zera a grade para o inicio do jogo
void inicializaGrade()
{
	for(int i = 0; i < LARGURA_GRADE; i++)
		for(int j = 0; j < ALTURA_GRADE; j++)
			grade[i][j] = POS_VAZIA;
}

// Armazena pe�a atual na grade do jogo
void colocaPecaNaGrade(int x, int y, int peca, int rotacao)
{
	for(int i1 = x, i2 = 0; i1 < x + QTD_BLOCOS_PECA; i1++, i2++)
	{
		for(int j1 = y, j2 = 0; j1 < y + QTD_BLOCOS_PECA; j1++, j2++)
		{
			//Grava s� os blocos 1(normal) e 2(rota��o)
			if(TipoBloco(peca, rotacao, i2, j2) != 0)
				grade[i1][j1] = POS_PREENCHIDA;
		}
	}
}

// Identifica se o jogo acabou
int GameOver()
{
	for(int i = 0; i < LARGURA_GRADE; i++)
	{
		if(grade[i][0] != POS_VAZIA)
			return TRUE;
	}
	return FALSE;
}

// Deleta uma linha especifica
void deletaLinha(int numLinha)
{
	//Para apagar uma linha x basta mover todas as linhas acima dela uma linha abaixo.
	for(int j = numLinha; j > 0; j--)
	{
		for(int i = 0; i < LARGURA_GRADE; i++)
		{
			grade[i][j] = grade[i][j-1];
		}
	}
}

//Deleta todas as linhas possiveis e retorna o numero de linhas retornadas.
int deletaLinhasPossiveis()
{
	int contador = 0;

	for(int j = 0; j < ALTURA_GRADE; j++)
	{
		int i = 0;
		while(i < LARGURA_GRADE)
		{
			if(grade[i][j] != POS_PREENCHIDA) break; // quando achar uma posicao na linha n�o preenchida para os testes e vai pra proxima linha.
			i++;
		}

		if(i == LARGURA_GRADE)
		{
			deletaLinha(j);
			contador++;
		}
	}
	return contador;
}

// Verifica se um bloco na grade est� livre.
int BlocoLivre(int x, int y)
{
	if(grade[x][y] == POS_VAZIA)
		return TRUE;
	return FALSE;
}

//Verifica se � possivel fazer o movimento desejado comparando a grade 5x5 onde a pe�a se encontra com os blocos j� armazenados na grade e os limites da grade.
int MovimentoPossivel(int x, int y, int peca, int rotacao)
{
	for (int i1 = x, i2 = 0; i1 < x + QTD_BLOCOS_PECA; i1++, i2++)
	{
		for (int j1 = y, j2 = 0; j1 < y + QTD_BLOCOS_PECA; j1++, j2++)
		{	
			//Verifica se a pe�a est� fora dos limites da grade.
			if (i1 < 0 			         || 
				i1 > LARGURA_GRADE  - 1  ||
				j1 > ALTURA_GRADE   - 1)
			{
				if (TipoBloco(peca, rotacao, i2, j2) != 0)
					return FALSE;		
			}

			// Verifica se a pe�a colidiu com algum bloco j� armazendo na grade.
			if (j1 >= 0)	
			{
				if ((TipoBloco (peca, rotacao, i2, j2) != 0) &&
					(!BlocoLivre (i1, j1)))
					return FALSE;
			}
		}
	}

	// Sem colis�o
	return TRUE;
}

//Retorna o tipo do bloco na Peca: 0 = vazio, 1 = bloco normal, 2 = bloco de rota��o
int TipoBloco(int peca, int rotacao, int x, int y)
	{
		return pecas[peca][rotacao][x][y];
	}

//Retorna o OffSet horizontal para que a pe�a seja desenhada corretamente
int PosicaoXInicial(int peca, int rotacao)
	{
		return pecasOffSet[peca][rotacao][0];
	}

//Retorna o OffSet vertical para que a pe�a seja desenhada corretamente
int PosicaoYInicial(int peca, int rotacao)
	{
		return pecasOffSet[peca][rotacao][1];
	}

//Desenha tudo o que � preciso na tela principal do jogo( grade e pontua��o ).
void DesenhaTela()
{
	//Emite um comando para limpar a tela do console.
	system("cls");
	DesenhaGrade();

	printf("\nPontuacao: %d", pontos);
}

// Cria nova pe�a
void CriaNovaPeca()
{
	tipoPeca = GeraNumeroAleatorio(0,6);
	rotacao  = GeraNumeroAleatorio(0,3);
	posicaoX = (LARGURA_GRADE / 2) + PosicaoXInicial(tipoPeca, rotacao);
	posicaoY = PosicaoYInicial(tipoPeca, rotacao);
}

// Gira pe�a para direita
void GiraDireita()
{
	int rot = rotacao + 1;

	if(rot == 4) rot = 0; // Se a rota��o for 4 volta do inicio do ciclo de rota��es.

	//Se for possivel, gire para a direita
	if(MovimentoPossivel(posicaoX, posicaoY, tipoPeca, rot))
		rotacao = rot;
}

// Gira pe�a para esquerda
void GiraEsquerda()
{
	int rot = rotacao - 1;

	if(rot == -1) rot = 3; // Se a rota��o for -1 volta do inicio do ciclo de rota��es.

	//Se for possivel, gire para a esquerda
	if(MovimentoPossivel(posicaoX, posicaoY, tipoPeca, rot))
		rotacao = rot;
}

// Gera um numero aleat�rio no intervalo entre inicio e fim para uso na gera��o de novas pe�as.
int GeraNumeroAleatorio(int inicio, int fim)
{
	return rand()%(fim - inicio + 1) + inicio;
}

// Inicializa a gera��o dos numeros aleat�rios e a primeira pe�a
void InicializaJogo()
{
	//Inicializa a gera��o de numeros aleatorios.
	srand((unsigned int)time(NULL));

	//Primeira Pe�a
	CriaNovaPeca();
}

// Retorna o tempo passado em milisegundos
int tempoMilisegundos()
{
	clock_t time = clock();
	int segundos = time * CLOCKS_PER_SEC;
	int milisegundos = segundos / 1000;
	return milisegundos;
}

// Faz com que o programa espere pelo tempo desejado
void espere(float segundos)
{
	clock_t tempo = (short)(clock() + segundos * CLOCKS_PER_SEC);
	while (clock() < tempo);
}

// Fun��o que verifica se na posi��o x,y da grade existe uma alguma pe�a para que ela seja desenhada.
int temPeca(int x, int y)
{
	int retorno = 0;
	int posicaoXNaPeca = x - posicaoX;
	int posicaoYNaPeca = y - posicaoY;
	
	if(posicaoXNaPeca >= 0 && posicaoXNaPeca < QTD_BLOCOS_PECA && posicaoYNaPeca >= 0 && posicaoYNaPeca < QTD_BLOCOS_PECA)
		if(pecas[tipoPeca][rotacao][posicaoXNaPeca][posicaoYNaPeca] != POS_VAZIA)
			retorno = 1;

	return retorno;
}

// Desenha o tabuleiro
void DesenhaGrade()
{
	//Desenha cada elemento da grade
	for(int j = 0; j < ALTURA_GRADE; j++)
		{
			//Borda to tabuleiro
			printf("||");
			for(int i = 0; i < LARGURA_GRADE; i++)
			{
				if(grade[i][j] != POS_VAZIA || temPeca(i, j) != 0)
					printf(BLOCO_PREENCHIDO);
				else
					printf(BLOCO_VAZIO);
			}
			//Borda to tabuleiro
			printf("||\n");
		}
	printf("==============\n");
}

// Fun��o principal do jogo. Se jogoSalvo = 0 inicia um novo jogo, sen�o carrega um jogo salvo.
void jogar(int jogoSalvo)
{
	int tempo1 = tempoMilisegundos(); // tempo inicial, atualizado sempre que o tempo de espera expira.
	int tempo2 = 0;                   // tempo final, usado para verificar se o tempo expirou.

	//Carrega jogo se necess�rio.
	if(jogoSalvo == 0)
	{
		inicializaGrade();
		InicializaJogo();
	}
	else
	{
		carregaJogo(jogoSalvo - 1);
	}

	// Variavel que indica se � necess�rio desenhar a tela novamente, caso tenha alguma altera��o.
	int precisaDesenhar = 0;

	// Enquanto o jogo n�o acabar, jogue...
	while(!GameOver())
	{
		if(precisaDesenhar == 1)
		{
			DesenhaTela();
			precisaDesenhar = 0;
		}

		//------------------------------------------------------------------------------------------------------------------------

		//Tratamento das teclas direcionais.
		if(GetAsyncKeyState(VK_LEFT)) // Move Esquerda
		{
			if(MovimentoPossivel(posicaoX - 1, posicaoY, tipoPeca, rotacao))
				posicaoX--;
			precisaDesenhar = 1;
		}

		if(GetAsyncKeyState(VK_RIGHT)) // Move Direita
		{
			if(MovimentoPossivel(posicaoX + 1, posicaoY, tipoPeca, rotacao))
				posicaoX++;
			precisaDesenhar = 1;
		}

		if(GetAsyncKeyState(VK_UP)) // Desce pe�a at� onde for poss�vel
		{
			while(MovimentoPossivel(posicaoX, posicaoY + 1, tipoPeca, rotacao))
				posicaoY++;
			colocaPecaNaGrade(posicaoX, posicaoY, tipoPeca, rotacao);
			precisaDesenhar = 1;
		}

		if(GetAsyncKeyState(VK_DOWN)) // Desce 1 bloco
		{
			if(MovimentoPossivel(posicaoX, posicaoY + 1, tipoPeca, rotacao))
				posicaoY++;
			precisaDesenhar = 1;
		}
		//Fim teclas direcionais.

		//------------------------------------------------------------------------------------------------------------------------

		//Teclas de giro
		if(GetAsyncKeyState('z') || GetAsyncKeyState('Z')) // Gira Esquerda
		{
			GiraEsquerda();
			precisaDesenhar = 1;
		}

		if(GetAsyncKeyState('x') || GetAsyncKeyState('X')) // Gira Direita
		{
			GiraDireita();
			precisaDesenhar = 1;
		}
		//Fim teclas de giro

		//termina o jogo
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			gravaRecorde();
			break;
		}

		//Salva o jogo
		if(GetAsyncKeyState('s') || GetAsyncKeyState('S'))
		{
			gravaJogo();
			break;
		}

		//Move pe�a para baixo quando atinge o tempo ou coloca a pe�a na grade se n�o tem mais movimento vertical possivel.
		tempo2 = tempoMilisegundos();

		if(tempo2 - tempo1 > tempoEspera)
		{
			if(MovimentoPossivel(posicaoX, posicaoY + 1, tipoPeca, rotacao))
			{
				posicaoY++;
				precisaDesenhar = 1;
			}
			else
			{
				colocaPecaNaGrade(posicaoX, posicaoY, tipoPeca, rotacao);
				int  linhas = deletaLinhasPossiveis();
				if(linhas > 0)
				{
					// Calcula os pontos
					int pontosGanhos = 10 * pow(10.0, linhas);

					// Acumula os pontos
					pontos += pontosGanhos;

					// Se atingiu a pontua��o para mudan�a de nivel, acelera o jogo
					if(pontos > pontuacaoMudancaNivel)
					{
						tempoEspera -= 30;

						// Aumenta a pontua��o para mudan�a de nivel.
						pontuacaoMudancaNivel += 10000;
					}
				}

				// Nova pe�a
				CriaNovaPeca();

				//Sinaliza que precisa desenhar a tela novamente.
				precisaDesenhar = 1;
			}

			//Atualiza o tempo inicial.
			tempo1 = tempoMilisegundos();
		}
		// Fim move para baixo.

		// Espera o tempo necess�rio.
		espere(tempoEspera);
	}
}

void menu()
{
	char escolha;

	// Menu.
	printf("            TETRIS           \n\n");
	printf("***Escolha uma das opcoes***\n");
	printf("J - Jogar\n");
	printf("L - Carrega Jogo\n");
	printf("R - Recordes\n");
	printf("S - Sair\n");

	fflush(stdin);
	escolha = getchar();

	
	switch(escolha)
	{
		case 'j':
		case 'J':
			jogar(0);
			break;

		case 'l':
		case 'L':
			carregarJogo();
			break;

		case 'r':
		case 'R':
			mostraRecordes();
			break;

		case 's':
		case 'S':
			break;

		default:
			printf("Op��o Invalida!\n");
	}
}

// rotina chamada pelo menu onde o jogador pode escolher um jogo para ser carregado.
void carregarJogo()
{
	jogoSalvo jogos[50];
	int count = 0;

	// Tenta abrir o arquivo onde s�o gravados os jogos
	FILE* arquivo = fopen("save.bin", "r+b");

	// Se o arquivo n�o existir, avisa o jogador que ser� iniciado um novo jogo.
	if(arquivo == NULL)
	{
		printf("Nao ha jogo para ser carregado!\n");
		printf("Voce ira comecar um novo jogo!\n");
		getch();
		jogar(0);
	}
	else
	{
		// Le todos os jogos gravados.
		while(fread(&jogos[count], sizeof(jogoSalvo), 1, arquivo))
		{
			count++;
		}

		// exibe na tela e espera que o jogador escolha um.
		for(int i = 0; i < count; i++)
		{
			printf("%d - Pontos: %d - Tempo Espera: %d\n", i + 1, jogos[i].pontuacao, jogos[i].tempoEspera);
		}

		int opcao;
		fflush(stdin);
		scanf("%d", &opcao);

		// Se for uma op��o v�lida, carrega o jogo.
		if(opcao >= 1 && opcao <= count)
			jogar(opcao);
	}
}

// carrerga um jogo especifico.
void carregaJogo(int pos)
{
	jogoSalvo jogo;

	// abre o arquivo
	FILE* arquivo = fopen("save.bin", "r+b");

	//Posiciona o ponteiro na posi��o correta, le a struct e fecha o arquivo.
	fseek(arquivo, pos * sizeof(jogoSalvo), SEEK_SET);
	fread(&jogo, sizeof(jogoSalvo), 1, arquivo);
	fclose(arquivo);

	// carrega as variaveis do jogo
	for(int i = 0; i < LARGURA_GRADE; i++)
		for(int j = 0; j < ALTURA_GRADE; j++)
			grade[i][j] = jogo.grade[i][j];

	pontos                = jogo.pontuacao;
	pontuacaoMudancaNivel = jogo.pontuacaoMudancaNivel;
	tempoEspera           = jogo.tempoEspera;
}

//Fun��es necessarias para a ordena��o dos recordes

//Assinatura da fun��o de compara��o
typedef int (*compfn)(const void*, const void*);

//Fun��o compara��o
int compare(record *rec1, record *rec2)
{
	if(rec1->pontuacao < rec2->pontuacao)
		return -1;
	if(rec1->pontuacao > rec2->pontuacao)
		return 1;
	return 0;
}
//Fim fun��es compara��o

// Fun��o chamada quando o jogador sai pressionando ESC. O jogo tenta salvar a pontua��o dele no ranking.
void gravaRecorde()
{
	carregaRecordes();

	// Limpa a tela.
	system("cls");

	// Pega o nome do jogador
	printf("Digite seu nome:");
	char nome[20];

	fflush(stdin);
	scanf("%s", nome);

	// Carrega uma struct record com os dados.
	record rec;
	strcpy(rec.nome, nome);
	rec.pontuacao = pontos;

	// Coloca a pontua��o em ultimo lugar, para ordenar depois.
	recordes[10] = rec;

	// Ordena
	qsort((void *) recordes,  //Array que ser� ordenado
		  11,                 //Tamanho do array
		  sizeof(record),     //Tamanho da struct que o array cont�m
		  (compfn)compare);   //Fun��o respons�vel pela compara��o.

	// Grava no arquivo.
	gravaRecordesArquivo();
}

// Fun��o que grava os recordes no arquivo highscore.bin.
void gravaRecordesArquivo()
{
	//Sobrescreve o arquivo
	FILE* arquivo = arquivo = fopen("highscore.bin", "w+b");

	//Grava os recordes em ordem decrescente.
	for(int i = 10; i > 1; i--)
	{
		fwrite(&recordes[i], sizeof(record), 1, arquivo);
	}

	fclose(arquivo);
}

// Carrega os recordes do arquivo em um vetor de structs record.
void carregaRecordes()
{
	FILE* arquivo = arquivo = fopen("highscore.bin", "r+b");

	//Se o arquivo n�o existir retorna
	if(arquivo == NULL)
	{
		return;
	}

	int count = 0;

	//Le todos os recordes.
	while(fread(&recordes[count], sizeof(record), 1, arquivo))
		count++;

	fclose(arquivo);
}

// Mostra os recordes na tela.
void mostraRecordes()
{
	carregaRecordes();

	system("cls");

	for(int i = 0; i <= 9; i++)
	{
		printf("%2d - %-20s - %7d\n", i+1, recordes[i].nome, recordes[i].pontuacao);
	}
}

// Grava o estado do jogo,  quando � pressionado a tecla S durante o jogo.
void gravaJogo()
{
	jogoSalvo jogo;
	
	for(int i = 0; i < LARGURA_GRADE; i++)
		for(int j = 0; j < ALTURA_GRADE; j++)
			jogo.grade[i][j] = grade[i][j];

	jogo.pontuacao             = pontos;
	jogo.pontuacaoMudancaNivel = pontuacaoMudancaNivel;
	jogo.tempoEspera           = tempoEspera;

	FILE* arquivo = fopen("save.bin", "r+b");
	if(arquivo == NULL)
	{
		arquivo = fopen("save.bin", "w+b");
	}

	fseek(arquivo, 0, SEEK_END);
	fwrite(&jogo, sizeof(jogoSalvo), 1, arquivo);
	fclose(arquivo);
}

// Fun��o de entrada do programa. Apenas chama o menu.
void main()
{
	menu();

	getch();
}