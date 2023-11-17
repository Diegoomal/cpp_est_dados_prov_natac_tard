// Declara��es da Escola Natacao
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstring>
#include <ctime>
#endif

using namespace std;

#ifdef _WIN32
#define PAUSA										system("pause")
#define LIMPA_TELA									system("cls")
#else
#define PAUSA \
    do { \
        printf("Pressione Enter para continuar..."); \
        getchar(); \
    } while(0)
#define LIMPA_TELA \
    do { \
        system("clear"); \
    } while(0)
#endif

// Op��es do menu
#define MATRICULAR_ALUNO							'M'		
#define LISTAR_ALUNOS_DE_UM_PERIODO					'P'
#define LISTAR_TODOS_OS_ALUNOS						'T'
#define CANCELAR_MATRICULA							'C'
#define LANCAR_DESPESA_EM_UM_ALUNO					'D'
#define CONSULTAR_UM_DADO_ALUNO						'U'
#define LISTAR_POR_ARGUMENTO						'A'
#define SAIR_DO_PROGRAMA							'S'
// quantidades de raias
#define QTDE_MIN_RAIAS								5	// Qtde minima de raias na piscina
#define QTDE_MAX_RAIAS								10	// Qtde maxima de raias na piscina
// tabela de transacoes
#define LANCHONETE									1
#define ACESSORIOS									2
#define HIGIENE										3

// tabela de periodos								
#define QTDE_PERIODOS								4
#define MANHA										1
#define TARDE										2
#define VESPERTINO									3
#define NOITE										4
// Comentario:
//	A escola de natacao tem uma piscina que funciona em tres periodos (manha, tarde, noite)
//	A quantidade de raias que a piscina tem sera informado pelo operador na main.
//	Cada raia pode ter um e apenas um aluno matriculado

// tabela de preco da mensalidade
#define	MENSALIDADE_BASICA							120.00
#define DESCONTO_MAIS_UM_MESMO_SOBRENOME			10				// 10%
#define DESCONTO_MAXIMO								40				// 40%
// Comentario:
//		O primeiro aluno da familia (Sobrenome) paga R$ 120.00
//		O segundo membro da mesma familia paga 120.00 - 10%
//		O terceiro membro da mesma familia paga 120.00 - 20%
//		O quarto membro da mesma familia para 120.00 - 30%
//		O quinto e os demais membros da familia pagam 120.00 - 40%

// struct dos dados do aluno
typedef struct tagALUNO
{
	char cSobrenome[21],						// sobrenome ou nome de familia
		cPrenome[31];							// prenome que pode ter brancos entre eles
	double dMensalidade;						// valor da mensalidade
} ALUNO;

// struct de cada transa��o aplicada a cada raia da piscina em um dado periodo
typedef struct tagTRANSACAO
{
	int nTipo;									// tipo da transacao conforme tabela de transacoes
	double dValor;								// valor da transacao
	tagTRANSACAO *ptrProxima;					// ponteiro para proxima transacao
} TRANSACAO;			

// struct de cada raia da escola de natacao
typedef struct tagRAIA							
{
	int	nPeriodo,								// periodo conforme tabela de periodos	
		nNumeroDaRaia;							// numero da raia da piscina (1, 2, 3 ..... 
	bool	flgLivreOuOcupado;					// true = ocupado, false = livre.
	ALUNO	stAluno;							// dados do aluno associado ao periodo e a 
												// raia da piscina
	double	dValorTotalTransacoes;				// valor total das transacoes
	TRANSACAO *ptrPrimeira,						// ponteiro para a primeira transacao
		*ptrUltima;								// ponteiro para a ultima transacao
} RAIA;

// classe da Escola Natacao 
class clEscolaNatacao
{
	
	// codificar atributos e metodos necessarios para as atividades impostas pelo menu
	private:
		// aqui sera
		int	i, j,									// variaveis genericas
			nSobrenome,
			nSalvaQtdeRaia;							// vai receber a quantidade de raias que tem a piscina (momento da construcao).
		char cTrabalho[12];
		RAIA *ptrVetRaias,							// ponteiro para o vetor de raias
			*ptrVetSalva;							// ponteiro de salvaguarda do vetor de raias
	
	public:

