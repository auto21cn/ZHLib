inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob, *inv;
	int i, count;
           string str;


	if( !arg ) return notify_fail("你要查看什么武器？\n");
   
	
	if( !objectp(ob = present(arg, me)) )
		return notify_fail("你身上没有这样东西。\n"); 

       if (ob->query("weapon_prop/damage"))
             message("vision", ob->short()+ "的伤害值为"+ob->query("weapon_prop/damage")+"\n",me);
       else 
             message("vision", ob->short()+ "的伤害值为"+ob->query("armor_prop/unarmed_damage")+"\n",me);
     return 1;
	}


