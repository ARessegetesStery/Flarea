#include "flrpch.h"

#include "Layer.h"

namespace FLR {

	Layer::Layer(std::string name = "Layer") : m_DebugName(name) {	}

	Layer::~Layer()
	{

	}

	void Layer::onAttach()
	{

	}

	void Layer::onDetach()
	{

	}

	void Layer::onUpdate()
	{

	}

	void Layer::onEvent()
	{

	}

	LayerStack::LayerStack()
	{
		m_InsertSig = m_Stack.begin();
	}

	LayerStack::~LayerStack()
	{
		for (auto i : m_Stack)
			delete i;
		for (auto i : m_PopedStack)
			delete i;
	}

	void LayerStack::attachLayer(Layer* lyr)
	{
		m_Stack.insert(m_InsertSig, lyr);
		lyr->onAttach();
		m_InsertSig = m_Stack.begin();
	}

	void LayerStack::attachOverlay(Layer* lyr)
	{
		m_Stack.emplace_back(lyr);
		lyr->onAttach();
	}

	void LayerStack::detachLayer(Layer* lyr)
	{
		auto iter = std::find(m_Stack.begin(), m_Stack.end(), lyr);
		if (iter != m_Stack.end())
		{
			// m_PopedStack.emplace(iter); // HACK unsure
			m_Stack.erase(iter);
			--m_InsertSig;
		}
	}

	void LayerStack::detachOverlay(Layer* lyr)
	{
		auto iter = std::find(m_Stack.begin(), m_Stack.end(), lyr);
		if (iter != m_Stack.end())
		{
			// m_PopedStack.emplace(iter); // HACK unsure
			m_Stack.erase(iter);
		}
		m_PopedStack.push_back(*iter);
	}

	std::vector<Layer*>::iterator LayerStack::begin()
	{
		return m_Stack.begin();
	}

	std::vector<Layer*>::iterator LayerStack::end()
	{
		return m_Stack.end();
	}

}