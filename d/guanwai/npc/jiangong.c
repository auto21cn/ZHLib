// jiangong 监工

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_job();
int  do_move(string arg);
int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("监工", ({ "jian gong", "jiangong" }));
        set("long", "这是一个监工，眼光不断闪烁，不知"
                    "道在打什么坏主意\n");
        set("gender", "男性");
        set("age", 38);
        set("no_get", 1);
        set_skill("unarmed", 100);

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);

        set("combat_exp", 500000);
        set("shen_type", 1);
        set("inquiry", ([
            "工作" : (: ask_job :),
            "搬石" : (: ask_job :),
            "job"  : (: ask_job :),
        ]));
        setup();

        set("chat_chance", 1);
        set("chat_msg", ({
                "监工喝道：快！快给我干！\n",
                "监工一扬鞭子，骂道：他奶奶的，你给我放老实点。\n",
                "监工打量着四周，不知道在打什么主意。 \n",
                "监工狠狠的抽了一个人几下，骂道：怎么把石头掉到地上了，你这笨蛋。\n",
        }) );
}

void init()
{
        add_action("do_move", "move");
}

string ask_buy()
{
        return "我这可有不少读书人必读的书哟!\n";
}

string ask_job()
{
	object *uob;
        object me;

        me = this_player();
        if (me->query_temp("job/move"))
                return "让你搬的石料你搬了没有？再胡闹我抽死你！";

        if (me->query("combat_exp") < 1500)
                return "你这点经验也来采石场混？随便一大哥看你不顺眼就把你放到了。";

        if (me->query("combat_exp") > 15000)
                return "大侠你也来搬石头？免了免了，我还是另找人吧！";

        if (me->query("qi") < 60)
                return "我看你上气不接下气了嘛，还是算了吧，我可不想闹出人命来。";

        if (me->query_str() < 25)
                return "我说你有多点力气，也来凑热闹？";

        uob = filter_array(users(), (: query_ip_name($1) == $(query_ip_name(me)) :));
	uob = filter_array(uob, (: objectp($1) && $1->query_temp("job/move") :));

	if (sizeof(uob) > 5)
	{
		me->start_busy(3);
		return "对不起，您这个IP做采石工作的ID太多了！";
	}

        me->set_temp("job/move", 1);
        return "好，你就去山上搬石料下来(move)，我这工资可不菲哦。";
}

int do_move(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙着呢，别着急。\n");

        if (! me->query_temp("job/move"))
                return notify_fail("你又没领活，瞎忙活啥？\n");

        me->set_temp("job/step", 1);
	me->start_busy((: working :), (: halt_working :));
        tell_object(me, "你开始工作。\n");
        return 1;
}

int working(object me)
{
        string msg;
        int finish;
        int b;

        if (! me->query_temp("job/step"))
                me->set_temp("job/step", 1);

        if (! living(me))
        {
                me->delete_temp("job/move");
                me->delete_temp("job/step");
                return 0;
        }

        finish = 0;
        switch (me->query_temp("job/step"))
        {
        case 1:
                me->receive_damage("qi", 3);
                msg = "$N快步的朝山上走去。";
                break;
        case 2:
                me->receive_damage("qi", 2);
                msg = "$N走到山腰，道：我是来搬石料的。";
                break;
        case 3:
                me->receive_damage("qi", 2);
                msg = "来往的工人扫了$N一眼，似乎没看到。一个爆破手道：嗨，那儿，去那儿搬。";
                break;
        case 4:
                me->receive_damage("qi", 8);
                msg = "$N赶到爆破的地方，选了一块正合适自己的石料，抗在肩头。";
                break;
        case 5:
        case 7:
        case 9:
                me->receive_damage("qi", 10);
                msg = "$N扛着石料，一步一步往山下挨。";
                break;
        case 6:
                me->receive_damage("qi", 12);
                msg = "$N喘了口气，掂了掂肩头的石料，继续前进。";
                break;
        case 8:
                me->receive_damage("qi", 15);
                msg = "$N觉得肩头的石料越来越重，只好换一下肩扛。";
                break;
        default:
                me->receive_damage("qi", 8);
                msg = "$N把石料扛到$n那里，把石料装上车子，总算松了口气。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                object ob;
                if (me->query_str() >= 30)
                        msg += "$n看了$N搬的石料，讶道：厉害"
                               "啊，这么大块石料也搬下来了！\n";
                else
                        msg += "$n看了$N搬的石料，道：行，干得"
                               "不赖！喏，这是你的工钱。\n";
                me->delete_temp("job/move");
                me->delete_temp("job/step");

                b = 7 + random(4);
                me->add("combat_exp", b);
                me->add("potential", (b + 2) / 3);
                me->improve_skill("unarmed", (b + 1) / 2);
                if (me->query("potential") > me->query_potential_limit())
                        me->set("potential", me->query_potential_limit());

                ob = new("/clone/money/coin");
                ob->set_amount(100 + (me->query_str() - 25) * 10);
                ob->move(this_object());
        }

        message_vision(msg, me, this_object());
        if (finish)
        {
                if (b > 0)
                {
                        tell_object(me, HIC "\n你获得了" +
                                    chinese_number(b) +
                                    "点经验和" +
                                    chinese_number((b + 2) / 3) +
                                    "点潜能。\n\n" NOR);
                }
                command("give coin to " + me->query("id"));
                command("drop coin");
                return 0;
        }

        me->add_temp("job/step", 1);
        return 1;
}

int halt_working(object me)
{
        if (me->query_temp("job/step") >= 4)
        {
                message_vision("$N把肩头的石料一仍，骂骂咧咧道："
                               "累死我了，真不是人干的活！\n", me);
        } else
        {
                message_vision("$N叹了口气，道：今天不干了！\n", me);
        }

        me->delete_temp("job/move");
        me->delete_temp("job/step");
        return 1;
}
