#pragma once

enum UserType{Factory=1,Advanced=2,Normal=3};

class UserInfo
{

public:
	CString name;
	CString pw;
	UserType usertype;

	UserInfo(CString name,CString pw,UserType usertype)
	{
		this->name=name;
		this->pw=pw;
		this->usertype=usertype;

	}

    UserInfo()
    {

    }
} ;

class CUserManage
{
public:
	CUserManage(void);
	~CUserManage(void);
	bool LoadAll(void);
	bool SaveAll(void);
	bool AddUser(CString name,CString ps, UserType type);
	bool DeleteUser(CString name);
	bool Login(CString name,CString ps);
	bool GetUserCount(int&);
	bool GetCurrentUserType(UserType&);
	bool GetAllUser(CList<UserInfo>&);
	bool EditUser(CString name,CString ps, UserType type);
	bool FindUser(CString name);

private:
	
	CMap<CString,LPCTSTR,UserInfo,UserInfo&> usermap;
	static CString currentuser;
};
