
/****************************************************************************** 
 * 
 *  file:  VersionVisitor.h
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


#ifndef TCLAP_VERSION_VISITOR_H
#define TCLAP_VERSION_VISITOR_H

#include <tclap/CmdLineInterface.h>
#include <tclap/CmdLineOutput.h>
#include <tclap/Visitor.h>

namespace TCLAP {

/**
 * A Vistor that will call the version method of the given CmdLineOutput
 * for the specified CmdLine object and then exit.
 */
class VersionVisitor: public Visitor
{
	protected:

		/**
		 * The CmdLine of interest.
		 */
		CmdLineInterface* _cmd;

		/**
		 * The output object. 
		 */
		CmdLineOutput** _out;

	public:

		/**
		 * Constructor.
		 * \param cmd - The CmdLine the output is generated for. 
		 * \param out - The type of output. 
		 */
		VersionVisitor( CmdLineInterface* cmd, CmdLineOutput** out ) 
				: Visitor(), _cmd( cmd ), _out( out ) { }

		/**
		 * Calls the version method of the output object using the
		 * specified CmdLine.
		 */
		void visit() { (*_out)->version(*_cmd); exit(0); }

};

}

#endif
