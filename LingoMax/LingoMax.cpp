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



void barra_progresso(double porcentagem, int cor) {
	const int p = 101; 
	char progresso[p] = "";
	char progresso_blank[p] = "";
	if (porcentagem < 0.0) porcentagem = 0.0;
	if (porcentagem > 100.0) porcentagem = 100.0;

	int cont_barra = (int)(porcentagem);
	for (int i = 0; i < cont_barra; i++) {
		strcat_s(progresso, p, " ");
	}
	for (int i = cont_barra; i < p - 1; i++) {
		strcat_s(progresso_blank, p, " ");
	}
	
	cout << "\033[4;1;7;" << cor <<"m[" << progresso << "\033[0m" << progresso_blank << "]";
}
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
			cout << "Descrição: " << table[pos].descricao << endl;
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

void insert_licao(Licao table[], Licao_index index[], Idioma idioma[], Idioma_index idioma_index[], int n, int len[]) {
	system("clear||cls");
	char finalizar[2];
	cout << "========= CADASTRAR LIÇÃO =========" << endl;
	for (int i = len[1]; i < n; i++) {
		cout << "Código: ";
		cin >> table[i].cod_licao;
		cout << "Código idioma: ";
		cin >> table[i].cod_idioma;
		consulta_idioma(idioma, busca_idioma(idioma, idioma_index, len, table[i].cod_idioma));
		cout << "Total niveis: ";
		cin >> table[i].total_niveis;
		table[i].deletado = false;
		register_index_licao(table, index, len, i);
		len[1]++;
		cout << "===========================================" << endl;
		cout << "Deseja cadastrar outra lição?[S][N] ";
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

void insert_usuario(Usuario table[], Usuario_index index[], Idioma idioma[], Idioma_index idioma_index[], int n, int len[]) {
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
		consulta_idioma(idioma, busca_idioma(idioma, idioma_index, len, table[i].cod_idioma));
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
			insert_usuario(table, index, idioma, idioma_index, n, len);
			return;
		}
	}
}

/*================================== FIM INSERIR DADOS ==================================*/

