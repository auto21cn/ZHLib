//黑店伙计程序
//edit by smallfish

#include <dbase.h>

//修改伙计属性
int do_modify(string arg)
{
        string msg;
        msg = HEIDIAN_D->do_modify(this_object(),this_player(),arg);
        write(msg);
        return 1;
}

//标价货物
int do_stock(string arg)
{
        string msg;
        msg = HEIDIAN_D->do_stock(this_object(),this_player(),arg);
        write(msg);
        return 1;
}

//取下货物
int do_unstock(string arg)
{
       string msg;
       msg = HEIDIAN_D->do_unstock(this_object(),this_player(),arg);
       write(msg);
       return 1;
}

//查询货物列表
int do_list(string arg)
{
        string msg;
        msg = HEIDIAN_D->do_list(this_object(),this_player(),arg);
        write(msg);
        return 1;
}

//购买货物
int do_buy(string arg)
{
        return HEIDIAN_D->do_buy(this_object(),this_player(),arg);
}

//店主结帐
int do_jiezhang()
{
        string msg;
        msg = HEIDIAN_D->do_jiezhang(this_object(),this_player());
        write(msg);
        return 1;
}

//设置、查询贵宾
int do_vip(string arg)
{
        string msg;
        if (arg)
                msg = HEIDIAN_D->do_vip(this_object(),this_player(),arg);
        else
                msg = HEIDIAN_D->list_vip(this_object(),this_player());
        write(msg);
        return 1;
}

//设置、查询贵宾
int do_unwelcome(string arg)
{
        string msg;
        if (arg)
                msg = HEIDIAN_D->do_unwelcome(this_object(),this_player(),arg);
        else
                msg = HEIDIAN_D->list_unwelcome(this_object(),this_player());
        write(msg);
        return 1;
}

string query_save_file()
{
        string id;

        id = query("shop_id");
        if( !stringp(id) ) return 0;
        return sprintf(DATA_DIR "/shop/%s", id);
}

int save()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file + __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;
        if( stringp(file = this_object()->query_save_file()) && file_size(file + __SAVE_EXTENSION__) > 0 )
                return restore_object(file);
        return 0;
}