#include <iostream>
#include <bitset>
#include <random>
#include <string>

#define BITS_PER_INDIVIDUAL 10
#define TOTAL_INDIVIDUALS 32
#define MAX_INDIVIDUAL_VALUE 1023
#define PROBABILITY 10
#define CROSS_POINT 2
#define MAX_SEARCH_VALUE 100

using namespace std;

void fillIndividuals(bitset<BITS_PER_INDIVIDUAL> *set){
	
		*set = rand() % MAX_INDIVIDUAL_VALUE;
		
}

void printIndividuals(bitset<BITS_PER_INDIVIDUAL> set){
	
		cout << set << endl;
}

bitset<BITS_PER_INDIVIDUAL> cruzaUnPunto(bitset<BITS_PER_INDIVIDUAL> &p1, bitset<BITS_PER_INDIVIDUAL> &p2, int cross_point) {

    bitset<BITS_PER_INDIVIDUAL> aux = p1;

    for (int i = 0; i <= cross_point; i++)
    {
    	aux.set(cross_point - i, p2[cross_point - i]);
    }

    return aux;
}

bitset<BITS_PER_INDIVIDUAL> cruzaDosPunto(bitset<BITS_PER_INDIVIDUAL> &p1, bitset<BITS_PER_INDIVIDUAL> &p2) {
    bitset<BITS_PER_INDIVIDUAL> aux1 = p1;
    bitset<BITS_PER_INDIVIDUAL> aux2 = p2;

    bitset<BITS_PER_INDIVIDUAL> res1;
    bitset<BITS_PER_INDIVIDUAL> res2;
    bitset<BITS_PER_INDIVIDUAL> res3;

    bitset<BITS_PER_INDIVIDUAL> result;

    bitset<BITS_PER_INDIVIDUAL> mask1 (string("1100000000"));
    bitset<BITS_PER_INDIVIDUAL> mask2 (string("0011110000"));
    bitset<BITS_PER_INDIVIDUAL> mask3 (string("0000001111"));

    res1 = aux1 & mask1;
    res2 = aux2 & mask2;
    res3 = aux1 & mask3;

    int total = res1.to_ulong() + res2.to_ulong() + res3.to_ulong();

    result = total;

    return result;
}

bitset<BITS_PER_INDIVIDUAL> cruzaUniforme(bitset<BITS_PER_INDIVIDUAL> &p1, bitset<BITS_PER_INDIVIDUAL> &p2){

	bitset<BITS_PER_INDIVIDUAL> aux1 = p1;
    bitset<BITS_PER_INDIVIDUAL> aux2 = p2;

    bitset<BITS_PER_INDIVIDUAL> res1;
    bitset<BITS_PER_INDIVIDUAL> res2;

    bitset<BITS_PER_INDIVIDUAL> mask1 (string("1001010110"));
    bitset<BITS_PER_INDIVIDUAL> mask2 (string("0110101001"));

    res1 = aux1 & mask1;
    res2 = aux2 & mask2;

    bitset<BITS_PER_INDIVIDUAL> result;

    int total = res1.to_ulong() + res2.to_ulong();

    result = total;

    return result;

}


int main(int argc, char const *argv[])
{
	bitset<BITS_PER_INDIVIDUAL> p1;
	bitset<BITS_PER_INDIVIDUAL> p2;
	bitset<BITS_PER_INDIVIDUAL> h1;
	bitset<BITS_PER_INDIVIDUAL> h2;

	srand (time(NULL));

	fillIndividuals(&p1);
	fillIndividuals(&p2);

	

	int op = 0;

	while(op != 4)
	{
		cout << "Padre 1: ";
		printIndividuals(p1);
		cout << "Padre 2: ";
		printIndividuals(p2);
		cout << endl;
		cout << "1) Cruza por un punto" << endl;
		cout << "2) Cruza de dos punto" << endl;
		cout << "3) Cruza uniforme" << endl;
		cout << "4) Cruza acentuada" << endl;
		cout << "5) Salir" << endl;
		cout << "Seleccion:   ";

		cin >> op;

		switch(op){
			case 1:
				cout << "Punto de cruza: 4" << endl;
				h1 = cruzaUnPunto(p1, p2, 5);
				h2 = cruzaUnPunto(p2, p1, 5);
				cout << "Hijo 1: ";
				printIndividuals(h1);
				cout << "Hijo 2: ";
				printIndividuals(h2);
				cout << endl;
				cout << endl;
			break;
			case 2:
				cout << "Puntos de cruza: 2, 6" << endl;
				h1 = cruzaDosPunto(p1, p2);
				h2 = cruzaDosPunto(p2, p1);
				cout << "Hijo 1: ";
				printIndividuals(h1);
				cout << "Hijo 2: ";
				printIndividuals(h2);
				cout << endl;
				cout << endl;
			break;
			case 3:
				cout << "Mascara definida: 1001010110 " << endl;
				h1 = cruzaUniforme(p1, p2);
				h2 = cruzaUniforme(p2, p1);
				cout << "Hijo 1: ";
				printIndividuals(h1);
				cout << "Hijo 2: ";
				printIndividuals(h2);
				cout << endl; 
				cout << endl;
			break;
			case 4:
			break;
			case 5:
				exit(0);
			break;
		 	default:
		 		cout << "Selecciona una opcion correcta " << endl;


		}

	}



	
	return 0;
}