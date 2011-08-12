#ifndef RENDERABLE_NODE_H
#define RENDERABLE_NODE_H

#include "SceneNode.h"
#include "Resources/MaterialCommon.h"


class Vao;
class Material;
class MaterialRuntime;


/// Abstract class that acts as an interface for the renderable objects of the
/// scene
class RenderableNode: public SceneNode
{
	public:
		RenderableNode(bool inheritParentTrfFlag, SceneNode* parent);

		/// Get VAO depending the rendering pass
		virtual const Vao& getVao(PassType p) const;

		/// Get vert ids number for rendering
		virtual uint getVertIdsNum() const = 0;

		/// Get the material resource
		virtual const Material& getMaterial() const = 0;

		/// Get the material runtime
		virtual MaterialRuntime& getMaterialRuntime() = 0;

		/// Const version of getMaterialRuntime
		virtual const MaterialRuntime& getMaterialRuntime() const = 0;
};


inline RenderableNode::RenderableNode(bool inheritParentTrfFlag,
	SceneNode* parent)
:	SceneNode(SNT_RENDERABLE, inheritParentTrfFlag, parent)
{}


#endif
