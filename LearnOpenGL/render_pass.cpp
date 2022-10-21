#include "render_pass.h"
RenderPass::RenderPass(std::shared_ptr<Entity> spEntity, std::shared_ptr<RenderState> spRenderState) :
	m_spEntity(spEntity), m_spRenderState(spRenderState)
{

}

RenderPass::~RenderPass()
{

}

void RenderPass::Apply(std::shared_ptr<Camera> spCamera)
{
	m_spRenderState->Use();
	m_spRenderState->ApplyState();
	m_spRenderState->ApplyTransform(spCamera);
	m_spRenderState->ApplyLights(spCamera);
	m_spRenderState->ApplyPreState();
	m_spEntity->DrawSelfAndChild();
	m_spRenderState->ApplyPostState();
}

std::shared_ptr<RenderState> RenderPass::GetRenderState() const
{
	return m_spRenderState;
}
