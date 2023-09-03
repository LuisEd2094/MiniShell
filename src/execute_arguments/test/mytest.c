#include <unity.h>
#include <unity_internals.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

char *i_just_want_to_see(void)
{
    return (NULL);
}

void my_test(void)
{
    TEST_ASSERT(NULL == i_just_want_to_see());
    TEST_ASSERT("HELLO" == i_just_want_to_see());


}

void another_test(void)
{
    TEST_ASSERT("ADIOS" == i_just_want_to_see());

}
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(my_test);
    RUN_TEST(another_test);

    return UNITY_END();
}