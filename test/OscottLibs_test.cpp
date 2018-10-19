/* Unit test for String using BOOST framework                             */
/*------------------------------------------------------------------------*/
/* Main class for testing base behavior of the 2018 updated String class  */
/* from 2004.                                                             */
/*                                                                        */
/* Uwe Rosner                                                             */
/* 09/2016                                                                */
/*------------------------------------------------------------------------*/

#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include "SimpleString.h"
#include "LinkedList.h"



BOOST_AUTO_TEST_CASE( testStringAndNumbers )
{
  SimpleString simpleStringTestConstr1(12345);
  BOOST_CHECK(simpleStringTestConstr1 == "12345");

  SimpleString simpleStringTestConstr2(-329);
  BOOST_CHECK(simpleStringTestConstr2 == "-329");

  double testD = -127.659;
  long testL = (long)testD;
  SimpleString simpleStringTestConstr3(testL);
  BOOST_CHECK(simpleStringTestConstr3 == "-127");

  SimpleString simpleString1 = "Time was ";
  BOOST_CHECK(simpleString1 == "Time was ");

  long time = 23112017;
  simpleString1 += time;

  simpleString1 += " milliseconds.";
  BOOST_CHECK(simpleString1 == "Time was 23112017 milliseconds.");

  SimpleString simpleString2 = "It was ";

  double years = -999.345;
  simpleString2 += (long)years;

  simpleString2 += " years ago.";
  BOOST_CHECK(simpleString2 == "It was -999 years ago.");
}

