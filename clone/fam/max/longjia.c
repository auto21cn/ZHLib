// longjia.c 子午龙甲丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "子午龙甲丹" NOR, ({ "longjia dan", "longjia", "dan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR "灵药中的神品，服用后不但可以医治任何内伤，而且\n"
                                "可平增一个甲子以上的功力。更有相传说此丹散发出\n"
                                "的异香可缭绕周围数十万方圆。\n" NOR);
                set("value", 100000);
                set("unit", "颗");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        log_file("static/using", sprintf("%s(%s) eat 子午龙甲丹 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        effect = 0;

        if (me->query("skybook/item/longjia"))
        {

        	message_vision(HIW "$N" HIW "一仰脖，吞下了一颗子午龙甲丹，只见$P"
                               HIW "浑身一颤，七窍都冒出白烟来。\n" NOR, me);

        	me->add("combat_exp", 10000 + random(5000));
        	me->add("potential", 1000);

        	mapsk = me->query_skill_mapped("force");
        	if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	me->improve_neili(50);
        	me->set("skybook/item/longjia", 1);        	

	}
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}