/*================================== INICIO LEITURA EXAUSTIVA ==================================*/
void exaustiva_idioma(struct Idioma table[], struct Idioma_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	cout << "========= IDIOMAS =========" << endl;
	for (int k = 0; k < len[0]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			cout << "==================================" << endl;
			cout << "\nCod. Idioma: " << table[i].cod_idioma;
			cout << "\tDescrição: " << table[i].descricao << endl;
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
	cout << "========= LIÇÕES =========" << endl;
	for (int k = 0; k < len[1]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			cout << "==================================" << endl;
			cout << "\nCod. Lição: " << table[i].cod_licao;
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
	cout << "========= EXERCICIOS =========" << endl;
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
	cout << "========= USUARIOS =========" << endl;
	for (int k = 0; k < len[3]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			cout << "==================================" << endl;
			cout << "\nCod. Usuario: " << table[i].cod_usuario;
			cout << "\tNome: " << table[i].nome;
			cout << "\tCod. Idioma: " << table[i].cod_idioma;
			cout << "\tNivel atual: " << table[i].nivel_atual;
			cout << "\tPontuação total: " << table[i].pontuacao_total << endl;
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

/*================================== INICIO DELETAR DADOS ==================================*/

void delete_idioma(Idioma table[], Idioma_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	int cod, result;
	cout << "========= DELETAR IDIOMA =========" << endl;
	cout << "Codigo Idioma (-1 para cancelar): ";
	cin >> cod;
	if (cod >= 0) {
		result = busca_idioma(table, index, len, cod);
		if (result >= 0) {
			table[result].deletado = true;
			cout << "Idioma " << table[result].descricao << " deletado lógicamente!" << endl;
		}
		else {
			cout << "Registro não encontrado!" << endl;
		}
	}
	else {
		cout << "Instrução cancelada!" << endl;
	}
	cout << "==================================" << endl;
	cout << "Deseja deletar outro idioma?[S][N] ";
	cin >> finalizar;
	if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
		return;
	}
	else {
		delete_idioma(table, index, len);
		return;
	}
}

void delete_licao(Licao table[], Licao_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	int cod, result;
	cout << "========= DELETAR LIÇÃO =========" << endl;
	cout << "Codigo Lição (-1 para cancelar): ";
	cin >> cod;
	if (cod >= 0) {
		result = busca_licao(table, index, len, cod);
		if (result >= 0) {
			table[result].deletado = true;
			cout << "Lição " << table[result].cod_licao << " deletado lógicamente!" << endl;
		}
		else {
			cout << "Registro não encontrado!" << endl;
		}
	}
	else {
		cout << "Instrução cancelada!" << endl;
	}
	cout << "==================================" << endl;
	cout << "Deseja deletar outra lição?[S][N] ";
	cin >> finalizar;
	if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
		return;
	}
	else {
		delete_licao(table, index, len);
		return;
	}
}

void delete_exercicio(Exercicio table[], Exercicio_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	int cod, result;
	cout << "========= DELETAR EXERCICIO =========" << endl;
	cout << "Codigo Exercicio (-1 para cancelar): ";
	cin >> cod;
	if (cod >= 0) {
		result = busca_exercicio(table, index, len, cod);
		if (result >= 0) {
			table[result].deletado = true;
			cout << "Exercicio " << table[result].cod_exercicio << " deletado lógicamente!" << endl;
		}
		else {
			cout << "Registro não encontrado!" << endl;
		}
	}
	else {
		cout << "Instrução cancelada!" << endl;
	}
	cout << "==================================" << endl;
	cout << "Deseja deletar outro exercicio?[S][N] ";
	cin >> finalizar;
	if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
		return;
	}
	else {
		delete_exercicio(table, index, len);
		return;
	}
}

void delete_usuario(Usuario table[], Usuario_index index[], int len[]) {
	system("clear||cls");
	char finalizar[2];
	int cod, result;
	cout << "========= DELETAR USUARIO =========" << endl;
	cout << "Codigo Usuario (-1 para cancelar): ";
	cin >> cod;
	if (cod >= 0) {
		result = busca_usuario(table, index, len, cod);
		if (result >= 0) {
			table[result].deletado = true;
			cout << "Usuario " << table[result].nome << " deletado lógicamente!" << endl;
		}
		else {
			cout << "Registro não encontrado!" << endl;
		}
	}
	else {
		cout << "Instrução cancelada!" << endl;
	}
	cout << "==================================" << endl;
	cout << "Deseja deletar outro usuario?[S][N] ";
	cin >> finalizar;
	if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
		return;
	}
	else {
		delete_usuario(table, index, len);
		return;
	}
}
/*================================== FIM DELETAR DADOS ==================================*/

/*================================== INICIO REORGANIAZAR DADOS ==================================*/
void reorganizar_idioma(struct Idioma_index index[], struct Idioma_index newindex[], struct Idioma table[], struct Idioma newtable[], int len[]) {
	int j = -1;
	
	for (int k = 0; k < len[0]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			j++;
			newtable[j].cod_idioma = table[i].cod_idioma;
			strcpy_s(newtable[j].descricao, table[i].descricao);
			newtable[j].deletado = false;
			newindex[j].cod = table[i].cod_idioma;
			newindex[j].end = i;
		}
	}
	for (int l = 0; l < len[0]; l++) {
		table[l].cod_idioma = NULL;
		strcpy_s(table[l].descricao, NULL);
		table[l].deletado = NULL;
		index[l].cod = NULL;
		index[l].end = NULL;
	}
    len[0] = j + 1;
	for (int l = 0; l < len[0]; l++) {
		table[l].cod_idioma = newtable[l].cod_idioma;
		strcpy_s(table[l].descricao, newtable[l].descricao);
		table[l].deletado = newtable[l].deletado;
		index[l].cod = newindex[l].cod;
		index[l].end = newindex[l].end;
	}
}


