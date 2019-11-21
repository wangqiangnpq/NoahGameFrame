/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2019 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#ifndef NFI_UI_MODULE_H
#define NFI_UI_MODULE_H

#include <iostream>
#include "NFIModule.h"

enum NFViewType
{
	NONE,
	OperatorView,
	ContainerView,
	GodView,
	SceneView,
	HierachyView,
	ConsoleView,
	ProfileView,
	InspectorView,
	BluePrintView,
	ProjectView,
	GameView,
};

class NFIView;
class NFIUIModule
    : public NFIModule
{
public:
    virtual ~NFIUIModule(){}

	virtual NF_SHARE_PTR<NFIView> GetView(NFViewType viewType) = 0;

	virtual const std::vector<NF_SHARE_PTR<NFIView>>& GetViews() = 0;

	virtual void ExecuteBegin(const std::string& name, bool* visible) = 0;
	virtual void ExecuteEnd() = 0;

};

class NFIView : public NFIModule
{
public:

	NFIView(NFIPluginManager* p, NFViewType vt, const std::string& name)
	{
		this->viewType = vt;
		pPluginManager = p;
		this->name = name;

		m_pUIModule = pPluginManager->FindModule<NFIUIModule>();
	}

    void OccupySubRender (NFIView* pOccupyView)
    {
		m_pOccupyView = pOccupyView;
    }

	virtual void ExecuteBegin()
    {
		m_pUIModule->ExecuteBegin(name, &visible);
	}

    virtual bool Execute()
    {


        return true;
    }
	
	virtual void SubRender()
	{

	}

	virtual void ExecuteEnd()
    {
		if (m_pOccupyView)
		{
			m_pOccupyView->SubRender();
		}

		m_pUIModule->ExecuteEnd();
	}

	NFIUIModule* m_pUIModule;
	NFIView* m_pOccupyView = nullptr;;

    bool visible = true;
	NFViewType viewType;
	std::string name;
};

#endif