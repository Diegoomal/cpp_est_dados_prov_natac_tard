#include "Escola.h"

int PedirValorValido(char *ptrAcao)
{
	int nPeriodo;			// para receber o periodo
	cout << "\tAcao: " << ptrAcao << endl;
	do
	{
		cout << "Informe periodo \n\t1 = Manha\n\t2 = Tarde\n\t3 = Noite\n\tOu zero para cancelar: ";
		cin >> nPeriodo;
	} while(nPeriodo < 0 || nPeriodo > 3);
	return nPeriodo;		// retorna o valor que foi digitado
}