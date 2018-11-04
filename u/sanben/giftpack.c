//小礼包


#include <ansi.h>
inherit ITEM;


void create()
{
        set_name(NOR + HIG "小礼包" NOR, ({ "giftpack" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这是中华英雄巫师组发放的小礼包，"
                            "你可以打开它(open giftpack)。\n");                
                set("no_put", "这样东西不能离开你。\n");
                set("no_sell", "这样东西不能离开你。\n");
        }
        setup();
}

void init()
{
     add_action("do_open","open");    
}

int do_open( string arg )
{
   string ob;
   object gift;
   string *ob_list = ({
                "/clone/fam/pill/renshen1",
                "/clone/fam/pill/lingzhi1",
                "/clone/fam/pill/xuelian1",
                "/clone/fam/pill/linghui1",  
                "/clone/fam/pill/puti4",                  
                "/clone/fam/pill/full1",               
                "/clone/fam/pill/neili2",
                "/clone/fam/gift/perwan",                
                "/clone/money/cash",
                "/clone/money/cash",
                "/clone/money/cash",
                "/clone/money/cash",
                "/clone/money/cash",              
    });  

    if ( !arg || arg != "giftpack")
    return notify_fail("你要打开什么？\n");

    ob = ob_list[random(sizeof(ob_list))];
    if ( ! ob || ob == 0 ) ob = "/clone/money/cash";
    gift = new(ob);
    gift->move(this_player());
    tell_object(this_player(), HIY"恭喜你获得的礼物是"NOR + 
                               gift->name() + "。\n"NOR);   
    destruct(this_object());   
    return 1;

}

