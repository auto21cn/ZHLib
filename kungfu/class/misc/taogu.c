// taogu.c 桃谷

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("桃谷", ({ "tao gu", "tao", "gu" }));
        set("long",  "他就是桃花岛的隐世高手桃谷老人，据说是桃谷六仙的师祖。\n");
        set("gender", "男性");
        set("age", 66);
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

        set_skill("force", 670);             // 基本内功
        set_skill("bibo-shengong", 670);     // 碧波神功
        set_skill("luoying-xinfa", 670);     // 落英心法
        set_skill("hand",600);              // 基本手法
        set_skill("finger", 670);            // 基本指法
        set_skill("tanzhi-shentong", 670);   // 弹指神通
        set_skill("unarmed", 620);           // 基本拳脚
        set_skill("strike", 620);            // 基本拳脚
        set_skill("luoying-shenzhang", 620); // 落英神剑掌
        set_skill("xuanfeng-leg", 620);      // 旋风扫叶腿
        set_skill("dodge", 670);             // 基本躲闪
        set_skill("anying-fuxiang", 670);    // 暗影浮香
        set_skill("parry", 670);             // 基本招架
        set_skill("sword", 660);             // 基本剑法
	set_skill("throwing", 670);	     // 基本暗器
        set_skill("luoying-shenjian", 660);  // 落英神剑
        set_skill("luoying-shenfa",660);
        set_skill("yuxiao-jian", 660);       // 玉箫剑法
        set_skill("lanhua-shou", 670);       // 兰花拂穴手
        set_skill("qimen-wuxing", 620);      // 奇门五行
        set_skill("count", 620);             // 阴阳八卦
        set_skill("literate", 660);          // 读书识字
        set_skill("chuixiao-jifa", 600);     // 吹箫技法
        set_skill("bihai-chaosheng", 600);   // 碧海潮生
        set_skill("taohua-yuan", 660);       // 桃花怨
        set_skill("medical", 600);           // 基本医术
        set_skill("taohua-yaoli", 600);      // 桃花药理

        map_skill("force"  , "bibo-shengong");
        map_skill("finger" , "tanzhi-shentong");
        map_skill("hand"   , "lanhua-shou");
        map_skill("unarmed", "luoying-zhang");
        map_skill("strike" , "xuanfeng-leg");
        map_skill("dodge"  , "luoying-shenfa");
        map_skill("parry"  , "tanzhi-shentong");
        map_skill("sword"  , "yuxiao-jian");
        map_skill("chuixiao-jifa", "bihai-chaosheng");
	map_skill("throwing", "tanzhi-shentong");

        prepare_skill("finger" , "tanzhi-shentong");
        prepare_skill("hand"   , "lanhua-shou");

        create_family("桃花岛", 0, "隐士");

        setup();
        carry_object("/d/taohua/obj/yuxiao")->wield();
        carry_object("/d/taohua/obj/bupao")->wear();
}


