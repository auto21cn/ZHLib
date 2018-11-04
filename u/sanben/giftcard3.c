
#include <ansi.h>
 
inherit ITEM;

int is_head() { return 1; }

void create()
{
        set_name(HIG "普通兑奖劵" NOR, ({ "common card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "凭这张普通卡可以在武庙的浪翻云那里兑换一点奖励点数。\n"NOR);			
                set("unit", "张");
                set("value", 10);
                set("gft_pt", 1);
                set("weight", 1);
                set("material", "paper");		  		  
             }	         
        setup();
}

void init()
{
     remove_call_out("dest");
     call_out("dest", 600);     

}

void dest()
{
     tell_room(environment(), HIR"奖劵突然不见了。\n"NOR);
     destruct(this_object());

}


		
