// FaWang.h for fight and get letter from FaWang

#include "mingjiao.h"

int accept_object(object ob, object obj)
{
	object me = this_object();

	mapping my_fam  = me->query("family");
	mapping ob_fam  = ob->query("family");

	if ( ob->query_temp("have_letter") && present("tuijian xin5", ob) ) 
	{
                command("say �������������ҵ��Ƽ���ȥ�ݹ���ʹ������ ?");
		return 0;
	}

	if((obj->query("id") == "tieyan ling")
	&& ob_fam["family_name"] == "����"
	&& ob_fam["generation"] == me->query("family/generation") + 1
	&& !ob->query_temp("have_letter") ) 
	{
		ob->set_temp("fight_ok",1);
                command("say �ã���Ȼ�ѵõ��������ɣ����Ǿ�����֤һ���书��");
		remove_call_out("destroying");
		call_out("destroying", 1, me, obj);
		return 1;
	}
        
	if (obj->query("id") == "tuijian xin4" 
	&& ob->query_temp("have_letter") 
	&& ob_fam["generation"] == my_fam["generation"] + 2)
	{
		ob->set_temp("apprentice_ok",1);
	        command("say �ã�" + ob->query("name") + "����Ը�����Ϊʦ��");
		remove_call_out("destroying");
		call_out("destroying", 1, me, obj);
		return 1;
	}

        command("smile");
        command("say �ⶫ�����ҿ�û��ʲ���á�");
        command("give " + obj->query("id") + " to " + me->query("id"));
	return 0;

}

void destroying(object me, object obj)
{
	destruct(obj);
	return;
}

int accept_fight(object ob)
{
	object me  = this_object();
	
	if ( !ob->query_temp("fight_ok") ) return 0;

	remove_call_out("checking");
	call_out("checking", 1, me, ob);

	ob->delete_temp("fight_ok");
	
	return 1;
}

int checking(object me, object ob)
{

	object obj;
	int my_max_qi, his_max_qi;

	my_max_qi  = me->query("max_qi");
	his_max_qi = ob->query("max_qi");

	if (me->is_fighting()) 
	{
		call_out("checking",2, me, ob);
                return 1;
	}

	if ( !present(ob, environment()) ) return 1; 

	if (( (int)me->query("qi")*100 / my_max_qi) <= 50 ) 
	{
                command("say ������ʤ����������������̵ļѵ��� ! ��ϲ���� !\n");
		message_vision("$N����$nһ���Ƽ��š�\n", me, ob);
		ob->set_temp("have_letter",1);
                obj=new("/d/mingjiao/obj/tuijianxin-5");
		obj->move(ob);
		return 1;
	}

	if (( (int)ob->query("qi")*100 / his_max_qi) < 50 ) 
	{
		command("say ����" + RANK_D->query_respect(ob) + 
                        "���ö����ϰ�������������������г���ͷ�� !\n");
		return 1;
	}

	return 1;  
}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping ob_fam;
	mapping my_fam  = me->query("family");

	string name, new_name;

        if (! permit_recruit(ob) )
                return;

	name = ob->query("name");

        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "����")
	{
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}

	if ( ob_fam["generation"] <= my_fam["generation"] )
	{
                command("say " + RANK_D->query_respect(ob) + "����������ҵ� !");
		return;
	}

        if ( ob_fam["generation"] == (my_fam["generation"] + 1) )
	{
		command("say " + ob_fam["master_name"] + "��ͽ�������ܵ���������ˣ������� !");
		command("recruit " + ob->query("id"));
	}

	if ( ob_fam["generation"] == (my_fam["generation"] + 2) )
	{
		if ( ob->query_temp("apprentice_ok") )
		{
			ob->delete_temp("have_letter");
			ob->delete_temp("apprentice_ok");
	
			command("say ��" + ob_fam["master_name"] + "���������ҵİɣ������� !");
                        command("say �������ֵ�һ����֮�ţ����ǿ�ϲ�ɺ� !");
                         command("recruit " + ob->query("id"));
		}
		else
		{
			command("say " + RANK_D->query_respect(ob) + "����û���Ƽ��ţ�����Խ����ʦ��");
			return;
		}
	}

	return;
}