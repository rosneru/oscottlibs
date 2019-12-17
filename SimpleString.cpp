#include "SimpleString.h"
#include <string.h>
#include <stdio.h>


SimpleString::SimpleString()
  : m_Len(0),
    m_pBuf(new char[m_Len + 1])
{
  m_pBuf[0] = '\0';
}

SimpleString::SimpleString(const char *pTxt)
  : m_Len(strlen(pTxt)),
    m_pBuf(new char[m_Len + 1])
{
  strcpy(m_pBuf, pTxt);
}

SimpleString::SimpleString(const SimpleString& other)
  : m_Len(other.m_Len),
    m_pBuf(new char[m_Len + 1])
{
  strcpy(m_pBuf, other.m_pBuf);
}

SimpleString::SimpleString(const char character, size_t count)
  : m_Len(count),
    m_pBuf(new char[m_Len + 1])
{
  for(size_t i = 0; i < count; i++)
  {
    m_pBuf[i] = character;
  }

  m_pBuf[count]='\0';
}

SimpleString::SimpleString(const long number)
  : m_Len(0),
    m_pBuf(NULL)
{
  // Get number of digits
  int digits = 1;
  long div = number;
  while(div /= 10)
  {
    digits++;
  }

  if(number < 0)
  {
    // Space for '-' char
    digits++;
  }

  m_Len = digits;
  m_pBuf = new char[m_Len + 1];

  sprintf(m_pBuf, "%ld", number);
  m_pBuf[m_Len] = '\0';
}

SimpleString::~SimpleString()
{
  delete[] m_pBuf;
}

const char* SimpleString::C_str() const
{
  return m_pBuf;
}

size_t SimpleString::Length() const
{
  return m_Len;
}

SimpleString SimpleString::SubStr(size_t index, size_t len) const
{
  if(len > m_Len)
  {
    len = m_Len;
  }

  if(index > (m_Len - 1))
  {
    index = m_Len - 1;
    len = 0;
  }

  if((index + len) >= m_Len)
  {
    size_t shortenBy = index + len - m_Len;
    len -= shortenBy;
  }

  char* pNewBuf = new char[len + 1];

  strncpy(pNewBuf, m_pBuf + index, len);
  pNewBuf[len] = '\0';

  SimpleString newStr(pNewBuf);
  delete[] pNewBuf;
  return newStr;
}

SimpleString& SimpleString::Replace(size_t index, SimpleString& replaceBy)
{
  size_t copyLen = replaceBy.Length();
  if((index + copyLen) > m_Len)
  {
    size_t shortenBy = index + copyLen - m_Len;
    copyLen -= shortenBy;
  }

  strncpy(m_pBuf + index, replaceBy.m_pBuf, copyLen);
  m_pBuf[m_Len] = '\0';

  return *this;
}

SimpleString&SimpleString::Replace(size_t index, const char* pReplaceBy)
{
  size_t copyLen = strlen(pReplaceBy);
  if((index + copyLen) > m_Len)
  {
    size_t shortenBy = index + copyLen - m_Len;
    copyLen -= shortenBy;
  }

  strncpy(m_pBuf + index, pReplaceBy, copyLen);
  m_pBuf[m_Len] = '\0';

  return *this;
}

SimpleString& SimpleString::Insert(size_t index, SimpleString& insert)
{
  if(index > m_Len)
  {
    index = m_Len;
  }

  m_Len = m_Len + insert.m_Len;
  char* pNewBuf = new char[m_Len + 1];

  strncpy(pNewBuf, m_pBuf, index);
  strncpy(pNewBuf + index, insert.m_pBuf, insert.m_Len);
  strcpy(pNewBuf + index + insert.m_Len, m_pBuf + index);

  delete[] m_pBuf;
  m_pBuf = pNewBuf;
  return *this;
}

SimpleString& SimpleString::Insert(size_t index, const char* pInsert)
{
  if(index > m_Len)
  {
    index = m_Len;
  }

  m_Len = m_Len + strlen(pInsert);
  char* pNewBuf = new char[m_Len + 1];

  strncpy(pNewBuf, m_pBuf, index);
  strncpy(pNewBuf + index, pInsert, strlen(pInsert));
  strcpy(pNewBuf + index + strlen(pInsert), m_pBuf + index);

  delete[] m_pBuf;
  m_pBuf = pNewBuf;
  return *this;
}

SimpleString& SimpleString::Erase(size_t index, size_t len)
{
  if(index >= m_Len)
  {
    return *this;
  }

  size_t copyLen1 = index;
  size_t copyLen2 = m_Len - index - len;
  if(index + len > m_Len)
  {
    copyLen2 = 0;
  }

  m_Len = copyLen1 + copyLen2;
  char* pNewBuf = new char[m_Len + 1];

  if(copyLen1 > 0)
  {
    strncpy(pNewBuf, m_pBuf, copyLen1);
  }

  if(copyLen2 > 0)
  {
    strncpy(pNewBuf + copyLen1, m_pBuf + copyLen1 + len, copyLen2);
  }

  pNewBuf[m_Len] = '\0';

  delete[] m_pBuf;
  m_pBuf = pNewBuf;
  return *this;
}



