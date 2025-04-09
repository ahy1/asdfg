#pragma once

#include <elm.hpp>

struct game_name_app : elm::application
{
	game_name_app(const struct elm::application_specification &spec,
		struct elm::application_command_line_args args);
};
