// moyao.c

#include "herb.h"

void create()
{
	set_name(WHT "没药" NOR, ({ "moyao", "herb_moyao" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "这是中药药材。\n");
		set("base_unit", "根");
		set("base_value", 300);
        	set("base_weight", 50);
	}
	setup();
}
