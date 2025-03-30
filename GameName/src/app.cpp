#include "app.h"
#include "game_layer.h"

game_name_app::game_name_app(const struct elm::application_specification &spec, struct elm::application_command_line_args args)
	: elm::application(spec, args)
{
	push_layer(new game_layer());
}
