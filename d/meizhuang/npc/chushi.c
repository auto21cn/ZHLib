// chushi.c

inherit NPC;

string ask_me();

void create()
{
        set_name("厨师", ({ "chu shi", "chu" }));
        set("title", "梅庄");
        set("long",
                "梅庄的一名厨师，笑眯眯地看着你，看来很和善的样子。\n");
        set("gender", "男性");
        set("age", 34);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("max_qi", 200);
        set("max_jing", 50);
        set("neili", 0);
        set("max_neili", 0);
        set("jiali", 0);
        set("combat_exp", 500);
        set("shen",0);
        set("score", 0);
        set("no_get",1);
        set_skill("force", 10);
        set_skill("dodge", 10);
        set_skill("cuff", 10);
        set_skill("parry", 10);

        setup();
}
