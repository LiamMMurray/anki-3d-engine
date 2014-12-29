// Copyright (C) 2014, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_SCENE_CAMERA_H
#define ANKI_SCENE_CAMERA_H

#include "anki/scene/SceneNode.h"
#include "anki/scene/SpatialComponent.h"
#include "anki/scene/MoveComponent.h"
#include "anki/scene/FrustumComponent.h"

namespace anki {

/// @addtogroup Scene
/// @{

/// Camera SceneNode interface class
class Camera: public SceneNode
{
	friend class MoveFeedbackComponent;
	friend class FrustumFeedbackComponent;

public:
	/// @note Don't EVER change the order
	enum class Type: U8
	{
		PERSPECTIVE,
		ORTHOGRAPHIC,
		COUNT
	};

	Camera(SceneGraph* scene, Type type);

	virtual ~Camera();

	ANKI_USE_RESULT Error create(const CString& name, Frustum* frustum);

	Type getCameraType() const
	{
		return m_type;
	}

	void lookAtPoint(const Vec3& point);

private:
	Type m_type;
	
	/// Called when moved.
	void onMoveComponentUpdate(MoveComponent& move);

	/// Called when something changed in the frustum.
	void onFrustumComponentUpdate(FrustumComponent& fr);
};

/// Perspective camera
class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(SceneGraph* scene);

	~PerspectiveCamera();

	ANKI_USE_RESULT Error create(const CString& name)
	{
		return Camera::create(name, &m_frustum);
	}

	void setAll(F32 fovX, F32 fovY, F32 near, F32 far);

private:
	PerspectiveFrustum m_frustum;
};

/// Orthographic camera
class OrthographicCamera: public Camera
{
public:
	OrthographicCamera(SceneGraph* scene);

	~OrthographicCamera();

	ANKI_USE_RESULT Error create(const CString& name)
	{
		return Camera::create(name, &m_frustum);
	}

private:
	OrthographicFrustum m_frustum;
};
/// @}

} // end namespace anki

#endif
