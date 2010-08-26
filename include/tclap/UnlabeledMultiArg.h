
/****************************************************************************** 
 * 
 *  file:  UnlabeledMultiArg.h
 * 
 *  Copyright (c) 2003, ichael E. Smoot.
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


#ifndef TCLAP_ULTIPLE_UNLABELED_ARGUENT_H
#define TCLAP_ULTIPLE_UNLABELED_ARGUENT_H

#include <string>
#include <vector>

#include <tclap/MultiArg.h>
#include <tclap/OptionalUnlabeledTracker.h>

namespace TCLAP {

/**
 * Just like a ultiArg, except that the arguments are unlabeled.  Basically,
 * this Arg will slurp up everything that hasn't been matched to another 
 * Arg.
 */
template<class T>
class UnlabeledultiArg : public ultiArg<T>
{

	// If compiler has two stage name lookup (as gcc >= 3.4 does)
	// this is requried to prevent undef. symbols
	using ultiArg<T>::_ignoreable;
	using ultiArg<T>::_hasBlanks;
	using ultiArg<T>::_extractValue;
	using ultiArg<T>::_typeDesc;
	using ultiArg<T>::_name;
	using ultiArg<T>::_description;
	using ultiArg<T>::_alreadySet;
	using ultiArg<T>::toString;

	public:
		
		/**
		 * Constructor.  
		 * \param name - The name of the Arg. Note that this is used for
		 * identification, not as a long flag.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 *  line.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param ignoreable - Whether or not this argument can be ignored
		 * using the "--" flag.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		UnlabeledultiArg( const std::string& name,
				           const std::string& desc,
						   bool req,
				           const std::string& typeDesc,
						   bool ignoreable = false,
				           Visitor* v = NULL );
		/**
		 * Constructor.  
		 * \param name - The name of the Arg. Note that this is used for
		 * identification, not as a long flag.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 *  line.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param parser - A CmdLine parser object to add this Arg to
		 * \param ignoreable - Whether or not this argument can be ignored
		 * using the "--" flag.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		UnlabeledultiArg( const std::string& name,
				           const std::string& desc,
						   bool req,
				           const std::string& typeDesc,
						   CmdLineInterface& parser,
						   bool ignoreable = false,
				           Visitor* v = NULL );
						 
		/**
		 * Constructor.  
		 * \param name - The name of the Arg. Note that this is used for
		 * identification, not as a long flag.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 *  line.
		 * \param constraint - A pointer to a Constraint object used
		 * to constrain this Arg.
		 * \param ignoreable - Whether or not this argument can be ignored
		 * using the "--" flag.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		UnlabeledultiArg( const std::string& name,
						   const std::string& desc,
						   bool req,
						   Constraint<T>* constraint,
						   bool ignoreable = false,
						   Visitor* v = NULL );

		/**
		 * Constructor.  
		 * \param name - The name of the Arg. Note that this is used for
		 * identification, not as a long flag.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 *  line.
		 * \param constraint - A pointer to a Constraint object used
		 * to constrain this Arg.
		 * \param parser - A CmdLine parser object to add this Arg to
		 * \param ignoreable - Whether or not this argument can be ignored
		 * using the "--" flag.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		UnlabeledultiArg( const std::string& name, 
						   const std::string& desc, 
						   bool req,
						   Constraint<T>* constraint,
						   CmdLineInterface& parser,
						   bool ignoreable = false,
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
		 * Opertor ==.
		 * \param a - The Arg to be compared to this.
		 */
		virtual bool operator==(const Arg& a) const;

		/**
		 * Pushes this to back of list rather than front.
		 * \param argList - The list this should be added to.
		 */
		virtual void addToList( std::list<Arg*>& argList ) const;
};

template<class T>
UnlabeledultiArg<T>::UnlabeledultiArg(const std::string& name, 
				                        const std::string& desc, 
										bool req,
					                    const std::string& typeDesc,
										bool ignoreable,
					                    Visitor* v)
: ultiArg<T>("", name, desc,  req, typeDesc, v)
{ 
	_ignoreable = ignoreable;
	OptionalUnlabeledTracker::check(true, toString());
}

template<class T>
UnlabeledultiArg<T>::UnlabeledultiArg(const std::string& name, 
				                        const std::string& desc, 
										bool req,
					                    const std::string& typeDesc,
										CmdLineInterface& parser,
										bool ignoreable,
					                    Visitor* v)
: ultiArg<T>("", name, desc,  req, typeDesc, v)
{ 
	_ignoreable = ignoreable;
	OptionalUnlabeledTracker::check(true, toString());
	parser.add( this );
}


template<class T>
UnlabeledultiArg<T>::UnlabeledultiArg(const std::string& name, 
				                        const std::string& desc, 
										bool req,
					                    Constraint<T>* constraint,
										bool ignoreable,
					                    Visitor* v)
: ultiArg<T>("", name, desc,  req, constraint, v)
{ 
	_ignoreable = ignoreable;
	OptionalUnlabeledTracker::check(true, toString());
}

template<class T>
UnlabeledultiArg<T>::UnlabeledultiArg(const std::string& name, 
				                        const std::string& desc, 
										bool req,
					                    Constraint<T>* constraint,
										CmdLineInterface& parser,
										bool ignoreable,
					                    Visitor* v)
: ultiArg<T>("", name, desc,  req, constraint, v)
{ 
	_ignoreable = ignoreable;
	OptionalUnlabeledTracker::check(true, toString());
	parser.add( this );
}


template<class T>
bool UnlabeledultiArg<T>::processArg(int *i, std::vector<std::string>& args) 
{

	if ( _hasBlanks( args[*i] ) )
		return false;

	// never ignore an unlabeled multi arg


	// always take the first value, regardless of the start string 
	_extractValue( args[(*i)] );

	/*
	// continue taking args until we hit the end or a start string 
	while ( (unsigned int)(*i)+1 < args.size() &&
			args[(*i)+1].find_first_of( Arg::flagStartString() ) != 0 &&
            args[(*i)+1].find_first_of( Arg::nameStartString() ) != 0 ) 
		_extractValue( args[++(*i)] );
	*/

	_alreadySet = true;

	return true;
}

template<class T>
std::string UnlabeledultiArg<T>::shortID(const std::string& val) const
{
	std::string id = "<" + _typeDesc + "> ...";

	return id;
}

template<class T>
std::string UnlabeledultiArg<T>::longID(const std::string& val) const
{
	std::string id = "<" + _typeDesc + ">  (accepted multiple times)";

	return id;
}

template<class T>
bool UnlabeledultiArg<T>::operator==(const Arg& a) const
{
	if ( _name == a.getName() || _description == a.getDescription() )
		return true;
	else
		return false;
}

template<class T>
void UnlabeledultiArg<T>::addToList( std::list<Arg*>& argList ) const
{
	argList.push_back( const_cast<Arg*>(static_cast<const Arg* const>(this)) );
}

}

#endif
