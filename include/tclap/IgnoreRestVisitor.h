
/****************************************************************************** 
 * 
 *  file:  IgnoreRestVisitor.h
 * 
 *  Copyright (c) 2003, ichael E. Smoot .
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


#ifndef TCLAP_IGNORE_REST_VISITOR_H
#define TCLAP_IGNORE_REST_VISITOR_H

#include <tclap/Visitor.h>
#include <tclap/Arg.h>

namespace TCLAP {

/**
 * A Vistor that tells the CmdLine to begin ignoring arguments after
 * this one is parsed.
 */
class IgnoreRestVisitor: public Visitor
{
	public:

		/**
		 * Constructor.
		 */
		IgnoreRestVisitor() : Visitor() {}

		/**
		 * Sets Arg::_ignoreRest.
		 */
		void visit() { Arg::beginIgnoring();  }
};

}

#endif
