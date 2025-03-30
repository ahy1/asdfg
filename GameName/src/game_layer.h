#pragma once

#include <elm.h>

struct game_layer : elm::layer
{
	game_layer(void);
	virtual ~game_layer(void) = default;

	virtual void on_attach(void) override;
	virtual void on_detach(void) override;
	virtual void on_update(elm::timestep ts) override;
	virtual void on_event(elm::event &e) override;
	virtual void on_imgui_render(void) override;
};
