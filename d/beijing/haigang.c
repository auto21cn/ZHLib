#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "东海之滨");
        set("long", @LONG
这里就是大海之滨，浪花拍打着礁石，发出阵阵响声，海面上一群群海
鸥『欧欧..』地叫着，不时有鱼儿跃出海面，溅起层层的浪花。边上有艘大
船(chuan)， 船上坐着几个渔夫打扮的人，乘船可渡过大海到达海的另一端。
西面一直走就是燕京了，东面是一望无际的大海。极目眺望不禁让人心胸开
扩，神舒意畅，的确是一个好居处。
LONG );
        set("exits", ([
                "west" : __DIR__"road10",
                "north" : "/d/tulong/tulong/haian",
        ]));
        set("item_desc", ([
                "chuan" : "一艘大帆船，造得很结实，看来可以出远海的。\n",
        ]));
        set("objects", ([
                "/d/shenlong/npc/chuanfu" :1,
        ]));
        set("max_room", 3);
        set("outdoors", "beijing");
        set("navigate",1);
        set("opposite","/d/shenlong/haitan");
        setup();
}
void init()
{
        object dao, room, ren, ding;
        object me = this_player();
        room = load_object("/d/tulong/tulong/huichang");
        ding = present("chang jinpeng", room);

        if (objectp(ding)) 
        dao = present("tulong blade", ding);

        if (objectp(dao))
        {
                room = load_object("/d/tulong/tulong/daobian");
                ren = present("bai guishou",room);
                message_vision(HIC "你看见海滨上停泊满了海船，所有的海船全部标记着天赢教的标记。\n"NOR, me);
                message_vision(CYN "白龟寿对你说道：我天鹰教得到屠龙宝刀，这位武林同道可愿意参加扬刀立威大会？\n"NOR, me);
                shout(HIR "\n【倚天屠龙】" NOR+WHT "白龟寿仰天一声长笑。" NOR );
                shout(HIR "\n【倚天屠龙】" NOR+WHT "白龟寿：我天鹰教得到屠龙宝刀，今在王盘山岛举行扬刀立威大会。\n" NOR );
                remove_call_out("mes");
                call_out("mes",3,this_player());
                this_player()->set_temp("to_wang",1);
                add_action("do_accept","accept");
        }
}

void mes(object me)
{
        message_vision(HIR "你愿意参加(accept)王盘山岛扬刀立威大会吗？\n"NOR, me);
}

int do_accept()
{
        object me = this_player();
        if (me->query_temp("to_wang")) 
        {
                tell_object(me, HIR "你决定去参加扬刀立威大会。\n" NOR);
                remove_call_out("moveto");
                call_out("moveto",10,me);
        }
        return 1;
}

int moveto(object me)
{
        me->move("/d/tulong/tulong/boat");
        message_vision(HIC "\n$N坐上了天鹰教的大船，听到舵子手喊道：“开船了！”，大船慢慢的向大海驶进。\n"NOR, me);
        remove_call_out("arrive1");
        call_out("arrive1",10,me);
        return 1;
}

int arrive1(object me)
{
        message_vision(HIB "\n天鹰教的大船在大海上慢慢的漂着......$N不禁感到睡意朦胧。\n"NOR, me);
        remove_call_out("arrive2");
        call_out("arrive2",10,me);
        return 1;
}

int arrive2(object me)
{
        message_vision(HIY "\n$N突然听到一声惊喝：“到了，下船吧”！$N顿时提起精神，跟着天鹰教教众下了船。\n"NOR, me);
        me->move("/d/tulong/tulong/daobian");
        tell_object(me, HIR "\n你突然想到：最好先砸了其他人的船(break boat)，让他们无路可逃。\n" NOR);
        return 1;
}


