

/****************************************************************************** 
 * 
 *  file:  OptionalUnlabeledTracker.h
 * 
 *  Copyright (c) 2005, ichael E. Smoot .
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


#ifndef TCLAP_OPTIONAL_UNLABELED_TRACKER_H
#define TCLAP_OPTIONAL_UNLABELED_TRACKER_H

#include <string>

namespace TCLAP {

class OptionalUnlabeledTracker
{

	public:

		static void check( bool req, const std::string& argName );

		static void gotOptional() { alreadyOptionalRef() = true; }

		static bool& alreadyOptional() { return alreadyOptionalRef(); } 

	private:

		static bool& alreadyOptionalRef() { static bool ct = false; return ct; }
};


void OptionalUnlabeledTracker::check( bool req, const std::string& argName )
{
    if ( OptionalUnlabeledTracker::alreadyOptional() )
        throw( SpecificationException(
	"You can't specify ANY Unlabeled Arg following an optional Unlabeled Arg",
	                argName ) );

    if ( !req )
        OptionalUnlabeledTracker::gotOptional();
}


} // namespace TCLAP

#endif
