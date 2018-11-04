// wuming.c ������ɮ

inherit NPC;
inherit F_COAGENT;

void create()
{
	set_name("������ɮ", ({ "wuming laoseng", "wuming" }));
	set("long",
		"����һλ�뷢���׵���ɮ�����Ŵֲ���������"
                "������������ӵ�ɮ�ˡ�\n"
	);

	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 98);
	set("shen_type", 1);
	set("str", 37);
	set("int", 42);
	set("con", 41);
	set("dex", 36);
	set("max_qi", 7000);
	set("max_jing", 3500);
	set("neili", 8000);
	set("max_neili", 8000);
	set("jiali", 85);
	set("combat_exp", 3000000);

	set_skill("buddhism", 450);
	set_skill("literate", 300);

	set_skill("blade", 300);
	set_skill("claw", 300);
	set_skill("club", 300);
	set_skill("cuff", 300);
	set_skill("dodge", 300);
	set_skill("finger", 300);
	set_skill("force", 350);
	set_skill("hand", 300);
	set_skill("parry", 300);
	set_skill("staff", 300);
	set_skill("strike", 300);
	set_skill("sword", 300);
	set_skill("whip", 300);

	set_skill("banruo-zhang", 300);
	set_skill("cibei-dao", 300);
	set_skill("damo-jian", 300);
	set_skill("fengyun-shou", 300);
	set_skill("fumo-jian", 300);
	set_skill("hunyuan-yiqi", 300);
	set_skill("shaolin-xinfa", 300);
	set_skill("jingang-quan", 300);
	set_skill("longzhua-gong", 300);
	set_skill("luohan-quan", 300);
	set_skill("nianhua-zhi", 300);
	set_skill("pudu-zhang", 300);
	set_skill("qianye-shou", 300);
	set_skill("sanhua-zhang", 300);
	set_skill("riyue-bian", 300);
	set_skill("shaolin-shenfa", 300);
	set_skill("weituo-gun", 300);
	set_skill("wuchang-zhang", 300);
	set_skill("xiuluo-dao", 300);
	set_skill("yingzhua-gong", 300);
	set_skill("yijinjing", 350);
	set_skill("yizhi-chan", 300);
	set_skill("zui-gun", 300);

	map_skill("blade", "cibei-dao");
	map_skill("claw", "longzhua-gong");
	map_skill("club", "wuchang-zhang");
	map_skill("cuff", "luohan-quan");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");
	map_skill("force", "yijinjing");
	map_skill("hand", "fengyun-shou");
	map_skill("parry", "nianhua-zhi");
	map_skill("staff", "weituo-gun");
	map_skill("strike", "sanhua-zhang");
	map_skill("sword", "fumo-jian");
	map_skill("whip", "riyue-bian");

	prepare_skill("finger", "nianhua-zhi");
	prepare_skill("strike", "sanhua-zhang");

	create_family("������", 0, "����ɮ��");

	setup();

        carry_object("/d/shaolin/obj/cheng-cloth")->wear();

}