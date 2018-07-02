//Se necesita un archivo de texto "in.txt"

#include <bits/stdc++.h>

using namespace std;

struct Proceso {
	int i, bt, at, pri;
	int wt=0, ct=0;
};

class ListProceso {
private:
	int n;
	int cont = 0;
	vector<Proceso> procesos;

public:
	ListProceso(int n) {
		this->n = n;
		vector<Proceso> aux(n);
		procesos = aux;
	}

	void insertar(int a, int b, int c, int d) {
		procesos[cont].bt = a;
		procesos[cont].at = b;
		procesos[cont].pri = c;
		procesos[cont].i = d;
		cont++;
	}

	float AWT() {
		float a=0;
		for (int i = 0; i < n; i++)
			a += procesos[i].wt;
		return a / n;
	}

	float ACT() {
		float a=0;
		for (int i = 0; i < n; i++)
			a += procesos[i].ct;
		return a / n;
	}

	void planificar_fifo() {
		int tmin = -1;
		int tmax = 0;
		int cont = n;
		vector<Proceso> aux;
			while (aux.empty()==false || cont>0) {
			for (int j = 0; j < n; j++) {
				if (procesos[j].at > tmin&&procesos[j].at <= tmax) {
					aux.push_back(procesos[j]);
				}
			}
			for (int i = 0; i < aux.size() - 1; i++) {
				for (int j = i + 1; j < aux.size(); j++) {
					if (aux[i].pri > aux[j].pri) swap(aux[i], aux[j]);
				}
			}
			tmin = tmax;
			tmax += aux[0].bt;
			procesos[aux[0].i ].wt = tmin - aux[0].at;
			procesos[aux[0].i ].ct = tmax;
			if(tmin>10) cout <<tmin<< " |--- P" << aux[0].i << " ---| " << tmax<<endl;
			else cout <<" "<< tmin << " |--- P" << aux[0].i << " ---| " << tmax << endl;
			aux.erase(aux.begin());
			cont--;
		}
	}
	
	void planificar_sjf() {
		int tmin = -1;
		int tmax = 0;
		int cont = n;
		vector<Proceso> aux;
		while (aux.empty() == false || cont>0) {
			for (int j = 0; j < n; j++) {
				if (procesos[j].at > tmin&&procesos[j].at <= tmax) {
					aux.push_back(procesos[j]);
				}
			}
			for (int i = 0; i < aux.size() - 1; i++) {
				for (int j = i + 1; j < aux.size(); j++) {
					if (aux[i].pri > aux[j].pri) swap(aux[i], aux[j]);
					if (aux[i].pri == aux[j].pri) {
						if(aux[i].bt > aux[j].bt) swap(aux[i], aux[j]);
					}
				}
			}
			tmin = tmax;
			tmax += aux[0].bt;
			procesos[aux[0].i ].wt = tmin - aux[0].at;
			procesos[aux[0].i ].ct = tmax;
			if(tmin>10) cout << tmin << " |--- P" << aux[0].i << " ---| " << tmax << endl;
			else cout <<" "<< tmin << " |--- P" << aux[0].i << " ---| " << tmax << endl;
			aux.erase(aux.begin());
			cont--;
		}
	}
};

int main()
{
	cout<<endl;
	cout<<"Caso de prueba:"<<endl;
	cout<<"6"<<endl<<"1"<<endl;
	cout<<"18 0 2"<<endl;
	cout<<"5 10 2"<<endl;
	cout<<"14 18 1"<<endl;
	cout<<"4 25 3"<<endl;
	cout<<"10 30 2"<<endl;
	cout<<"6 31 3"<<endl<<endl;
	//freopen("in2.txt", "r", stdin);
	//locale::global(locale("spanish"));
	int n, bt, at, pri, tipo, tq;
	cout << "Instrucciones" << endl << endl;
	cout << "(1) FIFO" << endl << "(2) SJF" << endl << endl;
	cout << "Primera línea: Número de procesos" << endl;
	cout << "Segunda línea: tipo de planificación" << endl;
	cout << "Líneas siguientes: BT, AT y Prioridad de los procesos" << endl << endl;
	cin >> n;
	cin >> tipo;
	ListProceso *lista = new ListProceso(n);
	for (int i = 0; i < n; i++) {
		cout << "P" << i << " ->\t";
		cin >> bt >> at >> pri;
		lista->insertar(bt, at, pri, i);
	}
	cout<<endl;
	if (tipo == 1) lista->planificar_fifo();
	if (tipo == 2) lista->planificar_sjf();
	cout << endl << endl;
	cout << "ACT = " << lista->ACT();
	cout << endl;
	cout << "AWT = " << lista->AWT();
	return 0;
}
