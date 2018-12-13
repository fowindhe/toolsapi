/*************************************************
* 函数介绍：分割字符串
* 输入参数：源字符串，vector容器，分割key
* 输出参数：分割后的vector容器
* 返回值  ：错误号
*************************************************/
void SplitString(const string& strSrc, vector<string>& lstDest, const string& key)
{
  string::size_type pos1, pos2;
  pos2 = strSrc.find(key);
  pos1 = 0;

  while(string::npos != pos2)
  {
    lstDest.push_back(strSrc.substr(pos1, pos2-pos1));
    pos1 = pos2 + key.size();
    pos2 = strSrc.find(key, pos1);
  }

  if(pos1 != strSrc.length())
  {
    lstDest.push_back(strSrc.substr(pos1));
  }
}

/*************************************************
* 函数介绍：格式化csv中特殊字符
* 输入参数：源字符串
* 输出参数：格式化后的字符串
* 返回值  ：错误号
*************************************************/
void FormatCSVStr(string& strSrc)
{

    if( (strSrc.find("\"")==string::npos) && (strSrc.find(",")==string::npos))
    {
        return;
    }

    vector<string> tmplst;
    
    if(strSrc.find("\"") != string::npos)
    {
        SplitString(strSrc, tmplst,"\"");
        strSrc = "";

        for(vector<string>::iterator iter = tmplst.begin(); iter != tmplst.end(); iter++)
        {
            strSrc += (*iter) + "\"\"";
        }

        strSrc = strSrc.substr(0, strSrc.length()-2);
    }

    strSrc = "\"" + strSrc + "\"";
}

/*************************************************
* 函数介绍：格式化Src：1、去除回车
* 输入参数：源字符串
* 输出参数：格式化后的字符串
* 返回值  ：错误号
*************************************************/
void FormateSrcStr(string& strSrc)
{
    if(strSrc.find("\n")==string::npos)
    {
        return;
    }

    vector<string> tmplst;  
    SplitString(strSrc, tmplst,"\n");
    strSrc = "";

    for(vector<string>::iterator iter = tmplst.begin(); iter != tmplst.end(); iter++)
    {
        strSrc += (*iter);
    }

    return;
}

/*************************************************
* 函数介绍：获取下个关键字值，并将源串第一个关键字值去掉
* 输入参数：源字符串，关键字参数
* 输出参数：源字符串，关键字值
* 返回值  ：错误号
*************************************************/
void GetNextValue(string &src,string &value)
{
    int ipos = 0;
    if(src.length() < 1)
    {
        return;
    }

    ipos = src.find_first_of(' ');
    if(ipos < 0)
    {
        return;
    }
    src = src.substr(ipos);

    ipos = src.find_first_not_of(' ');
    if(ipos < 0)
    {
        return;
    }
    src = src.substr(ipos);

    ipos = src.find_first_of(' ');
    if(ipos < 0)
    {
        value = src;
    }
    else
    { 
        value = src.substr(0,ipos);
    }
}


/*************************************************
* 函数介绍：主机信息 主机名IP
* 输入参数：无
* 输出参数：无
* 返回值  ：错误号
*************************************************/
int GetHostInfo()
{
    int ret                             = ERR_OK;
    FILE *fp                            = NULL;
    char commandbuf[MAXCOMMANDLEN]      = {0};
    char infolinebuf[MAXINFOLINELEN]    = {0};
    int len                             = 0;
    char tmpHostName[256]               = {0};
    string tmpIP                        = "";

	ret = gethostname(tmpHostName, sizeof(tmpHostName));
    if(ret != 0)
    {
        TsgErrorLog("Secchk gethostname failed ");
        return ERR_GETHOST_FAILED;
    }

    len = snprintf(commandbuf, MAXCOMMANDLEN, "ifconfig | grep 'inet addr:'| grep 'Bcast:' | cut -f 2 -d :|cut -f 1 -d ' '");

    if (len < 0)
    {
        TsgErrorLog("snprintf getip cmd failed ");
        return ERR_SNPRINT_FAILED;
    }

    fp = popen(commandbuf, "r");

    if (fp == NULL)
    {
        TsgErrorLog("popen getip cmd failed");
        return ERR_OPEN_FAILED;
    }

    while (fgets(infolinebuf, MAXINFOLINELEN, fp))
    {
        if (strlen(infolinebuf) < 1)
        {
            continue;
        }
        
        tmpIP = infolinebuf;
        if (tmpIP.substr(tmpIP.length() - 1) == "\n")
        {
            tmpIP = tmpIP.substr(0, tmpIP.length() - 1);
        }
        break;

    }

    m_hostInfo->hostname = tmpHostName;
    m_hostInfo->ip = tmpIP;

    pclose(fp);
    fp = NULL;
    return ret;
}



