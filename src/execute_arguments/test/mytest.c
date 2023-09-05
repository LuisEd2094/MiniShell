#include <unity.h>
#include <unity_internals.h>
#include "../execute_internal.h"
#include <stdio.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

t_list *env_list;
char **g_env;


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void get_cmds_value_test(void)
{
    t_list *env_list = init_env(g_env);

    char * str = "ls -la | cat |                 grep";
    char *** result= get_cmds_value(str, env_list);


    TEST_ASSERT_EQUAL_STRING("ls", result[0][0]);
    TEST_ASSERT_EQUAL_STRING("-la", result[0][1]);
    TEST_ASSERT_EQUAL_STRING("cat", result[1][0]);
    TEST_ASSERT_EQUAL_STRING("grep", result[2][0]);

    str = "ls >> test";
    result = get_cmds_value (str, env_list);
    TEST_ASSERT_EQUAL_STRING("ls", result[0][0]);
    TEST_ASSERT_EQUAL_STRING(">>", result[0][1]);
    TEST_ASSERT_EQUAL_STRING("test", result[0][2]);

    str = "ls>>test";
    result = get_cmds_value (str, env_list);
    TEST_ASSERT_EQUAL_STRING("ls", result[0][0]);
    TEST_ASSERT_EQUAL_STRING(">>", result[0][1]);
    TEST_ASSERT_EQUAL_STRING("test", result[0][2]);

    str = "ls>>test | cat $PWD \"I AM INSIDE QUOTES\" | grep 'I AM SINGLE QUOTES >>' \
            | ls<<test |ls>test |ls>>test|ls<test";
    result = get_cmds_value (str, env_list);
    TEST_ASSERT_EQUAL_STRING("ls", result[0][0]);
    TEST_ASSERT_EQUAL_STRING(">>", result[0][1]);
    TEST_ASSERT_EQUAL_STRING("test", result[0][2]);
    TEST_ASSERT_EQUAL_STRING("cat", result[1][0]);
    TEST_ASSERT_EQUAL_STRING(getenv("PWD"), result[1][1]);
    TEST_ASSERT_EQUAL_STRING("I AM INSIDE QUOTES", result[1][2]);
    TEST_ASSERT_EQUAL_STRING("grep", result[2][0]);
    TEST_ASSERT_EQUAL_STRING("I AM SINGLE QUOTES >>", result[2][1]);

    TEST_ASSERT_EQUAL_STRING("ls", result[3][0]);
    TEST_ASSERT_EQUAL_STRING("<<", result[3][1]);
    TEST_ASSERT_EQUAL_STRING("test", result[3][2]);

    TEST_ASSERT_EQUAL_STRING("ls", result[4][0]);
    TEST_ASSERT_EQUAL_STRING(">", result[4][1]);
    TEST_ASSERT_EQUAL_STRING("test", result[4][2]);

    TEST_ASSERT_EQUAL_STRING("ls", result[5][0]);
    TEST_ASSERT_EQUAL_STRING(">>", result[5][1]);
    TEST_ASSERT_EQUAL_STRING("test", result[5][2]);

    TEST_ASSERT_EQUAL_STRING("ls", result[6][0]);
    TEST_ASSERT_EQUAL_STRING("<", result[6][1]);
    TEST_ASSERT_EQUAL_STRING("test", result[6][2]);
}


void get_cmds_quotes_test(void)
{
    char ***result = get_cmds_value("ls -la | cat \"Hello World \"", NULL);

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

    str = "ls>>test";
    count = get_argument_count(str);
    TEST_ASSERT_EQUAL_INT(3, count);

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


void    get_cmds_argumets_with_env_test(void)
{
    t_list *env_list = init_env(g_env);

    char * str = "ls $PWD";
    char **result = get_cmd_argument(str, env_list);

    TEST_ASSERT_EQUAL_STRING("ls", result[0]);
    TEST_ASSERT_EQUAL_STRING(getenv("PWD"), result[1]);

   
}


void    get_env_str_test(void)
{
    t_list *env_list = init_env(g_env);
    char *result = get_env_str("PWD", env_list);
    
    TEST_ASSERT_EQUAL_STRING(getenv("PWD"), result);

    result = get_env_str("NOEXISTE", env_list);
    TEST_ASSERT_EQUAL_STRING("\0", result);


}


int main(int argc, char **argv, char **env)
{  
    g_env = env; 
    UNITY_BEGIN();
    RUN_TEST(get_argument_count_test);
    RUN_TEST(ft_argument_split_test);
    RUN_TEST(get_cmds_value_test);
    RUN_TEST(get_env_str_test);
    RUN_TEST(get_cmds_argumets_with_env_test);

    return UNITY_END();
}