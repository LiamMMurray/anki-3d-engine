// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include <anki/scene/ReflectionProbe.h>
#include <anki/scene/MoveComponent.h>
#include <anki/scene/FrustumComponent.h>
#include <anki/scene/SceneGraph.h>
#include <anki/scene/SceneGraph.h>
#include <anki/renderer/Is.h>

namespace anki {

//==============================================================================
// ReflectionProbeMoveFeedbackComponent                                        =
//==============================================================================

/// Feedback component
class ReflectionProbeMoveFeedbackComponent: public SceneComponent
{
public:
	ReflectionProbeMoveFeedbackComponent(SceneNode* node)
		: SceneComponent(SceneComponent::Type::NONE, node)
	{}

	Error update(SceneNode& node, F32, F32, Bool& updated) override
	{
		updated = false;

		MoveComponent& move = node.getComponent<MoveComponent>();
		if(move.getTimestamp() == node.getGlobalTimestamp())
		{
			// Move updated
			ReflectionProbe& dnode = static_cast<ReflectionProbe&>(node);
			dnode.onMoveUpdate(move);
		}

		return ErrorCode::NONE;
	}
};

//==============================================================================
// ReflectionProbe                                                             =
//==============================================================================

//==============================================================================
Error ReflectionProbe::create(const CString& name, F32 radius)
{
	SceneComponent* comp;

	ANKI_CHECK(SceneNode::create(name));

	// Move component first
	comp = getSceneAllocator().newInstance<MoveComponent>(this);
	addComponent(comp, true);

	// Feedback component
	comp = getSceneAllocator().
		newInstance<ReflectionProbeMoveFeedbackComponent>(this);
	addComponent(comp, true);

	// The frustum components
	const F32 ang = toRad(90.0);
	const F32 zNear = FRUSTUM_NEAR_PLANE;

	Mat3 rot;
	const F32 PI = getPi<F32>();

	rot = Mat3(Euler(0.0, -PI / 2.0, 0.0)) * Mat3(Euler(0.0, 0.0, PI));
	m_cubeSides[0].m_localTrf.setRotation(Mat3x4(rot));
	rot = Mat3(Euler(0.0, PI / 2.0, 0.0)) * Mat3(Euler(0.0, 0.0, PI));
	m_cubeSides[1].m_localTrf.setRotation(Mat3x4(rot));
	rot = Mat3(Euler(PI / 2.0, 0.0, 0.0));
	m_cubeSides[2].m_localTrf.setRotation(Mat3x4(rot));
	rot = Mat3(Euler(-PI / 2.0, 0.0, 0.0));
	m_cubeSides[3].m_localTrf.setRotation(Mat3x4(rot));
	rot = Mat3(Euler(0.0, PI, 0.0)) * Mat3(Euler(0.0, 0.0, PI));
	m_cubeSides[4].m_localTrf.setRotation(Mat3x4(rot));
	rot = Mat3(Euler(0.0, 0.0, PI));
	m_cubeSides[5].m_localTrf.setRotation(Mat3x4(rot));

	for(U i = 0; i < 6; ++i)
	{
		m_cubeSides[i].m_localTrf.setOrigin(Vec4(0.0));
		m_cubeSides[i].m_localTrf.setScale(1.0);

		m_cubeSides[i].m_frustum.setAll(ang, ang, zNear, radius);
		m_cubeSides[i].m_frustum.resetTransform(m_cubeSides[i].m_localTrf);

		FrustumComponent* frc =
			getSceneAllocator().newInstance<FrustumComponent>(
			this, &m_cubeSides[i].m_frustum);

		frc->setEnabledVisibilityTests(
			FrustumComponent::VisibilityTestFlag::TEST_RENDER_COMPONENTS
			| FrustumComponent::VisibilityTestFlag::TEST_LIGHT_COMPONENTS);

		addComponent(frc, true);
	}

	// Spatial component
	m_spatialSphere.setCenter(Vec4(0.0));
	m_spatialSphere.setRadius(radius);
	comp = getSceneAllocator().newInstance<SpatialComponent>(
		this, &m_spatialSphere);

	// Reflection probe
	comp = getSceneAllocator().newInstance<ReflectionProbeComponent>(this);
	addComponent(comp, true);

	// Create graphics objects
	createGraphics();

	return ErrorCode::NONE;
}

//==============================================================================
void ReflectionProbe::createGraphics()
{
	// Create textures
	TextureInitializer init;
	init.m_type = TextureType::CUBE;
	init.m_width = init.m_height = m_fbSize;
	init.m_format = Is::RT_PIXEL_FORMAT;
	init.m_sampling.m_minMagFilter = SamplingFilter::LINEAR;

	m_colorTex = getSceneGraph().getGrManager().newInstance<Texture>(init);

	// Create framebuffers
	for(U i = 0; i < 6; ++i)
	{
		FramebufferInitializer fbInit;
		fbInit.m_colorAttachmentsCount = 1;
		fbInit.m_colorAttachments[0].m_texture = m_colorTex;
		fbInit.m_colorAttachments[0].m_layer = i;
		fbInit.m_colorAttachments[0].m_loadOperation =
			AttachmentLoadOperation::DONT_CARE;

		m_cubeSides[i].m_fb =
			getSceneGraph().getGrManager().newInstance<Framebuffer>(fbInit);
	}
}

//==============================================================================
void ReflectionProbe::onMoveUpdate(MoveComponent& move)
{
	// Update frustum components
	U count = 0;
	Error err = iterateComponentsOfType<FrustumComponent>(
		[&](FrustumComponent& frc) -> Error
	{
		Transform trf = m_cubeSides[count].m_localTrf;
		trf.setOrigin(move.getWorldTransform().getOrigin());

		frc.getFrustum().resetTransform(trf);
		frc.markTransformForUpdate();
		++count;

		return ErrorCode::NONE;
	});

	ANKI_ASSERT(count == 6);
	(void)err;

	// Update the spatial comp
	SpatialComponent& sp = getComponent<SpatialComponent>();
	sp.markForUpdate();
	sp.setSpatialOrigin(move.getWorldTransform().getOrigin());
}

} // end namespace anki
