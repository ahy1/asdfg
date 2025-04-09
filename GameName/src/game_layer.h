#pragma once

#include "ortho_camera_controller.hpp"

#include <elm.hpp>

#include <glm/glm.hpp>

#include <memory>

struct game_layer : elm::layer
{
	game_layer(void);
	virtual ~game_layer(void) = default;

	virtual void on_attach(void) override;
	virtual void on_detach(void) override;
	virtual void on_update(elm::timestep ts) override;
	virtual void on_event(elm::event &e) override;
	virtual void on_imgui_render(void) override;

	bool on_resize(elm::window_resize_event &e);

	std::shared_ptr<elm::vertex_array> va;
	std::shared_ptr<elm::shader> shader;
	std::shared_ptr<elm::texture> texture;

	ortho_camera_controller camera_controller;
	std::shared_ptr<elm::uniform_buffer> camera_ub;

	glm::mat4 model_transform1;
	glm::mat4 model_transform2;
	std::shared_ptr<elm::uniform_buffer> model_ub;
};
