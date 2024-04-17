#pragma once

namespace FLR {

	class Layer
	{
	public:
		Layer(std::string name);
		virtual ~Layer();

		virtual void onAttach();
		virtual void onDetach();

		virtual void onUpdate();
		virtual void onEvent();

		inline std::string getDebugName() { return m_DebugName; };

	private:
		std::string m_DebugName;
	};

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void attachLayer(Layer* lyr);
		void attachOverlay(Layer* lyr);

		void detachLayer(Layer* lyr);
		void detachOverlay(Layer* lyr);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();

	private:
		std::vector<Layer*> m_Stack;
		std::vector<Layer*>::iterator m_InsertSig;

		std::vector<Layer*> m_PopedStack;
	};

}