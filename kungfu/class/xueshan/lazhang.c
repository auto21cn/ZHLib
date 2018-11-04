// /kungfu/class/xueshan/lazhang.c  拉章活佛 
// by secret 
//modified by rama@hx
 
inherit NPC; 
inherit F_MASTER; 

#include <ansi.h>
#include "xueshan.h"

string ask_for_join();
string ask_me();

void create() 
{ 
        set_name("拉章活佛", ({ "lazhang huofo", "huofo", "lazhang" })); 
        set("long",@LONG 
    他是本寺藏经阁的主管，曾经远渡天竺求经，历时三十年。五十二岁时来住本寺，
在辩经大会上独占鳌头。他看上去面黄肌瘦，身形瘦高。);
LONG 
        ); 
        set("title",HIY"活佛"NOR); 
        set("gender", "男性"); 
        set("age", 50); 
        set("attitude", "peaceful"); 
        set("shen_type", -1); 
        set("str", 30); 
        set("int", 30); 
        set("con", 30); 
        set("dex", 30);
        set("max_qi", 2900); 
        set("max_jing", 1400); 
        set("neili", 3000); 
        set("max_neili", 3000); 
        set("jiali", 40); 
        set("combat_exp", 470000); 
        set("score", 40000); 
 
        set_skill("lamaism", 150);
        set_skill("literate", 120);
        set_skill("force", 150);
        set_skill("mizong-neigong", 100);
        set_skill("dodge", 120);
        set_skill("shenkong-xing", 110);
        set_skill("hand", 140); 
        set_skill("dashou-yin", 140); 
        set_skill("parry", 120); 
        set_skill("sword", 100); 
        set_skill("mingwang-jian", 100); 
 
        map_skill("force", "mizong-neigong"); 
        map_skill("dodge", "shenkong-xing"); 
        map_skill("hand",  "dashou-yin"); 
        map_skill("parry", "mingwang-jian"); 
        map_skill("sword", "mingwang-jian"); 
 
        prepare_skill("hand",  "dashou-yin");
        set("book_count",3);

        create_family("雪山寺", 3, "活佛"); 
        set("class", "bonze"); 

        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "藏经" : (: ask_me :),
        ]));

        setup(); 
 
        carry_object("/d/xueshan/obj/y-jiasha")->wear(); 
        carry_object("/d/xueshan/obj/sengmao")->wear(); 
 
        add_money("silver", 20);
} 
 
 
void attempt_apprentice(object ob) 
{
        if (! permit_recruit(ob))
                return;
 
        if ((string)ob->query("gender") != "男性")
        {
                command("say 修习密宗内功需要纯阳之体。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }
 
        if ((string)ob->query("class") != "bonze")
        {
                command("say 我佛门的清规戒律甚多。");
                ob->set_temp("pending/join_bonze", 1);
                command("say 施主若真心皈依我佛，就请跪下(kneel)受戒。\n");
                return;
        }
 
        if ((int)ob->query_skill("lamaism", 1) < 50)
        {
                command("say 入我雪山寺，修习密宗心法是首要的。" +
                        "\n这位" + RANK_D->query_respect(ob) +
                        "是否还应该多多钻研本门的心法？");

                return;
        }
 
        command("smile");
        command("nod");
        command("say 你就随我学习佛法吧！");
        command("recruit " + ob->query("id"));
        ob->set("title",HIY"大喇嘛"NOR);
}

void init()
{
        add_action("do_kneel", "kneel");

}

string ask_for_join()
{
        object me;

        me = this_player();

        if ((string)me->query("class")=="bonze")
                return "阿弥陀佛！你我同是出家人，何故跟贫僧开这等玩笑？\n";

        if ((string)me->query("gender") != "男性")
                return "施主若真心向佛，真是可喜可贺，可惜本寺只收男徒。\n";

        me->set_temp("pending/join_bonze", 1);
        return "阿弥陀佛！善哉！善哉！施主若真心皈依我佛，请"
               "跪下(kneel)受戒。\n";
}

int do_kneel()
{
        object me = this_player();

        if( !me->query_temp("pending/join_bonze") )
                return notify_fail("你跪了半点，结果没人理你。\n");

        message_vision("$N双手合十，恭恭敬敬地跪了下来。\n\n"
                       "$n伸出手掌，在$N头顶轻轻地摩挲了几下，将"
                       "$N的头发尽数剃去。\n\n", me, this_object());

        command("smile");

        me->set("class", "bonze");

        return 1;
}
string ask_me()
{
        mapping fam;
        object ob;

        if (!(fam = this_player()->query("family")) || fam["family_name"] !="雪山寺"
        && fam["family_name"] !="血刀门")
                return RANK_D->query_respect(this_player()) +
                "与本寺素无来往，不知此话从何谈起？";
        if (query("book_count") < 1)
                return "你来晚了，本寺的经书不在此处。";
        add("book_count", -1);
        ob = new("/d/xueshan/obj/fojing3.c");
        ob->move(this_player());
        return "好吧，这本经书你拿回去好好钻研。";
}