		// Codificar o construtor recebendo a quantidade raias que a piscina tem
		// Este dado sera informado no momento da construcao do objeto
		//	Parametros:
		//		Entrada: int nQtdeRaias - quantidade de raias informado pelo instanciador da
		//									classe
		//				 bool *flgAlocacaoOK - endereco para receber true - se foi tudo ok
		//									ou false se alocacao dinamica falhou
		clEscolaNatacao(int nQtdeRaias, bool *flgAlocacaoOK)
		{
			// <<<<<< ***** >>>>>>
			// Salvar a quantidade de raias para uso futuro
			// Fazer a alocacao dinamica do vetor de raias considerando que sao QTDE_PERIODOS 
			//	e cada periodo tem nQtdeRaias.
			// Inicializar o vetor de raias indicando o periodo, numero da raia (1, 2, 3...)
			//	indicar que a raia esta livre e nao tem nenhuma transacao realizada....

			//	Se houver problema na alocacao dinamica (insuficiencia de memeria)
			//	mover false para o endereco apontado por flgAlocacaoOK	
			//	Em cada periodo as raias serao numeradas de 1 a nQtdeRaias.
			//	Inicializar cada raia indicando o seu periodo e dentro do periodo seu numero
			//		e indicar que cada raia esta livre
			//	Indicar que nenhuma raia tem a lista ligada de transacao
			// Mover true para o endereco indicado em flgAlocacaoOK
		
			nSalvaQtdeRaia = nQtdeRaias;															// Salva a quantidade de raias
			ptrVetRaias = new RAIA[nQtdeRaias * QTDE_PERIODOS];										// Faz alocacao do vetor de raias na mem�ria
			// Testar a quantidade de memoria disponivel
			if(ptrVetRaias == NULL)																	
			{	// sem memoria disponivel
				*flgAlocacaoOK = false;																// avisa que esta sem espaco
				return;																				// cai fora do programa
			}
			else
			{
				// matriz que passara por todos os periodos e raias deixando tudo em estado inicial (zerado)
				for(i = 0; i < QTDE_PERIODOS; i++)													// Loop que passa pela quantidade de Periodos
					for(j = 0; j < nQtdeRaias; j++)													// Loop que passa pela quantidade de Raias
					{
						ptrVetRaias[(i * nQtdeRaias) + j].dValorTotalTransacoes = 0.0;				// 
						ptrVetRaias[(i * nQtdeRaias) + j].stAluno.dMensalidade = 0.0;				// Lista de Mensalidades vazia
						ptrVetRaias[(i * nQtdeRaias) + j].flgLivreOuOcupado = false;				// raia livre
						ptrVetRaias[(i * nQtdeRaias) + j].nNumeroDaRaia = j + 1;					// Numero da raia
						ptrVetRaias[(i * nQtdeRaias) + j].nPeriodo = i + 1;							// Numero do periodo
						
					}
				*flgAlocacaoOK = true;																// tudo OK
			}
		}

