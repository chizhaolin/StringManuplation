#include<stdio.h>
#include<memory.h>

char* strtok(char* str, const char* tok)
{
    /*
     * There are 256 characters, so usually we can use a byte array with 256 elements
     * to represent those 256 characters. However, here we use a byte array with only
     * 32 elements, because we would like to use each bit to represent a character,
     * it's caculated as 256/8 = 32 bytes.
     * And for each character we can use [character/8] to find which byte it should be
     * stored, and use [1<<(character%8)] to find which bit of the byte it should be 
     * stored. 
     * It's a classical use case of bit manipulation.
     */
    unsigned char map[32];
    char *tmpTok, *tmpStr;
    static char* sRest; // This static variable is used to store the rest string after each strtok function.

    // Reset the map table, which is used to stored the token
    memset(map, 0, sizeof(map));

    // Store the token in each corresponding bit
    tmpTok = tok;
    while(*tmpTok) {
        map[*tmpTok>>3] |= (1<<(*tmpTok&7));
        tmpTok++;
    }

    if (str == NULL)
        tmpStr = sRest;
    else
        tmpStr = str;

    // Discard the token string at the beging of the source string.
    while(map[*tmpStr>>3] & (1<<(*tmpStr&7)))
        tmpStr++;

    str = tmpStr;

    while(*tmpStr) {
        if (map[*tmpStr>>3] & (1<<(*tmpStr&7))) {
            *tmpStr++ = '\0';
            break;
        }
        tmpStr++;
    }

    sRest = tmpStr;

    if (str == tmpStr)
        return NULL;
    else
        return str;
}

int main()
{
    char str[] = "a b c d e;f,g,h";
    char tok[] = " ;,";
    char* str1;

    str1 = strtok(str, tok);
    while(str1) {
        printf("%s\n", str1);
        str1 = strtok(NULL, tok);
    }

    return 0;
}
