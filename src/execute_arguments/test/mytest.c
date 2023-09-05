#include <unity.h>
#include <unity_internals.h>
#include "../execute_internal.h"
#include <stdio.h>


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void get_cmds_value_test(void)
{
    char *** result= get_cmds_value("ls -la | cat | grep");


    TEST_ASSERT_EQUAL_STRING("ls", result[0][0]);
    TEST_ASSERT_EQUAL_STRING("-la", result[0][1]);
    TEST_ASSERT_EQUAL_STRING("cat", result[1][0]);
    TEST_ASSERT_EQUAL_STRING("grep", result[2][0]);
}

void get_cmds_quotes_test(void)
{
    char ***result = get_cmds_value("ls -la | cat \"Hello World \"");

    TEST_ASSERT_EQUAL_STRING("ls", result[0][0]);
    TEST_ASSERT_EQUAL_STRING("-la", result[0][1]);
    TEST_ASSERT_EQUAL_STRING("cat", result[1][0]);
    TEST_ASSERT_EQUAL_STRING("Hello World ", result[1][1]);

}



void get_argument_count_test(void)
{
    char *str = "cat \"Hello World \"";
    int count = get_argument_count(str);
    

    TEST_ASSERT_EQUAL_INT(2, count);

    str = "ls 'hello $ADD '         ";
    count = get_argument_count(str);
    TEST_ASSERT_EQUAL_INT(2, count);
    str = "ls $HELLO 'THIS IS ONE QUOTE $ASD' \"THis is double qoute\"       ";
    count = get_argument_count(str);
    TEST_ASSERT_EQUAL_INT(4, count);
}

char **ft_argument_split(char *cmd);


void ft_argument_split_test(void)
{
    char *str = "cat \"Hello World   \"";
    char ** result = ft_argument_split(str);

    TEST_ASSERT_EQUAL_STRING("cat", result[0]);
    TEST_ASSERT_EQUAL_STRING("Hello World   ", result[1]);

}

int main(void)
{    

    UNITY_BEGIN();
    RUN_TEST(get_cmds_value_test);
    RUN_TEST(get_argument_count_test);
    RUN_TEST(ft_argument_split_test);
    return UNITY_END();
}