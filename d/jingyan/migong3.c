#include <room.h>
#include <ansi.h>
inherit ROOM;

void random_exit();

void create()
{
        set("short", "左雁殿");
        set("long", @LONG
   左雁殿里空无一物，四周墙上刻满浮雕。
这些浮雕造型高古,手工细致精雅，工程惊人庞大，
内容令人难解，描绘的都是些奇禽异兽你虽见识宽
广，但浮雕上的奇禽异兽竟一样也没见过，真是奇
怪之极！
LONG );
                set("item_desc", ([       
"浮雕" : "你发现浮雕有点凹凸不平，若不是有目标的查察，
必会当是石纹忽略过去,你不禁想按下(an)浮雕!\n",  
                          ]));
              set("no_stab", 1); 
       set("exits", ([
                "west" :"d/jingyan/migong2",                                           
                                                ]));
                set("no_clean_up", 0);
        setup();
} 
void init()
{
  object me = this_player();
        add_action("do_an", "an");
        add_action("do_la", "la"); 
        add_action("do_zhuan", "zhuan");
}
void check_longtou()
{
    object me;
    me = this_player();
if(query("longtou")==6)
{
   message_vision(HIC"突然浮雕凸了出来，你用力{la)了一下!!。\n"NOR, this_player());
      me->set_temp("la_longtou",1);
remove_call_out("on_del");
call_out("on_del", 10);
}
}
int do_la(string arg)
{
        object me;
        me = this_player(); 
   if( !me->query_temp("la_longtou")) return 0;   
     if( !arg || arg=="" ) return notify_fail("你要拉什么东西!\n");
            if( arg=="浮雕") {
             write(HIB"你一把将浮雕拉了起来。 \n"NOR); 
         write(HIR"浮雕似乎可以往左右转动，到底转哪边好呢? \n"NOR); 
             me->delete_temp("la_longtou");             this_player()->set_temp("zhuan_longtou", 1);
             return 1;
       }
}
 int do_an(string arg)
{
        object zhu, me=this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="浮雕" )
                             { 
if(query("longtou")<10)
{                                             message_vision(
HIC"$N把浮雕用力往里按!\n"NOR, this_player());
add("longtou",1);
check_longtou();
return 1;
                }
delete("longtou");
 message_vision(HIG"你按过头了,浮雕又陷了回去!\n"NOR, this_player());
                return 1;
        }
        return 1;
}
int do_zhuan(string arg)
{
    object me; 
    object room;
    string dir;
             me = this_player();
 if (!me->query_temp("zhuan_longtou")) 
return 0;
      if( !arg || arg=="" ) return notify_fail("你要转什么东西!\n");
      if( sscanf(arg, "%s", dir)==1 ) {
    if( dir=="left" ) {
   message_vision(HIC"$N把浮雕往左转了一转。\n"NOR, this_player()); 
            add("zhuanmen", 1); 
return 1;
}
 else if( dir=="right") {
         if (query("zhuanmen")) {   
                        message_vision(HIC"$N把浮雕又转了回去。\n"NOR, this_player()); 
                        message_vision(HIC"浮雕座落原位，果然与先前丝毫无异。\n"NOR, this_player());
                        
                this_player()->delete_temp("zhuan_longtou"); 
                
                random_exit();
                        
room = load_object("/d/jingyan/migong5.c");
    message("vision", "浮雕该是连接着一些机关，你感到扭动和震荡。\n",me );
    message("vision", "突然你面前出现9个大洞，不知道是哪个才能进入密道。\n",room ); 
        message("channel:chat", HIW"【惊雁宫】"+me->query("name")+"成功进入惊雁宫密道了!!\n"NOR,users());
                call_out("on_guanmen", 180);
}
}
return 1;
        }
        else {
            write("你想转向哪个方向?\n");
            return 1;
        }
}
void on_guanmen(object room)
{ 
      if( room = find_object("/d/jingyan/migong5.c") ) 
            room->delete("exits/1");
            room->delete("exits/2");
            room->delete("exits/3");
            room->delete("exits/4");
            room->delete("exits/5");
            room->delete("exits/6");
            room->delete("exits/7");
            room->delete("exits/8");
            room->delete("exits/9");
delete("longtou");  
 message_vision(HIG"突然出现咔咔的响声，洞口又消失了!\n"NOR, room);
}

void on_del()
{
  object me = this_player();

if (!me) return 0;

if (environment(me)!=this_object())
{
delete("longtou");
remove_call_out("on_del");
return 0;
}
  call_out("on_del", 10);
}

void random_exit()
        {
                object room = load_object("/d/jingyan/migong5.c");
        
                int *a = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
                int x = random(9) + 1;
                
                if (! room)
                        return 0;//没这个房间
                
                room->set("exits/"+x , "/d/jingyan/lev1/dong01");
                a -= ({x});
                
                for( int i = 0; i < 8;i++)
                        room->set("exits/"+a[i], "/d/city/wumiao");      
                        
                        //return x;//返回值为通往密道房间的数值
                        return;
        }

