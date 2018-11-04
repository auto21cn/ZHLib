// largewood.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "木材" NOR, ({ "large wood", "wood" }));
	set_weight(120000);
	if (clonep())
		set_default_object(__FILE__);
	else
        {
                set("value", 2000);
		set("unit", "根");
		set("long", "这是一根伐自长白山的上好的大木料。\n");
	}
	setup();
}

int fire(object me, object ob)
{
        return notify_fail("好家伙，这么大块木头你也要点啊？\n");
}
