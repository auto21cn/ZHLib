// yangdingtian.c 阳顶天

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
    set_name("阳顶天", ({ "yang dingtian", "yang", "dingtian" }));
    set("long", "他就是明教前教主阳顶天，统领天下十万教众，抗元扶汉，威震天下。\n");
    set("title",HIG "明教" HIM " 前教主" NOR);
    set("gender", "男性");
    set("age", 60);
    set("shen_type",1);
    set("attitude", "peaceful");
    set("class", "fighter");

    set("str", 33);
    set("int", 36);
    set("con", 38);
    set("dex", 33);

    set("qi", 9999);
    set("max_qi", 9999);
    set("jing", 9999);
    set("max_jing", 9999);
    set("neili", 9999);
    set("max_neili", 9999);
    set("jiali", 300);
    set("combat_exp", 10000000);
    set("score", 10000000);
    
    set_skill("force", 680);
    set_skill("cuff", 680);
    set_skill("dodge", 680);
    set_skill("parry", 680);
    set_skill("sword", 680);
    set_skill("strike",680);
    set_skill("literate", 680);

    set_skill("shenghuo-xuanming", 680);
    set_skill("qiankun-danuoyi", 680);
    set_skill("lingxu-bu", 680);
    set_skill("shenghuo-quan", 680);
    set_skill("liehuo-jian", 680);
    set_skill("shenghuo-ling", 680);
    set_skill("guangming-zhang", 680);
    set_skill("qishang-quan", 680);

    map_skill("force", "shenghuo-xuanming");
    map_skill("dodge", "lingxu-bu");
    map_skill("cuff", "qishang-quan");
    map_skill("sword","shenghuo-ling");
    map_skill("parry","qiankun-danuoyi");
    map_skill("strike","guangming-zhang");

    prepare_skill("cuff", "qishang-quan");

    create_family("明教", 0, "前教主");
    setup();
}