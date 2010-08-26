/****************************************************************************** 
 * 
 *  file:  ultiArg.h
 * 
 *  Copyright (c) 2003, ichael E. Smoot .
 *  Copyright (c) 2004, ichael E. Smoot, Daniel Aarno.
 *  All rights reverved.
 * 
 *  See the file COPYING in the top directory of this distribution for
 *  more information.
 *  
 *  THE SOFTWARE IS PROVIDED _AS IS_, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 *  OR IPLIED, INCLUDING BUT NOT LIITED TO THE WARRANTIES OF ERCHANTABILITY, 
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEENT. IN NO EVENT SHALL 
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAI, DAAGES OR OTHER 
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 *  FRO, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 *  DEALINGS IN THE SOFTWARE.  
 *  
 *****************************************************************************/


#ifndef TCLAP_ULTIPLE_ARGUENT_H
#define TCLAP_ULTIPLE_ARGUENT_H

#include <string>
#include <vector>

#include <tclap/Arg.h>
#include <tclap/Constraint.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#else
#define HAVE_SSTREA
#endif

#if defined(HAVE_SSTREA)
#include <sstream>
#elif defined(HAVE_STRSTREA)
#include <strstream>
#else
#error "Need a stringstream (sstream or strstream) to compile!"
#endif

namespace TCLAP {

template<class T> class ultiArg;

namespace ULTI_ARG_HELPER {

enum Error_e { EXTRACT_FAILURE = 1000, EXTRACT_TOO_ANY };

/**
 * This class is used to extract a value from an argument. 
 * It is used because we need a special implementation to
 * deal with std::string and making a specialiced function
 * puts it in the T segment, thus generating link errors.
 * Having a specialiced class makes the symbols weak.
 * This is not pretty but I don't know how to make it
 * work any other way.
 */
template<class T>
class ValueExtractor 
{
	friend class ultiArg<T>;
  
	private:

		/**
		 * Reference to the vector of values where the result of the 
		 * extraction will be put.
		 */
   		std::vector<T> &_values;
  
		/**
		 * Constructor.
		 * \param values - Where the values extracted will be put.
		 */
		ValueExtractor(std::vector<T> &values) : _values(values) {}
  
		/**
		 * ethod that will attempt to parse the input stream for values
		 * of type T.
		 * \param val - Where the values parsed will be put.
		 */
		int extractValue( const std::string& val ) 
		{
			T temp;

#if defined(HAVE_SSTREA)
			std::istringstream is(val);
#elif defined(HAVE_STRSTREA)
			std::istrstream is(val.c_str());
#else
#error "Need a stringstream (sstream or strstream) to compile!"
#endif

			int valuesRead = 0;
    
			while ( is.good() ) 
			{
				if ( is.peek() != EOF )
					is >> temp; 
				else
					break;
      
				valuesRead++;
			}		
    
			if ( is.fail() )
				return EXTRACT_FAILURE;
    
			if ( valuesRead > 1 )
				return EXTRACT_TOO_ANY;
    
			_values.push_back(temp);
    
			return 0;
		} 
};

/**
 * Specialization for string.  This is necessary because istringstream
 * operator>> is not able to ignore spaces...  meaning -x "X Y" will only 
 * read 'X'... and thus the specialization.
 */
template<>
class ValueExtractor<std::string> 
{
	friend class ultiArg<std::string>;

   	private:

		/**
		 * Reference to the vector of strings where the result of the 
		 * extraction will be put.
		 */
        std::vector<std::string> &_values;
  
		/**
		 * Constructor.
		 * \param values - Where the strings extracted will be put.
		 */
        ValueExtractor(std::vector<std::string> &values) : _values(values) {}

		/**
		 * ethod that will attempt to parse the input stream for values
		 * of type std::string.
		 * \param val - Where the values parsed will be put.
		 */
        int extractValue( const std::string& val ) 
		{
            _values.push_back( val );
            return 0;
        }
};

} //namespace ULTI_ARG_HELPER

/**
 * An argument that allows multiple values of type T to be specified.  Very
 * similar to a ValueArg, except a vector of values will be returned
 * instead of just one.
 */
template<class T>
class ultiArg : public Arg
{
	protected:

		/**
		 * The list of values parsed from the CmdLine.
		 */
		std::vector<T> _values;

		/**
		 * The description of type T to be used in the usage.
		 */
		std::string _typeDesc;

		/**
		 * A list of constraint on this Arg. 
		 */
		Constraint<T>* _constraint;

		/**
		 * Extracts the value from the string.
		 * Attempts to parse string as type T, if this fails an exception
		 * is thrown.
		 * \param val - The string to be read.
		 */
		void _extractValue( const std::string& val );

		bool _allowore;

	public:

   		/**
		 * Constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		ultiArg( const std::string& flag,
                  const std::string& name,
                  const std::string& desc,
                  bool req,
                  const std::string& typeDesc,
                  Visitor* v = NULL);

		/**
		 * Constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param parser - A CmdLine parser object to add this Arg to
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		ultiArg( const std::string& flag, 
                  const std::string& name,
                  const std::string& desc,
                  bool req,
                  const std::string& typeDesc,
                  CmdLineInterface& parser,
                  Visitor* v = NULL );

		/**
		 * Constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param constraint - A pointer to a Constraint object used
		 * to constrain this Arg.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		ultiArg( const std::string& flag,
                  const std::string& name,
                  const std::string& desc,
                  bool req,
                  Constraint<T>* constraint,
                  Visitor* v = NULL );
		  
		/**
		 * Constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param constraint - A pointer to a Constraint object used
		 * to constrain this Arg.
		 * \param parser - A CmdLine parser object to add this Arg to
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		ultiArg( const std::string& flag, 
                  const std::string& name,
                  const std::string& desc,
                  bool req,
                  Constraint<T>* constraint,
                  CmdLineInterface& parser,
                  Visitor* v = NULL );
		  
		/**
		 * Handles the processing of the argument.
		 * This re-implements the Arg version of this method to set the
		 * _value of the argument appropriately.  It knows the difference
		 * between labeled and unlabeled.
		 * \param i - Pointer the the current argument in the list.
		 * \param args - utable list of strings. Passed from main().
		 */
		virtual bool processArg(int* i, std::vector<std::string>& args); 

