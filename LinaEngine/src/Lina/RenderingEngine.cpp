/*
Author: Inan Evin
www.inanevin.com

Copyright 2018 �nan Evin

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions
and limitations under the License.

Class: RenderingEngine
Timestamp: 1/2/2019 10:51:47 PM

*/

#include "LinaPch.hpp"
#include "RenderingEngine.hpp"  
#include "Package Manager/GraphicsAdapter.hpp"

namespace LinaEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	RenderingEngine::RenderingEngine()
	{
		// Get a graphics adapter.
		GraphicsAdapter graphicsAdapter;

		// Get window from the adapter.
		m_Window = std::unique_ptr<Window>(graphicsAdapter.CreateEngineWindow());
		
	}

	RenderingEngine::~RenderingEngine()
	{

	}
	void RenderingEngine::OnUpdate()
	{
		// Update window.
		m_Window->OnUpdate();
	}
}

