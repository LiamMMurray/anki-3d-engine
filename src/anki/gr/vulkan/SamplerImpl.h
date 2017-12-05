// Copyright (C) 2009-2017, Panagiotis Christopoulos Charitos and contributors.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#pragma once

#include <anki/gr/vulkan/VulkanObject.h>
#include <anki/gr/vulkan/SamplerFactory.h>

namespace anki
{

/// @addtogroup vulkan
/// @{

/// Vulkan implementation of Sampler.
class SamplerImpl : public VulkanObject
{
public:
	MicroSamplerPtr m_sampler;

	SamplerImpl(GrManager* manager)
		: VulkanObject(manager)
	{
	}

	~SamplerImpl()
	{
	}

	ANKI_USE_RESULT Error init(const SamplerInitInfo& init);
};
/// @}

} // end namespace anki
