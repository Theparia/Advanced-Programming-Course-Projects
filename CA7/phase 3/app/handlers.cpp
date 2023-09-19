#include <string>
#include <sstream>
#include "handlers.hpp"
using namespace std;

Response *ShowHotelDetails::callback(Request *req)
{
  Response *res = new Response;
  if (!utrip->hasSomeOneLoggedIn())
    return Response::redirect("/error4");
  res->setHeader("Content-Type", "text/html");
  Hotel *hotel = utrip->findHotelById(req->getQueryParam("id"));
  ostringstream body;
  body << "<!DOCTYPE html>"
       << "   <html>" << endl
       << "       <head><title>Home</title>" << endl
       << "       </head>" << endl
       << "   <style>" << endl
       << "      input[type=text] {" << endl
       << "           width: 100%;" << endl
       << "       }" << endl
       << "      .navbar {" << endl
       << "           overflow: hidden;" << endl
       << "           background-color: #4CAF50;" << endl
       << "       }" << endl
       << "      .navbar a {" << endl
       << "           float: left;" << endl
       << "           display: block;" << endl
       << "           color: white;" << endl
       << "           text-align: center;" << endl
       << "           padding: 14px 20px;" << endl
       << "           text-decoration: none;" << endl
       << "       }" << endl
       << "      .navbar a:hover {" << endl
       << "           background-color: #ddd;" << endl
       << "           color: black;" << endl
       << "       }" << endl
       << "      .header {" << endl
       << "           padding:20px;" << endl
       << "           text-align: center;" << endl
       << "           background: #666666;" << endl
       << "           color: white;" << endl
       << "       }" << endl
       << "      .header h1 {" << endl
       << "           font-size: 60px;" << endl
       << "           font-family: 'Lucida Console', Courier, monospace;" << endl
       << "       }" << endl
       << "       body {" << endl
       << "           background-color:white;" << endl
       << "       }" << endl
       << "       img {" << endl
       << "           display: block;" << endl
       << "           margin-left: auto;" << endl
       << "           margin-right: auto;" << endl
       << "           border-radius: 50%;" << endl
       << "       }" << endl
       << "       .myDiv {" << endl
       << "           color: black;" << endl
       << "           margin: 50px;" << endl
       << "           background-color: #a6a6a6;" << endl
       << "           text-align: center;" << endl
       << "       }" << endl
       << "       .btn-group .button {" << endl
       << "           background-color: #4CAF50;" << endl /* Green */
       << "           border: none;" << endl
       << "           color: white;" << endl
       << "           padding: 15px 32px;" << endl
       << "           text-align: center;" << endl
       << "           text-decoration: none;" << endl
       << "           display: inline-block;" << endl
       << "           font-size: 16px;" << endl
       << "           cursor: pointer;" << endl
       << "           float: left;" << endl
       << "       }" << endl
       << "       .btn-group .button:hover {" << endl
       << "           background-color: #3e8e41;" << endl
       << "       }" << endl
       << "       .btn-group .button:not(:last-child) {" << endl
       << "           border-right: none;" << endl
       << "       }" << endl
       << "       table.center {" << endl
       << "           margin-left:auto; " << endl
       << "           margin-right:auto;" << endl
       << "       }" << endl
       << "   </style>" << endl
       << "   <div class='header'>" << endl
       << "       <h1> UTRIP </h1>" << endl
       << "   </div>" << endl
       << "   <body style='text-align: center;'>" << endl
       << "       <div class='navbar'>" << endl
       << "           <div class='btn-group'>"
       << "               <form action='/logout' method='post'>" << endl
       << "                   <button class='button' type='submit' >Logout</buttton>" << endl
       << "               </form>" << endl
       << "             <form action='/home' method='get'>" << endl
       << "                   <button class='button' type='submit' >Home</buttton>" << endl
       << "             </form>" << endl
       << "             <form action='/wallet' method='get'>" << endl
       << "                   <button class='button' type='submit' >Wallet</buttton>" << endl
       << "             </form>" << endl
       << "         </div>" << endl
       << "       </div>" << endl
       << "       <div class='myDiv' >" << endl
       << "           </br>" << endl
       << "           <p><img src='" << hotel->getImageUrl() << "' width='300' height='300';>"
       << "           <h2> Property Name: </h2>" << endl
       << "           <p>" << hotel->getPropertyName() << "</p>" << endl
       << "           <h2> City: </h2>" << endl
       << "           <p>" << hotel->getCity() << "</p>" << endl
       << "           <h2> Hotel Star Rating: </h2>" << endl
       << "           <p>" << hotel->getStarRating() << "</p>" << endl
       << "           <h2> Overview: </h2>" << endl
       << "           <p>" << hotel->getOverview() << "</p>" << endl
       << "           <h2> Rooms: </h2>" << endl
       << "           <table border=1 class='center'>" << endl
       << "               <tr>" << endl
       << "                   <th>&nbsp;</th>" << endl
       << "                   <th>Standard</th>" << endl
       << "                   <th>Deluxe</th>" << endl
       << "                   <th>Luxury</th>" << endl
       << "                   <th>Premium</th>" << endl
       << "               </tr>" << endl
       << "               <tr>" << endl
       << "                   <th> Cost </th> " << endl
       << "                   <td>" << hotel->getPrices()["standard"] << "</td>" << endl
       << "                   <td>" << hotel->getPrices()["deluxe"] << "</td>" << endl
       << "                   <td>" << hotel->getPrices()["luxury"] << "</td>" << endl
       << "                   <td>" << hotel->getPrices()["premium"] << "</td>" << endl
       << "               </tr>" << endl
       << "               <tr>" << endl
       << "                   <th> Quantity </th>" << endl
       << "                   <td>" << hotel->getRoomsOfType("standard").size() << "</td>" << endl
       << "                   <td>" << hotel->getRoomsOfType("deluxe").size() << "</td>" << endl
       << "                   <td>" << hotel->getRoomsOfType("luxury").size() << "</td>" << endl
       << "                   <td>" << hotel->getRoomsOfType("premium").size() << "</td>" << endl
       << "           </table>" << endl
       << "           <ul>" << endl
       << "               <h2> Property Amenities: </h2>" << endl;
  for (int i = 0; i < hotel->getAmenities().size(); i++)
  {
    body << "<li>" << hotel->getAmenities()[i] << "</li>" << endl;
  }
  body << "               </ul>" << endl
       << "            </p>" << endl
       << "    </body>" << endl
       << "</html>" << endl;

  res->setBody(body.str());
  return res;
}

