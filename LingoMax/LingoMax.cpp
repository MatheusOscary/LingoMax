#include <iostream>

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

}

int main() {
	const int n = 1000;
	int len[4];
	/*
		len[0] -> Idioma
		len[1] -> Licao
		len[2] -> Exercicio
		len[3] -> Usuario
	*/
	Idioma idiomas[n];
	Idioma_index idiomas_index[n];
}