/*
Author: Inan Evin
www.inanevin.com

Copyright 2018 Inan Evin

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions 
and limitations under the License.

Class: LayerStack
Timestamp: 1/2/2019 1:43:13 AM

*/

#pragma once
#ifndef LayerStack_HPP
#define LayerStack_HPP

#include "Layer.hpp"
#include "APIExport.hpp"
#include "DataStructures.hpp"

namespace LinaEngine
{
	class LINA_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		LinaArray<Layer*>::iterator begin() { return m_Layers.begin(); }
		LinaArray<Layer*>::iterator end() { return m_Layers.end(); }

	private:

		LinaArray<Layer*> m_Layers;
		LinaArray<Layer*>::iterator m_LayerInsert;
	};
}


#endif