#ifndef ERROR_COLLECTOR_H
#define ERROR_COLLECTOR_H

#include "Array.h"
#include "SimpleString.h"

class ErrorCollector
{
public:
  ErrorCollector();
  virtual ~ErrorCollector();

  void Add(const char* pErrorMsg);
  void Add(const SimpleString& pErrorMsgStr);

  const SimpleString& ErrorMessageString();

private:
  Array<SimpleString*> m_ErrorMessagesCollection;
  SimpleString m_ErrorMessage;
  bool m_bAlreadyComposed;

  void composeErrorMessage();

};

#endif // ERROR_COLLECTOR_H
