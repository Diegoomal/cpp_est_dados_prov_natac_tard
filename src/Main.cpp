//Prova B2 - Estrutura de Dados 22/05/2014
// FATEC - Mogi das Cruzes - Versao 0.0
#include "Escola.h"

//	Funcao que pede um periodo valido (1 - manha, 2 - tarde ou 3 - noite) ou zero
//		caso o operador vai desistir
//	Parametros:
//		Entrada: char *ptrAcao - endereco do string com a acao que esta sendo executada
//		Retorno: periodo desejado ou zero se vai cancelar
int PedirPeriodoValido(char *ptrAcao)
{
	// mostrar na tela: A��o: XXXXXXXXXXXXXXXX - a��o que est� sendo executada
	// ficar em looping at� o operador informar um per�odo v�lido ou zero para
	//	cancelar
	// retornar o que foi informado
	int nPeriodo;						// para receber o per�odo
	cout << "\tAcao: " << ptrAcao << endl;
	do
	{
		cout << "Informe periodo \n\t1 = Manha\n\t2 = Tarde\n\t3 = Noite\n\tOu zero para cancelar: ";
		cin >> nPeriodo;
	} while(nPeriodo < 0 || nPeriodo > 3);
	return nPeriodo;					// retorna o valor que foi digitado
}

