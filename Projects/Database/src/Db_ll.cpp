#include "Db_ll.h"

DbLl::DbLl()
{
    hptr = std::make_shared<DbData>(nullptr);
    length = 0;
}

return_codes DbLl::get_Data(const Db_key &Mkey, Db_offset &Moffset)
{
    if( this->length == 0 )
    {
        return LlEmpty;
    }
    
    std::weak_ptr<DbData> wp_cur = hptr;
    do
    {
        if(hptr != nullptr)
        {
            while(auto sp_cur = wp_cur.lock())
            {
                if(sp_cur->key == Mkey)
                {
                    Moffset = sp_cur->offset;
                    return Success;
                }
                else
                {
                    wp_cur = sp_cur->NextNode;
                }
            }
            break;
        }
        else
        {
            break;
        }
    }while(0);
    
    return KeyNotPresent;
}

bool DbLl::get_KeyPresent(const Db_key &Mkey)
{
    if( this->length == 0 )
    {
        return false;
    }

    std::weak_ptr<DbData> wp_cur = hptr;
    do
    {
        if(hptr != nullptr)
        {
            while(auto sp_cur = wp_cur.lock())
            {
                if(sp_cur->key == Mkey)
                {
                    return true;
                }
                else
                {
                    wp_cur = sp_cur->NextNode;
                }
            }
            break;
        }
        else
        {
            break;
        }
    }while(0);
    
    return true;
}

return_codes DbLl::data_Insert(const Db_key &Mkey,const Db_offset &Moffset)
{
    if( get_KeyPresent(Mkey) == true )
    {
        return KeyAlreadyPresent;
    }

    std::weak_ptr<DbData> wp_cur = hptr;
    if(hptr != nullptr)
    {
        while(auto sp_cur = wp_cur.lock())
        {
            if(sp_cur->NextNode == nullptr)
            {
                sp_cur->NextNode = std::make_shared<DbData>(Mkey, Moffset);
                break;
            }
            else
            {
                wp_cur = sp_cur->NextNode;
            }
        }
    }
    else
    {
        hptr = std::make_shared<DbData>(Mkey, Moffset);
    }
    length+=1;

    return Success;
}

return_codes DbLl::data_Remove(const Db_key &Mkey)
{
    if( this->length == 0 )
    {
        return LlEmpty;
    }

    std::weak_ptr<DbData> wp_cur = hptr;
    do
    {
        if(hptr != nullptr)
        {
            if(hptr->key == Mkey)
            {
                std::shared_ptr<DbData> tmp_ptr = hptr;
                hptr = hptr->NextNode;
                tmp_ptr.reset();
                length -= 1;
                return Success;
            }

            while(auto sp_cur = wp_cur.lock())
            {
                if(sp_cur->NextNode == nullptr)
                {
                    break;
                }
                if(sp_cur->NextNode->key == Mkey)
                {
                    std::shared_ptr<DbData> tmp_ptr = sp_cur->NextNode;
                    sp_cur->NextNode = sp_cur->NextNode->NextNode;
                    tmp_ptr.reset();
                    length -= 1;
                    return Success;
                }
                else
                {
                    wp_cur = sp_cur->NextNode;
                }
            }
            break;
        }
        else
        {
            break;
        }
    }while(0);

    return KeyNotPresent;
}

return_codes DbLl::data_Replace(const Db_key &Mkey, const Db_offset &Moffset)
{
    if( this->length == 0 )
    {
        return LlEmpty;
    }

    std::weak_ptr<DbData> wp_cur = hptr;
    do
    {
        if(hptr != nullptr)
        {
            while(auto sp_cur = wp_cur.lock())
            {
                if(sp_cur->key == Mkey)
                {
                    sp_cur->offset = Moffset;
                    return Success;
                }
                else
                {
                    wp_cur = sp_cur->NextNode;
                }
            }
            break;
        }
        else
        {
            break;
        }
    }while(0);

    return KeyNotPresent;
}
