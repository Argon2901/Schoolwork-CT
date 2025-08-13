// username: collint@mtu.edu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aspell.h"


int main(){
    AspellConfig * spell_config = new_aspell_config();
    aspell_config_replace(spell_config, "lang", "en_US");
    AspellCanHaveError * possible_err = new_aspell_speller(spell_config);
    AspellSpeller * spell_checker = 0;
    if (aspell_error_number(possible_err) != 0)
        puts(aspell_error_message(possible_err));
    else
        spell_checker = to_aspell_speller(possible_err);
    
    char* string[8];

    while(scanf("%s[^\n]", string) != EOF){ 
        if(aspell_speller_check(spell_checker, (const char *)string, -1)){
            printf("%s\n", string);
        }
    }
}