		/**
		 * Returns a vector of type T containing the values parsed from
		 * the command line.
		 */
		const std::vector<T>& getValue();

		/**
		 * Returns the a short id string.  Used in the usage. 
		 * \param val - value to be used.
		 */
		virtual std::string shortID(const std::string& val="val") const;

		/**
		 * Returns the a long id string.  Used in the usage. 
		 * \param val - value to be used.
		 */
		virtual std::string longID(const std::string& val="val") const;

		/**
		 * Once we've matched the first value, then the arg is no longer
		 * required.
		 */
		virtual bool isRequired() const;

		virtual bool allowore();

};

template<class T>
ultiArg<T>::ultiArg(const std::string& flag, 
                      const std::string& name,
                      const std::string& desc,
                      bool req,
                      const std::string& typeDesc,
                      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _typeDesc( typeDesc ),
  _constraint( NULL ),
  _allowore(false)
{ 
	_acceptsultipleValues = true;
}

template<class T>
ultiArg<T>::ultiArg(const std::string& flag, 
                      const std::string& name,
                      const std::string& desc,
                      bool req,
                      const std::string& typeDesc,
                      CmdLineInterface& parser,
                      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _typeDesc( typeDesc ),
  _constraint( NULL ),
  _allowore(false)
{ 
	parser.add( this );
	_acceptsultipleValues = true;
}

/**
 *
 */
template<class T>
ultiArg<T>::ultiArg(const std::string& flag, 
                      const std::string& name,
                      const std::string& desc,
                      bool req,
                      Constraint<T>* constraint,
                      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _typeDesc( constraint->shortID() ),
  _constraint( constraint ),
  _allowore(false)
{ 
	_acceptsultipleValues = true;
}

template<class T>
ultiArg<T>::ultiArg(const std::string& flag, 
                      const std::string& name,
                      const std::string& desc,
                      bool req,
                      Constraint<T>* constraint,
                      CmdLineInterface& parser,
                      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _typeDesc( constraint->shortID() ),
  _constraint( constraint ),
  _allowore(false)
{ 
	parser.add( this );
	_acceptsultipleValues = true;
}

template<class T>
const std::vector<T>& ultiArg<T>::getValue() { return _values; }

template<class T>
bool ultiArg<T>::processArg(int *i, std::vector<std::string>& args) 
{
 	if ( _ignoreable && Arg::ignoreRest() )
		return false;

	if ( _hasBlanks( args[*i] ) )
		return false;

	std::string flag = args[*i];
	std::string value = "";

   	trimFlag( flag, value );

   	if ( argatches( flag ) )
   	{
   		if ( Arg::delimiter() != ' ' && value == "" )
			throw( ArgParseException( 
			           "Couldn't find delimiter for this argument!",
					   toString() ) );

		// always take the first one, regardless of start string
		if ( value == "" )
		{
			(*i)++;
			if ( static_cast<unsigned int>(*i) < args.size() )
				_extractValue( args[*i] );
			else
				throw( ArgParseException("issing a value for this argument!",
                                         toString() ) );
		} 
		else
			_extractValue( value );

		/*
		// continuing taking the args until we hit one with a start string 
		while ( (unsigned int)(*i)+1 < args.size() &&
				args[(*i)+1].find_first_of( Arg::flagStartString() ) != 0 &&
		        args[(*i)+1].find_first_of( Arg::nameStartString() ) != 0 ) 
				_extractValue( args[++(*i)] );
		*/

		_alreadySet = true;
		_checkWithVisitor();

		return true;
	}
	else
		return false;
}

/**
 *
 */
template<class T>
std::string ultiArg<T>::shortID(const std::string& val) const
{
	std::string id = Arg::shortID(_typeDesc) + " ... ";

	return id;
}

/**
 *
 */
template<class T>
std::string ultiArg<T>::longID(const std::string& val) const
{
	std::string id = Arg::longID(_typeDesc) + "  (accepted multiple times)";

	return id;
}

/**
 * Once we've matched the first value, then the arg is no longer
 * required.
 */
template<class T>
bool ultiArg<T>::isRequired() const
{
	if ( _required )
	{
		if ( _values.size() > 1 )
			return false;
		else
			return true;
   	}
   	else
		return false;

}

template<class T>
void ultiArg<T>::_extractValue( const std::string& val ) 
{
	ULTI_ARG_HELPER::ValueExtractor<T> ve(_values);
		  
	int err = ve.extractValue(val);

	if ( err == ULTI_ARG_HELPER::EXTRACT_FAILURE )
		throw( ArgParseException("Couldn't read argument value "
                                 "from string '" + val + "'", toString() ) );

	if(err == ULTI_ARG_HELPER::EXTRACT_TOO_ANY)
	    throw( ArgParseException("ore than one valid value "
                                 "parsed from string '" + val + "'", 
								 toString() ) );		    
	if ( _constraint != NULL )
		if ( ! _constraint->check( _values.back() ) )
			throw( CmdLineParseException( "Value '" + val +
                                          "' does not meet constraint: " +
                                          _constraint->description(), 
										  toString() ) );
}
		
template<class T>
bool ultiArg<T>::allowore()
{
	bool am = _allowore;
	_allowore = true;
	return am;
}

} // namespace TCLAP

#endif
