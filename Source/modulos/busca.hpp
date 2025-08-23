#ifndef BUSCA_H
#define BUSCA_H

#include <bits/stdc++.h>

using namespace std;

class BuscaSequencial {
private:
  vector<string> log_caotico;
  const string narrativa;

public:
  BuscaSequencial();
  void run();
  bool busca(vector<string> arquivos, string nome_arquivo);
};

class BuscaBinaria {
private:
  struct SetorInfo {
    int id;
    string name;
  };

  vector<SetorInfo> setorArq;
  const string narrativa;

public:
  BuscaBinaria();
  void run();
  bool busca(vector<SetorInfo> setores, int id_setor, int ind_esq,
             int ind_dir);
};

class BuscaRabinKarp {
private:
  string arquivo_log;
  const string narrativa;

public:
  BuscaRabinKarp();
  void run();
  bool busca(string texto, string subtexto, int d, int q);
};

#endif
