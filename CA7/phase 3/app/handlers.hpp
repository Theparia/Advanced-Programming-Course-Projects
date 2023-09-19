#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include "Utrip.hpp"
#include <iostream>

class ShowHomePage : public RequestHandler
{
public:
	ShowHomePage(UtripService *utrip_) : utrip(utrip_) {}
	Response *callback(Request *);

private:
	UtripService *utrip;
};
class ShowHotelDetails : public RequestHandler
{
public:
	ShowHotelDetails(UtripService *utrip_) : utrip(utrip_) {}
	Response *callback(Request *);

private:
	UtripService *utrip;
};
class SignupHandler : public RequestHandler
{
public:
	SignupHandler(UtripService *utrip_) : utrip(utrip_) {}
	Response *callback(Request *);

private:
	UtripService *utrip;
};
class LoginHandler : public RequestHandler
{
public:
	LoginHandler(UtripService *utrip_) : utrip(utrip_) {}
	Response *callback(Request *);

private:
	UtripService *utrip;
};
class LogoutHandler : public RequestHandler
{
public:
	LogoutHandler(UtripService *utrip_) : utrip(utrip_) {}
	Response *callback(Request *);

private:
	UtripService *utrip;
};
class FilterHandler : public RequestHandler
{
public:
	FilterHandler(UtripService *utrip_) : utrip(utrip_) {}
	Response *callback(Request *);

private:
	UtripService *utrip;
};
class WalletHandler : public RequestHandler
{
public:
	WalletHandler(UtripService *utrip_) : utrip(utrip_) {}
	Response *callback(Request *);

private:
	UtripService *utrip;
};
class DepositHandler : public RequestHandler
{
public:
	DepositHandler(UtripService *utrip_) : utrip(utrip_) {}
	Response *callback(Request *);

private:
	UtripService *utrip;
};

#endif
