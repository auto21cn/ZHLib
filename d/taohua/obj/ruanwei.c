// ruanwei jia

#include <armor.h>

inherit CLOTH;

void create()
{
    	set_name( "��⬼�",({ "ruanwei jia","jia", }) );
    	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
        	set("long", "һ����ƮƮ�ġ��������񵹴̵Ļ��ס�\n");
		set("material", "copper");
	        set("value",20000);
	        set("armor_prop/armor", 75);
	        set("armor_prop/dodge", -5);
	}
	setup();
}

