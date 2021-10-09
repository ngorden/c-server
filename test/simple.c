#include "minunit.h"


MU_TEST(check_test)
{
  mu_check(1);
}

MU_TEST_SUITE(itworks)
{
  MU_RUN_TEST(check_test);
}

int main(void)
{
  MU_RUN_SUITE(itworks);
  MU_REPORT();
  return MU_EXIT_CODE;
}