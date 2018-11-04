// 金蜜散(jinmi san)
// by April 2001.11.10

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW "金蜜散" NOR, ({"jinmi san", "jinmi", "san"}));
    set_weight(25);
    if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "包");
		set("value", 8000);
		set("only_do_effect", 1); 
	}

    setup();
}

int do_effect(object me)
{
	if (!me->query_condition("yf_zhen_poison"))
	{
		tell_object(me,"你并没有中蜂毒啊！\n");
		return 1;
	}

        me->clear_condition("yf_zhen_poison");
	message_vision(HIY "$N服下了一包金蜜散。苦中带甜，甜中带苦，一股香气沁人心脾。\n"NOR,me);
	tell_object(me,HIY "你感觉体内的蜂毒已慢慢消去。\n" NOR, me);

	destruct(this_object());
	return 1;
}