BOOST_AUTO_TEST_CASE( testString )
{
  //
  // Basic tests
  //
  SimpleString simpleString;
  BOOST_CHECK(simpleString == "");
  BOOST_CHECK_EQUAL(simpleString.Length(), 0);

  simpleString = "abc";
  BOOST_CHECK(simpleString == "abc");

  simpleString = simpleString + simpleString;
  BOOST_CHECK(simpleString == "abcabc");

  SimpleString test("Test ");
  test = test + simpleString;
  BOOST_CHECK(test == "Test abcabc");

  // overloaded += operator
  test = "Test";
  SimpleString otherStr = "_ABC_";
  test += otherStr += test;
  BOOST_CHECK(test == "Test_ABC_Test");

  test = "Test";
  test += "_DEF_";
  BOOST_CHECK(test == "Test_DEF_");

  //
  // Testing copy constructor
  //
  SimpleString simpleStr1 = "Hallo";
  SimpleString simpleStr2(simpleStr1);
  BOOST_CHECK(simpleStr1 == "Hallo");
  BOOST_CHECK(simpleStr2 == "Hallo");
  simpleStr1 = "Welt";
  BOOST_CHECK(simpleStr1 == "Welt");
  BOOST_CHECK(simpleStr2 == "Hallo");

  //
  // Test SubStr method
  //
  SimpleString secondStr = simpleString.SubStr(1, 4);
  BOOST_CHECK(secondStr == "bcab");

  // testing if after SubStr original str is still untouched
  BOOST_CHECK(simpleString == "abcabc");

  // testing substr outher limits
  SimpleString thirdStr = secondStr.SubStr(1, 3);
  BOOST_CHECK(thirdStr == "cab");
  BOOST_CHECK(secondStr == "bcab");

  thirdStr = secondStr.SubStr(1, 4);
  BOOST_CHECK(thirdStr == "cab");

  thirdStr = secondStr.SubStr(1, 400);
  BOOST_CHECK(thirdStr == "cab");

  thirdStr = secondStr.SubStr(2, 400);
  BOOST_CHECK(thirdStr == "ab");

  thirdStr = secondStr.SubStr(3, 400);
  BOOST_CHECK(thirdStr == "b");

  thirdStr = secondStr.SubStr(4, 400);
  BOOST_CHECK(thirdStr == "");

  thirdStr = secondStr.SubStr(400, 400);
  BOOST_CHECK(thirdStr == "");

  thirdStr = secondStr.SubStr(-1, 3);
  BOOST_CHECK(thirdStr == "");

  thirdStr = secondStr.SubStr(1, 1);
  BOOST_CHECK(thirdStr == "c");

  thirdStr = secondStr.SubStr(1, 0);
  BOOST_CHECK(thirdStr == "");

  thirdStr = secondStr.SubStr(1, -1);

  // this is because gcc doens't produce an error on the -1 above
  BOOST_CHECK(thirdStr == "cab");

  //
  // Test Replace method
  //
  SimpleString replaceWith = "w";
  SimpleString strToReplace = "sagt";
  strToReplace.Replace(0, replaceWith);
  BOOST_CHECK(strToReplace == "wagt");

  replaceWith = "w";
  strToReplace = "sagt";
  strToReplace.Replace(1, replaceWith);
  BOOST_CHECK(strToReplace == "swgt");

  replaceWith = "aber";
  strToReplace = "sagt";
  strToReplace.Replace(1, replaceWith);
  BOOST_CHECK(strToReplace == "sabe");

  strToReplace = "dog";
  strToReplace.Replace(0, "cat");
  BOOST_CHECK(strToReplace == "cat");

  strToReplace = "dog";
  strToReplace.Replace(0, "catamaran");
  BOOST_CHECK(strToReplace == "cat");

  strToReplace = "benderrodriguez";
  strToReplace.Replace(6, "fryleela");
  BOOST_CHECK(strToReplace == "benderfryleelaz");

  //
  // Test Insert method
  //
  SimpleString insertStr = "w";
  SimpleString strToInsert = "sagt";
  strToInsert.Insert(0, insertStr);
  BOOST_CHECK(strToInsert == "wsagt");

  insertStr = "w";
  strToInsert = "sagt";
  strToInsert.Insert(1, insertStr);
  BOOST_CHECK(strToInsert == "swagt");

  insertStr = "aber";
  strToInsert = "sagt";
  strToInsert.Insert(0, insertStr);
  BOOST_CHECK(strToInsert == "abersagt");

  insertStr = "aber";
  strToInsert = "sagt";
  strToInsert.Insert(44, insertStr);
  BOOST_CHECK(strToInsert == "sagtaber");

  strToInsert = "dog";
  strToInsert.Insert(0, "cat");
  BOOST_CHECK(strToInsert == "catdog");

  //
  // Test Erase method
  //
  SimpleString strToErase = "ABCDEFG";
  BOOST_CHECK(strToErase == "ABCDEFG");
  BOOST_CHECK_EQUAL(strToErase.Length(), 7);

  strToErase.Erase(2, 2);
  BOOST_CHECK(strToErase == "ABEFG");
  BOOST_CHECK_EQUAL(strToErase.Length(), 5);

  strToErase = "ABCDEFG";
  strToErase.Erase(0, 3);
  BOOST_CHECK(strToErase == "DEFG");
  BOOST_CHECK_EQUAL(strToErase.Length(), 4);

  strToErase = "ABCDEFG";
  strToErase.Erase(5, 5);
  BOOST_CHECK(strToErase == "ABCDE");
  BOOST_CHECK_EQUAL(strToErase.Length(), 5);

  strToErase = "ABCDEFG";
  strToErase.Erase(0, 500);
  BOOST_CHECK(strToErase == "");
  BOOST_CHECK_EQUAL(strToErase.Length(), 0);

  //
  // Test Erase, Replace and Insert mixed
  //
  // With STL methods and these steps 'Hallo' ist turned to 'weil':
  //    #include <iostream>
  //    #include <string>
  //
  //    int main()
  //    {
  //      std::string testStr = "Hallo";
  //      std::cout << testStr << std::endl;
  //      testStr.replace(0, 1, "w");
  //      std::cout << testStr << std::endl;
  //      testStr.erase(3, 2);
  //      std::cout << testStr << std::endl;
  //      testStr.insert(2, "i");
  //      std::cout << testStr << std::endl;
  //      testStr.replace(1, 1, "e");
  //      std::cout << testStr << std::endl;
  //      return 0;
  //    }
  //
  SimpleString strMixed = "Hallo";
  strMixed.Replace(0, "w");
  strMixed.Erase(3, 2);
  strMixed.Insert(2, "i");
  strMixed.Replace(1, "e");
  BOOST_CHECK(strMixed == "weil");

  //
  // Test Trim
  //
  SimpleString stringToTrim = "  ABC  ";
  SimpleString trimmed = stringToTrim.Trim(true);
  BOOST_CHECK(trimmed == "ABC");

  stringToTrim = " Hallo, ich bin dabei!  ";
  trimmed = stringToTrim.Trim(true);
  BOOST_CHECK(trimmed == "Hallo, ich bin dabei!");

  stringToTrim = "  \r  \n\tHallo,\r\nich bin\tdabei! \t  \n     \r";
  trimmed = stringToTrim.Trim(true);
  BOOST_CHECK(trimmed == "Hallo,\r\nich bin\tdabei!");

  stringToTrim = "Hallo, ich bin dabei!";
  trimmed = stringToTrim.Trim(true);
  BOOST_CHECK(trimmed == "Hallo, ich bin dabei!");

  stringToTrim = "";
  trimmed = stringToTrim.Trim(true);
  BOOST_CHECK(trimmed == "");

  stringToTrim = "\t";
  trimmed = stringToTrim.Trim(true);
  BOOST_CHECK(trimmed == "");

  stringToTrim = "";
  trimmed = stringToTrim.Trim();
  BOOST_CHECK(trimmed == "");

  stringToTrim = "\t";
  trimmed = stringToTrim.Trim();
  BOOST_CHECK(trimmed == "");

  stringToTrim = "  \r  \n\tHallo,\r\nich bin\tdabei! \t  \n     \r";
  trimmed = stringToTrim.Trim();
  BOOST_CHECK(trimmed == "  \r  \n\tHallo,\r\nich bin\tdabei!");

  stringToTrim = " Hallo, ich bin dabei!  ";
  trimmed = stringToTrim.Trim();
  BOOST_CHECK(trimmed == " Hallo, ich bin dabei!");

  stringToTrim = "\r\n";
  trimmed = stringToTrim.Trim();
  BOOST_CHECK(trimmed == "");
}


