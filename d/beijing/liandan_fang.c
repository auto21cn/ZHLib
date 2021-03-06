#include <ansi.h>
inherit ROOM;

int do_liandan(string arg);

void create()
{       set("short", HIY"炼丹房"NOR);
        set("long", @LONG
这是姚春的炼丹房，四周堆放着炼丹的药材，一个漆黑的炼丹炉(lu)耸立
在中央，房中的药味经久不散，并且总有一股散不尽的淡青色烟雾，长时间的
丹药炼制已经让这个房间充满了神秘的色彩。
LONG );
        set("no_fight", 1);
        set("item_desc", ([
                "lu" : "一个深黑色的大铁丹炉，顶部不停地升起丝丝青烟。",
        ]));

        set("exits", ([
                "south" : __DIR__"liandan_yaoshi",
        ]));
        set("objects",([
                "/d/beijing/npc/jpl": 1,
                "/d/beijing/npc/jpl2": 1,
]));

        setup();
}
void init()
{
        add_action("do_liandan","liandan");
}
int do_liandan(string arg)
{
        int time;
        object me = this_player();
        time = 10 + random(10);

        if ( (int)me->query_temp("liandan") < 1)
                return notify_fail("炼丹之地，切勿滋扰。\n");

        if ( (int)me->query_temp("liandan") < 2)
                return notify_fail("原料都没有，炼什么啊？\n");

        if ( (int)me->query_temp("liandan") == 3)
                return notify_fail("丹药炼制中，请勿分心。\n");

        if ( (int)me->query_temp("liandan") == 4)
                return notify_fail("炼制成功，快去复命吧。\n");

        if ( (int)me->query("jing") < 50)
                return notify_fail("你已经筋疲力尽了。\n");

        message_vision(HIY "$N" HIY "将原料药材一一放进炉中，盘"
                       "腿坐下，闭目静待。\n"NOR,me); 
        me->set_temp("liandan", 3);
        call_out("liandan", time, me);
        me->start_busy( time );
        return 1;
}
int liandan(object me)
{
        object ob;   object ob1;  object ob2;  object ob3;
        object ob4;  object ob5;  object ob6;  object ob7;
        object ob8;  object ob9;  object ob10; object ob11;
        object ob12; object ob13; object ob14; object ob15;
        object ob16; object ob17; object ob18; object ob19;
        object ob20; object ob21; object ob22; object ob23;
        object ob24; object ob25; object ob26; object ob27;
        object ob28; object ob29; object ob30; object ob31;
        object ob32; object ob33; object ob34; object ob35;
        int a;
        if (random(2) == 1) 
        {
                me->receive_damage("jing",50 + random(30));
                me->receive_damage("qi",50 + random(30));
                me->set_temp("liandan", 1);
                message_vision(HIR "正当$N" HIR "昏昏然的时候，一阵刺鼻"
                               "的气味从炉中冲出，$N" HIR "急忙开炉取药，"
                               "结果被弄得个灰头土脸。\n"NOR,me);
        }
   else if (random(10) == 1) 
        {
                me->receive_damage("jing",50+random(30));
                me->receive_damage("qi",50+random(30));
                me->set_temp("liandan", 1);
                message_vision(HIC "炉顶青烟渐渐转淡，丹药气味渐浓，$N"
                               HIC "高兴地把炼制而成的丹丸取出。\n" NOR,me);
                me->set_temp("liandan", 4);
                a = random(11);
                ob=new("/d/beijing/npc/dan/danS_1");
                ob1=new("/d/beijing/npc/dan/danS_2");
                ob2=new("/d/beijing/npc/dan/danS_3");
                ob3=new("/d/beijing/npc/dan/danS_4");
                ob4=new("/d/beijing/npc/dan/danS_5");
                ob5=new("/d/beijing/npc/dan/danM_9");
                ob6=new("/d/beijing/npc/dan/danM_8");
                ob7=new("/d/beijing/npc/dan/danM_7");
                ob8=new("/d/beijing/npc/dan/danM_5");
                ob9=new("/d/beijing/npc/dan/danM_4");
                ob10=new("/d/beijing/npc/dan/danM_3");
                     if (a == 1) ob->move(me);
                else if (a == 2) ob1->move(me);
                else if (a == 3) ob2->move(me);
                else if (a == 4) ob3->move(me);
                else if (a == 5) ob4->move(me);
                else if (a == 6) ob5->move(me);
                else if (a == 7) ob6->move(me);
                else if (a == 8) ob7->move(me);
                else if (a == 9) ob8->move(me);
                else if (a == 10) ob9->move(me);
                else ob10->move(me);
        }
     else 
        {
                me->receive_damage("jing",50+random(50));
                me->receive_damage("qi",50+random(50));
                message_vision(HIC "炉顶青烟渐渐转淡，丹药气味渐浓，$N"
                               HIC "高兴地把炼制而成的丹丸取出。\n"NOR,me);
                me->set_temp("liandan", 4);  
                a = random(25); 
                ob11=new("/d/beijing/npc/dan/danM_1");
                ob12=new("/d/beijing/npc/dan/danM_2");
                ob13=new("/d/beijing/npc/dan/danM_6");
                ob14=new("/d/beijing/npc/dan/danA_1");
                ob15=new("/d/beijing/npc/dan/danA_2");
                ob16=new("/d/beijing/npc/dan/danA_3");
                ob17=new("/d/beijing/npc/dan/danA_4");
                ob18=new("/d/beijing/npc/dan/danA_5");
                ob19=new("/d/beijing/npc/dan/danB_1");
                ob20=new("/d/beijing/npc/dan/danB_2");
                ob21=new("/d/beijing/npc/dan/danB_3");
                ob22=new("/d/beijing/npc/dan/danB_4");
                ob23=new("/d/beijing/npc/dan/danB_5");
                ob24=new("/d/beijing/npc/dan/danB_6");
                ob25=new("/d/beijing/npc/dan/danC_1");
                ob26=new("/d/beijing/npc/dan/danC_2");
                ob27=new("/d/beijing/npc/dan/danC_3");
                ob28=new("/d/beijing/npc/dan/danC_4");
                ob29=new("/d/beijing/npc/dan/danC_5");
                ob30=new("/d/beijing/npc/dan/danD_1");
                ob31=new("/d/beijing/npc/dan/danD_2");
                ob32=new("/d/beijing/npc/dan/danD_3");
                ob33=new("/d/beijing/npc/dan/danD_4");
                ob34=new("/d/beijing/npc/dan/danD_5");
                ob35=new("/d/beijing/npc/dan/danD_6");
                     if (a == 1) ob11->move(me);
                else if (a == 2) ob12->move(me);
                else if (a == 3) ob13->move(me);
                else if (a == 4) ob14->move(me);
                else if (a == 5) ob15->move(me);
                else if (a == 6) ob16->move(me);
                else if (a == 7) ob17->move(me);
                else if (a == 8) ob18->move(me);
                else if (a == 9) ob19->move(me);
                else if (a == 10) ob20->move(me);
                else if (a == 11) ob21->move(me);
                else if (a == 12) ob22->move(me);
                else if (a == 13) ob23->move(me);
                else if (a == 14) ob24->move(me);
                else if (a == 15) ob25->move(me);
                else if (a == 16) ob26->move(me);
                else if (a == 17) ob27->move(me);
                else if (a == 18) ob28->move(me);
                else if (a == 19) ob29->move(me);
                else if (a == 20) ob30->move(me);
                else if (a == 21) ob31->move(me);
                else if (a == 22) ob32->move(me);
                else if (a == 23) ob33->move(me);
                else if (a == 24) ob34->move(me);
                else ob35->move(me);
        }
        return 1;
}


