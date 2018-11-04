// pantao.c 蟠桃
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
    set_name(HIW"蟠桃"NOR, ({"pan tao", "pantao"}));
    set_weight(40);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "这是产自昆仑山中的蟠桃，食之据说能延年益寿。\n");
        set("unit", "只");
        set("value", 80);
        set("food_remaining", 10);
        set("food_supply", 30);
    }
}

void init()
{
    add_action("do_eat", "eat");
}

int do_eat(string arg)
{
    if (!id(arg))
        return notify_fail("你要吃什么？\n");
    if(arg=="pan tao" || "pantao") 
    {
        this_player()->set_temp("nopoison", 1);
        tell_object(this_player(),
        HIG"你吃下一只蟠桃，只觉一股清香沁入心肺，顿时灵台一片空明，神意清爽！\n"NOR);
        destruct(this_object());
    }
    return 1;
}


