local scene = getSceneGraph()
local events = getEventManager()
local rot
local node
local inst
local lcomp

node = scene:newModelNode("roomroom-materialnone0", "assets/roomroom-material.ankimdl")
trf = Transform.new()
trf:setOrigin(Vec4.new(0, 0, 0, 0))
rot = Mat3x4.new()
rot:setAll(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0)
trf:setRotation(rot)
trf:setScale(1)
node:getSceneNodeBase():getMoveComponent():setLocalTransform(trf)

node = scene:newModelNode("columnroom-materialnone1", "assets/columnroom-material.ankimdl")
trf = Transform.new()
trf:setOrigin(Vec4.new(4.90187, 5.43441, -4.52919, 0))
rot = Mat3x4.new()
rot:setAll(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0)
trf:setRotation(rot)
trf:setScale(1)
node:getSceneNodeBase():getMoveComponent():setLocalTransform(trf)

node = scene:newModelNode("sectorportal-materialnone2", "assets/sectorportal-material.ankimdl")
trf = Transform.new()
trf:setOrigin(Vec4.new(0, 0, 0, 0))
rot = Mat3x4.new()
rot:setAll(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0)
trf:setRotation(rot)
trf:setScale(1.16458)
node:getSceneNodeBase():getMoveComponent():setLocalTransform(trf)

node = scene:newModelNode("columnroom-materialnone3", "assets/columnroom-material.ankimdl")
trf = Transform.new()
trf:setOrigin(Vec4.new(-4.59369, 5.43441, -4.49454, 0))
rot = Mat3x4.new()
rot:setAll(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0)
trf:setRotation(rot)
trf:setScale(1)
node:getSceneNodeBase():getMoveComponent():setLocalTransform(trf)

node = scene:newModelNode("columnroom-materialnone4", "assets/columnroom-material.ankimdl")
trf = Transform.new()
trf:setOrigin(Vec4.new(-4.61101, 5.43441, 4.79029, 0))
rot = Mat3x4.new()
rot:setAll(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0)
trf:setRotation(rot)
trf:setScale(1)
node:getSceneNodeBase():getMoveComponent():setLocalTransform(trf)

node = scene:newModelNode("columnroom-materialnone5", "assets/columnroom-material.ankimdl")
trf = Transform.new()
trf:setOrigin(Vec4.new(4.95098, 5.43441, 4.79029, 0))
rot = Mat3x4.new()
rot:setAll(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0)
trf:setRotation(rot)
trf:setScale(1)
node:getSceneNodeBase():getMoveComponent():setLocalTransform(trf)

node = scene:newPointLightNode("Point")
lcomp = node:getSceneNodeBase():getLightComponent()
lcomp:setDiffuseColor(Vec4.new(10, 10, 10, 1))
lcomp:setRadius(12.77)
trf = Transform.new()
trf:setOrigin(Vec4.new(0.0680842, 9.57987, 0.0302386, 0))
rot = Mat3x4.new()
rot:setAll(1, 0, 0, 0, 0, 4.63287e-05, 1, 0, 0, -1, 4.63287e-05, 0)
trf:setRotation(rot)
trf:setScale(1)
node:getSceneNodeBase():getMoveComponent():setLocalTransform(trf)
lcomp:setShadowEnabled(1)

node = scene:newPerspectiveCameraNode("Camera")
scene:setActiveCameraNode(node:getSceneNodeBase())
frustumc = node:getSceneNodeBase():getFrustumComponent()
frustumc:setPerspective(0.1, 100, 1.5708, 1.0 / getMainRenderer():getAspectRatio() * 1.5708)
trf = Transform.new()
trf:setOrigin(Vec4.new(-0.0971127, 3.80237, 5.98675, 0))
rot = Mat3x4.new()
rot:setAll(1, 0, 0, 0, 0, 1, -4.63724e-05, 0, 0, 4.63724e-05, 1, 0)
trf:setRotation(rot)
trf:setScale(1)
node:getSceneNodeBase():getMoveComponent():setLocalTransform(trf)
