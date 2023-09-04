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

/*================================== INICIO BUSCA BINARIA ==================================*/

int busca_idioma(struct Idioma table[], struct Idioma_index index[], int len[], int cod) {
	int i = 0, f = len[0] - 1;
	int m = (i + f) / 2;
	for (; f >= i && cod != index[m].cod; m = (i + f) / 2) {
		if (cod > index[m].cod)
			i = m + 1;
		else
			f = m - 1;
	}
	if (cod == index[m].cod) {
		return index[m].end;
	}
	else
		return -1;
}

int busca_licao(struct Licao table[], struct Licao_index index[], int len[], int cod) {
	int i = 0, f = len[1] - 1;
	int m = (i + f) / 2;
	for (; f >= i && cod != index[m].cod; m = (i + f) / 2) {
		if (cod > index[m].cod)
			i = m + 1;
		else
			f = m - 1;
	}
	if (cod == index[m].cod) {
		return index[m].end;
	}
	else
		return -1;
}

int busca_exercicio(struct Exercicio table[], struct Exercicio_index index[], int len[], int cod) {
	int i = 0, f = len[2] - 1;
	int m = (i + f) / 2;
	for (; f >= i && cod != index[m].cod; m = (i + f) / 2) {
		if (cod > index[m].cod)
			i = m + 1;
		else
			f = m - 1;
	}
	if (cod == index[m].cod) {
		return index[m].end;
	}
	else
		return -1;
}

int busca_usuario(struct Usuario table[], struct Usuario_index index[], int len[], int cod) {
	int i = 0, f = len[3] - 1;
	int m = (i + f) / 2;
	for (; f >= i && cod != index[m].cod; m = (i + f) / 2) {
		if (cod > index[m].cod)
			i = m + 1;
		else
			f = m - 1;
	}
	if (cod == index[m].cod) {
		return index[m].end;
	}
	else
		return -1;
}

void consulta_idioma(struct Idioma table[], int pos) {
	if (pos < 0) {
		cout << "Idioma indefinido!" << endl;
	}
	else {
		if (!(table[pos].deletado)) {
			cout << "Descri��o: " << table[pos].descricao << endl;
		}
		else {
			cout << "Idioma indefinido!" << endl;
		}
	}
}
/*================================== FIM BUSCA BINARIA ==================================*/

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
		cout << "C�digo: ";
		cin >> table[i].cod_idioma;
		cout << "Descri��o: ";
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

void insert_licao(Licao table[], Licao_index index[], Idioma idioma[], Idioma_index idioma_index[], int n, int len[]) {
	system("clear||cls");
	char finalizar[2];
	cout << "========= CADASTRAR LI��O =========" << endl;
	for (int i = len[1]; i < n; i++) {
		cout << "C�digo: ";
		cin >> table[i].cod_licao;
		cout << "C�digo idioma: ";
		cin >> table[i].cod_idioma;
		consulta_idioma(idioma, busca_idioma(idioma, idioma_index, len, table[i].cod_idioma));
		cout << "Total niveis: ";
		cin >> table[i].total_niveis;
		table[i].deletado = false;
		register_index_licao(table, index, len, i);
		len[1]++;
		cout << "===========================================" << endl;
		cout << "Deseja cadastrar outra li��o?[S][N] ";
		cin >> finalizar;
		if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
			return;
		}
		else {
			insert_licao(table, index, idioma, idioma_index, n, len);
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
		cout << "C�digo: ";
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
		cout << "C�digo: ";
		cin >> table[i].cod_usuario;
		cout << "Nome: ";
		cin.ignore();
		cin.getline(table[i].nome, 60);
		cout << "C�digo idioma: ";
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

/*================================== INICIO LEITURA EXAUSTIVA ==================================*/
void exaustiva_idioma(struct Idioma table[], struct Idioma_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	for (int k = 0; k < len[0]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			cout << "==================================" << endl;
			cout << "\nCod. Idioma: " << table[i].cod_idioma;
			cout << "\tDescri��o: " << table[i].descricao << endl;
		}
	}
	cout << "==================================" << endl;
	cout << "Deseja listar novamente?[S][N] ";
	cin >> finalizar;
	if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
		return;
	}
	else {
		exaustiva_idioma(table, index, len);
		return;
	}
}

