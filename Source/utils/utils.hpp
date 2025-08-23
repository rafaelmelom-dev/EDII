#ifndef UTILS_H
#define UTILS_H


#include <string>
using namespace std;

// Códigos de cor ANSI
extern const string RESET;
extern const string BLACK;
extern const string RED;
extern const string GREEN;
extern const string YELLOW;
extern const string BLUE;
extern const string MAGENTA;
extern const string CYAN;
extern const string WHITE;
extern const string BOLD;

void clean_screen();
void pretty_print(const string &text, int delay_ms);
void wait_enter();

#endif
