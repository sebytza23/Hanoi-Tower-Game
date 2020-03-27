#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

char Nume[20];
int moves;


struct nod {
	string info;
	int tag;
	nod* pred;
};

typedef struct nod Stiva;

void PRINT_ERROR(int);

Stiva* INIT(Stiva* st) {
	st->pred = NULL;
	st->tag = NULL;
	return st;
}

Stiva* TOP(Stiva* st) {
	return st;
}

int LENGTH(Stiva* st) {
	int k = 0;
	while (st->pred) {
		st = st->pred;
		k++;
	}
	return k;
}

void EMPTY(Stiva*& st) {
	if (st->pred) {
		while (st->pred) {
			Stiva* aux;
			aux = st;
			st = st->pred;
			delete aux;
		}
	}
	else PRINT_ERROR(1);
}

Stiva* PUSH(Stiva* vf, int inf) {
	Stiva* aux;
	aux = new(Stiva);
	aux = INIT(aux); 
	string c;
	for (int i = 1; i <= inf; i++) {
		c =  c + "*"+" " ;
	}
	aux->info = c;
	aux->tag = inf;
	if (vf) {
		aux->pred = vf;
		vf = aux;
	}
	else vf = aux;
	return vf;
}

Stiva* POP(Stiva* &st1,Stiva* st2) {
		Stiva* aux;
		aux = new(Stiva);
		aux = INIT(aux);
		aux ->info = st1->info;
		aux->tag = st1->tag;
		if (st2) {
			aux->pred = st2;
			st2 = aux;
		}
		else st2 = aux;
		st1 = st1->pred;
		return st2;
}

void PRINT(Stiva* st1,Stiva* st2,Stiva* st3, int n) {
		cout << endl;
		n++;
		cout << "Mutari actuale: " << moves << endl << endl << endl;
		while (st1->pred)
		{
			for (int i = 1; i <= LENGTH(st1); i++) {
				cout << " ";
			}
			cout << st1->info << endl;
			st1 = st1->pred;
		}
		for (int i = 1; i <= n*2; i++) {
			cout << "=";
		}
		cout << endl << setw(n+strlen("Turnul 1")/2)<< "Turnul 1" << endl << endl;
		while (st2->pred)
		{
			for (int i = 1; i <= LENGTH(st2); i++) {
				cout << " ";
			}
			cout << st2->info << endl;
			st2 = st2->pred;
		}
		for (int i = 1; i <= n*2; i++) {
			cout << "=";
		}
		cout << endl << setw(n + strlen("Turnul 2")/2) << "Turnul 2" << endl << endl;
		while (st3->pred)
		{
			for (int i = 1; i <= LENGTH(st3); i++) {
				cout << " ";
			}
			cout << st3->info << endl;
			st3 = st3->pred;
		}
		for (int i = 1; i <= n*2; i++) {
			cout << "=";
		}
		cout << endl << setw(n + strlen("Turnul 3")/2) << "Turnul 3" << endl << endl;
}

void Choice()
{
	int choice;
		cout << endl;
	eroare:
		system("cls");
		cout << " 1) Porneste jocul.\n";
		cout << " 2) Cum se joaca?.\n";
		cout << " 3) Iesire.\n";
		cout << "\tAlege>: ";
		cin >> choice;
		if (cin.fail() || (choice > 3 || choice < 1)) {
			cin.clear();
			cin.ignore();	
			PRINT_ERROR(4);	
			system("pause");
			goto eroare;
		}
		switch (choice)
		{
		case 1:
			cout << "Jocul a pornit, va rugam sa introduceti un nume:"; cin >> Nume;
			break;
		case 2:
			system("cls");
			cout << "Jocul se bazeaza pe o tabla cu 3 bete,unde se pune un anumit numar de discuri pe batul 1.\nDiscurile trebuie sa fie : Primul sa fie cel mai mic, Iar ultimul sa fie cel mai mare.\n";
			system("pause");
			goto eroare;
			break;
		case 3:
			cout << "Iesire Joc.\n";
			system("pause");
			exit(0);
		}
}
void discuri(int& n)
{
eroare:
	system("cls");
	cout << "Va rugam introduceti numarul de discuri(minim 3):";
	cin >> n;
	if (cin.fail() || (n < 3)) {
		cin.clear();
		cin.ignore();
		PRINT_ERROR(4);
		system("pause");
		goto eroare;
	}
}

