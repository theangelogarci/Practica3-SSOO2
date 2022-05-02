#ifndef _COLORS_
#define _COLORS_

#define RESET  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CIAN  "\x1B[36m"
#define WHITE  "\x1B[37m"
#define ULINE  "\x1B[4m"


#define ERROR(x) RED x RESET
#define CORRECT(x) GREEN x RESET
#define WARNING(x) YELLOW x RESET 
#define RESULT(x) MAGENTA x RESET 
#define LINE(x) CIAN

#define BOLD(x) "\x1B[1m" x RESET
#define UNDERLINE(x) ULINE x RESET

#endif