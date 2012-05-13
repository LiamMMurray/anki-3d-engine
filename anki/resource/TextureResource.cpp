#include "anki/resource/TextureResource.h"
#include "anki/resource/Image.h"
#include "anki/util/Exception.h"


namespace anki {


//==============================================================================
void TextureResource::load(const char* filename)
{
	try
	{
		load(Image(filename));
	}
	catch(std::exception& e)
	{
		throw ANKI_EXCEPTION("File \"" + filename + "\"") << e;
	}
}


//==============================================================================
void TextureResource::load(const Image& img)
{
	Initializer init;
	init.width = img.getWidth();
	init.height = img.getHeight();
	init.dataSize = img.getDataSize();

	bool compressionEnabled = 
		TextureManagerSingleton::get().getCompressionEnabled();

	switch(img.getColorType())
	{
	case Image::CT_R:
		init.internalFormat = (compressionEnabled) 
			? GL_COMPRESSED_RED : GL_RED;
		init.format = GL_RED;
		init.type = GL_UNSIGNED_BYTE;
		break;

	case Image::CT_RGB:
		init.internalFormat = (compressionEnabled) 
			? GL_COMPRESSED_RGB : GL_RGB;
		init.format = GL_RGB;
		init.type = GL_UNSIGNED_BYTE;
		break;

	case Image::CT_RGBA:
		init.internalFormat = (compressionEnabled) 
			? GL_COMPRESSED_RGBA : GL_RGBA;
		init.format = GL_RGBA;
		init.type = GL_UNSIGNED_BYTE;
		break;

	default:
		ANKI_ASSERT(0);
	}

	switch(img.getDataCompression())
	{
	case Image::DC_NONE:
		break;

	case Image::DC_DXT1:
		init.internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;

	case Image::DC_DXT3:
		init.internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;

	case Image::DC_DXT5:
		init.internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	}

	init.data = img.getData();
	init.mipmapping = TextureManagerSingleton::get().getMipmappingEnabled();
	init.filteringType = init.mipmapping ? TFT_TRILINEAR : TFT_LINEAR;
	init.repeat = true;
	init.anisotropyLevel = TextureManagerSingleton::get().getAnisotropyLevel();

	create(init);
}


} // end namespace