void reorganizar_licao(struct Licao_index index[], struct Licao_index newindex[], struct Licao table[], struct Licao newtable[], int len[]) {
	int j = -1;

	for (int k = 0; k < len[1]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			j++;
			newtable[j].cod_licao = table[i].cod_licao;
			newtable[j].cod_idioma = table[i].cod_idioma;
			newtable[j].total_niveis = table[i].total_niveis;
			newtable[j].deletado = false;
			newindex[j].cod = newtable[j].cod_licao;
			newindex[j].end = j;
		}
	}
	for (int l = 0; l < len[1]; l++) {
		table[l].cod_licao = NULL;
		table[l].cod_idioma = NULL;
		table[l].total_niveis = NULL;
		table[l].deletado = NULL;
		index[l].cod = NULL;
		index[l].end = NULL;
	}
	len[1] = j + 1;
	for (int l = 0; l < len[1]; l++) {
		table[l].cod_licao = newtable[l].cod_licao;
		table[l].cod_idioma = newtable[l].cod_idioma;
		table[l].total_niveis = newtable[l].total_niveis;
		table[l].deletado = newtable[l].deletado;
		index[l].cod = newindex[l].cod;
		index[l].end = newindex[l].end;
	}
}

void reorganizar_exercicio(struct Exercicio_index index[], struct Exercicio_index newindex[], struct Exercicio table[], struct Exercicio newtable[], int len[]) {
	int j = -1;

	for (int k = 0; k < len[2]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			j++;
			newtable[j].cod_exercicio = table[i].cod_exercicio;
			newtable[j].nivel_dificuldade = table[i].nivel_dificuldade;
			newtable[j].pontos = table[i].pontos;
			strcpy_s(newtable[j].pergunta, table[i].pergunta);
			strcpy_s(newtable[j].resposta_correta, table[i].resposta_correta);
			newtable[j].deletado = false;
			newindex[j].cod = newtable[i].cod_exercicio;
			newindex[j].end = i; 
		}
	}
	for (int l = 0; l < len[2]; l++) {
		table[l].cod_exercicio = NULL;
		table[l].nivel_dificuldade = NULL;
		table[l].pontos = NULL;
		strcpy_s(table[l].pergunta, NULL);
		strcpy_s(table[l].resposta_correta, NULL);
		table[l].deletado = NULL;
		index[l].cod = NULL;
		index[l].end = NULL;
	}
	len[2] = j + 1;
	for (int l = 0; l < len[2]; l++) {
		table[l].cod_exercicio = newtable[l].cod_exercicio;
		table[l].nivel_dificuldade = newtable[l].nivel_dificuldade;
		table[l].pontos = newtable[l].pontos;
		strcpy_s(table[l].pergunta, newtable[l].pergunta);
		strcpy_s(table[l].resposta_correta, newtable[l].resposta_correta);
		table[l].deletado = newtable[l].deletado;
		index[l].cod = newindex[l].cod;
		index[l].end = newindex[l].end;
	}
}

