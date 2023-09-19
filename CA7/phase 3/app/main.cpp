#include "handlers.hpp"
#include "../server/server.hpp"
#include <iostream>
#include "Utrip.hpp"

using namespace std;

int main(int argc, char **argv)
{
  try
  {
    Server server(8080);
    UtripService *utrip = new UtripService(argv[1]);
    server.get("/signup", new ShowPage("static/signup.html"));
    server.get("/login", new ShowPage("static/login.html"));
    server.get("/error1", new ShowPage("static/error1.html"));
    server.get("/error2", new ShowPage("static/error2.html"));
    server.get("/error3", new ShowPage("static/error3.html"));
    server.get("/error4", new ShowPage("static/error4.html"));
    server.get("/error5", new ShowPage("static/error5.html"));
    server.get("/accountCreation", new ShowPage("static/accountCreation.html"));
    server.get("/accountCharge", new ShowPage("static/deposit.html"));
    server.post("/login", new LoginHandler(utrip));
    server.post("/signup", new SignupHandler(utrip));
    server.get("/home", new ShowHomePage(utrip));
    server.get("/moreDetails", new ShowHotelDetails(utrip));
    server.post("/logout", new LogoutHandler(utrip));
    server.post("/filter", new FilterHandler(utrip));
    server.post("/deposit", new DepositHandler(utrip));
    server.get("/logout", new LogoutHandler(utrip));
    server.get("/filter", new FilterHandler(utrip));
    server.get("/deposit", new DepositHandler(utrip));
    server.get("/wallet", new WalletHandler(utrip));
    server.run();
  }
  catch (Server::Exception e)
  {
    cerr << e.getMessage() << endl;
  }
}
