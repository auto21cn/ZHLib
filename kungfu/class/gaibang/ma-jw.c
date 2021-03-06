// gaibang npc code

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("马俱为", ({"ma juwei", "ma", "juwei"}));
        set("title", "丐帮七袋弟子");
        set("gender", "男性");
        set("age", 35);
        set("long", 
                "这是位武艺精强，却沉默寡言的丐帮七袋弟子。\n");
        set("attitude", "peaceful");
        set("rank",7);
        set("str", 25);
        set("int", 22);
        set("con", 25);
        set("dex", 30);

        set("qi", 800);
        set("max_qi", 800);
        set("jing", 350);
        set("max_jing", 350);
        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 32);
        
        set("combat_exp", 180000);
        
        set_skill("force", 120);
        set_skill("jiaohua-neigong", 120);
        set_skill("unarmed", 120);
        set_skill("changquan", 120);
        set_skill("dodge", 120);
        set_skill("feiyan-zoubi", 120);
        set_skill("parry", 120);
        set_skill("staff", 120);
        set_skill("begging", 60);

        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "changquan");
        map_skill("parry", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        
        create_family("丐帮", 19, "弟子");
        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(6);
        carry_object("/d/gaibang/obj/budai")->wear();
        
}

void attempt_apprentice(object ob)
{
        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="女性")
                        command ("say 师太是是出家人，怎么能在本帮做叫化子呢？");
                return;
        }

        if( ob->query("con") < 20 ) return;

        if( ob->query("family/family_name") != "丐帮" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say 本帮以忠义为先，可容不下你这种无信无义的家伙！\n");
                        return;
                }

                command("say 你拜我为师，可要做好吃苦的准备，好好做个丐帮弟子！");
                ob->set("rank", 1); 
                command("recruit " + ob->query("id"));
                ob->set("title", "丐帮一袋弟子");
        } 
        else
        {
                ob->set_temp("title", ob->query("title"));
                command("recruit " + ob->query("id"));
                ob->set("title", ob->query_temp("title"));
                ob->delete_temp("title");
        }
}

#include "/kungfu/class/gaibang/promote.h"

