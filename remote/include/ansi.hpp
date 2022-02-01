//table of ansi escape codes
namespace ansi{
    typedef char ansi_s[5]; //short escape code
    typedef char ansi_n[6]; //normal escape code
    typedef char ansi_l[7]; //long escape code
    ansi_s reset = "\x1b[0m";
    struct bk {
        //normal
            ansi_n d_black = "\x1b[40m"; //black
            ansi_n d_red = "\x1b[41m"; // dark red
            ansi_n d_green = "\x1b[42m"; //dark green 
            ansi_n d_yellow = "\x1b[43m"; //dark yellow
            ansi_n d_blue = "\x1b[44m"; //dark blue
            ansi_n d_magenta = "\x1b[45m"; //dark magenta
            ansi_n d_cyan = "\x1b[46m"; //dark cyan
            ansi_n d_white = "\x1b[47m"; //dark white
        //light 
            ansi_l l_black = "\x1b[100m"; //gray
            ansi_l l_red = "\x1b[101m"; //light red 
            ansi_l l_green = "\x1b[102m"; //light green
            ansi_l l_yellow = "\x1b[103m"; //light yellow
            ansi_l l_blue = "\x1b[104m"; //light blue
            ansi_l l_magenta = "\x1b[105m"; //light magenta
            ansi_l l_cyan = "\x1b[106m"; //light cyan
            ansi_l l_white = "\x1b[107m"; //light white
        //special
            ansi_n def = "\x1b[49m";
    };
    //foreground text colors
    struct fr {
        //normal
            ansi_l d_black = "\x1b[30m"; //black
            ansi_l d_red = "\x1b[31m"; // dark red
            ansi_l d_green = "\x1b[32m"; //dark green 
            ansi_l d_yellow = "\x1b[33m"; //dark yellow
            ansi_l d_blue = "\x1b[34m"; //dark blue
            ansi_l d_magenta = "\x1b[35m"; //dark magenta
            ansi_l d_cyan = "\x1b[36m"; //dark cyan
            ansi_l d_white = "\x1b[37m"; //dark white
        //light 
            ansi_n l_black = "\x1b[90m"; //gray
            ansi_n l_red = "\x1b[91m"; //light red 
            ansi_n l_green = "\x1b[92m"; //light green
            ansi_n l_yellow = "\x1b[93m"; //light yellow
            ansi_n l_blue = "\x1b[94m"; //light blue
            ansi_n l_magenta = "\x1b[95m"; //light magenta
            ansi_n l_cyan = "\x1b[96m"; //light cyan
            ansi_n l_white = "\x1b[97m"; //light white
        //special
            ansi_n def = "\x1b[39m";
    };
    //text effects
    struct ef {
        char bold[5] = "\x1b[1m"; //bold
        ansi_s underline = "\x1b[4m"; //underline
        ansi_s slow_blink = "\x1b[5m"; //slow blinking text
        ansi_s fast_blink = "\x1b[6m"; //fast blinking text
        ansi_s reverse = "\x1b[7m"; //invert
        ansi_n no_underline = "\x1b[24m"; //remove underline 
        ansi_n positive = "\x1b[27m"; // uninvert
        ansi_n d_white = "\x1b[37m"; //dark white
    };
} // namespace ansi