BOOST_AUTO_TEST_CASE( testLinkedListBasic )
{
  char caTop[] = {"Top"};
  char caAbove[] = {"Above"};
  char caMiddle[] = {"Middle"};
  char caBelow[] = {"Below"};
  char caBottom[] = {"Bottom"};

  char* allItems[] = { caTop, caAbove, caMiddle, caBelow, caBottom};

  // Create list
  LinkedList linkedList;

  // Fill list, performe some navigations and check if behavior is as wanted
  BOOST_CHECK(linkedList.GetFirst() == nullptr);
  BOOST_CHECK_EQUAL(linkedList.Size(), 0);
  BOOST_CHECK_EQUAL(linkedList.InsertTail(caMiddle), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 1);
  BOOST_CHECK(linkedList.GetFirst() != nullptr);
  BOOST_CHECK(linkedList.GetFirst() == caMiddle);
  BOOST_CHECK(linkedList.GetLast() == caMiddle);
  BOOST_CHECK(linkedList.GetSelected() == caMiddle);
  BOOST_CHECK_EQUAL(linkedList.InsertBefore(caAbove), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 2);
  BOOST_CHECK(linkedList.GetSelected() == caAbove);
  BOOST_CHECK(linkedList.GetPrev() == nullptr);
  BOOST_CHECK(linkedList.GetSelected() == caAbove);
  BOOST_CHECK(linkedList.GetNext() == caMiddle);
  BOOST_CHECK(linkedList.GetSelected() == caMiddle);
  BOOST_CHECK(linkedList.GetNext() == nullptr);
  BOOST_CHECK(linkedList.GetSelected() == caMiddle);
  BOOST_CHECK_EQUAL(linkedList.InsertBehind(caBelow), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 3);
  BOOST_CHECK(linkedList.GetSelected() == caBelow);
  BOOST_CHECK(linkedList.GetSelected() == caBelow);
  BOOST_CHECK(linkedList.GetNext() == nullptr);
  BOOST_CHECK(linkedList.GetSelected() == caBelow);
  BOOST_CHECK_EQUAL(linkedList.InsertHead(caTop), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 4);
  BOOST_CHECK(linkedList.GetSelected() == caTop);
  BOOST_CHECK(linkedList.GetPrev() == nullptr);
  BOOST_CHECK(linkedList.GetSelected() == caTop);
  BOOST_CHECK(linkedList.GetNext() == caAbove);
  BOOST_CHECK(linkedList.GetSelected() == caAbove);
  BOOST_CHECK_EQUAL(linkedList.InsertTail(caBottom), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 5);
  BOOST_CHECK(linkedList.GetSelected() == caBottom);
  BOOST_CHECK(linkedList.GetNext() == nullptr);
  BOOST_CHECK(linkedList.GetPrev() == caBelow);
  BOOST_CHECK(linkedList.GetFirst() == caTop);
  BOOST_CHECK(linkedList.GetLast() == caBottom);

  // Checking if GetPrev and GetNext return correct nullptr when list is on
  // Head or Tail position. In this cases list position must not change but
  // remain on Head/Tail position.
  BOOST_CHECK(linkedList.GetFirst() == caTop);
  BOOST_CHECK(linkedList.GetPrev() == nullptr);
  BOOST_CHECK(linkedList.GetSelected() == caTop);
  BOOST_CHECK(linkedList.GetLast() == caBottom);
  BOOST_CHECK(linkedList.GetNext() == nullptr);
  BOOST_CHECK(linkedList.GetSelected() == caBottom);

  // That should be it. But to be totally shure we iterate the list and check if
  // the items are in the right order
  char* pCurrentItem = (char*)linkedList.GetFirst();
  int allItemsCount = sizeof(allItems) / sizeof(char*);
  int i = 0;
  while(pCurrentItem != nullptr)
  {
    if(i > (allItemsCount -1))
    {
      break;
    }

    BOOST_CHECK(pCurrentItem == allItems[i]);

    pCurrentItem = (char*)linkedList.GetNext();
    i++;
  }

  // Now replace the first and second item. Replacing is done by removing the
  // old and adding the new item at the same position.
  char caNewTop[] = {"FIRST"};
  char caNewAbove[] = {"SECOND"};
  allItems[0] = caNewTop;
  allItems[1] = caNewAbove;

  char* pFirst = (char*)linkedList.GetFirst();
  BOOST_CHECK(pFirst == caTop);

  BOOST_CHECK_EQUAL(linkedList.Size(), 5);
  BOOST_CHECK_EQUAL(linkedList.RemoveItem(), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 4);
  BOOST_CHECK(linkedList.GetSelected() == caAbove);

  BOOST_CHECK_EQUAL(linkedList.RemoveItem(), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 3);
  BOOST_CHECK(linkedList.GetSelected() == caMiddle);

  BOOST_CHECK_EQUAL(linkedList.InsertBefore(caNewAbove), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 4);
  BOOST_CHECK(linkedList.GetSelected() == caNewAbove);

  BOOST_CHECK_EQUAL(linkedList.InsertBefore(caNewTop), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 5);
  BOOST_CHECK(linkedList.GetSelected() == caNewTop);

  char* pLast = (char*)linkedList.GetLast();
  BOOST_CHECK(pLast == caBottom);

  BOOST_CHECK_EQUAL(linkedList.RemoveItem(), true);
  BOOST_CHECK_EQUAL(linkedList.Size(), 4);
  BOOST_CHECK(linkedList.GetSelected() == caBelow);


  // Again check the whole list in a loop
  pCurrentItem = (char*)linkedList.GetFirst();
  allItemsCount = sizeof(allItems) / sizeof(char*);
  i = 0;
  while(pCurrentItem != nullptr)
  {
    if(i > (allItemsCount -1))
    {
      break;
    }

    BOOST_CHECK(pCurrentItem == allItems[i]);

    pCurrentItem = (char*)linkedList.GetNext();
    i++;
  }
}


