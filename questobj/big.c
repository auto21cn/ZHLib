// jin-nang by zzfy
#include <ansi.h>
inherit ITEM;
void create()
{
        string *order=({HIB"蓝色锦囊"NOR, HIR"红色锦囊"NOR, HIY"金色锦囊"NOR,HIW"白色锦囊"NOR,HIM"紫色锦囊"NOR,HIC"青色锦囊"NOR});
        set_name((order[random(6)]) , ({ "jin-nang", "jin","nang"}) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
                HIY "一个用金丝编成的锦囊，似乎可以(open)打开。\n"NOR);
                set("unit","个");
                set("value", 0);
        }
        }
void init()
{
        add_action("open_gongbao","open");
}
int open_gongbao(string arg)
{
        int exp;
        int pot;
        int sscore;
        if ( arg == "jin-nang"){
        exp = 2500 + random(2500);
        pot = 350 + random(350);
        sscore = 35 + random(25);
        message_vision(HIM"$N擦了擦额头的汗水，迫不及待地用颤抖的双手打开了锦囊。\n"NOR,this_player());
        this_player()->add("combat_exp",exp);
        this_player()->add("potential",pot); 
        this_player()->add("score",sscore);
        tell_object(this_player(),HIR"哇！！！！你被奖励了：\n\n" +
        chinese_number(exp) + "点实战经验。\n"+
        chinese_number(pot) + "点潜能。\n" +
        chinese_number(sscore) + "点综合评价。请继续努力！！！\n"NOR);
        destruct(this_object());
        return 1;
     }
     return 0; 
}
