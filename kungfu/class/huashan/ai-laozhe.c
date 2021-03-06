// ai-laozhe.c

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "qizong.h"

void create()
{
	set_name("矮老者", ({ "ai laozhe", "ai" }));
	set("title", HIG"华山第十二代长老"NOR);
	set("long", "他就是华山的长老矮老者。一张严肃"
                    "威严的脸，望而生畏。\n");
	set("gender", "男性");
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 31);
	set("int", 35);
	set("con", 31);
	set("dex", 32);
	set("age", 66);

	set("qi", 4800);
	set("max_qi", 4800);
	set("jing", 2400);
	set("max_jing", 2400);
	set("neili", 5200);
	set("max_neili", 5200);
	set("jiali", 70);

	set("combat_exp", 1900000);
	set("score", 70000);

	set_skill("cuff", 190);
	set_skill("force", 210);
	set_skill("blade", 180);
	set_skill("sword", 220);
	set_skill("dodge", 190);
	set_skill("parry", 200);
	set_skill("strike", 190);
	set_skill("zixia-shengong", 210);
	set_skill("huashan-xinfa", 210);
	set_skill("poyu-quan", 190);
	set_skill("fanliangyi-dao", 180);
	set_skill("huashan-sword", 220);
	set_skill("hunyuan-zhang", 190);
        set_skill("feiyan-huixiang",190);
	set_skill("literate", 140);

	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");

	map_skill("cuff", "poyu-quan");
	map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "fanliangyi-dao");
	map_skill("blade", "fanliangyi-dao");
	map_skill("sword", "huashan-sword");
	map_skill("strike", "hunyuan-zhang");

	create_family("华山派", 12, "弟子");

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "blade.sanshen" :),
		(: exert_function, "recover" :),
	}) );

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob) )
                return;

        if ((int)ob->query_skill("zixia-shengong", 1) < 120)
	{
		command("say 我看你的紫霞神功还没学到家吧，本派有本的"
                        "紫霞秘籍，你可曾研读？");
		return;
	}

        if ((int)ob->query_skill("sword", 1) < 150)
	{
                command("say 我看你的剑法还没学到家吧，基本剑法都不打"
                        "好基础，谈什么上乘剑术。");
		return;
	}

        if ((int)ob->query_skill("huashan-sword", 1) < 150)
	{
                command("say 我看你的华山剑法还没学到家吧，练好了本门"
                        "剑术你再来。");
		return;
	}

        if ((int)ob->query("shen") < 20000)
	{
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严"  
                        "，在德行方面，你还做得不够啊！");
		return;
	}

	command("say 好吧，我就收下你了，不要丢我们华山派的脸。");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "fighter")
		ob->set("class", "fighter");
}