BOOST_AUTO_TEST_CASE( testLinkedListExtended )
{
  //
  // testing GetIndexed
  //

  char itemIdx0[] = {"0"};
  char itemIdx1[] = {"1"};
  char itemIdx2[] = {"2"};
  char itemIdx3[] = {"3"};
  char itemIdx4[] = {"4"};

  // Create list
  LinkedList linkedList;

  linkedList.InsertTail(itemIdx0);
  linkedList.InsertTail(itemIdx1);
  linkedList.InsertTail(itemIdx2);
  linkedList.InsertTail(itemIdx3);
  linkedList.InsertTail(itemIdx4);

  BOOST_CHECK_EQUAL(linkedList.Size(), 5);
  BOOST_CHECK(linkedList.GetIndexed(0) == itemIdx0);
  BOOST_CHECK(linkedList.GetIndexed(5) == nullptr);
  BOOST_CHECK(linkedList.GetIndexed(4) == itemIdx4);
  BOOST_CHECK(linkedList.GetIndexed(1) == itemIdx1);
  BOOST_CHECK(linkedList.GetIndexed(2) == itemIdx2);
  BOOST_CHECK(linkedList.GetIndexed(3) == itemIdx3);
  BOOST_CHECK(linkedList.GetSelected() == itemIdx3);
}

