#ifndef LOOKUPEXCEPTION_H
#define LOOKUPEXCEPTION_H

#include <string>
using std::string;

namespace TermInterpreter
{


class LookupException
{
public:
    LookupException(string object, string exceptiontext) : m_obj(object), m_extxt(exceptiontext) {}
    string getObject() { return m_obj; }
    string getExceptionText() { return m_extxt; }
private:
    string m_obj;
    string m_extxt;
};


} // namespace

#endif // LOOKUPEXCEPTION_H
