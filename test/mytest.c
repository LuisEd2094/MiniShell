#include <unity.h>
#include <unity_internals.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <stdbool.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int    parse_input(char *input);

void check_basic_input(void)
{
    TEST_ASSERT_EQUAL(0, parse_input("Hola\n"));
    TEST_ASSERT_EQUAL(0, parse_input("asdsdaasdajhdagjhdaghjsghajdghdaghadsghjadghjadshjgadsghjdaghjghjasdjhasjdh ajhgdasjhg a sdjhg dasjhd sahjgd jahgsdjg asdjgh ajhdga jhga jhg dajsgd ajg dashjg asjhd ahj\n"));
    TEST_ASSERT_EQUAL(0, parse_input("[[AS[D[AD[DAS[D[AD[A[DAS[DA[SD[AS[D]]]]]]]]]]]]]\n"));
    TEST_ASSERT_EQUAL(0, parse_input("adadadasdasdsadasdas\n"));
}

void check_quotes(void)
{
    TEST_ASSERT_EQUAL(0, parse_input("\"Hola\""));
    TEST_ASSERT_EQUAL(0, parse_input("\'Hola \' \' \'"));
    TEST_ASSERT_EQUAL(0, parse_input("\'\'\'\'"));
    TEST_ASSERT_EQUAL(0, parse_input("\"Hola \" \" \""));
    TEST_ASSERT_EQUAL(0, parse_input("\"\"\"\""));
    TEST_ASSERT_EQUAL(0, parse_input("\'Hola\'"));


    TEST_ASSERT_EQUAL(1, parse_input("\"Hola"));
    TEST_ASSERT_EQUAL(1, parse_input("\"Hola \" \" "));
    TEST_ASSERT_EQUAL(1, parse_input("\'Hola"));
    TEST_ASSERT_EQUAL(1, parse_input("\'Hola \' \' "));

}

void check_pipes(void)
{
    
    TEST_ASSERT_EQUAL(0, parse_input("hola | hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola | hola| hola"));

    TEST_ASSERT_EQUAL(1, parse_input("hola | "));
    TEST_ASSERT_EQUAL(258, parse_input(" | hola"));
    TEST_ASSERT_EQUAL(1, parse_input("hola | hola| "));
    TEST_ASSERT_EQUAL(258, parse_input("hola | | hola"));
    TEST_ASSERT_EQUAL(258, parse_input("hola | |  "));
}

void check_redirections(void)
{
    TEST_ASSERT_EQUAL(0, parse_input("hola > hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola >hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola >>hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola>hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola>>hola"));


    TEST_ASSERT_EQUAL(0, parse_input("hola <hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola <<hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola<hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola<<hola"));
    TEST_ASSERT_EQUAL(1, parse_input("hola<>hola"));

    TEST_ASSERT_EQUAL(1, parse_input("hola >|infile"));
    TEST_ASSERT_EQUAL(0, parse_input("ls >$out"));
    TEST_ASSERT_EQUAL(0, parse_input("ls >$ out"));


    TEST_ASSERT_EQUAL(0, parse_input("hola > hola > hola > hola"));
    TEST_ASSERT_EQUAL(0, parse_input("hola > hola > hola < hoolaa   a"));
    TEST_ASSERT_EQUAL(0, parse_input("ls | >#outfile")); 
    TEST_ASSERT_EQUAL(0, parse_input("ls >$out")); //bash: $out: ambiguous redirect



    TEST_ASSERT_EQUAL(258, parse_input("hola >"));
    TEST_ASSERT_EQUAL(258, parse_input("hola > "));
    TEST_ASSERT_EQUAL(258, parse_input("hola <<>hola "));
    TEST_ASSERT_EQUAL(258, parse_input("hola >><hola "));

    TEST_ASSERT_EQUAL(258, parse_input("hola < >hola "));
    TEST_ASSERT_EQUAL(258, parse_input("hola ><hola "));

//hola >>$hola if env not set it gives an error too

}



void check_all(void)
{
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\""));
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"\""));
    TEST_ASSERT_EQUAL(0, parse_input("hola \" hola > hola \""));
    TEST_ASSERT_EQUAL(0, parse_input("hola \"> hola \""));
    TEST_ASSERT_EQUAL(0, parse_input("hola \" hola >\""));

    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\" | cat"));
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\" | cat < infile"));
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\" | cat < infile | ls"));
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\" | cat < infile | ls >> outfile"));
    TEST_ASSERT_EQUAL(0, parse_input("ls | > outfile"));
    TEST_ASSERT_EQUAL(0, parse_input("ls | > asda #outfile"));
    TEST_ASSERT_EQUAL(0, parse_input("ls | > #outfile")); //newline
    TEST_ASSERT_EQUAL(0, parse_input("ls|>outfile")); //newline
    TEST_ASSERT_EQUAL(0, parse_input("ls|cat -e")); //newline
    TEST_ASSERT_EQUAL(0, parse_input("ls>|cat")); //newline
    TEST_ASSERT_EQUAL(0, parse_input("ls>|cat -e")); //newline




    TEST_ASSERT_EQUAL(1, parse_input("hola > \"hola"));
    TEST_ASSERT_EQUAL(1, parse_input("hola > \""));
    TEST_ASSERT_EQUAL(258, parse_input("hola > "));



}

int main(int argc, char **argv, char **env)
{  
    UNITY_BEGIN();
    
    RUN_TEST(check_basic_input);
    RUN_TEST(check_quotes);
    RUN_TEST(check_pipes);
    RUN_TEST(check_redirections);
    RUN_TEST(check_all);


    return UNITY_END();
}
