#include <weapon.h>
#include <ansi.h>
#include <armor.h> 
inherit HANDS; 

void create()
{
        set_name(HIM "��ң���ɻ�" NOR, ({ "shenxian huan" , "xiaoyao" , "shenxian", "huan" }) );
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "ö");
                set("long", HIM "ɢ���Ź��ӹ�������ָ���������ң������������ң���ɻ���\n" NOR);
                set("value", 800000);
                set("no_sell", "���š��ⶫ�����ǹ���󣬿��������Զ�������Թ��ۡ�");
                set("material", "steel");
                set("armor_prop/armor", 30);
        	set("armor_prop/hand", 50);
        	set("armor_prop/strike", 50);
        	set("armor_prop/unarmed_damage", 80);
	        set("wear_msg", HIM "$N" HIM "΢΢һЦ���������һö���ָ����ʱָ��⻪���䡣\n" NOR);
        	set("remove_msg", HIM "$N" HIM "����ң���ɻ���ָ��ȡ��������\n" NOR);
                set("stable", 100);
        }
        setup();
}