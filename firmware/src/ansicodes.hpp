/* simple listing of ansi codes to control terminal coloring
(c) Tom Powell, under the GPL
uses c++11 features
*/
#include <string.h>
namespace ANSI {
    const char* reset = "\x1b[0m";
    //backgrounds
    class bk {
        public:
        //normal
            const char* d_black = "\x1b[40m"; //black
            const char* d_red = "\x1b[41m"; // dark red
            const char* d_green = "\x1b[42m"; //dark green
            const char* d_yellow = "\x1b[43m"; //dark yellow
            const char* d_blue = "\x1b[44m"; //dark blue
            const char* d_magenta = "\x1b[45m"; //dark magenta
            const char* d_cyan = "\x1b[46m"; //dark cyan
            const char* d_white = "\x1b[47m"; //dark white
        //light
            const char* l_black = "\x1b[100m"; //gray
            const char* l_red = "\x1b[101m"; //light red
            const char* l_green = "\x1b[102m"; //light green
            const char* l_yellow = "\x1b[103m"; //light yellow
            const char* l_blue = "\x1b[104m"; //light blue
            const char* l_magenta = "\x1b[105m"; //light magenta
            const char* l_cyan = "\x1b[106m"; //light cyan
            const char* l_white = "\x1b[107m"; //light white
        //special
            const char* def = "\x1b[49";
    };
    //foreground text colors
    class fr {
        public:
        //normal
            const char* d_black = "\x1b[30m"; //black
            const char* d_red = "\x1b[31m"; // dark red
            const char* d_green = "\x1b[32m"; //dark green
            const char* d_yellow = "\x1b[33m"; //dark yellow
            const char* d_blue = "\x1b[34m"; //dark blue
            const char* d_magenta = "\x1b[35m"; //dark magenta
            const char* d_cyan = "\x1b[36m"; //dark cyan
            const char* d_white = "\x1b[37m"; //dark white
        //light
            const char* l_black = "\x1b[90m"; //gray
            const char* l_red = "\x1b[91m"; //light red
            const char* l_green = "\x1b[92m"; //light green
            const char* l_yellow = "\x1b[93m"; //light yellow
            const char* l_blue = "\x1b[94m"; //light blue
            const char* l_magenta = "\x1b[95m"; //light magenta
            const char* l_cyan = "\x1b[96m"; //light cyan
            const char* l_white = "\x1b[97m"; //light white
        //special
            const char* def = "\x1b[39m";
    };
    //text effects
    class ef {
        public:
        //normal
            const char* bold = "\x1b[1m"; //bold
            const char* underline = "\x1b[4m"; //underline
            const char* slow_blink = "\x1b[5m"; //slow blinking text
            const char* fast_blink = "\x1b[6m"; //fast blinking text
            const char* reverse = "\x1b[7m"; //invert
            const char* no_underline = "\x1b[24m"; //remove underline
            const char* positive = "\x1b[27m"; // uninvert
            const char* d_white = "\x1b[37m"; //dark white
    };
}
