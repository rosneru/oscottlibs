/* SimpleString.h                                                          */
/*-------------------------------------------------------------------*/
/* Class for basic string handling                                   */
/*                                                                   */
/* Uwe Rosner                                                        */
/* Created 12/2004, Updated 09/2018                                  */
/*-------------------------------------------------------------------*/
#ifndef OSCOTTLIBS_STRING
#define OSCOTTLIBS_STRING

#include <stdlib.h>

class SimpleString
{
public:
  SimpleString();
  SimpleString(const char* pTxt);
  SimpleString(const SimpleString& other);
  SimpleString(const char character, size_t count);
  SimpleString(const long number);

  ~SimpleString();

  // Operators
  SimpleString& operator=(const SimpleString& other);
  SimpleString& operator=(const char* pOtherChar);
  SimpleString operator+(const SimpleString& other);
  SimpleString operator+(const char* pOtherChar);
  SimpleString& operator+=(const SimpleString& other);
  SimpleString& operator+=(const char* pOtherChar);
  SimpleString& operator+=(long number);
  bool operator==(const SimpleString& other) const;
  bool operator<(const SimpleString& other) const;
  bool operator>(const SimpleString& other) const;
  char& operator[](size_t index);

  /**
   * Get C string equivalent
   */
  const char* C_str() const;

  /**
   * Get length of string
   */
  size_t Length() const;


  /**
   * @brief
   * Returns a newly constructed string object with its value
   * initialized to a copy of a substring of this object.
   *
   * @param index
   * Index of the first character to be copied as a substring. If this
   * is equal to or bigger than the string length, the function returns
   * an empty string.
   *
   * @param len
   * Number of characters to include in the substring. If the string
   * is shorter, as many characters as possible are used.
   */
  SimpleString SubStr(size_t index, size_t len) const;


  /**
   * @brief
   * Replaces the portion of the string that begins at index pos and
   * spans len characters (or the part of the string in the range
   * between [i1,i2)) with a given SimpleString.
   *
   * WARNING This creates *no* copy. It changes the string directly!
   *
   * @param index
   * Index of the first character to be replaced. If this is greater
   * than the string length, nothing will be done.
   *
   *
   * @param replaceBy
   * String that will be inserted at replace position
   *
   */
  SimpleString& Replace(size_t index, SimpleString& replaceBy);

  /**
   * @brief
   * Replaces the portion of the string that begins at index pos and
   * spans len characters (or the part of the string in the range
   * between [i1,i2)) with a given text.
   *
   * WARNING This creates *no* copy. It changes the string directly!
   *
   * @param index
   * Index of the first character to be replaced. If this is greater
   * than the string length, nothing will be done.
   *
   *
   * @param pReplaceBy
   * Pointer to the C string that will be inserted at replace position
   *
   */
  SimpleString& Replace(size_t index, const char* pReplaceBy);

  /**
   * @brief
   * Inserts a given SimpleString at given position into this string
   *
   * WARNING This creates *no* copy. It changes the string directly!
   *
   */
  SimpleString& Insert(size_t index, SimpleString& insert);

  /**
   * @brief
   * Inserts a given C string at given position into this string
   *
   * WARNING This creates *no* copy. It changes the string directly!
   *
   */
  SimpleString& Insert(size_t index, const char* pInsert);

  /**
   * @brief
   * Erases part of the string, reducing its length.
   *
   * Erases the portion of the string value that begins at index and
   * spans len characters (or until the end of the string, if the
   * content is too short).
   *
   * WARNING This creates *no* copy. It changes the string directly!
   */
  SimpleString& Erase(size_t index, size_t len);

  /**
   * @brief
   * Returns a newly constructed string object with all occurrences of
   * '\r', '\n', '\t' and ' ' from the end of the string are removed.
   *
   * Per Default the parameter bRemoveAlsoLeadingWhiteSp is set to
   * false so all leading and trailing white spaces are removed.
   *
   * @param bRemoveAlsoLeadingWhiteSp
   * When true only trailing white spaces are removed. When false the
   * trailing and also leading white spaces are removed.
   */
  SimpleString Trim(bool bRemoveAlsoLeadingWhiteSp = false);

  /**
   * @brief
   * Returns a newly constructed string object where all upper case
   * letters are converted into lower case.
   *
   * NOTE: Only plain ASCII is processed.
   *       Localization / 'umlauts' are skipped.
   */
  SimpleString ToLower();

private:
  size_t m_Len;
  char *m_pBuf;

  bool containsOnlyWhiteSpaces();
};

#endif
