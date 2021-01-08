/*****************************************************************************
 * File name:   uid_test.c
 * Developer:   Yaron Meister
 * Date:        2018-11-25 11:59:11
 * Description: This file contains the 'main' function. 
                Program execution begins and ends there.
 * Test Flow:
 *****************************************************************************/

#include "uid.h"
#include "tests.h"

/* Forward Declarations    */

class UidTest : public Test
{
public:
  void test();
};

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
  UidTest uidTest;

  uidTest.test();

  return (EXIT_SUCCESS);
}

/******************************************************************************/
void UidTest::test()
{

  CUid uid1;
  CUid uid2;

  printf("\n********************* UID-TEST ******************************\n");

  equalityTest<size_t>(uid1.getCounter(), 1);
  equalityTest<size_t>(uid2.getCounter(), 2);
  equalityTest<bool>(uid2.isBad(), false);

  uid2 = uid1;
  equalityTest<bool>(uid2 == uid1, true);
  
  bool isBad = true;
  CUid uid3(isBad);
  equalityTest<bool>(uid3.isBad(), true);
}
