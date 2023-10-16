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
bool     check_unset(char *arg);


void    check_unset_test(void)
{
    char *str;

    str = "hola";
    TEST_ASSERT_EQUAL(0, check_unset(str));
    str = "h1ola";
    TEST_ASSERT_EQUAL(0, check_unset(str));
    str = "hol1a";
    TEST_ASSERT_EQUAL(0, check_unset(str));
    str = "hol_a";
    TEST_ASSERT_EQUAL(0, check_unset(str));
    str = "hola";
    TEST_ASSERT_EQUAL(0, check_unset(str));
    str = "h1ol_a";
    TEST_ASSERT_EQUAL(0, check_unset(str));
    str = "_hola";
    TEST_ASSERT_EQUAL(0, check_unset(str));

    str = "1_hola";
    TEST_ASSERT_EQUAL(1, check_unset(str));
    str = "?hola";
    TEST_ASSERT_EQUAL(1, check_unset(str));
    str = "$hola";
    TEST_ASSERT_EQUAL(1, check_unset(str));
    str = "_h?la";
    TEST_ASSERT_EQUAL(1, check_unset(str));
    str = "/hola";
    TEST_ASSERT_EQUAL(1, check_unset(str));
    str = "+hola";
    TEST_ASSERT_EQUAL(1, check_unset(str));
    str = "hola+";
    TEST_ASSERT_EQUAL(1, check_unset(str));
}

int main(int argc, char **argv, char **env)
{  
    UNITY_BEGIN();
    
    RUN_TEST(check_unset_test);


    return UNITY_END();
}
