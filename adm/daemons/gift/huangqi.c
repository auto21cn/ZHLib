// huangqi.c 黄芪
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(YEL"黄芪"NOR, ({"huang qi", "huangqi"}));
    set_weight(40);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "这是产自昆仑山中的黄芪，食之据说能延年益寿。\n");
        set("unit", "株");
        set("value", 80);
    }
}

void init()
{
    add_action("do_eat", "eat");
}

int do_eat(string arg)
{
    object me = this_player();
    if (me->is_busy())
        return notify_fail("别急，慢慢吃，小心别噎着了。\n");
    if (!id(arg))
        return notify_fail("你要吃什么？\n");
    if(arg=="huang qi" || "huangqi") 
    {
        this_player()->set("eff_qi",this_player()->query("max_qi"));
        this_player()->set("qi",this_player()->query("max_qi"));
        message_vision(HIY"$N服下一株黄芪，只觉得全身暖洋洋的，精力大见旺盛。\n"NOR,me);
        me->start_busy(1);
        destruct(this_object());
    }
    return 1;
}


