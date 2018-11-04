//ROOM xuanbing.c

inherit ROOM;



void init();
int do_climb(object me);



        
void create()
{
        set("short","玄冰室");
        set("long",@LONG
这是修练内功的地方。 屋子正中有一块千年玄冰(ice)，冰上冒出丝
丝寒气， 屋里因此寒气逼人，你不由得打了一个寒颤。
LONG
        );
        
        set("exits", ([
                "east" : __DIR__"changl13",
        ]));

        set("item_desc", ([
            "ice" : "这是一块采自天山之巅的千年玄冰,据说在那上面打坐事半功倍.\n你可以试着爬(climb)上去.\n",
        ]));

        set("coor/x",-130);
        set("coor/y",130);
        set("coor/z",70);
        setup();
}


void init()
{
        add_action("do_climb", "climb");
        
}

int do_climb(object me)
{      
        me=this_player();
        if(!me->query_skill("bahuang-gong", 1)||(int)me->query_skill("bahuang-gong", 1) < 10)
           {
                write("你的八荒六合唯我独尊功修为不够，抵御不了奇寒！\n");                   
                message_vision("$N费劲地爬上了玄冰,结果给冻得惨惨的，赶紧爬了下来。\n",me);
                return 1; 
          }
        
        message_vision("$N费劲地爬上了玄冰,现在打坐可以练功了。\n",me);
        
        me->set_temp("ice", 1);

        me->move("d/lingjiu/ice");
        return 1;
}

        
        


