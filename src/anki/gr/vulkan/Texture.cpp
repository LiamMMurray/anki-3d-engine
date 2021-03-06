// Copyright (C) 2009-2019, Panagiotis Christopoulos Charitos and contributors.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include <anki/gr/Texture.h>
#include <anki/gr/vulkan/TextureImpl.h>
#include <anki/gr/GrManager.h>

namespace anki
{

Texture* Texture::newInstance(GrManager* manager, const TextureInitInfo& init)
{
	TextureImpl* impl = manager->getAllocator().newInstance<TextureImpl>(manager, init.getName());
	Error err = impl->init(init);
	if(err)
	{
		manager->getAllocator().deleteInstance(impl);
	}
	return impl;
}

} // end namespace anki