void exaustiva_licao(struct Licao table[], struct Licao_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	for (int k = 0; k < len[1]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			cout << "==================================" << endl;
			cout << "\nCod. Li��o: " << table[i].cod_licao;
			cout << "\tCod. Idioma: " << table[i].cod_idioma;
			cout << "\tTotal niveis: " << table[i].total_niveis << endl;
		}
	}
	cout << "==================================" << endl;
	cout << "Deseja listar novamente?[S][N] ";
	cin >> finalizar;
	if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
		return;
	}
	else {
		exaustiva_licao(table, index, len);
		return;
	}
}

void exaustiva_exercicio(struct Exercicio table[], struct Exercicio_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	for (int k = 0; k < len[2]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			cout << "==================================" << endl;
			cout << "\nCod. Exercicio: " << table[i].cod_exercicio;
			cout << "\tNivel de dificuldade: " << table[i].nivel_dificuldade;
			cout << "\tPergunta: " << table[i].pergunta;
			cout << "\tResposta: " << table[i].resposta_correta;
			cout << "\tPontos: " << table[i].pontos << endl;
		}
	}
	cout << "==================================" << endl;
	cout << "Deseja listar novamente?[S][N] ";
	cin >> finalizar;
	if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
		return;
	}
	else {
		exaustiva_exercicio(table, index, len);
		return;
	}
}

void exaustiva_usuario(struct Usuario table[], struct Usuario_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	for (int k = 0; k < len[3]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			cout << "==================================" << endl;
			cout << "\nCod. Usuario: " << table[i].cod_usuario;
			cout << "\tNome: " << table[i].nome;
			cout << "\tCod. Idioma: " << table[i].cod_idioma;
			cout << "\tNivel atual: " << table[i].nivel_atual;
			cout << "\tPontua��o total: " << table[i].pontuacao_total << endl;
		}
	}
	cout << "==================================" << endl;
	cout << "Deseja listar novamente?[S][N] ";
	cin >> finalizar;
	if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
		return;
	}
	else {
		exaustiva_usuario(table, index, len);
		return;
	}
}
/*================================== FIM LEITURA EXAUSTIVA ==================================*/



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
		cout << "LISTAGEM         [2]" << endl;
		cout << "DIGITE UMA OP��O: ";
		cin >> opcao;
		system("clear||cls");
		switch (opcao) {
		case 1:
			cout << "---------- CADASTROS ----------" << endl;
			cout << "CADASTRAR IDIOMA    [1]" << endl;
			cout << "CADASTRAR LI��O     [2]" << endl;
			cout << "CADASTRAR EXERCICIO [3]" << endl;
			cout << "CADASTRAR USUARIO   [4]" << endl;
			cout << "DIGITE UMA OP��O DE CADASTRO (0 parar sair): ";
			cin >> opcao;
			switch (opcao) {
			case 1:
				insert_idioma(idiomas, idiomas_index, n, len);
				break;
			case 2:
				insert_licao(licoes, licoes_index, idiomas, idiomas_index, n, len);
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
		case 2:
			cout << "---------- LISTAGEM ----------" << endl;
			cout << "LISTAR IDIOMAS    [1]" << endl;
			cout << "LISTAR LI��ES     [2]" << endl;
			cout << "LISTAR EXERCICIOS [3]" << endl;
			cout << "LISTAR USUARIOS   [4]" << endl;
			cout << "DIGITE UMA OP��O DE LISTAGEM (0 parar sair): ";
			cin >> opcao;
			switch (opcao) {
			case 1:
				exaustiva_idioma(idiomas, idiomas_index, len);
				break;
			case 2:
				exaustiva_licao(licoes, licoes_index, len);
				break;
			case 3:
				exaustiva_exercicio(exercicios, exercicios_index, len);
				break;
			case 4:
				exaustiva_usuario(usuarios, usuarios_index, len);
				break;
			case 0:
				break;
			}
			
			break;
		}
	
	};
}