Response *ShowHomePage::callback(Request *req)
{
  Response *res = new Response;
  if (!utrip->hasSomeOneLoggedIn())
    return Response::redirect("/error4");
  res->setHeader("Content-Type", "text/html");
  vector<Hotel *> hotels = utrip->getFilteredHotels(req->getSessionId());
  ostringstream body;
  body
      << "<!DOCTYPE html>"
      << "    <html>" << endl
      << "        <head><title>Home</title>" << endl
      << "        </head>" << endl
      << "        <style>" << endl
      << "          input[type=text] {" << endl
      << "              width: 50%;" << endl
      << "           }" << endl
      << "          .navbar {" << endl
      << "              overflow: hidden;" << endl
      << "              background-color: #4CAF50;" << endl
      << "           }" << endl
      << "          .navbar a {" << endl
      << "              float: left;" << endl
      << "              display: block;" << endl
      << "              color: white;" << endl
      << "              text-align: center;" << endl
      << "              padding: 14px 20px;" << endl
      << "              text-decoration: none;" << endl
      << "           }" << endl
      << "          .navbar a:hover {" << endl
      << "              background-color: #ddd;" << endl
      << "              color: black;" << endl
      << "           }" << endl
      << "          .header {" << endl
      << "              padding:20px;" << endl
      << "              text-align: center;" << endl
      << "              background: #666666;" << endl
      << "              color: white;" << endl
      << "           }" << endl
      << "          .header h1 {" << endl
      << "              font-size: 60px;" << endl
      << "              font-family: 'Lucida Console', Courier, monospace;" << endl
      << "           }" << endl
      << "           body {" << endl
      << "              background-color:white;" << endl
      << "           }" << endl
      << "          img {" << endl
      << "              display: block;" << endl
      << "              margin-left: auto;" << endl
      << "              margin-right: auto;" << endl
      << "              border-radius: 50%;" << endl
      << "           }" << endl
      << "         .myDiv {" << endl
      << "              color: black;" << endl
      << "              margin: 50px;" << endl
      << "              background-color: #a6a6a6;" << endl
      << "              text-align: center;" << endl
      << "          }" << endl
      << "          .btn-group .button {" << endl
      << "              background-color: #4CAF50;" << endl
      << "              border: none;" << endl
      << "              color: white;" << endl
      << "              padding: 15px 32px;" << endl
      << "              text-align: center;" << endl
      << "              text-decoration: none;" << endl
      << "              display: inline-block;" << endl
      << "              font-size: 16px;" << endl
      << "              cursor: pointer;" << endl
      << "              float: left;" << endl
      << "          }" << endl
      << "          .btn-group .button:hover {" << endl
      << "              background-color: #3e8e41;" << endl
      << "          }" << endl
      << "          .btn-group .button:not(:last-child) {" << endl
      << "              border-right: none;" << endl
      << "          }" << endl
      << "      </style>" << endl
      << "      <div class='header'>" << endl
      << "        <h1> UTRIP </h1>" << endl
      << "      </div>" << endl
      << "      <body style='text-align: center;'>" << endl
      << "          <div class='navbar'>" << endl
      << "<div class='btn-group'>"
      << "                <form action='/logout' method='post'>" << endl
      << "                    <button class='button' type='submit' >Logout</buttton>" << endl
      << "                </form>" << endl
      << "                <form action='/home' method='get'>" << endl
      << "                    <button class='button' type='submit' >Home</buttton>" << endl
      << "                </form>" << endl
      << "                <form action='/wallet' method='get'>" << endl
      << "                    <button class='button' type='submit' >Wallet</buttton>" << endl
      << "                </form>" << endl
      << "            </div>" << endl
      << "          </div>" << endl
      << "          <div class='myDiv'>" << endl
      << "            <p style='font-family:'Courier New''>Please fill in this form to filter hotels.</p>" << endl
      << "            <form action='/filter' method='post'>" << endl
      << "                <input name='min-star' type='text' placeholder='Min Star' /> <br>" << endl
      << "                <input name='max-star' type='text' placeholder='Max Star' /> <br>" << endl
      << "                <button type='submit' >Filter</button>" << endl
      << "            </form>" << endl
      << "          </div>" << endl
      << "          <div class='myDiv' >" << endl
      << "            </br>" << endl;
  for (int i = 0; i < hotels.size(); i++)
  {
    body << "         <div >" << endl
         << "           <p><img src='" << hotels[i]->getImageUrl() << "' width='200' height='200';>"
         << "           <p>Property Name: " << hotels[i]->getPropertyName() << "</p>" << endl
         << "           <p>City: " << hotels[i]->getCity() << "</p>" << endl
         << "           <p>Star: " << hotels[i]->getStarRating() << "</p>" << endl
         << "           <p><a href='moreDetails?id=" << hotels[i]->getUniqueId() << "'>More Details</a></p>" << endl
         << "           </p>" << endl
         << "       </div>" << endl
         << "       </br>";
  }
  body
      << "        </div>" << endl
      << "      </body>" << endl
      << "    </html>" << endl;
  res->setBody(body.str());

  return res;
}
Response *SignupHandler::callback(Request *req)
{
  Response *res = new Response;
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string rePassword = req->getBodyParam("re-password");
  string email = req->getBodyParam("email");
  if (utrip->isSignUpInvalid(email, password))
    return Response::redirect("/error2");
  if (password != rePassword)
    return Response::redirect("/error1");
  utrip->signUpUser(email, username, password);
  res = Response::redirect("/accountCreation");
  res->setSessionId(username);
  return res;
}
Response *LoginHandler::callback(Request *req)
{
  Response *res = new Response;
  string password = req->getBodyParam("password");
  string username = req->getBodyParam("username");
  if (!utrip->isLoginValid(username, password))
    return Response::redirect("/error3");
  utrip->logIn(username, password);
  res = Response::redirect("/home");
  res->setSessionId(username);
  return res;
}
Response *LogoutHandler::callback(Request *req)
{
  Response *res = new Response;
  if (!utrip->hasSomeOneLoggedIn())
    return Response::redirect("/error4");
  res = Response::redirect("/login");
  utrip->logOut(req->getSessionId());
  res->setSessionId("");
  return res;
}
Response *FilterHandler::callback(Request *req)
{
  Response *res = new Response;
  if (!utrip->hasSomeOneLoggedIn())
    return Response::redirect("/error4");
  int minStar = stoi(req->getBodyParam("min-star").c_str());
  int maxStar = stoi(req->getBodyParam("max-star").c_str());
  utrip->addStarRatingFilter(minStar, maxStar, req->getSessionId());
  res = Response::redirect("/home");
  return res;
}

