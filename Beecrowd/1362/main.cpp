#include <bits/stdc++.h>
#include <limits>
using namespace std;

int algoritmo_hungaro(const vector<vector<int>> &custos) {
  int J = custos.size();
  int W = custos[0].size();
  int inf = numeric_limits<int>::max();

  vector<int> job(W + 1, -1); // voluntario relacionado a iésima camiseta
  vector<int> ys(J);          // potencial para linha
  vector<int> yt(W + 1);      // potencial para coluna

  for (int jCur = 0; jCur < J; jCur++) {
    int wCur = W;
    job[wCur] = jCur;

    vector<int> minTo(W + 1, inf);
    vector<int> prev(W + 1, -1);
    vector<bool> inZ(W + 1);

    while (job[wCur] != -1) {
      inZ[wCur] = true;
      const int j = job[wCur];
      int delta = inf;
      int wNext;

      for (int w = 0; w < W; w++) {
        if (!inZ[w]) {
          if (minTo[w] > (custos[j][w] - ys[j] - yt[w])) {
            prev[w] = wCur;
            minTo[w] = custos[j][w] - ys[j] - yt[w];
          }
          if (delta > minTo[w]) {
            wNext = w;
            delta = minTo[w];
          }
        }
      }

      for (int w = 0; w <= W; w++) {
        if (inZ[w]) {
          ys[job[w]] += delta;
          yt[w] -= delta;
        } else {
          minTo[w] -= delta;
        }
      }
      wCur = wNext;
    }

    for (int w; wCur != W; wCur = w)
        job[wCur] = job[w = prev[wCur]];
  }

  return -yt[W];
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
    vector<vector<int>> custos(
        m, vector<int>(n, 10));

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
