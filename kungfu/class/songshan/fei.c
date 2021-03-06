#include <ansi.h>
#include "songshan.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_COAGENT;

void create()
{
        set_name("费彬", ({ "fei bing", "bing", "fei" }) );
        set("nickname", HIW "大嵩阳手" NOR);
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 45);
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 26);

        set("max_qi", 4500);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);
        set("shen_type", 1);
        set("combat_exp", 940000);

        set_skill("cuff", 200);
        set_skill("strike", 220);       
        set_skill("sword", 220);
        set_skill("force", 200);
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("songshan-sword", 220);
        set_skill("jiuqu-jian", 220);
        set_skill("songshan-xinfa", 200);
        set_skill("songyang-zhang", 200);
        set_skill("songshan-zhang", 200);
        set_skill("songshan-quan", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "songshan-xinfa");
        map_skill("sword", "jiuqu-jian");
        map_skill("parry", "jiuqu-jian");
        map_skill("strike", "songyang-zhang");
        map_skill("cuff", "songshan-quan");
        map_skill("dodge", "lingxu-bu");

        prepare_skill("strike", "songyang-zhang");
             
        create_family("嵩山派", 13, "护法");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.wan" :),
                (: perform_action, "strike.ying" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));
     
        set_temp("apply/attack", 60);
        set_temp("apply/damage", 60);
        set_temp("apply/unarmed_damage", 60);
        set_temp("apply/armor", 120);

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}


void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") < 30000)
        {
                command("say 我嵩山剑派乃是堂堂名门正派，对弟子要求严格。");
                command("say 你在这侠义与德行方面是否还做得不够？");
                return;
        }

	if ((int)ob->query("combat_exp") < 200000)
	{
		command("say 你现在经验尚浅，还是多在江湖上走走吧。");
		return;
	}

        if ((int)ob->query_skill("songshan-sword", 1) < 120)
	{	
		command("say 我嵩山剑派乃五岳剑派之一，最为重视剑法。");
		command("say 你的嵩山剑法还不够熟练，下去练练再来吧。");
        	return;
        }
   
        if ((int)ob->query_skill("songshan-xinfa", 1) < 100)
	{
		command("say 我嵩山剑派虽善用剑，但内功却是御剑之本。");
		command("say 你是否还应该在嵩山心法上多下点功夫？");
		return;
 	} 

	    command("haha");
        command("say 孺子可教，孺子可教。今日我就收下你吧。");
        command("say 你以后定要勤练武，多行善，扬我嵩山派派雄风。");
        command("recruit " + ob->query("id"));
}
 
void unconcious()
{
        die();
}



