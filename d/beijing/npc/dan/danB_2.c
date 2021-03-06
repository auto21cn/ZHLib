#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(YEL"大还丹"NOR, ({"dahuan dan", "dan"}));
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

        if (time() - me->query_temp("last_eat/dan(B)") < 10)
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["qi"] == my["max_qi"])
        {
                write("你现在体力充沛，无需服用" + name() + "。\n");
                return 1;
        }
        if( me->is_busy() )
                return notify_fail("急什么，小心别噎着了。\n");

        me->set_temp("last_eat/dan(B)", time());

        message_vision(YEL "$N吃下一粒大还丹，感到内息得到了比较大的调整。\n" NOR, me);
        me->receive_curing("qi", 200);
        me->receive_heal("qi", 200);

        me->start_busy(3);
        destruct(this_object());
        return 1;
}

