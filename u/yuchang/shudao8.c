#include <ansi.h>
inherit ROOM;

#define _DEBUG_1_
#ifdef _DEBUG_1_
#else
#endif

// 多长时间打开一次？一天(24小时=86400秒)
#define PERIOD_TIME 86400

// 每次打开多长时间？(10分钟)
#define OPEN_TIME   600

// misu 2006-1-16 19:30
// add some function to open the enterance randomly
// 为了简单起见，直接将时间的控制放在了这个文件里面；在实际运行的时候，
// 为了准确，可以用一个adm/daemons/下的文件来保存每次计算和打开的时间，
// 在mud重起的时候自动的载入这个daemon

// 最后一次是什么时候计算打开时间的？
int last_init_time;
// 最后一次打开的时间
int last_open_time;

void open()
{
    // 打开链接
    set("exits/down", "/u/yuchang/dongkou.c");

    CHANNEL_D->do_channel(this_object(), "rumor", "传说成都洪水泛滥，麒麟窟重现人间了！");
    remove_call_out("open");
    call_out("close", OPEN_TIME);
}

void close()
{
    delete("exits/down");
    CHANNEL_D->do_channel(this_object(), "rumor", "成都洪水减退，麒麟窟再次淹没在洪水之中！");
    remove_call_out("open");
    remove_call_out("close");
}

void recalc()
{
    last_open_time = time() + random(PERIOD_TIME); // 在接下来的24个小时里，随机的打开一次
    last_init_time = time() + PERIOD_TIME;

    remove_call_out("open");
    remove_call_out("close");
    remove_call_out("recalc");
    call_out("open", last_open_time-time());
    call_out("recalc", PERIOD_TIME);
}

int do_open(string arg)
{
    object who = this_player();
    string id = who->query("id");

    if( id == "yuchang" )
    {
        last_open_time = time() + 10; // 在接下来的10秒之后打开
        last_init_time = time() + PERIOD_TIME;

        remove_call_out("open");
        remove_call_out("close");
        call_out("open", last_open_time-time());
        call_out("recalc", PERIOD_TIME);

        return 1;
    }

    return 0;
}

int do_close(string arg)
{
    object who = this_player();
    string id = who->query("id");

    if( id == "yuchang" )
    {
        close();

        return 1;
    }

    return 0;
}

void init()
{
#ifdef _DEBUG_1_
    add_action("do_open", "do_open");
    add_action("do_close", "do_close");
#endif

    // 还没有计算打开的时间
    if( !last_init_time )
    {
        last_open_time = time() + random(PERIOD_TIME) + 10; // 在接下来的24个小时里，随机的打开一次
                                                            // +10 保证在10秒之后才打开
        last_init_time = time() + PERIOD_TIME;

        remove_call_out("open");
        remove_call_out("close");
        remove_call_out("recalc");

        call_out("open", last_open_time-time());
        call_out("recalc", PERIOD_TIME);
    }

    // 已经超过一天没有更新了
    if( last_init_time < time() )
    {
        last_open_time = time() + random(PERIOD_TIME); // 在接下来的24个小时里，随机的打开一次
        last_init_time = time() + PERIOD_TIME;

        remove_call_out("open");
        remove_call_out("close");
        remove_call_out("recalc");
        call_out("open", last_open_time-time());
        call_out("recalc", PERIOD_TIME);
    }
}

void create()
{
        set("short", "峭壁");
        set("long", @LONG
自古有云：蜀道难，难于上青天，呜呼。无怪大诗人李白
如此写。路到了这里真可谓惊险无比，一边是滔滔的江水，一
边是如刀切般的峭壁。你正爬在一个很危险的峭壁上，你还是
快走吧，别一不小心掉了下去。
LONG);
        set("exits", ([
                "eastdown" : __DIR__"shudao7",
                "westup" : __DIR__"shudao9",
        ]));

        // 注意，设置这个参数，这个房间不会被更新
        set("no_clean_up", 1);

        set("outdoors", "chengdu");
        setup();
        //replace_program(ROOM);
}


