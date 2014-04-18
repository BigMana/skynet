// include skynet.h first for malloc hook
#include "skynet.h"

#include <lua.h>
#include <lauxlib.h>

#include "malloc_hook.h"

static int
ltotal(lua_State *L) {
	size_t t = malloc_used_memory();
	lua_pushunsigned(L, t);

	return 1;
}

static int
lblock(lua_State *L) {
	size_t t = malloc_memory_block();
	lua_pushunsigned(L, t);

	return 1;
}

static int
ldumpinfo(lua_State *L) {
	memory_info_dump();

	return 0;
}

static int
ldump(lua_State *L) {
	dump_c_mem();

	return 0;
}

int
luaopen_memory(lua_State *L) {
	luaL_checkversion(L);

	luaL_Reg l[] = {
		{ "total", ltotal },
		{ "block", lblock },
		{ "dumpinfo", ldumpinfo },
		{ "dump", ldump },
		{ NULL, NULL },
	};

	luaL_newlib(L,l);

	return 1;
}
