// wangyuyan 2002.4.29
#include <ansi.h>
inherit ITEM;
void create()
{
    set_name( HIG "兵器谱" NOR, ({ "bingqipu" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "记载各种兵器的一本奇书，不过你觉得它的封面也太厚了，厚的不象话。\n");
          }
    setup();
}
/*
void init()
{

if(environment()==this_player())
add_action("do_open","open");
}
int do_open(string arg)
{
object gold;
if(arg != "bingqipu" && arg != "兵器谱") return 0;
if(query("opened"))
return notify_fail("你用小刀“兹”的一声划开封面，但里面是空的！\n");
gold = new("/questobj/obj/paper");
gold->set_amount(1);
gold->move(this_player());
set("opened",1);
return notify_fail("你用小刀“兹”的一声划开封面，从里面拿出一张纸！\n");
}
*/