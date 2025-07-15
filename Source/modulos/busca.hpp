#ifndef BUSCA_H
#define BUSCA_H

#include "../utils/utils.hpp"
#include <string>
#include <vector>

class BuscaSequencial {
private:
  std::vector<std::string> log_caotico;
  const std::string narrativa;

public:
  BuscaSequencial();
  void run();
  bool busca(std::vector<std::string> arquivos, std::string nome_arquivo);
};

class BuscaBinaria {
private:
  struct SetorInfo {
    int id;
    std::string name;
  };

  std::vector<SetorInfo> setorArq;
  const std::string narrativa;

public:
  BuscaBinaria();
  void run();
  bool busca(std::vector<SetorInfo> setores, int id_setor, int ind_esq,
             int ind_dir);
};

class BuscaRabinKarp {
private:
  std::string arquivo_log;
  const std::string narrativa;

public:
  BuscaRabinKarp();
  void run();
  bool busca(std::string texto, std::string subtexto, int d, int q);
};

#endif
