#include "unity.h"
#include "../redirections_internal.h"
#include <stdio.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

void remove_redir_from_cmds(char **cmds, int i);

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


void remove_redir_from_cmds_test(void)
{
    char *test[] = {"cat", "<", "test", "hola"};

    remove_redir_from_cmds(test, 1);


    TEST_ASSERT_NULL(test[2]);
    TEST_ASSERT_NULL(test[3]);
    TEST_ASSERT_NULL(test[4]);

}

int main(void)
{
    UNITY_BEGIN();



    return UNITY_END();
}