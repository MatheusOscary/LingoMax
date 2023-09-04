#include <iostream>
#include <locale>

using namespace std;

struct Idioma {
	int cod_idioma;
	char descricao[30];
	bool deletado;
};

struct Idioma_index {
	int cod;
	int end;
};

struct Licao {
	int cod_licao;
	int cod_idioma;
	int total_niveis;
	bool deletado;
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
	bool deletado;
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
	bool deletado;
};

struct Usuario_index {
	int cod;
	int end;
};

/*================================== INICIO INSERIR DADOS ==================================*/

void register_index_idioma(Idioma table[], Idioma_index index[], int len[], int end) {
	int fim = len[0] - 1;
	for (; fim >= 0 && index[fim].cod > table[end].cod_idioma; fim--) {
        index[fim + 1] = index[fim];
    }
	index[fim + 1].cod = table[end].cod_idioma;
	index[fim + 1].end = end;
}


void insert_idioma(Idioma table[], Idioma_index index[], int n, int len[]) {
	system("clear||cls");
	char finalizar[2];
	cout << "========= CADASTRAR IDIOMA =========" << endl;
	for (int i = len[0]; i < n; i++) {
		cout << "Código: ";
		cin >> table[i].cod_idioma;
		cout << "Descrição: ";
		cin.ignore();
		cin.getline(table[i].descricao, 30);
		table[i].deletado = false;
		register_index_idioma(table, index, len, i);
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

void register_index_licao(Licao table[], Licao_index index[], int len[], int end) {
	int fim = len[1] - 1;
	for (; fim >= 0 && index[fim].cod > table[end].cod_licao; fim--) {
		index[fim + 1] = index[fim];
	}
	index[fim + 1].cod = table[end].cod_licao;
	index[fim + 1].end = end;
}

void insert_licao(Licao table[], Licao_index index[], int n, int len[]) {
	system("clear||cls");
	char finalizar[2];
	cout << "========= CADASTRAR LIÇÃO =========" << endl;
	for (int i = len[1]; i < n; i++) {
		cout << "Código: ";
		cin >> table[i].cod_licao;
		cout << "Código idioma: ";
		cin >> table[i].cod_idioma;
		cout << "Total niveis: ";
		cin >> table[i].total_niveis;
		table[i].deletado = false;
		register_index_licao(table, index, len, i);
		len[1]++;
		cout << "===========================================" << endl;
		cout << "Deseja cadastrar outro lição?[S][N] ";
		cin >> finalizar;
		if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
			return;
		}
		else {
			insert_licao(table, index, n, len);
			return;
		}
	}
}


void register_index_exercicio(Exercicio table[], Exercicio_index index[], int len[], int end) {
	int fim = len[2] - 1;
	for (; fim >= 0 && index[fim].cod > table[end].cod_exercicio; fim--) {
		index[fim + 1] = index[fim];
	}
	index[fim + 1].cod = table[end].cod_exercicio;
	index[fim + 1].end = end;
}

void insert_exercicio(Exercicio table[], Exercicio_index index[], int n, int len[]) {
	system("clear||cls");
	char finalizar[2];
	cout << "========= CADASTRAR EXERCICIO =========" << endl;
	for (int i = len[2]; i < n; i++) {
		cout << "Código: ";
		cin >> table[i].cod_exercicio;
		cout << "Nivel de dificuldade: ";
		cin >> table[i].nivel_dificuldade;
		cout << "Pergunta: ";
		cin.ignore();
		cin.getline(table[i].pergunta, 120);
		cout << "Resposta: ";
		cin.ignore();
		cin.getline(table[i].resposta_correta, 100);
		cout << "Pontos: ";
		cin >> table[i].pontos;
		table[i].deletado = false;
		register_index_exercicio(table, index, len, i);
		len[2]++;
		cout << "===========================================" << endl;
		cout << "Deseja cadastrar outro exercicio?[S][N] ";
		cin >> finalizar;
		if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
			return;
		}
		else {
			insert_exercicio(table, index, n, len);
			return;
		}
	}
}

void register_index_usuario(Usuario table[], Usuario_index index[], int len[], int end) {
	int fim = len[3] - 1;
	for (; fim >= 0 && index[fim].cod > table[end].cod_usuario; fim--) {
		index[fim + 1] = index[fim];
	}
	index[fim + 1].cod = table[end].cod_usuario;
	index[fim + 1].end = end;
}

void insert_usuario(Usuario table[], Usuario_index index[], int n, int len[]) {
	system("clear||cls");
	char finalizar[2];
	cout << "========= CADASTRAR USUARIO =========" << endl;
	for (int i = len[3]; i < n; i++) {
		cout << "Código: ";
		cin >> table[i].cod_usuario;
		cout << "Nome: ";
		cin.ignore();
		cin.getline(table[i].nome, 60);
		cout << "Código idioma: ";
		cin >> table[i].cod_idioma;
		table[i].nivel_atual = 0;
		table[i].pontuacao_total = 0;

		table[i].deletado = false;
		register_index_usuario(table, index, len, i);
		len[3]++;
		cout << "===========================================" << endl;
		cout << "Deseja cadastrar outro usuario?[S][N] ";
		cin >> finalizar;
		if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
			return;
		}
		else {
			insert_usuario(table, index, n, len);
			return;
		}
	}
}

/*================================== FIM INSERIR DADOS ==================================*/


int main() {
	setlocale(LC_ALL, "portuguese");
	const int n = 1000;
	int len[4] = {0};
	int opcao = 0;
	/*
		len[0] -> Idioma
		len[1] -> Licao
		len[2] -> Exercicio
		len[3] -> Usuario
	*/
	Idioma idiomas[n];
	Idioma_index idiomas_index[n];

	Licao licoes[n];
	Licao_index licoes_index[n];

	Exercicio exercicios[n];
	Exercicio_index exercicios_index[n];

	Usuario usuarios[n];
	Usuario_index usuarios_index[n];

	while (true) {
		system("clear||cls");
		cout << "---------- MENU ----------" << endl;
		cout << "CADASTROS        [1]" << endl;
		cout << "DIGITE UMA OPÇÃO: ";
		cin >> opcao;
		switch (opcao) {
		case 1:
			system("clear||cls");
			cout << "---------- CADASTROS ----------" << endl;
			cout << "CADASTRAR IDIOMA    [1]" << endl;
			cout << "CADASTRAR LIÇÃO     [2]" << endl;
			cout << "CADASTRAR EXERCICIO [3]" << endl;
			cout << "CADASTRAR USUARIO   [4]" << endl;
			cout << "DIGITE UMA OPÇÃO DE CADASTRO (0 parar sair): ";
			cin >> opcao;
			switch (opcao) {
			case 1:
				insert_idioma(idiomas, idiomas_index, n, len);
				break;
			case 2:
				insert_licao(licoes, licoes_index, n, len);
				break;
			case 3:
				insert_exercicio(exercicios, exercicios_index, n, len);
				break;
			case 4:
				insert_usuario(usuarios, usuarios_index, n, len);
				break;
			case 0:
				break;
			}
			break;
		}
	
	};
}