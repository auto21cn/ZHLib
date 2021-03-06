// duansh.c 段伤虹

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("段伤虹", ({ "duan shanghong", "shanghong" }));
        set("long",  "段氏皇族开山皇帝，在建立段家江山之前，本就是当时华夏武林绝顶高手。\n");
        set("gender", "男性");
        set("age", 65);
        set("attitude", "peaceful");
        set("shen_type", 1);
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

	set_skill("force", 640);		// 基本内功
	set_skill("kurong-changong", 640);	// 枯荣禅功
	set_skill("finger", 720);		// 基本指法
	set_skill("sun-finger", 720);		// 一阳指
	set_skill("dodge", 650);		// 基本躲闪
	set_skill("tiannan-step", 650);		// 天南步法
	set_skill("parry", 680);		// 基本招架

	map_skill("force", "kurong-changong");
	map_skill("dodge", "tiannan-step");
	map_skill("parry", "six-finger");
	map_skill("finger", "sun-finger");
	prepare_skill("finger","sun-finger");

        create_family("段氏皇族", 0, "高祖");

        setup();
	carry_object("/clone/misc/cloth")->wear();
}


