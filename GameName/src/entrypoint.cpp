#include "app.h"

#include <elm.hpp>
#include <elm/core/entypoiny.hpp>

namespace elm {

	application* application::create(struct application_command_line_args args)
	{
		struct elm::application_specification spec;
		spec.name = "asdfg";
		spec.vsync = true;
		return new game_name_app(spec, args);
	}
}