int main(void)
{

	// codificar as vari�veis necess�rias
	int nRetorno,
		nQuantidadeRaias,		// quantidade de rais		
		nPeriodo,				// periodo da aula
		nRaia,					// raia da piscina
		nTipo;					// tipo de despesa
	double dValor;				// valor da despesa
	char cOpcao,				// opcao do operador
		cNomeAluno[] = "Diego Vasque Maldonado",
		cRA_Aluno[] = "1122101",
		cWork[100];				// para trabalho
	bool flgResult;				// flg para resultado do construtor
	ALUNO stAluno;				// struct para o nome e sobrenome
	
	// receber data e hora do sistema
	#ifdef _WIN32
	SYSTEMTIME stTime;
	#else
	std::time_t currentTime = std::time(nullptr);
	#endif

	// para tratamento do ponto decimal
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	setlocale(LC_ALL, "portuguese_brazil");

	// perguntar quantas raias tem a piscina ( minimo QTDE_MIN_RAIAS e no maximo
	//	QTDE_MAX_RAIAS) ou zero para cancelar a execucao do programa
	// Instanciar a classe clEscolaNatacao informando a quantidade de raias e
	//	endereco da bool a receber o retorno do contrutor da classe.

	// .... codificar a partir daqui
	do
	{
		cout << "Qtde de raias minimo de " << QTDE_MIN_RAIAS << " e " << QTDE_MAX_RAIAS << endl 
			<< "Ou zero para cancelar a execucao do programa: " << endl;
		cin >> nQuantidadeRaias;
		if(nQuantidadeRaias == 0)					// cancelado pelo operador?
			return 0;
	} while(nQuantidadeRaias < QTDE_MIN_RAIAS || nQuantidadeRaias > QTDE_MAX_RAIAS);
	
	// vai instanciar a clEscolaNatacao criando o objEscola
	clEscolaNatacao objEscola = clEscolaNatacao(nQuantidadeRaias, &flgResult);
	
	// <<<<<< ***** >>>>>>
	// Analisar o retorno para ver se o programa sera abortado
	// Ficar em um loop infinito exibindo o menu das opcoes do operador

	while(true)	//loop infinito
	{
		LIMPA_TELA;

		// Pedir data e hora do sistema
		#ifdef _WIN32
		GetLocalTime(&stTime);
		sprintf(cWork,
			"Escola de Natacao FATEC - MC - Turma Tarde - %02d/%02d/%04d as %02d:%02d",
			stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute);
		#else
		struct tm* stTime = std::localtime(&currentTime);
		sprintf(cWork, 
			"Escola de Natacao FATEC - MC - Turma Tarde - %02d/%02d/%04d as %02d:%02d",
			stTime->tm_mday, stTime->tm_mon, stTime->tm_year + 1900, stTime->tm_hour, stTime->tm_min);
		#endif
		
		cout << cWork << endl;
		sprintf(cWork, "\tAluno: %s RA: %s", cNomeAluno, cRA_Aluno);
		cout << cWork << endl;
		cout << MATRICULAR_ALUNO			<< " - Matricular aluno"					<< endl;
		cout << LISTAR_ALUNOS_DE_UM_PERIODO	<< " - Listar alunos de um periodo"			<< endl;
		cout << LISTAR_TODOS_OS_ALUNOS		<< " - Listar todos os alunos"				<< endl;
		cout << CANCELAR_MATRICULA			<< " - Cancelar Matricula"					<< endl;
		cout << LANCAR_DESPESA_EM_UM_ALUNO	<< " - Lancar despesa em um aluno"			<< endl;
		cout << CONSULTAR_UM_DADO_ALUNO		<< " - Consultar um dado aluno"				<< endl;
		cout << LISTAR_POR_ARGUMENTO		<< " - Listar por argumento do sobrenome"	<< endl;
		cout << SAIR_DO_PROGRAMA			<< " - Sair do Programa"					<< endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;					//recebendo o desejo do operador
		cOpcao = toupper(cOpcao);		//convertendo para caixa alta

		switch(cOpcao)
		{
			#pragma region MATRICULAR_ALUNO
			
			//matriculando um novo aluno

			case MATRICULAR_ALUNO:

				// <<<<<< ***** >>>>>>
				// chamar a fun��o PedirPeriodoValido e analisar o retorno.
				//	Se o operador desistiu, voltar ao menu principal
				// Pedir o prenome e sobrenome do aluno (stAluno) n�o se esquecendo que
				//	tanto o prenome e sobrenome podem ter brancos no meio...
				// invocar o m�todo para matricular (MatricularAluno) e analizar o retorno...
				//	se o retorno for zero significa que n�o tinha raia livre naquele
				//  per�odo e assim avisar ao operador e voltar ao menu principal...
				//	Exibir a raia que o aluno foi matriculado...
				
				nPeriodo = PedirPeriodoValido("Matricula de aluno");
				// nPeriodo contem o periodo do horario do aluno
				// se o nPeriodo for zero volta ao menu
				if(nPeriodo == 0)
					break;
				
				cout << "Insira o nome do Aluno: " << endl;
				cin.ignore(1, EOF);
				cin.getline(stAluno.cPrenome, sizeof(stAluno.cPrenome),'\n');
				cout << "Insira o sobrenome do Aluno: " << endl;
				cin.ignore(1, EOF);
				cin.getline(stAluno.cSobrenome, sizeof(stAluno.cSobrenome),'\n');

				nRetorno = objEscola.MatricularAluno(nPeriodo, &stAluno);

				if( nRetorno == 0) {
					cout << "Nao existem raias livres no periodo " << nPeriodo << endl;
					PAUSA;
					LIMPA_TELA;
					break;
				}
				
				cout << "Aluno " << stAluno.cPrenome << " " << stAluno.cSobrenome
					<< " esta matriculado na raia" << nRetorno+1 << " do periodo " << nPeriodo 
					<< "A mensalidade e " << stAluno.dMensalidade << endl << endl;
				PAUSA;
				LIMPA_TELA;
				break;

			#pragma endregion

			#pragma region LISTAR_ALUNOS_DE_UM_PERIODO

			case LISTAR_ALUNOS_DE_UM_PERIODO:

				// <<<<<< ***** >>>>>>
				// chamar a fun��o PedirPeriodoValido e analisar o retorno.
				//	Se o operador desistiu, voltar ao menu principal
				
				nPeriodo = PedirPeriodoValido("Listar alunos de um periodo");
				// nPeriodo contem o periodo do horario do aluno
				// se o nPeriodo for zero volta ao menu
				if(nPeriodo == 0)
					break;
				//
				// Listagem de alunos
				//
				objEscola.ListarUmPeriodo(nPeriodo);
				break;
			
			#pragma endregion

			#pragma region LISTAR_TODOS_OS_ALUNOS

			case LISTAR_TODOS_OS_ALUNOS:
			
				// <<<<<< ***** >>>>>>
				// invocar o metodo para listar todos os alunos
			
				objEscola.ListarTodosOsAlunos();

				break;
			
			#pragma endregion

			#pragma region CANCELAR_MATRICULA

			case CANCELAR_MATRICULA:

				// <<<<<< ***** >>>>>>
				// chamar a fun��o PedirPeriodoValido e analisar o retorno.
				//	Se o operador desistiu, voltar ao menu principal
				//	Ficar em looping pedindo a raia do aluno que tem que ser v�lida ou
				//		zero se vai desistir....
				// Invocar o m�todo que cancela a matr�cula....
				//	Analisar o resultado
			
				nPeriodo = PedirPeriodoValido("Cancelar Matricula");
				if(nPeriodo == 0)																		// Operador cancelou
					break;																				// Cai fora e volta ao menu
				//	looping que pede a raia do aluno (v�lida) ou 0 se vai desistir....
				do
				{
					cout << "Selecione a raia entre 1 e " << nQuantidadeRaias << ": ";
					cin >> nRaia;
				} while(nRaia <= 0 || nRaia > nQuantidadeRaias);
				
				// Invocar o m�todo que cancela a matr�cula....
				//	Analisar o resultado
				objEscola.CancelarMatricula(nPeriodo, nRaia);
				
				break;
			
			#pragma endregion

			#pragma region LANCAR_DESPESA_EM_UM_ALUNO

			case LANCAR_DESPESA_EM_UM_ALUNO:

				// <<<<<< ***** >>>>>>
				// chamar a fun��o PedirPeriodoValido e analisar o retorno.
				//	Se o operador desistiu, voltar ao menu principal
				//	Ficar em looping pedindo a raia do aluno que tem que ser v�lida ou
				//		zero se vai desistir....
				// Ficar em looping pedindo um tipo de despesa v�lido ou zero para
				//		desistir....
				// Pedir o valor da despesa
				// Invocar o m�todo que lan�a a despesa....
				//	Analisar o resultado...
				
				nPeriodo = PedirPeriodoValido("Lancar despesa de um aluno");
				// nPeriodo contem o periodo do horario do aluno
				// se o nPeriodo for zero volta ao menu
				if(nPeriodo == 0)
					break;

				do
				{
					cout << "Digite o valor da raia (deve estar entre " << QTDE_MIN_RAIAS << " e " << QTDE_MAX_RAIAS << ")";
					cin >> nRaia;
				} while(nRaia > QTDE_MIN_RAIAS || nRaia < QTDE_MAX_RAIAS);

				if(nRaia == 0)
					break;

				flgResult = true;
				while(flgResult)
				{
					cout << "Tipos de despesa" << endl;
					cout << LANCHONETE	<< " - lanchonete " << endl;
					cout << ACESSORIOS	<< " - Acessorios " << endl;
					cout << HIGIENE		<< " - higiene "	<< endl;
					cin >> nTipo;
					cout << "Digite o valor da despesa: ";
					cin >> dValor;
					if(objEscola.LancarDespesa(nPeriodo, nRaia, nTipo, dValor))
						cout << "adicionado a outras despesas!" << endl;
					cout << "Deseja adicionar mais gastos? (S ou N): ";
					cin >> cOpcao;
					cOpcao = toupper(cOpcao);
					if(cOpcao == 'S')
						break;
				}

			#pragma endregion

			#pragma region CONSULTAR_UM_DADO_ALUNO

			case CONSULTAR_UM_DADO_ALUNO:

				// <<<<<< ***** >>>>>>
				// chamar a fun��o PedirPeriodoValido e analisar o retorno.
				//	Se o operador desistiu, voltar ao menu principal
				//	Ficar em looping pedindo a raia do aluno que tem que ser v�lida ou
				//		zero se vai desistir....
				// Invocar o m�todo que consulta um dado aluno....

				nPeriodo = PedirPeriodoValido("Consultar Aluno");
				
				if(nPeriodo == 0)		// Operador cancelou
					break;				// Cai fora e volta ao menu
				
				objEscola.ConsultarAluno(nPeriodo, nRaia);
				
				break;
			
			#pragma endregion

			#pragma region LISTAR_POR_ARGUMENTO

			case LISTAR_POR_ARGUMENTO:

				// <<<<<< ***** >>>>>>
				// Pedir o argumento considerando que o metodo ira buscar
				//	considerando maiuscula e minusculas
				// Invocar o metodo que ira listar todos os alunos cujo o
				//	sobrenome contem o argumento informado

				break;

			#pragma endregion

			#pragma region SAIR_DO_PROGRAMA & DEFAULT

			//sair

			case SAIR_DO_PROGRAMA:
					cout << "tem certeza que deseja finalizar o sistema (S/N)?" << endl;
					cin >> cOpcao;
					cOpcao = toupper(cOpcao);		//convertendo para caixa alta
					if(cOpcao == 'S')				//deseja sair?
					{//sim
						cout << "Finalizando o sistema..." << endl;
						PAUSA;
						return 0;
					}
					//nao
					break;

			default:
				cout << "Opcao invalida!!!" << endl;
				PAUSA;
			
			#pragma endregion
		}
	}

} // main
