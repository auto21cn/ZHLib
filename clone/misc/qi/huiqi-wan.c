
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "回气丸" NOR, ({"huiqi wan", "huiqi", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("long", HIR "一颗黑色的药丸。恢复1000点气血和最大气血。\n" NOR);
                set("value", 30000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if (time() - me->query_temp("last_eat") < 5)
        {
                write("你刚吃过药，药力还没有完全吸收。\n");
                return 1;
        }
        me->set_temp("last_eat", time());

        message_vision(HIR "$N" HIR "吃下一颗回气丸，只觉舒泰之极！\n" NOR, me);

        if (me->query("max_qi") - me->query("eff_qi") <= 1000)
        {
                 me->set("eff_qi", me->query("max_qi"));
                 if (me->query("max_qi") - me->query("qi") <= 1000)
                        me->set("qi", me->query("max_qi"));
                 
                 else 
                        me->add("qi", 1000);  
        }


        else 
        {
                me->add("eff_qi", 1000);
                me->add("qi", 1000);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