SimpleString SimpleString::Trim(bool bRemoveAlsoLeadingWhiteSp)
{
  if(containsOnlyWhiteSpaces() == true)
  {
    // String contains only white spaces: return an empty string
    SimpleString trimmed = "";
    return trimmed;
  }

  SimpleString trimmed = *this;
  if(bRemoveAlsoLeadingWhiteSp == true)
  {
    for (size_t i = 0; i < Length(); i++)
    {
      char& c = trimmed[i];
      if(!(c == '\r') &&
         !(c == '\n') &&
         !(c == '\t') &&
         !(c == ' '))
      {
        trimmed = trimmed.SubStr(i, trimmed.Length() - i);
        break;
      }
    }
  }

  if(trimmed.Length() == 1)
  {
    char& c = trimmed[0];
    if((c == '\r') ||
       (c == '\n') ||
       (c == '\t') ||
       (c == ' '))
    {
      // The only character of the string is a to be trimmed special
      // char: create an new empty string
      trimmed = "";
    }
  }
  else if(trimmed.Length() > 1)
  {
    size_t i = trimmed.Length() - 1;
    char& c = trimmed[i];
    while((c == '\r') ||
       (c == '\n') ||
       (c == '\t') ||
       (c == ' '))
    {
      i--;
      c = trimmed[i];
    }

    size_t shortenBy = trimmed.Length() - i - 1;
    trimmed = trimmed.SubStr(0, trimmed.Length() - shortenBy);
  }

  return trimmed;
}

bool SimpleString::containsOnlyWhiteSpaces()
{
  for(size_t i=0; i < m_Len; i++)
  {
    if(!(m_pBuf[i] == '\r') &&
       !(m_pBuf[i] == '\n') &&
       !(m_pBuf[i] == '\t') &&
       !(m_pBuf[i] == ' '))
    {
      // first non-whitespace character found
      return false;
    }
  }

  return true;
}



SimpleString& SimpleString::operator=(const SimpleString& other)
{
  m_Len = other.m_Len;
  if(&other == this)
  {
    return *this;
  }

  delete[] m_pBuf;
  m_pBuf = new char[m_Len + 1];
  strcpy(m_pBuf, other.m_pBuf);
  return *this;
}

SimpleString& SimpleString::operator=(const char* pOtherChar)
{
  delete[] m_pBuf;

  m_Len = strlen(pOtherChar);
  m_pBuf = new char[m_Len + 1];
  strcpy(m_pBuf, pOtherChar);
  return *this;
}


SimpleString SimpleString::operator+(const SimpleString& other)
{
  m_Len = m_Len + other.m_Len;
  char* pNewBuf = new char[m_Len + 1];

  strcpy(pNewBuf, m_pBuf);
  strcat(pNewBuf, other.m_pBuf);

  SimpleString newStr(pNewBuf);
  delete[] pNewBuf;
  return newStr;
}

SimpleString SimpleString::operator+(const char* pOtherChar)
{
  m_Len = m_Len + strlen(pOtherChar);
  char* pNewBuf = new char[m_Len + 1];

  strcpy(pNewBuf, m_pBuf);
  strcat(pNewBuf, pOtherChar);

  SimpleString newStr(pNewBuf);
  delete[] pNewBuf;
  return newStr;
}

SimpleString& SimpleString::operator+=(const SimpleString& other)
{
  m_Len = m_Len + other.m_Len;

  char* pOldBuf = m_pBuf;
  m_pBuf = new char[m_Len + 1];
  strcpy(m_pBuf, pOldBuf);
  strcat(m_pBuf, other.m_pBuf);

  delete[] pOldBuf;
  return *this;
}

SimpleString& SimpleString::operator+=(const char* pOtherChar)
{
  m_Len = m_Len + strlen(pOtherChar);

  char* pOldBuf = m_pBuf;
  m_pBuf = new char[m_Len + 1];
  strcpy(m_pBuf, pOldBuf);
  strcat(m_pBuf, pOtherChar);

  delete[] pOldBuf;
  return *this;
}

SimpleString& SimpleString::operator+=(long number)
{
  SimpleString numberStr(number);

  m_Len = m_Len + numberStr.Length();

  char* pOldBuf = m_pBuf;
  m_pBuf = new char[m_Len + 1];
  strcpy(m_pBuf, pOldBuf);
  strcat(m_pBuf, numberStr.C_str());

  delete[] pOldBuf;
  return *this;
}

bool SimpleString::operator==(const SimpleString& other) const
{
  if(strcmp(m_pBuf, other.m_pBuf) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool SimpleString::operator<(const SimpleString& other) const
{
  if(strcmp(m_pBuf, other.m_pBuf) < 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool SimpleString::operator>(const SimpleString& other) const
{
  if(strcmp(m_pBuf, other.m_pBuf) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

char& SimpleString::operator[](size_t index)
{
  if(index < m_Len)
  {
    return m_pBuf[index];
  }
  else
  {
    static char c;
    c = 0;
    return c;
  }
}
