#ifndef UTILS_H
#define UTILS_H


#include <string>

// Códigos de cor ANSI
extern const std::string RESET;
extern const std::string BLACK;
extern const std::string RED;
extern const std::string GREEN;
extern const std::string YELLOW;
extern const std::string BLUE;
extern const std::string MAGENTA;
extern const std::string CYAN;
extern const std::string WHITE;
extern const std::string BOLD;

void clean_screen();
void pretty_print(const std::string &text, int delay_ms);
void wait_enter();

#endif