BOOST_AUTO_TEST_CASE( testLinkedListAndDynamicString )
{
  LinkedList listOfStrings;

  listOfStrings.InsertTail(new SimpleString("Line 1"));
  listOfStrings.InsertTail(new SimpleString("Line 2"));
  listOfStrings.InsertTail(new SimpleString("Line 3"));
  listOfStrings.InsertTail(new SimpleString("Line 4"));

  BOOST_CHECK_EQUAL(listOfStrings.Size(), 4);

  void* pItem;
  SimpleString* pString;

  pItem = listOfStrings.GetSelected();
  pString = static_cast<SimpleString*>(pItem);
  delete pString;

  BOOST_CHECK_EQUAL(listOfStrings.RemoveItem(), true);
  BOOST_CHECK_EQUAL(listOfStrings.Size(), 3);

  pItem = listOfStrings.GetSelected();
  pString = static_cast<SimpleString*>(pItem);
  delete pString;

  BOOST_CHECK_EQUAL(listOfStrings.RemoveItem(), true);
  BOOST_CHECK_EQUAL(listOfStrings.Size(), 2);

  pItem = listOfStrings.GetSelected();
  pString = static_cast<SimpleString*>(pItem);
  delete pString;

  BOOST_CHECK_EQUAL(listOfStrings.RemoveItem(), true);
  BOOST_CHECK_EQUAL(listOfStrings.Size(), 1);

  pItem = listOfStrings.GetSelected();
  pString = static_cast<SimpleString*>(pItem);
  delete pString;

  BOOST_CHECK_EQUAL(listOfStrings.RemoveItem(), true);
  BOOST_CHECK_EQUAL(listOfStrings.Size(), 0);

  BOOST_CHECK_EQUAL(listOfStrings.RemoveItem(), false);
}

BOOST_AUTO_TEST_CASE( testLinkedListLimitBehavior )
{
  char caLine1[] = {"Line 1"};
  char caLine2[] = {"Line 2"};

  LinkedList linkedList;

  linkedList.InsertTail(caLine1);
  linkedList.InsertTail(caLine2);

  BOOST_CHECK_EQUAL(linkedList.Size(), 2);

  BOOST_CHECK(linkedList.GetIndexed(1) == caLine2);
  BOOST_CHECK(linkedList.GetSelected() == caLine2);
  BOOST_CHECK(linkedList.GetPrev() == caLine1);
  BOOST_CHECK(linkedList.GetSelected() == caLine1);
  BOOST_CHECK(linkedList.GetPrev() == nullptr);
  BOOST_CHECK(linkedList.GetSelected() == caLine1);

  BOOST_CHECK(linkedList.GetNext() == caLine2);
  BOOST_CHECK(linkedList.GetSelected() == caLine2);
  BOOST_CHECK(linkedList.GetNext() == nullptr);
  BOOST_CHECK(linkedList.GetSelected() == caLine2);

}
