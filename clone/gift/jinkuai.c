// jinkuai.c ���

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(YEL "���" NOR, ({ "jin kuai", "jin", "kuai" }));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
                set("long", "һ���ƳγεĽ�顣\n");
                set("value", 500000);
		set("unit", "��");
	}
}

int query_autoload() { return 1; }
