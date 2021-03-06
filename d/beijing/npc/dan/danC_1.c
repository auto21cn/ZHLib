#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW"小云丹"NOR, ({"xiaoyun dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int jl, mj;

        if (time() - me->query_temp("last_eat/dan(C)") < 180)
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        jl = (int)me->query("jingli") + 100;
        mj = (int)me->query("max_jingli") * 2;

        if (jl > mj)
        {
                write("你现在精力修为无需服用" + name() + "。\n");
                return 1;
        }
        if( me->is_busy() )
                return notify_fail("急什么，小心别噎着了。\n");

        me->set_temp("last_eat/dan(C)", time());

        message_vision(HIW "$N吃下一粒小云丹，精神随之一震，精力有所提高。\n" NOR, me);
        me->add("jingli", 100);

        me->start_busy(3);
        destruct(this_object());
        return 1;
}

