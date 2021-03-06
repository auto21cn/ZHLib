// feng-buping.c  封不平

inherit NPC;

#include <ansi.h>
#include "jianzong.h"

mixed ask_me();

void create()
{
        set_name("封不平", ({ "feng buping", "feng" }) );
        set("nickname", YEL"狂风快剑"NOR);
        set("gender", "男性");
        set("class", "swordsman");
        set("title", "华山剑宗第十三代弟子");
        set("age", 45);
        set("long",
                "封不平是华山剑宗第一高手，满脸戾气一张黄焦焦的面皮。\n");
        set("attitude", "peaceful");
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 29);

        set("max_qi", 4700);
        set("max_jing", 2400);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 50);

        set("combat_exp", 1800000);
        set("shen_type", -1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.feilong" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("unarmed", 180);
        set_skill("sword", 220);
        set_skill("force", 180);
        set_skill("parry", 200);
        set_skill("strike", 180);
        set_skill("dodge", 190);
        set_skill("literate", 100);
        set_skill("huashan-sword", 220);
        set_skill("kuangfeng-jian", 220);
        set_skill("huashan-xinfa", 180);
        set_skill("huashan-quanfa", 180);
        set_skill("huashan-zhangfa", 180);
        set_skill("huashan-shenfa", 190);

        map_skill("sword", "kuangfeng-jian");
        map_skill("parry", "kuangfeng-jian");
        map_skill("force", "huashan-neigong");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("strike", "huashan-zhangfa");
        map_skill("dodge", "huashan-shenfa");

        set("inquiry", ([
                "绝招"   : (: ask_me :),
                "绝技"   : (: ask_me :),
                "天外飞龙" : (: ask_me :),
        ]));

        create_family("华山剑宗", 13, "弟子");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/huashan-sword/feilong"))
                return "你还不快去练习武功，以我剑宗的绝技重振剑宗风采？";

        if (me->query("family/family_name") != "华山派")
                return RANK_D->query_respect(me) + "不是我们华山派的人，请走吧！";

        if (me->query_skill("huashan-sword", 1) < 150)
                return "你的华山剑法还不到家，不要再给我丢脸了！";

        message_vision(HIY "$n" HIY "大喝一声，手中粘了一个石子"
                       "奋力击出，飞至半空突然化作粉末！\n"
                       HIY "$n" HIY "回头凝视着$N" HIY "道：这一"
                       "招没什么稀奇，就是要舍生忘死，运足内力！"
                        "虽然华山应该终于剑法，但是你也要好好修炼内力！\n" NOR,
                       me, this_object());
        tell_object(me, HIG "你学会了天外飞龙。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->set("can_perform/huashan-sword/feilong", 1);
        return 1;
}

void attempt_apprentice(object ob)
{
        command("say 老夫有要事在身，潜心练剑，你要拜师还是另请高明吧！");
	return;
}