#include <iostream>
#include <thread>
#include "utils.hpp"

// Platform-specific headers for non-blocking input
#ifdef _WIN32
#include <conio.h> // For _kbhit and _getch
#else
#include <termios.h> // For tcsetattr, tcgetattr
#include <unistd.h>  // For STDIN_FILENO
#include <fcntl.h>   // For fcntl, F_SETFL, O_NONBLOCK
#endif

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
// Global original terminal settings for Linux
#ifndef _WIN32
static struct termios original_termios;
static bool terminal_mode_set = false;

// Function to set terminal to raw mode (non-blocking, no echo)
void set_terminal_raw_mode() {
    if (terminal_mode_set) return; // Already set
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    raw.c_cc[VMIN] = 0;  // Minimum number of characters for non-canonical read
    raw.c_cc[VTIME] = 0; // Timeout in tenths of a second for non-canonical read
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    // Set stdin to non-blocking
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    terminal_mode_set = true;
}

// Function to restore terminal to original mode
void restore_terminal_mode() {
    if (!terminal_mode_set) return; // Not set, nothing to restore
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);

    // Restore stdin to blocking
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    terminal_mode_set = false;
}
#endif

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
  bool skip_delay = false; // New flag

#ifndef _WIN32
  set_terminal_raw_mode(); // Set raw mode for non-blocking input on Linux
#endif

  for (char c : text) {
    std::cout << c << std::flush;

    // Check for user input to skip delay
#ifdef _WIN32
    if (_kbhit()) {
      char key = _getch();
      if (key == '\r' || key == '\n') { // Enter key: '\r' for Windows, '\n' after read is possible
        skip_delay = true;
      }
    }
#else
    char buffer[1];
    int bytesRead = read(STDIN_FILENO, buffer, 1);
    if (bytesRead > 0) {
      if (buffer[0] == '\n' || buffer[0] == '\r') { // Enter key
        skip_delay = true;
      }
    }
#endif

    if (c == '\033')
      escape_code_activated = true;

    if (!escape_code_activated && !skip_delay) // Apply delay only if not skipping
      std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

    if (escape_code_activated && c == 'm')
      escape_code_activated = false;
  }
  std::cout << std::endl;

#ifndef _WIN32
  restore_terminal_mode(); // Restore original mode on Linux
#endif
}

void wait_enter() {
  std::cout << GREEN << "Pressione Enter para continuar..." << RESET;
  std::cin.get();
}
