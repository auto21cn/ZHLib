// zhanglao.c 长老

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("长老", ({ "zhang lao", "zhang", "lao" }));
        set("long",  "日月神教开山鼻祖方腊手下第一贴身侍卫，无人知晓其真实姓名。\n");
        set("gender", "男性");
        set("age", 145);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 32);
        set("int", 33);
        set("con", 32);
        set("dex", 31);
        
        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 300);
        set("combat_exp", 10000000);
        set("score", 10000000);

    set_skill("force", 720);
    set_skill("riyue-xinfa", 700);
    set_skill("riyue-guanghua", 720);
    set_skill("sword", 700);
    set_skill("riyue-jian", 690);
    set_skill("pixie-jian", 700);
    set_skill("dodge", 600);
    set_skill("piaomiao-shenfa", 600);
    set_skill("parry",690);
    set_skill("cuff", 690);
    set_skill("xuwu-piaomiao", 690);
    set_skill("hand", 690);
    set_skill("huanmo-longtianwu", 690);
    set_skill("literate", 120);

    map_skill("force", "riyue-guanghua");
    map_skill("sword", "pixie-jian");
    map_skill("dodge", "pixie-jian");
    map_skill("parry", "pixie-jian");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("hand", "huanmo-longtianwu");

    prepare_skill("cuff", "xuwu-piaomiao");
    prepare_skill("hand", "huanmo-longtianwu");

    create_family("日月神教", 0, "护教长老");

    setup();

    carry_object("/d/fuzhou/obj/xiuhua")->wield();
    carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
    carry_object("/d/heimuya/obj/yuxiao");
}