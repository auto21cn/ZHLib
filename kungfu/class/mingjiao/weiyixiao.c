// WeiYiXiao.c
// pal 1997.05.10

#include <ansi.h>
#include "fawang.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

void create()
{
	set_name("韦一笑", ({"wei yixiao", "wei", "yixiao",}));
	set("long",
		"他长得活象是一只青翼大蝙蝠。\n"
		"他的脸色灰扑扑的。\n"
	);

	set("title",HIG "明教" HIC "青翼蝠王" NOR);
	set("level",9);
	set("gender", "男性");
	set("attitude", "peaceful");

	set("age", 48);
	set("shen_type", 1);

	set("str", 28);
	set("int", 27);
	set("con", 33);
	set("dex", 38);

	set("max_qi", 4500);
	set("max_jing", 2200);
	set("neili", 5500);
	set("max_neili", 5500);
	set("jiali", 100);

	set("combat_exp", 1800000);

	set_skill("force", 180);
	set_skill("dodge", 180);
	set_skill("parry", 180);
	set_skill("sword", 180);
	set_skill("cuff", 180);
	set_skill("strike", 220);
	set_skill("literate", 110);

	set_skill("shenghuo-xinfa", 180);
	set_skill("qingfu-shenfa", 220);
	set_skill("shenghuo-quan", 180);
	set_skill("guangming-zhang", 180);
	set_skill("liehuo-jian", 180);
	set_skill("hanbing-mianzhang", 220);

	map_skill("force", "shenghuo-xinfa");
	map_skill("dodge", "qingfu-shenfa");
	map_skill("strike", "hanbing-mianzhang");
	map_skill("sword", "liehuo-jian");
	map_skill("parry", "hanbing-mianzhang");
	map_skill("cuff", "shenghuo-quan");

	prepare_skill("strike","hanbing-mianzhang");

	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: command("perform xixueqingfu") :),
	}) );
	create_family("明教", 35, "护法法王");
        set("inherit_title",HIG"明教"NOR"光明散人"NOR);

	setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}
