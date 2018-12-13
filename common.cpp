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

