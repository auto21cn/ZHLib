
#include <ansi.h>
 
inherit ITEM;

int is_head() { return 1; }

void create()
{
        set_name(HIY "金卡兑奖劵" NOR, ({ "gold card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "凭这张金卡可以在武庙的浪翻云那里兑换十点奖励点数。\n"NOR);			
                set("unit", "张");
                set("value", 10);
                set("gft_pt",10);
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
		