void reorganizar_usuario(struct Usuario_index index[], struct Usuario_index newindex[], struct Usuario table[], struct Usuario newtable[], int len[]) {
	int j = -1;

	for (int k = 0; k < len[3]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			j++;
			newtable[j].cod_usuario = table[i].cod_usuario;
			newtable[j].cod_idioma = table[i].cod_idioma;
			newtable[j].nivel_atual = table[i].nivel_atual;
			newtable[j].pontuacao_total = table[i].pontuacao_total;
			strcpy_s(newtable[j].nome, table[i].nome);
			newtable[j].deletado = false;
			newindex[j].cod = newtable[i].cod_usuario;
			newindex[j].end = i;
		}
	}
	for (int l = 0; l < len[3]; l++) {
		table[l].cod_usuario = NULL;
		table[l].cod_idioma = NULL;
		table[l].nivel_atual = NULL;
		table[l].pontuacao_total = NULL;
		strcpy_s(table[l].nome, NULL);
		table[l].deletado = NULL;
		index[l].cod = NULL;
		index[l].end = NULL;
	}
	len[3] = j + 1;
	for (int l = 0; l < len[3]; l++) {
		table[l].cod_usuario = newtable[l].cod_usuario;
		table[l].cod_idioma = newtable[l].cod_idioma;
		table[l].nivel_atual = newtable[l].nivel_atual;
		table[l].pontuacao_total = newtable[l].pontuacao_total;
		strcpy_s(table[l].nome, newtable[l].nome);
		table[l].deletado = newtable[l].deletado;
		index[l].cod = newindex[l].cod;
		index[l].end = newindex[l].end;
	}
}


/*================================== FIM REORGANIAZAR DADOS ==================================*/

/*================================== INICIO PRATICAR ==================================*/

int escolher_usuario(Usuario table[], Usuario_index index[], Idioma idiomas[], Idioma_index idiomas_index[], int len[]) {
	int cod_usuario;
	int ret;
	char finalizar[2];
	cout << "========= ESCOLHER USUARIO =========" << endl;
	for (int k = 0; k < len[3]; k++) {
		int i = index[k].end;
		if (!(table[i].deletado)) {
			cout << "\nCod.: " << table[i].cod_usuario;
			cout << "\tNome: " << table[i].nome;
			cout << "\tIdioma: " << idiomas[busca_idioma(idiomas, idiomas_index, len, table[i].cod_idioma)].descricao << endl;
		}
	}
	cout << "Digite o código do usuario(-1 para cancelar): ";
	cin >> cod_usuario;
	if (cod_usuario == -1) {
		return -1;
	}
	ret = busca_usuario(table, index, len, cod_usuario);
	if (ret == -1) {
		cout << "Usuario não existente!" << endl;
		cout << "==================================" << endl;
		cout << "Deseja tentar outro usuario?[S][N] ";
		cin >> finalizar;
		if (strcmp(finalizar, "N") == 0 || strcmp(finalizar, "n") == 0) {
			return -1;
		}
		else {
			return escolher_usuario(table, index, idiomas, idiomas_index, len);
		}
	}
	else {
		return ret;
	}
}

int escolher_nivel(Licao table[], Licao_index index[]) {

}

