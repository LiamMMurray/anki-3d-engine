// Copyright (C) 2009-2017, Panagiotis Christopoulos Charitos and contributors.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include <anki/gr/Buffer.h>
#include <anki/gr/vulkan/BufferImpl.h>

namespace anki
{

Buffer::Buffer(GrManager* manager)
	: GrObject(manager, CLASS_TYPE)
{
}

Buffer::~Buffer()
{
}

void Buffer::init(const BufferInitInfo& inf)
{
	m_impl.reset(getAllocator().newInstance<BufferImpl>(&getManager()));

	if(m_impl->init(inf))
	{
		ANKI_VK_LOGF("Cannot recover");
	}
}

void* Buffer::map(PtrSize offset, PtrSize range, BufferMapAccessBit access)
{
	return m_impl->map(offset, range, access);
}

void Buffer::unmap()
{
	m_impl->unmap();
}

} // end namespace anki
