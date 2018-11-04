#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIC"修罗"NOR+HIR"无常"NOR+HIY"丹"NOR, ({"xiuluo dan", "dan"}));
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

        if (time() - me->query_temp("last_eat/dan(C)") < 240)
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        if( me->is_busy() )
                return notify_fail("急什么，小心别噎着了。\n");

        me->set_temp("last_eat/dan(C)", time());

        message_vision(HIR "$N吃下一粒修罗无常丹，精力得到了完全的调整。\n" NOR, me);
        me->set("jingli",me->query("max_jingli"));

        me->start_busy(3);
        destruct(this_object());
        return 1;
}

