// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

#ifndef _TEMPORALHANDLER_HPP_
#define _TEMPORALHANDLER_HPP_

#include "../ADE.hpp"
#include "Version.hpp"
#include "VersionTransition.hpp"
#include "Transaction.hpp"
#include "Workspace.hpp"

class TempHandler : public ADEHandler
{
protected:
	temporal::Version* _currentVersion;
	temporal::VersionTransition* _currentTransition;
	temporal::Transaction* _currentTransaction;
	bool _inFromTags;
	bool _inToTags;
	std::vector<temporal::Version*> _versions;
	std::vector<temporal::VersionTransition*> _transitions;
	std::map<std::string, temporal::Workspace> _workspaces;

public:
	TempHandler(void);
	TempHandler(citygml::CityGMLHandler* gmlHandler);
	void startElement(std::string, void*);
	void endElement(std::string);
	void endDocument();
protected:
	std::string getAttribute(void*, const std::string&, const std::string&);
	std::string removeNamespace(std::string);
	std::string getIDfromQuery(std::string);
	//private:
		//  JE 17/02/2016: DISCARDED BECAUSE PROBLEMS WITH RECENT VERSIONS OF UBUNTU:
		//Adding to ADE register (template in ADE.hpp)
		//static ADERegister<TempHandler> reg;
};

#endif
