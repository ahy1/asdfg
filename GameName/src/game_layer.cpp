#include "game_layer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

game_layer::game_layer(void)
	: layer("GameLayer"),
	camera_controller(1.0f)
{
}

struct vertex_s {
	float x, y, z;
	float u, v;
	float r, g, b, a;
};

void game_layer::on_attach(void)
{
	struct vertex_s vertices[] = {
		{
			-0.5f, -0.5f, 0.0f,
			0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f},
		{
			0.5f, -0.5, 0.0f,
			4.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f},
		{
			0.5f, 0.5f, 0.0f,
			4.0f, 4.0f,
			0.0f, 0.0f, 1.0f, 1.0f},
		{
			-0.5f, 0.5f, 0.0f,
			0.0f, 4.0f,
			1.0f, 1.0f, 1.0f, 1.0f}
	};
	uint32_t indices[] ={
		0u, 1u, 2u,
		0u, 2u, 3u
	};

	this->va = elm::vertex_array::create();

	auto vb = elm::vertex_buffer::create(vertices, sizeof vertices);
	elm::vertex_buffer_layout layout = {
		{elm::shader_data_type::FLOAT3, "a_position"},
		{elm::shader_data_type::FLOAT2, "a_uv"},
		{elm::shader_data_type::FLOAT4, "a_color"}
	};
	vb->set_layout(&layout);

	this->va->add_vertex_buffer(vb);
	
	auto ib = elm::index_buffer::create(indices, sizeof indices / sizeof indices[0]);
	this->va->set_index_buffer(ib);

	elm::texture_specification spec;
	//spec.format = elm::image_format::RGB8;
	//this->texture = elm::texture_2d::create("content/textures/IMG_2137.JPG", spec);

	spec.format = elm::image_format::RGBA8;
	spec.width = 8;
	spec.height = 8;
	spec.mag_filter = elm::texture_filter::NEAREST;
	spec.wrap_s = elm::texture_wrap::REPEAT;
	spec.wrap_t = elm::texture_wrap::REPEAT;
	this->texture = elm::texture_2d::create(spec);
	uint32_t texture_data[8*8] = {0};
	for (int iy=0; iy<8; ++iy) {
		for (int ix =0; ix<8; ++ix) {
			texture_data[ix+8*iy] = (iy+ix)%2 ? UINT32_MAX : 255u << 24;
		}
	}
	this->texture->set_data(texture_data, sizeof texture_data);


	shader = elm::shader::create("./content/shaders/shader.glsl");

	auto window = elm::application::get()->get_window();
	this->camera_controller.resize_viewport(window->get_width(), window->get_height());
	this->camera_ub = elm::uniform_buffer::create(sizeof (glm::mat4), 0);

	this->model_transform1 = glm::translate(glm::mat4(1.0f), {0.0f, 0.0f, 0.0f});
	this->model_transform2 = glm::translate(glm::mat4(1.0f), {0.5f, 0.2f, 0.0f});
	this->model_ub = elm::uniform_buffer::create(sizeof model_transform1, 1);
}

void game_layer::on_detach(void)
{
}

void game_layer::on_update(elm::timestep ts)
{
	static float then_deg = 0.0f;

	this->camera_controller.on_update(ts);

	then_deg += 180.0f * ts.get_seconds();
	this->model_transform1 = glm::rotate(glm::mat4(1.0f), glm::radians(then_deg), {0.0f, 1.0f, 0.0f});
	this->model_transform2 = glm::translate(glm::mat4(1.0f), {elm::time::get_seconds()/25.0f, 0.2f, 0.0f});

	/*auto cam_trans = glm::rotate(glm::mat4(1.0f), glm::radians(then_deg), {0.0f, 0.0f, 1.0f})
		* glm::translate(glm::mat4(1.0f), {0.5f, 0.0f, 0.0f});
	this->view = glm::inverse(cam_trans);
	this->view_projection = projection * view;*/

	elm::render_command::set_clear_color({0.1f, 0.2f, 0.3f, 1.0f});
	elm::render_command::clear();

	this->shader->bind();
	this->camera_ub->bind();
	this->model_ub->bind();

	this->camera_ub->set_data(&this->camera_controller.get_camera().get_view_projection(), sizeof(glm::mat4));

	this->texture->bind(0u);
	this->va->bind();

	this->model_ub->set_data(&this->model_transform1, sizeof this->model_transform1);
	elm::render_command::draw_indexed(this->va);

	this->model_ub->set_data(&this->model_transform2, sizeof this->model_transform2);
	elm::render_command::draw_indexed(this->va);

}

void game_layer::on_event(elm::event &e)
{
	this->camera_controller.on_event(e);

	elm::event_dispatcher d(e);
	d.dispatch<elm::window_resize_event>(std::bind(&game_layer::on_resize, this, std::placeholders::_1));
}

void game_layer::on_imgui_render(void)
{
	auto t = elm::application::get()->get_telemetry();
	ImGui::Begin("Telemetry");
	ImGui::Text("FPS: %.2f", t->get_fps());
	ImGui::End();

/*	ImGui::Begin("Camera");
	
	bool invalidate_projection = false;
	if (ImGui::DragFloat("Left", &this->projection_left, 0.1f)) invalidate_projection = true;
	if (ImGui::DragFloat("Right", &this->projection_right, 0.1f)) invalidate_projection = true;
	if (ImGui::DragFloat("Buttom", &this->projection_bottom, 0.1f)) invalidate_projection = true;
	if (ImGui::DragFloat("Top", &this->projection_top, 0.1f)) invalidate_projection = true;
	if (invalidate_projection) {
		this->projection = glm::ortho(
			this->projection_left,
			this->projection_right*size.x/size.y,
			this->projection_bottom,
			this->projection_top);
	}

	ImGui::End();*/
}

bool game_layer::on_resize(elm::window_resize_event &e)
{
	this->camera_controller.resize_viewport(e.get_width(), e.get_height());
	return false;
}
