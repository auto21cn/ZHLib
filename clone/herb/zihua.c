// zihua.c

#include "herb.h"

void create()
{
	set_name(MAG "�ϻ�" NOR, ({ "zihua", "herb_zihua" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 50);
        	set("base_weight", 20);
	}
	setup();
}
