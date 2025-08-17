#include <bits/stdc++.h>
#include <limits>
using namespace std;

int algoritmo_hungaro(vector<vector<int>> &custos) {
  int n = custos.size();
  assert(n == custos[0].size());

  vector<vector<int>> cmat;
  vector<vector<int>> mmat(n, vector<int>(n, 0));

  vector<bool> xcobertos(n, false);
  vector<bool> ycobertos(n, false);

  vector<bool> xestrelas(n, false);
  vector<bool> yestrelas(n, false);

  cmat = custos;

  // reduzindo as linhas e colunas

  // linhas - passo 1
  for (int i = 0; i < n; i++) {

    int minl = cmat[i][0];

    for (int j = 0; j < n; j++) {
      if (cmat[i][j] < minl) {
        minl = cmat[i][j];
      }
    }

    for (int j = 0; j < n; j++) {
      cmat[i][j] -= minl;
    }
  }

  // colunas - passo 2
  for (int j = 0; j < n; j++) {
    int minc = cmat[0][j];

    for (int i = 0; i < n; i++) {
      if (cmat[i][j] < minc) {
        minc = cmat[i][j];
      }
    }

    for (int i = 0; i < n; i++) {
      cmat[i][j] -= minc;
    }
  }

  // marcando os zeros iniciais - passos 3

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (cmat[i][j] == 0 && !xestrelas[i] && !yestrelas[j]) {
        mmat[i][j] = 1;
        xestrelas[i] = true;
        yestrelas[j] = true;
        ycobertos[j] = true;
      }
    }
  }

  while (true) {
    // procurando caminhos de aumento - passo 4
    while (true) {
      int row = -1, col = -1;

      // procurando por um zero não coberto
      for (int i = 0; i < n; i++) {
        if (!xcobertos[i])
          for (int j = 0; j < n; j++) {
            if (!ycobertos[j] && cmat[i][j] == 0) {
              row = i;
              col = j;
              break;
            }
          }
        if (row != -1)
          break;
      }

      if (row == -1)
        break; // zero não coberto não achado

      mmat[row][col] = 2; // marcando o zero (prime)

      int estrela_col = -1;

      for (int i = 0; i < n; i++)
        if (mmat[row][i] == 1) {
          estrela_col = i;
          break;
        }

      if (estrela_col != -1) {
        xcobertos[row] =
            true; // cobrindo a linha, já que temos outro zero na mesma linha
        ycobertos[estrela_col] = false;
      } else {
        vector<pair<int, int>> caminho;
        caminho.push_back({row, col});
        bool f = false;

        while (!f) {
          int r = caminho.back()
                      .first; // linha do último elemento adicionado ao caminho
          int c =
              caminho.back()
                  .second; // coluna do último elemento adicionado ao caminho

          int estrela_lin = -1;
          for (int i = 0; i < n; i++) {
            if (mmat[i][c] == 1) {
              estrela_lin = i;
              break;
            }
          }

          if (estrela_lin == -1) {
            f = true;
          } else {
            caminho.push_back({estrela_lin, c});

            int prime_col = -1;

            for (int j = 0; j < n; j++) {
              if (mmat[estrela_lin][j] == 2) {
                prime_col = j;
                break;
              }
            }

            caminho.push_back({estrela_lin, prime_col});
          }
        }
        // agora com todos os caminhos achados, iremos trocar todas as estrelas
        // pelos primes

        for (const auto &c : caminho) {
          if (mmat[c.first][c.second] == 1) {
            mmat[c.first][c.second] = 0;
          } else {
            mmat[c.first][c.second] = 1;
          }
        }

        for (int i = 0; i < n; i++) {
          xcobertos[i] = false;
          ycobertos[i] = false;

          for (int j = 0; j < n; j++) {
            if (mmat[i][j] == 2)
              mmat[i][j] = 0;
          }
        }

        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            if (mmat[i][j] == 1) {
              ycobertos[j] = true;
            }
          }
        }
      }
    }

    // observando se já consegue um atribuição ótima - passo 5
    int estrelas = 0;

    for (int i = 0; i < n; i++) {
      if (ycobertos[i] || xcobertos[i])
        estrelas++;
    }

    if (estrelas == n)
      break;

    // se não conseguirmos iremos subtrair o menor elemento não coberto dos
    // elementos não cobertos
    int min = numeric_limits<int>::max();

    for (int i = 0; i < n; i++) {
      if (!xcobertos[i])
        for (int j = 0; j < n; j++) {
          if (!ycobertos[j] && cmat[i][j] < min)
            min = cmat[i][j];
        }
    }

    // subtraindo o menor elemento das linhas não cobertas
    for (int i = 0; i < n; i++) {
      if (!xcobertos[i]) {
        for (int j = 0; j < n; j++) {
          cmat[i][j] -= min;
        }
      }
    }

    // adicionando o menor elemento as colunas cobertas
    for (int j = 0; j < n; j++) {
      if (ycobertos[j])
        for (int i = 0; i < n; i++)
          cmat[i][j] += min;
    }
  }

  int custo = 0;

  // somando os custos das linhas selecionadas
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (mmat[i][j] == 1) {
        custo += custos[i][j];
      }
    }
  }

  return custo;
}

int main() {
  int casos_teste;
  int m, n;

  cin >> casos_teste;

  while (casos_teste--) {
    // lendo m e n
    cin >> n;
    cin >> m;
    int camisas_tam_diferentes =
        n / 6; // quantidade de camisas para cada tamanho

    // montando a matriz
    vector<vector<int>> custos(n, vector<int>(n, 10));

    for (int i = m; i < n; i++) {
      for (int j = 0; j < n; j++) {
        custos[i][j] = 0;
      }
    }

    // preenchendo com custo zero as possibilidades de camisas
    while (m--) {
      string a, b; // camisas possíveis
      int offset;  // deslocamento para preencher as possibilidades de camisa
                   // possibilidade de camisa = custo 0, se não custo 10

      cin >> a;
      cin >> b;

      if (a == "XS") {
        offset = camisas_tam_diferentes * 0;
      } else if (a == "S") {
        offset = camisas_tam_diferentes * 1;
      } else if (a == "M") {
        offset = camisas_tam_diferentes * 2;
      } else if (a == "L") {
        offset = camisas_tam_diferentes * 3;
      } else if (a == "XL") {
        offset = camisas_tam_diferentes * 4;
      } else if (a == "XXL") {
        offset = camisas_tam_diferentes * 5;
      }

      for (int i = 0; i < camisas_tam_diferentes; i++) {
        custos[m][i + offset] = 0;
      }

      if (b == "XS") {
        offset = camisas_tam_diferentes * 0;
      } else if (b == "S") {
        offset = camisas_tam_diferentes * 1;
      } else if (b == "M") {
        offset = camisas_tam_diferentes * 2;
      } else if (b == "L") {
        offset = camisas_tam_diferentes * 3;
      } else if (b == "XL") {
        offset = camisas_tam_diferentes * 4;
      } else if (b == "XXL") {
        offset = camisas_tam_diferentes * 5;
      }

      for (int i = 0; i < camisas_tam_diferentes; i++) {
        custos[m][i + offset] = 0;
      }
    }

    // matriz pronta
    // agora começa o algoritmo

    int custo = algoritmo_hungaro(custos);

    if (custo == 0) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}
