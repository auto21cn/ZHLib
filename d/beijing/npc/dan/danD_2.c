#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW"雪参丹"NOR, ({"xueshen dan", "dan"}));
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
        int nl, mn;

        if (time() - me->query_temp("last_eat/dan(D)") < 180)
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        nl = (int)me->query("neili") + 300;
        mn = (int)me->query("max_neili") * 2;

        if (nl > mn)
        {
                write("你现在内力修为无需服用" + name() + "。\n");
                return 1;
        }
        if( me->is_busy() )
                return notify_fail("急什么，小心别噎着了。\n");

        me->set_temp("last_eat/dan(D)", time());

        message_vision(HIW "$N吃下一粒雪参丹，感到内力有所补充。\n" NOR, me);
        me->add("neili", 300);

        me->start_busy(3);
        destruct(this_object());
        return 1;
}

