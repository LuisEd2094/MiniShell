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

bool    parse_input(char *input);

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
    TEST_ASSERT_EQUAL(1, parse_input(" | hola"));
    TEST_ASSERT_EQUAL(1, parse_input("hola | hola| "));
    TEST_ASSERT_EQUAL(1, parse_input("hola | | hola"));
    TEST_ASSERT_EQUAL(1, parse_input("hola | |  "));
}

void check_redirections(void)
{
        TEST_ASSERT_EQUAL(0, parse_input("hola > hola"));
        TEST_ASSERT_EQUAL(1, parse_input("hola >"));
}


void check_all(void)
{
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\""));
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\" | cat"));
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\" | cat < infile"));
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\" | cat < infile | ls"));
    TEST_ASSERT_EQUAL(0, parse_input("hola > \"hola\" | cat < infile | ls >> outfile"));



    

}

int main(int argc, char **argv, char **env)
{  
    UNITY_BEGIN();
    RUN_TEST(check_basic_input);
    RUN_TEST(check_quotes);
    RUN_TEST(check_pipes);
    RUN_TEST(check_all);


    return UNITY_END();
}