inherit ROOM;

void create()
{
        set("short", "中央广场");
        set("long", @LONG
这里是城市的正中心，一个很宽阔的广场，铺着青石地面。一些游手好
闲的人在这里溜溜达达，经常有艺人在这里表演。中央有一棵大榕树，盘根
错节，据传已有千年的树龄，是这座城市的历史见证。树干底部有一个很大
的树洞 (dong)。 你可以看到北边有来自各地的行人来来往往，南面人声鼎
沸，一派繁华景象，东边不时地传来朗朗的读书声，西边则见不到几个行人，
一片肃静。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "city");
        set("item_desc", ([
                "dong" : "这是一个黑不溜湫的大洞，里面不知道有些什么古怪。\n",
        ]));

        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "south" : __DIR__"nandajie1",
                "west" : __DIR__"xidajie1",
//            "up" : "/u/jedi/214room",
                "north" : __DIR__"beidajie1",
        ]));

        set("objects", ([
                "/d/city/npc/jpl2": 1,
                __DIR__"npc/liapo" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
        return 0;

        if( arg=="dong" ) 
        {
                if (me->is_busy() )
                {
                        return notify_fail("你的动作还没有完成，不能移动。\n");
                        return 1; 
                }

                message("vision",
                        me->name() + "一弯腰往洞里走了进去。\n",
                        environment(me), ({me}) );
                me->move("/d/gaibang/inhole");
                message("vision",
                        me->name() + "从洞里走了进来。\n",
                        environment(me), ({me}) );
                return 1;
        }
}       