Response *DepositHandler::callback(Request *req)
{
  Response *res = new Response;
  if (!utrip->hasSomeOneLoggedIn())
    return Response::redirect("/error4");
  double amount = stod(req->getBodyParam("amount").c_str());
  if (amount <= ZERO)
    return Response::redirect("/error5");
  utrip->chargeWallet(amount, req->getSessionId());
  res = Response::redirect("/accountCharge");
  return res;
}
Response *WalletHandler::callback(Request *req)
{
  Response *res = new Response;
  if (!utrip->hasSomeOneLoggedIn())
    return Response::redirect("/error4");
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body << "<!DOCTYPE html>"
       << "    <html>" << endl
       << "       <head><title>Wallet</title>" << endl
       << "       </head>" << endl
       << "       <style>" << endl
       << "       input[type=text] {" << endl
       << "           width: 50%;" << endl
       << "       }" << endl
       << "       .navbar {" << endl
       << "           overflow: hidden;" << endl
       << "           background-color: #4CAF50;" << endl
       << "       }" << endl
       << "       .navbar a {" << endl
       << "           float: left;" << endl
       << "           display: block;" << endl
       << "           color: white;" << endl
       << "           text-align: center;" << endl
       << "           padding: 14px 20px;" << endl
       << "           text-decoration: none;" << endl
       << "       }" << endl
       << "       .navbar a:hover {" << endl
       << "           background-color: #ddd;" << endl
       << "           color: black;" << endl
       << "       }" << endl
       << "       .header {" << endl
       << "           padding:20px;" << endl
       << "           text-align: center;" << endl
       << "           background: #666666;" << endl
       << "           color: white;" << endl
       << "       }" << endl
       << "       .header h1 {" << endl
       << "           font-size: 60px;" << endl
       << "           font-family: 'Lucida Console', Courier, monospace;" << endl
       << "       }" << endl
       << "       body {" << endl
       << "           background-color:white;" << endl
       << "       }" << endl
       << "       .btn-group .button {" << endl
       << "           background-color: #4CAF50;" << endl
       << "           border: none;" << endl
       << "           color: white;" << endl
       << "           padding: 15px 32px;" << endl
       << "           text-align: center;" << endl
       << "           text-decoration: none;" << endl
       << "           display: inline-block;" << endl
       << "           font-size: 16px;" << endl
       << "           cursor: pointer;" << endl
       << "           float: left;" << endl
       << "       }" << endl
       << "       .btn-group .button:hover {" << endl
       << "           background-color: #3e8e41;" << endl
       << "       }" << endl
       << "       .btn-group .button:not(:last-child) {" << endl
       << "            border-right: none;" << endl
       << "       }" << endl
       << "       .myDiv {" << endl
       << "           color: black;" << endl
       << "           margin: 50px;" << endl
       << "           background-color: #a6a6a6;" << endl
       << "           text-align: center;" << endl
       << "       }" << endl
       << "     </style>" << endl
       << "     <div class='header'>" << endl
       << "       <h1> UTRIP </h1>" << endl
       << "     </div>" << endl
       << "     <body style='text-align: center;'>" << endl
       << "        <div class='navbar'>" << endl
       << "           <div class='btn-group'>"
       << "               <form action='/logout' method='post'>" << endl
       << "                   <button class='button' type='submit' >Logout</buttton>" << endl
       << "               </form>" << endl
       << "               <form action='/home' method='get'>" << endl
       << "                   <button class='button' type='submit' >Home</buttton>" << endl
       << "               </form>" << endl
       << "               <form action='/wallet' method='get'>" << endl
       << "                   <button class='button' type='submit' >Wallet</buttton>" << endl
       << "               </form>" << endl
       << "           </div>" << endl
       << "       </div>" << endl
       << "       <div class='myDiv'>" << endl
       << "         <p style='font-size:45px'> Account Balance : " << utrip->getAccountBalance(req->getSessionId()) << "</p> </br>" << endl
       << "           <div>" << endl
       << "             <form action='/deposit' method='post'>" << endl
       << "               <input name='amount' type='text' placeholder='Charge Amount' /> <br>" << endl
       << "               <button type='submit' >Charge</button>" << endl
       << "           </form>" << endl
       << "          </div>" << endl
       << "         </div>" << endl
       << "     </body>" << endl
       << "</html>" << endl;
  res->setBody(body.str());
  return res;
}