		// Metodo para matricular um aluno em um dado periodo
		//	Parametros:
		//		Entrada: int nPeriodo - periodo desejado para matricula (1 ou 2 ou 3)
		//				 ALUNO *ptrAluno - endereco de uma struct que contem nome e sobrenome
		//						do aluno...
		//		Retorno: o n�mero da raia que o aluno foi matriculado ou zero se nao havia
		//				nenhuma raia livre no periodo.....
		int MatricularAluno(int nPeriodo, ALUNO *ptrAluno)
		{
			// <<<<<< ***** >>>>>>
			// Este m�todo ir� procurar a primeira raia livre do per�odo e vai associar
			//	o aluno � raia livre encontrada.

			// Se n�o houver nenhuma raia livre no per�odo o m�todo retorna zero e caso
			//	contr�rio retornar� o n�mero da raia que foi encontrada livre.
			// O ptrAluno aponta para uma struct da main que cont�m sobrenome e prenome e
			//	o valor da mensalidade ser� calculado em fun��o do n�mero de membros da
			//	mesma fam�lia matriculados na escola
			// Se houver algum aluno matriculado em qualquer per�odo com o mesmo sobrenome,
			//	o valor da mensalidade ter� desconto conforme tabela de descontos
			// Se for o primeiro membro da fam�lia o valor da mensalidade � o valor b�sico
			//	Zerar o total de transa��es e indicar que n�o tem nenhuma transa��o na
			//		lista ligada
			//	Indicar que a raia est� ocupada
			// ... codificar a partir daqui
			for(i = 0; i < nSalvaQtdeRaia; i++)
				if(ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].flgLivreOuOcupado == false)									// Raia est� desocupada ?
				{ 
					//
					strcpy(ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].stAluno.cPrenome, ptrAluno->cPrenome);				// Copia o nome aluno para estrutura de raia
					strcpy(ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].stAluno.cSobrenome, ptrAluno->cSobrenome);			// Copia o sobrenome aluno para estrutura de raia
					ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].flgLivreOuOcupado = true;									// Indica que est� ocupada
					ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].nPeriodo = nPeriodo;
					ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].dValorTotalTransacoes = 0.0;									// Zera o valor total de transa��es anteriores			
					//
					for(j = 0, nSobrenome = 0; j < (nSalvaQtdeRaia * QTDE_PERIODOS); j++)											// Loop para verificar alunos com memso sobrenome
						if(strcmp(ptrAluno->cSobrenome, ptrVetRaias[j].stAluno.cSobrenome) == 0)									// Mesmos Sobrenomes ?
							nSobrenome++;
					//
					if(nSobrenome == 1)
						ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].stAluno.dMensalidade = ptrAluno ->dMensalidade = MENSALIDADE_BASICA;
				
					else if(nSobrenome == 2)
						ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].stAluno.dMensalidade = ptrAluno ->dMensalidade =
						MENSALIDADE_BASICA - ((MENSALIDADE_BASICA * DESCONTO_MAIS_UM_MESMO_SOBRENOME) / 100);						// Desconto de 10%

					else if(nSobrenome == 3)
						ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].stAluno.dMensalidade = ptrAluno ->dMensalidade =
						MENSALIDADE_BASICA - ((MENSALIDADE_BASICA * (DESCONTO_MAIS_UM_MESMO_SOBRENOME + 10) / 100));				// Desconto de 20%
				
					else if(nSobrenome == 4)
						ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].stAluno.dMensalidade = ptrAluno ->dMensalidade =
						MENSALIDADE_BASICA - ((MENSALIDADE_BASICA * (DESCONTO_MAIS_UM_MESMO_SOBRENOME + 20) / 100));				// Desconto de 30%
				
					else if(nSobrenome >= 5)
						ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].stAluno.dMensalidade = ptrAluno ->dMensalidade =
						MENSALIDADE_BASICA - ((MENSALIDADE_BASICA * DESCONTO_MAXIMO) / 100);										// Desconto m�ximo

					return ptrVetRaias[((nPeriodo - 1) * nSalvaQtdeRaia) + i].nNumeroDaRaia;												// Retorna o numero da raia
				} 
		}//metodo

		// Metodo para listar os alunos de um dado per�odo
		//	Periodo: 1(manha), 2(tarde) e 3(noite)
		void ListarUmPeriodo(int nPeriodo)
		{
			// <<<<<< ***** >>>>>>
			// Este m�todo ir� listar os alunos que est�o matriculados no per�odo
			// Formato:
			//		Alunos do periodo: xxxxxx (escrever o per�odo: "manha", "tarde" ou "noite")
			//		Nome: xxxxxxxxxxxxxxxx
			//		Sobrenome: xxxxxxxxxx
			//		Raia: nn  Valor Mensalidade: zzzzz.zz
			//		No final da listagem exibir:
			//		Qtde total de alunos: nn
			if(nPeriodo == MANHA)
				cout << "Manha";
			else if(nPeriodo == TARDE)
				cout << "Tarde";
			else if(nPeriodo == VESPERTINO)
				cout << "Vespertino";
			else
				cout << "Noite";
		
			cout << "\n\tAlunos do periodo: " << cTrabalho << endl << endl;
			nSobrenome = 0;
			for(i = 0; i < QTDE_PERIODOS; i++)			// Loop para quantidade de Periodos
			{	
				for(j = 0; j < nSalvaQtdeRaia; j++)		// Loop para quantidade de Raias
				{
					if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].flgLivreOuOcupado == true && ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == nPeriodo)
					{
						cout << "Nome: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cPrenome << endl;
						cout << "Sobrenome: "	<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cSobrenome << endl;
						cout << "Raia: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].nNumeroDaRaia
							 << " Valor Mensalidade: " << ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.dMensalidade << endl << endl;
						nSobrenome++;
					}
				}
			}
			cout << "\nQuantidade total de alunos no periodo: " << nSobrenome << endl << endl;
			PAUSA;

		}
		// M�todo para listar todos os per�odos 

		void ListarTodosPeriodos()
		{
			// <<<<<< ***** >>>>>>
			// Este m�todo ir� listar os alunos matriculados nos tr�s periodos no
			// mesmo layout do m�todo anterior 
			// No final da listagem exibir:
			//		Qtde total de alunos em todos periodos: nnn
			nSobrenome = 0;
			cout << "\n\tListagem de todos os alunos" << endl;
			for(i = 0; i < QTDE_PERIODOS; i++)			// Loop para quantidade de Periodos
				for(j = 0; j < nSalvaQtdeRaia; j++)		// Loop para quantidade de Raias
					if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].flgLivreOuOcupado == true)
					{
						if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == MANHA)
							cout << "Manha";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == TARDE)
							cout << "Tarde";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == VESPERTINO)
							cout << "Vespertino";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == NOITE)
							cout << "Noite";

						cout << "Nome: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cPrenome << endl;
						cout << "Sobrenome: "	<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cSobrenome << endl;
						cout << "Raia: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].nNumeroDaRaia << endl;
						cout << " Valor Mensalidade: " << ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.dMensalidade << endl << endl;
						nSobrenome++;
					}
			cout << "\nQuantidade total de alunos: " << nSobrenome << endl << endl;
			PAUSA;
		}//metodo

		// M�todo para cancelar matr�cula
		//	Par�metros:
		//		Entrada: int nPeriodo - periodo 1 ou 2 ou 3
		//				 int nRaia - n�mero da raia dentro do per�odo
		//		Retorno: true - se a raia tinha aluno matriculado e
		//				 false - se a a raia estava livre...
		bool CancelarMatricula(int nPeriodo, int nRaia)
		{
			// <<<<<< ***** >>>>>>
			// Se a raia estiver desocupada no per�odo informado, retornar false
			// Informar:
			//		Nome: xxxxxxxxxxxxxxxx
			//		Sobrenome: xxxxxxxxx
			//		Periodo: n Raia: nn
			//		Matricula cancelada!
			//	Retornar true
			cout << "\n\tListagem de todos os alunos" << endl;
			for(i = 0; i < QTDE_PERIODOS; i++)													// Loop para quantidade de Periodos
				for(j = 0; j < nSalvaQtdeRaia; j++)												// Loop para quantidade de Raias
					if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].flgLivreOuOcupado == true)
					{
						ptrVetRaias[(i * nSalvaQtdeRaia) + j].dValorTotalTransacoes = 0.0;		// zera as tranza��es
						ptrVetRaias[(i * nSalvaQtdeRaia) + j].flgLivreOuOcupado = true;			// deixa como livre a raia
					}
			PAUSA;
			return true;																		// apenas para n�o dar erro
		}

		// M�todo para lan�ar despesa para um dado aluno
		//	Par�metros:
		//		Entrada: int nPeriodo - periodo 1 ou 2 ou 3
		//				 int nRaia - raia dentro do per�odo
		//				 int nTipo - tipo de despesa (conforme .h)
		//				 double dValor - valor da despesa
		bool LancarDespesa(int nPeriodo, int nRaia, int nTipo, double dValor)
		{	
			// <<<<<< ***** >>>>>>
			// Se a raia estiver desocupada no per�odo, retornar false
			// Somar o dValor no total de transa��es da raia e inserir esta
			// transa��o na lista ligada....
			// retornar true 
			for(i = 0; i < QTDE_PERIODOS; i++)														// Loop para quantidade de Periodos
				for(j = 0; j < nSalvaQtdeRaia; j++)													// Loop para quantidade de Raias
				{
					if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == nPeriodo
						&& ptrVetRaias[(i * nSalvaQtdeRaia) + j].nNumeroDaRaia == nRaia)
					{
						ptrVetRaias[(i * nSalvaQtdeRaia) + j].dValorTotalTransacoes += dValor;
						return true;
					}
					else
						return false;																// se estiver vazia
				}//for
		}

		// M�todo para consultar um dado aluno: os seus dados e suas despesas
		//	Par�metros:
		//		Entrada: int nPeriodo - per�odo 1, 2 ou 3
		//				 int nRaia - n�mero raia dentro do per�odo
		bool ConsultarAluno(int nPeriodo, int nRaia)
		{
			// <<<<<< ***** >>>>>>
			// Se a raia estiver desocupada retornar false
			// Exibir o seguinte:
			//		Nome: xxxxxxxxxxxxxxx
			//		Sobrenome: xxxxxxxx
			//		Raia: nn	Valor Mensalidade: zzzzz.zz
			//		Total transacoes: zzzzzz.zz
			//			Tipo: x		Valor: zzzz.zz		(lista ligada de transa��es)
			//											(listar todas as transa��es)
			//		Retornar true
			for(i = 0; i < QTDE_PERIODOS; i++)														// Loop para quantidade de Periodos
				for(j = 0; j < nSalvaQtdeRaia; j++)													// Loop para quantidade de Raias
				{
					if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == nPeriodo
						&& ptrVetRaias[(i * nSalvaQtdeRaia) + j].nNumeroDaRaia == nRaia)
					{
						if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == MANHA)
							cout << "Manha";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == TARDE)
							cout << "Tarde";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == VESPERTINO)
							cout << "Vespertino";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == NOITE)
							cout << "Noite";

						cout << "Nome: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cPrenome << endl;
						cout << "Sobrenome: "	<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cSobrenome << endl;
						cout << "Raia: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].nNumeroDaRaia << endl;
						cout << " Valor Mensalidade: " << ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.dMensalidade << endl << endl;
						PAUSA;
						LIMPA_TELA;
						return true;																// raia ocupada
					}
					else
						return false;																// se estiver vazia
				}
		}

		// M�todo que vai listar todos os alunos que tem o mesmo argumento
		//	no seu sobrenome
		//	Par�metros:
		//		Entrada: char *ptrArgumento - ponteiro para o argumento de busca
		//										que pode ser uma parte ou o todo do
		//										sobrenome
		void ListarSobrenomesComArgumento(char *ptrArgumento)
		{
			// <<<<<< ***** >>>>>>
			// Codificar um loop para percorrer todas as raias em todos o periodos
			// Ignorar as raias que estiverem livres
			// Verificar se o sobrenome contem o argumento que foi passado ou se �
			//	exatamente igual ao argumento
			//	Codificar um cabe�alho contendo "\tListagem dos alunos pelo argumento: xxxxxxxxx
			//	Listar cada aluno contendo o seguinte:
			//		Nome: xxxxxxxxxxxxxxx Sobrenome: xxxxxxxx
			//		Periodo: X Raia: nn	
			//  No final indicar quantos alunos foram encontrados com este argumento:
			//		Foram listados: XXX alunos
			for(i = 0; i < QTDE_PERIODOS; i++)														// Loop para quantidade de Periodos
				for(j = 0; j < nSalvaQtdeRaia; j++)													// Loop para quantidade de Raias
					if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cSobrenome == ptrArgumento)
					{
						if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == MANHA)
							cout << "Manha";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == TARDE)
							cout << "Tarde";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == VESPERTINO)
							cout << "Vespertino";
						else if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].nPeriodo == NOITE)
							cout << "Noite";

						cout << "Nome: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cPrenome 
							<< "Sobrenome: "	<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cSobrenome << endl;
						cout << "Raia: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].nNumeroDaRaia << endl;
						cout << " Valor Mensalidade: " << ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.dMensalidade << endl << endl;
						nSobrenome++;
					}
			PAUSA;
		}

		// m�todo para a listagem de todos os alunos
		void ListarTodosOsAlunos()
		{
			nSobrenome = 0;
			cout << "\n\tListagem de todos os alunos" << endl;
			for(i = 0; i < QTDE_PERIODOS; i++)														// Loop para quantidade de Periodos
				for(j = 0; j < nSalvaQtdeRaia; j++)													// Loop para quantidade de Raias
					if(ptrVetRaias[(i * nSalvaQtdeRaia) + j].flgLivreOuOcupado == true)
					{
						cout << "Nome: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cPrenome << endl;
						cout << "Sobrenome: "	<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.cSobrenome << endl;
						cout << "Periodo: "		<< cTrabalho << endl;
						cout << "Raia: "		<< ptrVetRaias[(i * nSalvaQtdeRaia) + j].nNumeroDaRaia << endl;
						cout << " Valor Mensalidade: " << ptrVetRaias[(i * nSalvaQtdeRaia) + j].stAluno.dMensalidade << endl << endl;
						nSobrenome++;
					}
			cout << "\nQuantidade total de alunos: " << nSobrenome << endl << endl;
			PAUSA;
		}

};