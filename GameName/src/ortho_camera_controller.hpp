#pragma once

#include <elm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <stdint.h>

struct ortho_camera_controller {
	ortho_camera_controller(float aspect_ratio):
		aspect_ratio(aspect_ratio),
		position {0.0f, 0.0f, 0.0f},
		zoom(1.0f),
		translation_speed(1.0f),
		camera(-aspect_ratio, aspect_ratio, -1.0f, 1.0f)
	{
	}

private:
	float aspect_ratio;
	glm::vec3 position;
	float zoom;
	float translation_speed;
	elm::orthographic_camera camera;

public:
	void resize_viewport(uint32_t width, uint32_t height)
	{
		this->aspect_ratio = (float)width/(float)height;
		this->camera.set_projection(
			-this->aspect_ratio*this->zoom,
			this->aspect_ratio*this->zoom,
			-this->zoom,
			this->zoom);
	}

	void on_event(elm::event &e)
	{
		elm::event_dispatcher d(e);
		d.dispatch<elm::mouse_scrolled_event>(std::bind(&ortho_camera_controller::on_mouse_scrolled, this, std::placeholders::_1));
		//d.dispatch<elm::key_pressed_event>(std::bind(&ortho_camera_controller::on_key_pressed, this, std::placeholders::_1));
	}

	bool on_mouse_scrolled(elm::mouse_scrolled_event &e)
	{
		this->zoom -=e.get_offset_y()*this->zoom/10;
		this->zoom = std::max(this->zoom, 0.1f);

		this->camera.set_projection(
			-this->aspect_ratio*this->zoom,
			this->aspect_ratio*this->zoom,
			-this->zoom,
			this->zoom);
		return false;
	}

	bool on_key_pressed(elm::key_pressed_event &e)
	{
		auto code = e.get_key_code();

		switch (code) {
		case elm::key::H:
		case elm::key::Left:
			this->position.x -= 0.1;
			break;
		case elm::key::J:
		case elm::key::Down:
			this->position.y -= 0.1;
			break;
		case elm::key::K:
		case elm::key::Up:
			this->position.y += 0.1;
			break;
		case elm::key::L:
		case elm::key::Right:
			this->position.x += 0.1;
			break;
		default:;
		}

		this->camera.set_view_matrix(glm::translate(glm::mat4(1.0f), -position));

		return false;
	}

	void on_update(elm::timestep ts)
	{
		if (elm::input::any_key_pressed<elm::key::H, elm::key::Left>()) {
			ELM_ASSERT(false);
		}
	}


	const elm::camera &get_camera()
	{
		return camera;
	}

};