// mtyadi.c 崖底

inherit ROOM;

int do_climb(string arg);
void create()
{
        set("short", "崖底");
        set("long", @TEXT
你的面前是一座比直的山峰，高若千丈，峰顶在云雾中隐约可
见，山峰光秃秃的，更无置手足处，山峰垂下一条铁链(lian)，仔
细一看，铁链并无锈迹，似乎有人用它爬上爬下.
TEXT );
        set("outdoors", "xiakedao");
        set("exits", ([
            "north" : __DIR__"mtroad",
        ]));
        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("do_climb","climb");
}

int do_climb(string arg)
{
        int n;
        n = this_player()->query_skill("dodge",1);
        if ( !arg || arg != "lian")
        {
            write("你要爬什么呀? \n");
            return 1;
        }
message_vision("$N深吸了一口气，慢慢沿着铁链的向上爬。\n", this_player());
        if(n >80){
message_vision("$N爬了半天，终于爬了上去，$N高兴的不禁跳了起来。\n", this_player());
            this_player()->move(__DIR__"mtdating");
        }
        else
        {
message_vision("$N爬了一会，一不小心摔了下来。\n", this_player());
            this_player()->receive_damage("qi",50);
            this_player()->receive_wound("qi",50);
        }
        return 1;
}
