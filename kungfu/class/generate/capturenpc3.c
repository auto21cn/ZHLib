#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

void random_move();

void create()
{
        mapping my;

        ::create();
        set("gender", "男性" );
        set("age", 30 + random(30));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("scale", 150);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 80);
        set_temp("born_time", time());

        NPC_D->init_npc_skill(this_object(), 10 + random(2));

        // 初始化NPC的能力
        my = query_entire_dbase();
        my["max_qi"] = 2500;
        my["max_jing"] = 2500;
        my["max_neili"] = 4000;
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        my["neili"] = my["max_neili"] * 2;
}

int accept_fight(object ob)
{
        command("say 我可没兴趣陪你玩，快给我滚开。");
        return 0;
}

int accept_hit(object ob)
{
        message_vision(HIR "$N" HIR "脸色一变，闪过一道杀气。喝道：“好"
                       "一个" + RANK_D->query_rude(ob) + HIR "，来吧！"
                       "”\n" NOR, this_object());
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        if (! living(this_object()))
                return 1;

        return accept_hit(ob);
}

int accept_ansuan(object ob)
{
        return notify_fail("那人警惕性好高，你难以下手。\n");
}

int accept_touxi(object ob)
{
        return notify_fail("那人警惕性好高，你难以下手。\n");
}

void random_move()
{
        NPC_D->random_move(this_object());
}

void remove()
{
        if (! environment() || query_temp("die"))
        {
                ::remove();
                return;
        }

        if (! living(this_object()))
        {
                message_vision(WHT "只见一道黑影闪过，将昏迷不醒的$N"
                               WHT "架起，一个飞纵，消失得无影无踪。"
                               "\n" NOR, this_object());
                return;
        }

        message_vision(WHT "$N" WHT "谨慎地看了看四周，急急忙忙的走"
                       "了。\n" NOR, this_object());

        ::remove();
}

void die(object killer)
{
        object ob;
        int exp, pot, ww, sc;

        exp = random(200) + 100;
        pot = random(150) + 100;
        ww = random(15) + 15;
        sc = random(20) + 30;

        if ((objectp(ob = killer)
           || objectp(ob = query_last_damage_from()))
           && ob->query_temp("capture/" + this_object()->query("id")))
        {
                ob->add("combat_exp", exp);
                ob->add("potential", pot);
                ob->add("score", sc);
                ob->add("weiwang", ww);
                ob->delete_temp("capture/" + this_object()->query("id"));
                tell_object(ob, HIC "你为六大门派扫清了异己，获得了" + chinese_number(exp) +
                                "点经验、" + chinese_number(pot) + "点潜能、" + chinese_number(sc)
                                + "点江湖\n阅历以及" + chinese_number(ww) + "点江湖威望。\n" NOR);

                CHANNEL_D->do_channel(this_object(), "rumor", "听说"
                                      + ob->name(1) + "(" + ob->query("id") +
                                      ")在" + environment()->short() + "为六"
                                      "大门派击毙了" + name() + "。");
        }
        set_temp("die", 1);
        ::die(killer);
}

