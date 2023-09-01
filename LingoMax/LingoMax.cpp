#include <iostream>
#include <locale>

using namespace std;

struct Idioma {
	int cod_idioma;
	char descricao[30];
};

struct Idioma_index {
	int cod;
	int end;
};

struct Licao {
	int cod_licao;
	int cod_idioma;
	int total_niveis;
};

struct Licao_index{
	int cod;
	int end;
};

struct Exercicio {
	int cod_exercicio;
	int nivel_dificuldade;
	char pergunta[120];
	char resposta_correta[100];
	float pontos;
};

struct Exercicio_index {
	int cod;
	int end;
};

struct Usuario {
	int cod_usuario;
	char nome[60];
	int cod_idioma;
	int nivel_atual;
	float pontuacao_total;
};

struct Usuario_index {
	int cod;
	int end;
};

void insert_idioma(Idioma table[], Idioma_index index[], int n, int len[]) {
	system("clear||cls");
	char finalizar[1];
	cout << "========= CADASTRAR IDIOMA =========" << endl;
	for (int i = 0; i < n; i++) {
		cout << "Código: ";
		cin >> table[n].cod_idioma;
		cout << "Descrição: ";
		cin.ignore();
		cin.getline(table[i].descricao, 30);
		len[0]++;
		cout << "===========================================" << endl;
		cout << "Deseja cadastrar outro idioma?[S][N] ";
		cin >> finalizar;
		if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
			return;
		}
		else {
			insert_idioma(table, index, n, len);
			return;
		}
	}
}


int main() {
	setlocale(LC_ALL, "portuguese");
	const int n = 1000;
	int len[4];
	int opcao = 0;
	/*
		len[0] -> Idioma
		len[1] -> Licao
		len[2] -> Exercicio
		len[3] -> Usuario
	*/
	Idioma idiomas[n];
	Idioma_index idiomas_index[n];

	while (true) {
		system("clear||cls");
		cout << "---------- MENU ----------" << endl;
		cout << "CADASTROS        [1]" << endl;
		cout << "DIGITE UMA OPCAO: ";
		cin >> opcao;
		switch (opcao) {
		case 1:
			system("clear||cls");
			cout << "---------- CADASTROS ----------" << endl;
			cout << "CADASTRAR IDIOMA [1]" << endl;
			cout << "DIGITE UMA OPÇÃO DE CADASTRO (0 parar sair): ";
			cin >> opcao;
			switch (opcao) {
			case 1:
				insert_idioma(idiomas, idiomas_index, n, len);
				break;
			case 0:
				break;
			}
			break;
		}
	};
	
}