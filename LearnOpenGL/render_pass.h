#pragma once
#include "entity.h"
#include "render_state.h"
#include "camera.h"

class RenderPass
{
public:
	RenderPass(std::shared_ptr<Entity> spEntity, std::shared_ptr<RenderState> spRenderState);
	~RenderPass();
	void Apply(std::shared_ptr<Camera> spCamera);
	std::shared_ptr<RenderState> GetRenderState()const;
private:
	std::shared_ptr<Entity> m_spEntity;
	std::shared_ptr<RenderState> m_spRenderState;
};

