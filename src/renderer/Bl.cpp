#include "anki/renderer/Bl.h"
#include "anki/renderer/Renderer.h"
#include "anki/resource/ShaderProgramResource.h"

namespace anki {

//==============================================================================
void Bl::init(const Renderer::Initializer& initializer)
{
	enabled = initializer.pps.bl.enabled;
	blurringIterationsNum = initializer.pps.bl.blurringIterationsNum;
	sideBlurFactor = initializer.pps.bl.sideBlurFactor;

	if(!enabled)
	{
		return;
	}

	// Horizontal
	//
	try
	{
		Renderer::createFai(r->getWidth(), r->getHeight(), GL_RGB, GL_RGB,
			GL_FLOAT, blurFai);

		hBlurFbo.create();
		hBlurFbo.setColorAttachments({&blurFai});
	}
	catch(const std::exception& e)
	{
		throw ANKI_EXCEPTION("Cannot create horizontal blur "
			"post-processing stage FBO") << e;
	}

	hBlurSProg.load(ShaderProgramResource::createSrcCodeToCache(
		"shaders/PpsBlurGeneric.glsl", "#define HPASS\n").c_str());

	// Vertical
	//
	try
	{
		vBlurFbo.create();
		vBlurFbo.setColorAttachments({&r->getPps().getPostPassFai()});
	}
	catch(std::exception& e)
	{
		throw ANKI_EXCEPTION("Cannot create vertical blur "
			"post-processing stage FBO") << e;
	}

	vBlurSProg.load(ShaderProgramResource::createSrcCodeToCache(
		"shaders/PpsBlurGeneric.glsl", "#define VPASS\n").c_str());

	// Side blur
	//
	try
	{
		sideBlurFbo.create();
		sideBlurFbo.setColorAttachments({&r->getMs().getNormalFai()});
	}
	catch(std::exception& e)
	{
		throw ANKI_EXCEPTION("Cannot create side blur "
			"post-processing stage FBO") << e;
	}

	sideBlurMap.load("engine-rsrc/side-blur.png");
	sideBlurSProg.load("shaders/PpsSideBlur.glsl");
}

//==============================================================================
void Bl::runSideBlur()
{
	if(sideBlurFactor == 0.0)
	{
		return;
	}

	sideBlurFbo.bind();
	sideBlurSProg->bind();

	GlStateSingleton::get().enable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	sideBlurSProg->findUniformVariableByName("tex")->set(
		static_cast<const Texture&>(*sideBlurMap));
	sideBlurSProg->findUniformVariableByName("factor")->set(sideBlurFactor);

	r->drawQuad();
}

//==============================================================================
void Bl::runBlur()
{
	GlStateSingleton::get().disable(GL_BLEND);

	// Setup programs here. Reverse order
	vBlurSProg->bind();
	vBlurSProg->findUniformVariableByName("img")->set(blurFai);
	vBlurSProg->findUniformVariableByName("msNormalFai")->set(
		r->getMs().getNormalFai());
	vBlurSProg->findUniformVariableByName("imgDimension")->set(
		float(r->getHeight()));

	hBlurSProg->bind();
	hBlurSProg->findUniformVariableByName("img")->set(
		r->getPps().getPostPassFai());
	hBlurSProg->findUniformVariableByName("msNormalFai")->set(
		r->getMs().getNormalFai());
	hBlurSProg->findUniformVariableByName("imgDimension")->set(
		float(r->getWidth()));

	for(uint32_t i = 0; i < blurringIterationsNum; i++)
	{
		// hpass
		hBlurFbo.bind();
		hBlurSProg->bind();
		r->drawQuad();

		// vpass
		vBlurFbo.bind();
		vBlurSProg->bind();
		r->drawQuad();
	}
}

//==============================================================================
void Bl::run()
{
	if(!enabled)
	{
		return;
	}

	runSideBlur();
	runBlur();
}

} // end namespace