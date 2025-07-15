#include <iostream>
#include <thread>
#include "utils.hpp"

// Códigos de cor ANSI
const std::string RESET = "\033[0m";
const std::string BLACK = "\033[30m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string BOLD = "\033[1m";

// Função para limpar a tela
void clean_screen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Função para imprimir textos na tela lentamente
void pretty_print(const std::string &text, int delay_ms) {
  bool escape_code_activated = false;
  for (char c : text) {
    std::cout << c << std::flush;
    if (c == '\033')
      escape_code_activated = true;
    if (!escape_code_activated)
      std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    if (escape_code_activated && c == 'm')
      escape_code_activated = false;
  }
  std::cout << std::endl;
}

void wait_enter() {
  std::cout << GREEN << "Pressione Enter para continuar..." << RESET;
  std::cin.get();
}
