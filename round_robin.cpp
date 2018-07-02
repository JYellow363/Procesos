// Round Robin con TQ fijo
//Se debe agregar un archivo de texto "in.txt"

#include <bits/stdc++.h>

using namespace std;

struct Proceso {
	int i, bt, at;
	int ct=0, tat=0, wt=0;
	bool visitado = false;
};

class ListProceso {
private:
	int n;
	int tq;
	int cont2 = 0;
	vector<Proceso> procesos;

public:
	ListProceso(int n, int tq) {
		this->n = n;
		this->tq = tq;
		vector<Proceso> aux(n);
		procesos = aux;
	}

	void insertar(int a, int b, int c) {
		procesos[cont2].bt = a;
		procesos[cont2].at = b;
		procesos[cont2].i = c;
		cont2++;
	}

	float ACT() {
		float a=0;
		for (int i = 0; i < n; i++) {
			a += procesos[i].ct;
		}
		return a / n;
	}

	float TAT() {
		float a=0;
		for (int i = 0; i < n; i++) {
			procesos[i].tat = procesos[i].ct - procesos[i].at;
			a += procesos[i].tat;
		}
		return a / n;
	}

	float AWT() {
		float a=0;
		for (int i = 0; i < n; i++) {
			procesos[i].wt = procesos[i].tat - procesos[i].bt;
			a += procesos[i].wt;
		}
		return a / n;
	}

	void planificar() {
		int tmin = -1;
		int tmax = 0;
		int cont = n;
		Proceso temp;
		vector<Proceso> aux;
		while (aux.empty() == false || cont > 0) {
			for (int j = 0; j < n; j++) {
				if (procesos[j].at > tmin&&procesos[j].at <= tmax) {
					//Si el proceso llegó en el tiempo de ejecución del anterior proceso
					aux.push_back(procesos[j]);
				}
			}

			bool q = false;
			for (int i = 0; i < aux.size(); i++) {
				if (q == false && aux[i].visitado == false) {
					//si el proceso ya fue ejecutado en la ronda, no puede volver a ser ejecutado
					temp = aux[i];
					aux.erase(aux.begin() + i);
					aux.insert(aux.begin(), temp);
					q = true;
				}
			}

			if (q == false) {
				//si la ronda terminó, los procesos pueden volver a ejecutarse
				for (int i = 0; i < aux.size(); i++)
					aux[i].visitado = false;
				cout<<"--Fin de la Ronda--"<<endl;
			}
			
			if (aux[0].bt <= tq) { //si el proceso es menor o igual al TQ, se ejecuta totalmente
				tmin = tmax;
				tmax += aux[0].bt; //se le suma el busrt time al tiempo actual de ejecucción
				if(tmin<10)	cout <<" "<< tmin << " |--- P" << aux[0].i << " ---| " << tmax << endl;
				else cout << tmin << " |--- P" << aux[0].i << " ---| " << tmax << endl;
				aux[0].visitado = true;
				procesos[aux[0].i - 1].ct = tmax;
				aux.erase(aux.begin());
				cont--;
			}
			
			else { //si el proceso no terminó de ejecutarse, se guarda en la cola con su nuevo bt
				tmin = tmax;
				tmax += tq;
				aux[0].bt -= tq;
				if(tmin<10)	cout <<" "<< tmin << " |--- P" << aux[0].i << " ---| " << tmax << endl;
				else cout << tmin << " |--- P" << aux[0].i << " ---| " << tmax << endl;
				aux[0].visitado = true;
				aux.push_back(aux[0]);
				aux.erase(aux.begin());
				cont--;
				
			}
		}
	}
};

int main()
{	
	
	cout<<endl<<"Caso de prueba:"<<endl;
	cout<<"6"<<endl<<"6"<<endl;
	cout<<"10 0"<<endl;
	cout<<"10 3"<<endl;
	cout<<"7 8"<<endl;
	cout<<"3 19"<<endl;
	cout<<"18 21"<<endl;
	cout<<"7 22"<<endl<<endl;
	cout << "Instrucciones" << endl << endl;
	cout << "Primera linea: Ingrese el número de procesos" << endl;
	cout << "Segunda linea: Ingrese el time quantum" << endl;
	cout << "Lineas siguientes: Ingrese el BT y AT de los procesos" << endl << endl;
	int n, tq, bt, at;
	//freopen("in.txt", "r", stdin);
	cin >> n >> tq;
	ListProceso *lista = new ListProceso(n, tq);
	for (int i = 0; i < n; i++) { //Ingresa procesos
		cout << "P" << i + 1 << " ->\t";
		cin >> bt >> at;
		lista->insertar(bt, at, i + 1);
	}
	cout << endl;
	lista->planificar();
	cout << endl;
	cout << "ACT = " << lista->ACT() << endl;
	lista->TAT();
	cout << "AWT = " << lista->AWT();
	return 0;
}
