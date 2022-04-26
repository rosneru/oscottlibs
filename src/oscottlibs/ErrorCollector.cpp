#include "ErrorCollector.h"

ErrorCollector::ErrorCollector()
  : m_bAlreadyComposed(false)
{

}

ErrorCollector::~ErrorCollector()
{
  for(size_t i = 0; i < m_ErrorMessagesCollection.Size(); i++)
  {
    SimpleString* pErrorString = m_ErrorMessagesCollection[i];
    if(pErrorString != NULL)
    {
      delete pErrorString;
    }
  }
}

void ErrorCollector::Add(const char* pErrorMsg)
{
  SimpleString* pErrorString = new SimpleString(pErrorMsg);
  m_ErrorMessagesCollection.Push(pErrorString);
  m_bAlreadyComposed = false;
}

void ErrorCollector::Add(const SimpleString& pErrorMsgStr)
{
  SimpleString* pErrorString = new SimpleString(pErrorMsgStr);
  m_ErrorMessagesCollection.Push(pErrorString);
  m_bAlreadyComposed = false;
}

const SimpleString& ErrorCollector::ErrorMessageString()
{
  composeErrorMessage();
  return m_ErrorMessage;
}


void ErrorCollector::composeErrorMessage()
{
  if(m_bAlreadyComposed)
  {
    return;
  }

  if(m_ErrorMessagesCollection.Size() < 1)
  {
    return;
  }

  m_ErrorMessage = "";
  SimpleString indent = "  ";
  SimpleString marker = ": ";
  size_t numErrors = m_ErrorMessagesCollection.Size();
  for(size_t i = 0; i < numErrors; i++)
  {
    // Indent current message
    if(i > 1)
    {
    for(size_t j = 0; j < (i - 1); j++)
    {
      m_ErrorMessage += indent;
    }
    }

    if(i > 0)
    {
      m_ErrorMessage += marker;
    }

    m_ErrorMessage += *(m_ErrorMessagesCollection[numErrors - i - 1]);
    m_ErrorMessage += "\n";
  }

  m_bAlreadyComposed = true;
}
