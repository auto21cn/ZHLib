// pang.c
#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_QUESTER;

void create()
{
        set_name("胖头陀", ({ "pang toutuo", "pang" ,"toutuo"}));
        set("title", "神龙教左护法");
        set("nickname","辽东胖尊者");
        set("long", "这头陀身材奇高，而且瘦得出奇；脸上皮包骨头、双\n"
                    "目深陷，当真便如僵尸一般。\n" );
        set("gender", "男性");
        set("age", 44);

        set("str", 32);
        set("int", 28);
        set("con", 31);
        set("dex", 25);

        set("max_qi", 4700);
        set("qi", 4700);
        set("max_jing", 2400);
        set("jing", 2400);
        set("neili", 4800); 
        set("max_neili", 4800);
        set("jiali", 60);

        set("combat_exp", 750000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 160);
        set_skill("hand", 160);
        set_skill("strike", 160);
        set_skill("staff", 160);
        set_skill("parry", 160);
        set_skill("dodge", 160);
        set_skill("yixingbu", 160);
        set_skill("shenlong-bashi", 160);
        set_skill("huagu-mianzhang", 160);
        set_skill("shenlong-xinfa", 160);
        set_skill("shedao-qigong", 160);

        map_skill("staff", "shedao-qigong");
        map_skill("force", "shenlong-xinfa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("dodge", "yixingbu");
        prepare_skill("hand", "shenlong-bashi");
        prepare_skill("strike", "huagu-mianzhang");

        create_family("神龙教", 0, "闲散教众");

        set("inquiry", ([
                "神龙教" : "一般人是入不了我神龙教的(join shenlongjiao).\n",
                "入教"   : "一般人是入不了我神龙教的(join shenlongjiao).\n",
                "洪安通" : "教主脾气不好,要讨他欢心才好。\n",
                "教主"   : "教主脾气不好,要讨他欢心才好。\n",
                "口号"   : "万年不老！永享仙福！寿与天齐！文武仁圣！",
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        command("say 慢来！慢来！你想拜师去找教主吧。");
}

