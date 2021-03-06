// Room: /d/gaibang/undertre.c
// Date: Haa 96/03/22

inherit ROOM;

void create()
{
	set("short", "树洞下");
	set("long", @LONG
这是老槐树底部，四周光线昏暗，人影晃晃，似乎有几个黑暗的洞口
在你身边，通向四面八方。  一位老乞丐大咧咧地坐在正中的地上。不经
意中你发现墙壁上画着幅粗糙的路线草图（map）。
LONG );
	set("exits", ([
		"up"   : __DIR__"inhole",
		"down" : __DIR__"chuchang",
		"1"    : __DIR__"xcandao1",
		"2"    : __DIR__"zlandao1",
		"3"    : __DIR__"slandao1",
		"4"    : __DIR__"xxandao1",
		"5"    : __DIR__"wdandao1",
		"6"    : __DIR__"hsandao1",
		"7"    : __DIR__"bjandao1",
		"8"    : __DIR__"qzandao1",
		"9"    : __DIR__"xsandao1",
		"a"    : __DIR__"dlandao1",
		"b"    : __DIR__"fzandao1",
	]));
	set("item_desc",([ "map" : 
		"出口一：通往小村。\n" +
		"出口二：通往竹林。\n" +
		"出口三：通往少林。\n" +
		"出口四：通往星宿。\n" +
		"出口五：通往武当。\n" +
		"出口六: 通往华山。\n" +
		"出口七：通往北京。\n" +
		"出口八：通往嘉兴。\n" +
		"出口九：通往雪山。\n" +
		"出口Ａ：通往大理。\n" +
		"出口Ｂ：通往福州。\n"
	]));
	set("objects",([
		CLASS_D("gaibang") + "/liang" : 1,
	]));
	setup();
	"/clone/board/gaibang_r"->foo();
}

/* int valid_leave(object me, string dir)^M
{
	object guarder;

	if (objectp(guarder = present("liang zhanglao", this_object())) &&
	    living(guarder) && dir != "up")
		return guarder->permit_pass(me, dir);

	return ::valid_leave(me, dir);
}*/



void init()
{
    mapping myfam;
    myfam = (mapping)this_player()->query("family");
    if ((!myfam||myfam["family_name"]!="丐帮"))
    {
        if(objectp(present("liang zhanglao", environment(this_player())))
        && living(present("liang zhanglao", environment(this_player()))))
        call_out("greeting", 1);
    }
}



void greeting()
{
        object me,ob;
        me = this_player();
    ob = present("liang zhanglao", environment(me));
        if( !ob || environment(ob) != environment() ) return;

        message_vision("\n梁长老看到$N闯进来，大喝一声：你不是丐帮弟子，给我滚出去！\n"
      "说完一脚踢在$N的屁股上，$N一下子向门外飞去。\n",me);
        me->move("/d/gaibang/inhole");
        message("vision", me->name() +"突然从小门里被人踢了出来，浑身都是泥，脸也肿了起来。\n",
         environment(me), ({me}));
}

