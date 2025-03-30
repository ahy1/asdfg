#include "app.h"
#include <elm.h>
#include <elm/core/entypoiny.h>

namespace elm {

	application* application::create(struct application_command_line_args args)
	{
		return new game_name_app(
			{
				.name = "GameName"
			},
			args);
	}
}
