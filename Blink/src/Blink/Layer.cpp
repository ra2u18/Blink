#include "blpch.h"
#include "Layer.h"

namespace Blink
{
	Layer::Layer(const std::string& name)
		: m_DebugName(name) {}

	Layer::~Layer() { }
}