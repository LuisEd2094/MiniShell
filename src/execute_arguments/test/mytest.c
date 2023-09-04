#include <unity.h>
#include <unity_internals.h>

int get_cmds_number(char *input);

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void get_cmds_number_test(void)
{
    TEST_ASSERT(2 == get_cmds_number("ls -la | cat"));
    TEST_ASSERT(2 == get_cmds_number("cat | grep       "));
    TEST_ASSERT(3 == get_cmds_number("ls |    cat    | adasd"));
    TEST_ASSERT(4 == get_cmds_number("ls |    grep    | crissssss |  asdada"));
    TEST_ASSERT(1 == get_cmds_number("ls"));
    TEST_ASSERT(1 == get_cmds_number("  l   s       "));

}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(get_cmds_number_test);
    return UNITY_END();
}