int main() {
	int n;
	Choice();
	start:
	int choice;
	Stiva* st1;
	Stiva* st2;
	Stiva* st3;
	st1 = new(Stiva);
	st1 = INIT(st1);
	st2 = new(Stiva);
	st2 = INIT(st2);
	st3 = new(Stiva);
	st3 = INIT(st3);
	discuri(n);
	moves = pow(2, n) - 1;
	for (int i = 1; i <= n; i++)
		st1 = PUSH(st1, n - i + 1);
	system("cls");
	cout << "Numarul minim de mutari pentru a rezolva Turnurile lui Hanoi este: " << moves << endl;
	moves = 0;
	system("pause");
	while (st1->tag || st2->tag) {
		system("cls");
		PRINT(st1, st2, st3, n);
		cout << "Valori disponibile de luat:\n";
		if ((TOP(st1)->tag > TOP(st2)->tag) && (TOP(st1)->tag > TOP(st3)->tag)) {
			if ((TOP(st2)->tag == NULL) && (TOP(st3)->tag == NULL)) {
				moves++;
				cout << "Jocul a luat discul din singura pozitie disponibila: Turnul 1\n"; choice = 1;
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
				eroare:
					cout << "\t1) Turnul 2\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare;
					}
					if (choice == 1) {
						st2 = POP(st1, st2);
					}
					else {
						st3 = POP(st1, st3);
					}
				}
			}
			else if ((TOP(st2)->tag > TOP(st3)->tag) && (TOP(st3)->tag == NULL)) {
				moves++;
				eroare1:
				cout << "\t1) Turnul 1\n\t2) Turnul 2\n\tAlegere > "; cin >> choice;
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					cout << "Jocul a plasat discul pe singura pozitie disponibila: Turnul 3\n";
					st3 = POP(st1, st3);
				}
				else {
					cout << "\t1) Turnul 1\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare1;
					}
					if (choice == 1) {
						st1 = POP(st2, st1);
					}
					else {
						st3 = POP(st2, st3);
					}
				}
			}
			else if ((TOP(st3)->tag > TOP(st2)->tag) && (TOP(st2)->tag == NULL)) {
				moves++;
				eroare2:
				cout << "\t1) Turnul 1\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
				if (cin.fail() || (choice > 2 || choice < 1)) {
					PRINT_ERROR(5);
					goto eroare2;
				}
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					cout << "Jocul a plasat discul pe singura pozitie disponibila: Turnul 2\n";
					st2 = POP(st1, st2);
				}
				else {
					eroare3:
					cout << "\t1) Turnul 1\n\t2) Turnul 2\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare3;
					}
					if (choice == 1) {
						st1 = POP(st3, st1);
					}
					else {
						st2 = POP(st3, st2);
					}
				}
			}
			else if (TOP(st2)->tag > TOP(st3)->tag) {
				moves++;
				cout << "Jocul a luat discul din singura pozitie disponibila: Turnul 3\n"; choice = 1;
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare4:
					cout << "\t1) Turnul 1\n\t2) Turnul 2\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare4;
					}
					if (choice == 1) {
						st1 = POP(st3, st1);
					}
					else {
						st2 = POP(st3, st2);
					}
				}
			}
			else {
				moves++;
				cout << "Jocul a luat discul din singura pozitie disponibila: Turnul 2\n"; choice = 1;
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare5:
					cout << "\t1) Turnul 1\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare5;
					}
					if (choice == 1) {
						st1 = POP(st2, st1);
					}
					else {
						st3 = POP(st2, st3);
					}
				}
			}
		}
		else if ((TOP(st1)->tag < TOP(st2)->tag) && (TOP(st2)->tag > TOP(st3)->tag)) {
			if ((TOP(st1)->tag == NULL) && (TOP(st3)->tag == NULL)) {
				moves++;
				cout << "Jocul a luat discul din singura pozitie disponibila: Turnul 2\n"; choice = 1;
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare6:
					cout << "\t1) Turnul 1\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare6;
					}
					if (choice == 1) {
						st1 = POP(st2, st1);
					}
					else {
						st3 = POP(st2, st3);
					}
				}
			}
			else if ((TOP(st1)->tag > TOP(st3)->tag) && (TOP(st3)->tag == NULL)) {
				moves++;
				eroare7:
				cout << "\t1) Turnul 1\n\t2) Turnul 2\n\tAlegere > "; cin >> choice;
				if (cin.fail() || (choice > 2 || choice < 1)) {
					PRINT_ERROR(5);
					goto eroare7;
				}
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare8:
					cout << "\t1) Turnul 2\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare8;
					}
					if (choice == 1) {
						st2 = POP(st1, st2);
					}
					else {
						st3 = POP(st1, st3);
					}
				}
				else {
					cout << "Jocul a plasat discul pe singura pozitie disponibila: Turnul 3\n";
					st3 = POP(st2, st3);
				}
			}
			else if ((TOP(st1)->tag < TOP(st3)->tag) && (TOP(st1)->tag == NULL)) {
				moves++;
				eroare9:
				cout << "\t1) Turnul 2\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
				if (cin.fail() || (choice > 2 || choice < 1)) {
					PRINT_ERROR(5);
					goto eroare9;
				}
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					cout << "Jocul a plasat discul pe singura pozitie disponibila: Turnul 1\n";
					st1 = POP(st2, st1);
				}
				else {
					eroare10:
					cout << "\t1) Turnul 1\n\t\2) Turnul 2n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare10;
					}
					if (choice == 1) {
						st1 = POP(st3, st1);
					}
					else {
						st2 = POP(st3, st2);
					}
				}
			}
			else if (TOP(st1)->tag > TOP(st3)->tag) {
				moves++;
				cout << "Jocul a luat discul din singura pozitie disponibila: Turnul 3\n"; choice = 1;
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare11:
					cout << "\t1) Turnul 1\n\t2) Turnul 2\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare11;
					}
					if (choice == 1) {
						st1 = POP(st3, st1);
					}
					else {
						st2 = POP(st3, st2);
					}
				}
			}
			else {
				moves++;
				cout << "Jocul a luat discul din singura pozitie disponibila: Turnul 1\n"; choice = 1;
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare12:
					cout << "\t1) Turnul 2\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare12;
					}
					if (choice == 1) {
						st2 = POP(st1, st2);
					}
					else {
						st3 = POP(st1, st3);
					}
				}
			}
		}
		else if ((TOP(st1)->tag < TOP(st3)->tag) && (TOP(st3)->tag > TOP(st2)->tag)) {
			if ((TOP(st1)->tag > TOP(st2)->tag) && (TOP(st2)->tag == NULL)) {
				moves++;
				eroare13:
				cout << "\t1) Turnul 1\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
				if (cin.fail() || (choice > 2 || choice < 1)) {
					PRINT_ERROR(5);
					goto eroare13;
				}
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare14:
					cout << "\t1) Turnul 2\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare14;
					}
					if (choice == 1) {
						st2 = POP(st1, st2);
					}
					else {
						st3 = POP(st1, st3);
					}
				}
				else {
					st2 = POP(st3, st2);
				}
			}
			else if ((TOP(st1)->tag < TOP(st2)->tag) && (TOP(st1)->tag == NULL)) {
				moves++;
				eroare15:
				cout << "\t1) Turnul 2\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
				if (cin.fail() || (choice > 2 || choice < 1)) {
					PRINT_ERROR(5);
					goto eroare15;
				}
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare16:
					cout << "\t1) Turnul 1\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare16;
					}
					if (choice == 1) {
						st1 = POP(st2, st1);
					}
					else {
						st3 = POP(st2, st3);
					}
				}
				else {
					st1 = POP(st3, st1);
				}
			}
			else if (TOP(st1)->tag < TOP(st2)->tag) {
				moves++;
				eroare17:
				cout << "\t1) Turnul 1\n\t2) Turnul 2\n\tAlegere > "; cin >> choice;
				if (cin.fail() || (choice > 2 || choice < 1)) {
					PRINT_ERROR(5);
					goto eroare17;
				}
				cout << "Valori disponibile de plasat:\n";
				if (choice == 1) {
					eroare18:
					cout << "\t1) Turnul 2\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare18;
					}
					if (choice == 1) {
						st2 = POP(st1, st2);
					}
					else {
						st3 = POP(st1, st3);
					}
				}
				else {
					cout << "Jocul a plasat discul pe singura pozitie disponibila: Turnul 3\n";
					st3 = POP(st2, st3);
				}
			}
			else if (TOP(st1)->tag > TOP(st2)->tag) {
				moves++;
				eroare19:
				cout << "\t1) Turnul 1\n\t2) Turnul 2\n\tAlegere > "; cin >> choice;
				if (cin.fail() || (choice > 2 || choice < 1)) {
					PRINT_ERROR(5);
					goto eroare19;
				}
				cout << "Valori disponibile de plasat:\n";
				if (choice == 2) {
					eroare20:
					cout << "\t1) Turnul 1\n\t2) Turnul 3\n\tAlegere > "; cin >> choice;
					if (cin.fail() || (choice > 2 || choice < 1)) {
						PRINT_ERROR(5);
						goto eroare20;
					}
					if (choice == 1) {
						st1 = POP(st2, st1);
					}
					else {
						st3 = POP(st2, st3);
					}
				}
				else {
					cout << "Jocul a plasat discul pe singura pozitie disponibila: Turnul 3\n";
					st3 = POP(st1, st3);
				}
			}
		}
		system("pause");
	}
	cout << "Felicitari " << Nume <<" ai terminat cu un numar de mutari de:  " << moves << endl;
	eroare21:
	cout << "Doresti sa reiei jocul de la capat? \n\t1)Da\n\tNu\n\tAlege > "; cin >> choice;
	if (cin.fail() || (choice > 2 || choice < 1)) {
		PRINT_ERROR(5);
		goto eroare21;
	}
	else if (choice == 1) {
		EMPTY(st3);
		goto start;
	}
	else exit(0);
	system("pause");
}

void PRINT_ERROR(int err) {
	switch (err) {
	case 4:  cout << "Valoarea introdusa nu este valida! Introduceti valoarea din nou!\n"; break;
	case 5: cin.clear();
		cin.ignore();
		PRINT_ERROR(4);
		system("pause");
		break;
	}
}