void praticar(Idioma idiomas[], Idioma_index idiomas_index[], Licao licoes[], Licao_index licoes_index[], Exercicio exercicios[], Exercicio_index exercicios_index[], Usuario usuarios[], Usuario_index usuarios_index[], int len[]) {
	int end_usuario;
	int nivel_exercicio;
	int cor;
	float percen;
	end_usuario = escolher_usuario(usuarios, usuarios_index, idiomas, idiomas_index, len);
	system("clear||cls");
	if (end_usuario == -1) {
		return;
	}
	cout << "Usuário: " << usuarios[end_usuario].nome << "\tNivel atual: " << usuarios[end_usuario].nivel_atual << endl;
	percen = 34;
	if (percen > 33 && percen < 70) {
		cor = 33;
	}
	else if (percen >= 70) {
		cor = 32;
	}
	barra_progresso(percen, cor);
	cin >> nivel_exercicio;
}
/*================================== FIM PRATICAR ==================================*/

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

	Idioma idiomas_bkp[n];
	Idioma_index idiomas_index_bkp[n];

	Licao licoes[n];
	Licao_index licoes_index[n];

	Licao licoes_bkp[n];
	Licao_index licoes_index_bkp[n];

	Exercicio exercicios[n];
	Exercicio_index exercicios_index[n];

	Exercicio exercicios_bkp[n];
	Exercicio_index exercicios_index_bkp[n];

	Usuario usuarios[n];
	Usuario_index usuarios_index[n];

	Usuario usuarios_bkp[n];
	Usuario_index usuarios_index_bkp[n];
	int cor = 31;
	for (int i = 0; i < 100; i = i +3) {
		cout << "Iniciando LingoMax..." << endl;
		if (i > 33 && i < 70) {
			cor = 33;
		}
		else if (i >= 70) {
			cor = 32;
		}
		barra_progresso(i, cor);
		system("clear||cls");
	}
	while (true) {
		system("clear||cls");
		cout << "---------- MENU ----------" << endl;
		cout << "\033[32mCADASTROS        [1]\033[0m" << endl;
		cout << "\033[34mLISTAGEM         [2]\033[0m" << endl;
		cout << "\033[31mDELETAR          [3]\033[0m" << endl;
		cout << "\033[33mREORGANIZAR      [4]\033[0m" << endl;
		cout << "\033[1;7;35mPRATICAR         [5]\033[0m" << endl;
		cout << "DIGITE UMA OPÇÃO: ";
		cin >> opcao;
		system("clear||cls");
		switch (opcao) {
		case 1:
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
				insert_licao(licoes, licoes_index, idiomas, idiomas_index, n, len);
				break;
			case 3:
				insert_exercicio(exercicios, exercicios_index, n, len);
				break;
			case 4:
				insert_usuario(usuarios, usuarios_index, idiomas, idiomas_index, n, len);
				break;
			case 0:
				break;
			}
			break;
		case 2:
			cout << "---------- LISTAGEM ----------" << endl;
			cout << "LISTAR IDIOMAS    [1]" << endl;
			cout << "LISTAR LIÇÕES     [2]" << endl;
			cout << "LISTAR EXERCICIOS [3]" << endl;
			cout << "LISTAR USUARIOS   [4]" << endl;
			cout << "DIGITE UMA OPÇÃO DE LISTAGEM (0 parar sair): ";
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
		case 3:
			cout << "---------- DELETAR ----------" << endl;
			cout << "DELETAR IDIOMA    [1]" << endl;
			cout << "DELETAR LIÇÃO     [2]" << endl;
			cout << "DELETAR EXERCICIO [3]" << endl;
			cout << "DELETAR USUARIO   [4]" << endl;
			cout << "DIGITE UMA OPÇÃO DE DELETAR (0 parar sair): ";
			cin >> opcao;
			switch (opcao) {
			case 1:
				delete_idioma(idiomas,idiomas_index,len);
				break;
			case 2:
				delete_licao(licoes, licoes_index, len);
				break;
			
			case 3:
				delete_exercicio(exercicios, exercicios_index, len);
				break;
			case 4:
				delete_usuario(usuarios, usuarios_index, len);
				break;
			}
			break;
		case 4:
			cout << "---------- REORGANIZAR ----------" << endl;
			cout << "REORGANIZAR IDIOMA    [1]" << endl;
			cout << "REORGANIZAR LIÇÃO     [2]" << endl;
			cout << "REORGANIZAR EXERCICIO [3]" << endl;
			cout << "REORGANIZAR USUARIO   [4]" << endl;
			cout << "DIGITE UMA OPÇÃO DE REORGANIZAR (0 parar sair): ";
			cin >> opcao;
			switch (opcao) {
			case 1:
				reorganizar_idioma(idiomas_index, idiomas_index_bkp, idiomas, idiomas_bkp, len);
				break;
			case 2:
				reorganizar_licao(licoes_index, licoes_index_bkp, licoes, licoes_bkp, len);
				break;
			case 3:
				reorganizar_exercicio(exercicios_index, exercicios_index_bkp, exercicios, exercicios_bkp, len);
				break;
			case 4:
				reorganizar_usuario(usuarios_index, usuarios_index_bkp, usuarios, usuarios_bkp, len);
				break;

			}
			break;
		case 5:
			praticar(idiomas, idiomas_index, licoes, licoes_index, exercicios, exercicios_index, usuarios, usuarios_index, len);
			break;
		}
		
	};

}