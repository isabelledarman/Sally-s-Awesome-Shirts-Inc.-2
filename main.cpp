/*
* main.cpp
*
* COSC 1020 Fall 2023
* Project #4
*
* Due on: NOV 13, 2023
* Author: Darman imd49
*
*
* In accordance with the class policies and Georgetown's
* Honor Code, I certify that, with the exception of the
* class resources and those items noted below, I have neither
* given nor received any assistance on this project.
*
* References not otherwise commented within the program source code.
* Note that you should not mention any help from the TAs, the professor,
* or any code taken from the class textbooks.
*/

#include <iostream>
#include <iomanip>
#include <locale>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

//constants for program
const int MAXIMUM = 14400;
const int MINIMUM = 0;
const double S_SET_UP_COST = 111;
const double S_PER_UNIT_COST = 1.59;
const double I_SET_UP_COST = 0.00;
const double I_PER_UNIT_COST = 2.35;
const double E_SET_UP_COST = 12;
const double E_PER_UNIT_COST = 7.99;
const double S_PER_CHARACTER_COST = 0.00;
const double I_PER_CHARACTER_COST = 0.27;
const double E_PER_CHARACTER_COST = 0.14;
const double MEDIUM_COST = 3.15;
const double LARGE_COST = 4.15;
const double EXTRA_LARGE_COST = 5.15;
const double COST_NON_WHITE_SHIRT = 0.22;
const double DISCOUNT_144_PLUS = 0.045;
const double DISCOUNT_14400_PLUS = 0.095;
const int MAX_MESSAGE_LENGTH = 49;
const int MIN_DISCOUNT = 144;
const int MAX_DISCOUNT = 1440;

/****************************************************************************
* Needed by given function to get region name from file name *
****************************************************************************/
enum REGION_INDEXES {SOUTH, WEST, NORTH, EAST, OTHER}; // DO NOT DELETE!!!
const string REGION_NAMES[] = { "South", "West", "North", "East", "Other" }; // DO NOT DELETE!!!

/****************************************************************************
****************************************************************************
** **
** class ShirtOrder declaration **
** **
** This code is provided to students **
** in COSC 1020 Fall 2023 to use in **
** part or in total for class projects. **
** Students may use this code as their **
** own, without any attribution. **
** **
****************************************************************************
****************************************************************************/
class ShirtOrder
{
    friend ostream& operator<<( ostream& os, const ShirtOrder& rhsObj );
    friend istream& operator>>( istream& in, ShirtOrder& rhsObj );
private:
// the data members below are required (you may change identifiers)
// there is no need for additional data members and none are allowed
    string region;
    int orderYear, orderMonth, orderDay;
    char printMethod; // 's', 'i', 'e', or 'n'
    string message;
    int mediums; // number of medium shirts ordered
    int larges; // number of large shirts ordered
    int xls; // number of XL shirts ordered
    string shirtColor;
    string inkColor;
    string nameAndEmail;
public:
    ShirtOrder();
    ShirtOrder( string region, int orderYear, int orderMonth, int orderDay,
                char printMethod, string message,
                int mediums, int larges, int xls,
                string shirtColor, string inkColor,
                string nameAndEmail );
    ShirtOrder( const ShirtOrder &otherOrder );
    ShirtOrder& operator=( const ShirtOrder &otherOrder );
    void setOrderDate(int yyyy, int mm, int dd);
    double getBlankCost() const;
    double getPrintingCost() const;
    double getTotalCost() const;
    string getMethodName() const;
// basic accessor methods provided with in-line implementation
// NOTE: must edit identifiers if you changed them above
    string getRegion() const { return region; }
    int getOrderYear() const { return orderYear; }
    int getOrderMonth() const { return orderMonth; }
    int getOrderDay() const { return orderDay; }
    char getPrintMethod() const { return printMethod; }
    string getMessage() const { return message; }
    int getMessageLength() const { return message.length(); }
    int getMediums() const { return mediums; }
    int getLarges() const { return larges; }
    int getXls() const { return xls; }
    string getShirtColor() const { return shirtColor; }
    string getInkColor() const { return inkColor; }
    string getNameAndEmail() const { return nameAndEmail; }
// basic mutator methods provided with in-line implementation
// NOTE: must edit identifiers if you changed them above
    void setRegion( string value ) { region = value; }
    void setOrderYear( int value ) { orderYear = value; }
    void setOrderMonth( int value ) { orderMonth = value; }
    void setOrderDay( int value ) { orderDay = value; }
    void setPrintMethod( char value ) { printMethod = value; }
    void setMessage( string value ) { message = value; }
    void setMediums( int value ) { mediums = value; }
    void setLarges( int value ) { larges = value; }
    void setXls( int value ) { xls = value; }
    void setShirtColor( string value ) { shirtColor = value; }
    void setInkColor( string value ) { inkColor = value; }
    void setNameAndEmail( string value ) { nameAndEmail = value; }
}; // END declaration of class ShirtOrder

/****************************************************************************
* Function Prototypes *
****************************************************************************/
string getRegionName(string); // For the given function to get region name from input file name
char displayMenu();
bool uploadFile(string fileName, vector<ShirtOrder>& vShirtOrders);
void allDetails(const vector<ShirtOrder>& vShirtOrders);
void summaryByMethod(const vector<ShirtOrder>& vShirtOrders);
void summaryByRegion(const vector<ShirtOrder>& vShirtOrders);
void clearAllData(vector<ShirtOrder>& vShirtOrders);

int main(){

    vector<ShirtOrder> vShirtOrders;
    string fileName = " ";
    char menuOption = '?';

    //sets precision
    cout << fixed << setprecision(5) << showpoint;

    //welcome message
    cout << "Welcome to the Sally's Awesome Shirts, Inc. (SASI)" << endl;
    cout << "            Regional Ordering Program" << endl;
    cout << "This application calculates material and printing costs\n"
            "based upon sales data input files.\n\n" << endl;

    // call the menu function for the first time
    menuOption = displayMenu();
    while ( menuOption != 'Q' )
    {
        switch ( menuOption )
        {
            case 'U':
                cout << "The user asked to do: " << menuOption << endl;
                cout << "Please enter the full path and filename to load: " << endl;
                cin >> fileName;
                cout << vShirtOrders.size() << " records currently loaded." << endl;
                uploadFile(fileName, vShirtOrders);
                break;
            case 'A':
                cout << "The user asked to do: " << menuOption << endl;
                allDetails(vShirtOrders);
                break;
            case 'M':
                cout << "The user asked to do: " << menuOption << endl;
                summaryByMethod(vShirtOrders);
                break;
            case 'R':
                cout << "The user asked to do: " << menuOption << endl;
                summaryByRegion(vShirtOrders);
                break;
            case 'C':
                cout << "The user asked to do: " << menuOption << endl;
                clearAllData(vShirtOrders);
                break;
            default:
                cout << "Menu choice of " << menuOption << " not known, not sure what to do." << endl;
        }//END switch statement to chose menuOption
        menuOption = displayMenu();
    } // END while loop to display and process menu of options
    cout << "Thank You for using Sally's Awesome Shirts, Inc. (SASI) Regional Ordering Program." << endl;
    return 0;

} // END main

//implementation code for default constructor
ShirtOrder::ShirtOrder()
{
    cout << "Entered default constructor for class ShirtOrder...";
    region = "";
    orderYear = 23;
    orderMonth = 4;
    orderDay = 1;
    printMethod = ' ';
    message = "";
    mediums = 0;
    larges = 0;
    xls = 0;
    shirtColor = "";
    inkColor = "";
    nameAndEmail = "";
    cout << "exit";
}

//implementation code for constructor with parameters
ShirtOrder::ShirtOrder( string region, int orderYear, int orderMonth, int orderDay,
char printMethod, string message, int mediums, int larges, int xls, string shirtColor,
string inkColor, string nameAndEmail )
{
    region = region;
    orderYear = orderYear;
    orderMonth = orderMonth;
    orderDay = orderDay;
    printMethod = printMethod;
    message = message;
    mediums = mediums;
    larges = larges;
    xls = xls;
    shirtColor = shirtColor;
    inkColor = inkColor;
    nameAndEmail = nameAndEmail;
}//END constructor with parameters

//implementation code for copy constructor
ShirtOrder::ShirtOrder( const ShirtOrder &otherOrder )
{
    this->region = otherOrder.region;
    this->orderYear = otherOrder.orderYear;
    this->orderMonth = otherOrder.orderMonth;
    this->orderDay = otherOrder.orderDay;
    this->printMethod = otherOrder.printMethod;
    this->message = otherOrder.message;
    this->mediums = otherOrder.mediums;
    this->larges = otherOrder.larges;
    this->xls = otherOrder.xls;
    this->shirtColor = otherOrder.shirtColor;
    this->inkColor = otherOrder.inkColor;
    this->nameAndEmail = otherOrder.nameAndEmail;
}//END copy constructor

//implementation code fo overloaded assignment operator
ShirtOrder& ShirtOrder::operator=( const ShirtOrder &otherOrder )
{
    this->region = otherOrder.region;
    this->orderYear = otherOrder.orderYear;
    this->orderMonth = otherOrder.orderMonth;
    this->orderDay = otherOrder.orderDay;
    this->printMethod = otherOrder.printMethod;
    this->message = otherOrder.message;
    this->mediums = otherOrder.mediums;
    this->larges = otherOrder.larges;
    this->xls = otherOrder.xls;
    this->shirtColor = otherOrder.shirtColor;
    this->inkColor = otherOrder.inkColor;
    this->nameAndEmail = otherOrder.nameAndEmail;

    return *this;
}//END overloaded assignment operator

//implementation for overloaded stream insertion operator
ostream& operator<<( ostream& os, const ShirtOrder& rhsObj )
{
    os << setfill('0') << setw(2) << rhsObj.getOrderYear() << "/" << setw(2) << rhsObj.getOrderMonth() << "/"
       << setw(2) << rhsObj.getOrderDay() << setfill(' ') << "     ";
    os << setw(1) << rhsObj.getPrintMethod();
    os << setw(5) << '"' << rhsObj.getMessage().substr(0, 5) << "..." << '"';
    os << setw(8) << rhsObj.getMessageLength();
    os << setw(10) << rhsObj.getMediums();
    os << setw(10) << rhsObj.getLarges();
    os << setw(10) << rhsObj.getXls();
    os << setw(10) << rhsObj.getShirtColor();
    os << setw(10) << rhsObj.getInkColor();

    return os;
} //END stream insertion

//implementation for overloaded stream extraction operator
istream& operator>>( istream& in, ShirtOrder& rhsObj )
{
    int orderYear = 0;
    int orderMonth = 0;
    int orderDay = 0;
    char printMethod = ' ';
    string message = "";
    int mediums = 0;
    int larges = 0;
    int xls = 0;
    string shirtColor = "";
    string inkColor = "";
    string nameAndEmail = "";

    char ch = '/';
    string blank = "";

    in >> orderYear >> ch >> orderMonth >> ch >> orderDay >> printMethod;
    getline(getline(in, blank, '"'), message, '"');
    in  >> mediums >> larges >> xls >> shirtColor >> inkColor;

    getline(in, nameAndEmail);

    rhsObj.setOrderYear(orderYear);
    rhsObj.setOrderMonth(orderMonth);
    rhsObj.setOrderDay(orderDay);
    rhsObj.setPrintMethod(printMethod);
    rhsObj.setMessage(message);
    rhsObj.setMediums(mediums);
    rhsObj.setLarges(larges);
    rhsObj.setXls(xls);
    rhsObj.setShirtColor(shirtColor);
    rhsObj.setInkColor(inkColor);
    rhsObj.setNameAndEmail(nameAndEmail);

    return in;
}//END stream insertion

void ShirtOrder:: setOrderDate(int yyyy, int mm, int dd)
{
    orderYear = yyyy;
    orderMonth = mm;
    orderDay = dd;
}
double ShirtOrder:: getBlankCost() const
{
    double blankCost = 0;
    int totalShirts = mediums + larges + xls;

    blankCost = mediums*MEDIUM_COST + larges*LARGE_COST + xls*EXTRA_LARGE_COST;

    if(shirtColor.compare("White") != 0)
    {
        blankCost += totalShirts * COST_NON_WHITE_SHIRT;
    }

    return blankCost;
}
double ShirtOrder:: getPrintingCost() const
{
    int messageLength = message.length();
    double totalPrintingCost = 0;
    int totalShirts = mediums + larges + xls;

    //message cost
    if(messageLength != 0) {
        if (printMethod == 'i' || printMethod == 'I') {
            totalPrintingCost += totalShirts * I_PER_CHARACTER_COST * messageLength;
        } else if (printMethod == 's' || printMethod == 'S') {
            totalPrintingCost += totalShirts * S_PER_CHARACTER_COST * messageLength;
        } else {
            totalPrintingCost += totalShirts * E_PER_CHARACTER_COST * messageLength;
        }
    } //end if for message cost

    //calculates cost for chosen printing type
    if(messageLength != 0) {
        if (printMethod == 's' || printMethod == 'S') {
            totalPrintingCost += S_SET_UP_COST + S_PER_UNIT_COST * totalShirts;
        } else if (printMethod == 'i' || printMethod == 'I') {
            totalPrintingCost += I_SET_UP_COST + I_PER_UNIT_COST * totalShirts;
        } else {
            totalPrintingCost += E_SET_UP_COST + E_PER_UNIT_COST * totalShirts;
        }
    } //end if to calculate part of printing cost

    return totalPrintingCost;
}
double ShirtOrder:: getTotalCost() const
{
    double discountedPrice = 0;
    double totalCost = getPrintingCost() + getBlankCost();
    int totalShirts = mediums + larges + xls;

    if(totalShirts >= MIN_DISCOUNT && totalShirts < MAX_DISCOUNT)
    {
        discountedPrice = totalCost * DISCOUNT_144_PLUS;
        totalCost -= discountedPrice;
    } //end if to calculate small discount

    if(totalShirts >= MAX_DISCOUNT)
    {
        discountedPrice = totalCost * DISCOUNT_14400_PLUS;
        totalCost -= discountedPrice;
    } //end if to calculate large discount

    return totalCost;
}
string ShirtOrder:: getMethodName() const
{
    string printingTypeString = "";

    if(printMethod == 's' || printMethod == 'S')
    {
        printingTypeString = "silk screen";
    }
    else if(printMethod == 'i' || printMethod == 'I')
    {
        printingTypeString = "iron-on";
    }
    else if(printMethod == 'n' || printMethod == 'N')
    {
        printingTypeString = "embroidered";
    }
    else
    {
        printingTypeString = printMethod;
    }

    return printingTypeString;
}

char displayMenu()
{
    char whatToDo = '?';

    while(whatToDo != 'U' && whatToDo != 'A' && whatToDo != 'M'
          && whatToDo != 'C' && whatToDo != 'Q' && whatToDo != 'R') {

        cout << "                   Upload a regional sales data file U\n"
                "                   display details (All loaded data) A\n"
                "                     display summary by print Method M\n"
                "                           display summary by region R\n"
                "                                      Clear all data C\n"
                "                                                Quit Q\n"
                "\n\nPlease enter your menu choice:" << endl;

        cin >> whatToDo;
        cin.ignore(500, '\n');
        cout << endl;
        whatToDo = toupper(whatToDo);
    }
    return whatToDo;
}
bool uploadFile(string fileName, vector<ShirtOrder>& vShirtOrders) {
    //variables for function
    ifstream inFile;
    string headings = getRegionName(fileName);
    string regionName = "";
    int size = vShirtOrders.size();
    ShirtOrder order;
    int goodRecords = 0;

    cout << "\tEntered function \n\tuploadFile( " << fileName << ", ... )" << endl;
    cout << "\tLoading data for region " << getRegionName(fileName) << endl;
    bool uploadStatus = true;

    //processes file
    inFile.open(fileName.c_str());
    if (!inFile) {
        cout << "ERROR!!! File name or path you entered was not valid." << endl;
        return false;
    } //end if if file processing fails
    else {
        regionName = getRegionName(fileName);
        //processes heading without printing them
        getline(inFile, headings);

        //prints headings
        cout << "--------------------------------------------------------------------------------"
                "------------------------------\n"
                "    order      p     5 chars        msg               SIZES                     "
                "COLORS              final\n"
                "     date      m     of msg         len        M        L        XL       shirt"
                "      ink            cost\n"
                "---------------------------------------------------------------------------------"
                "------------------------------\n";

        while (inFile >> order)
        {
            order.setRegion(regionName);

            cout << order;

            vShirtOrders.push_back(order);

            cout << setw(5) << "$" << setw(15) << order.getTotalCost() << endl;

            goodRecords++;
        }

        inFile.close();

        cout << "\tExiting function." << endl;
        cout << "\t" << goodRecords << " added to vectors, " << vShirtOrders.size()
             << " total records now loaded.\n" << endl;
        return uploadStatus;
    }
}
void allDetails(const vector<ShirtOrder>& vShirtOrders)
{
    cout << "\tEntered function allDetails" << endl;

    //prints headings
    cout << "--------------------------------------------------------------------------------"
            "------------------------------\n"
            "    order      p     5 chars        msg               SIZES                     "
            "COLORS              final\n"
            "     date      m     of msg         len        M        L        XL       shirt"
            "      ink            cost\n"
            "---------------------------------------------------------------------------------"
            "------------------------------\n";
    for (int i = 0; i < vShirtOrders.size(); i++) {

        cout << vShirtOrders.at(i);

        cout << "       $" << setw(15);
        cout << vShirtOrders.at(i).getTotalCost() << endl;


    }//END for loop to traverse vectors
    cout << "\tExiting function.\n" << endl;
}
void summaryByMethod(const vector<ShirtOrder>& vShirtOrders)
{
    //variables for function
    double silkScreenTotalCost = 0;
    double printCostSS = 0;
    double shirtCostSS = 0;
    double ironOnTotalCost = 0;
    double printCostI = 0;
    double shirtCostI = 0;
    double embroiderTotalCost = 0;
    double printCostE = 0;
    double shirtCostE = 0;
    double noneTotalCost = 0;
    double printCostN = 0;
    double shirtCostN = 0;
    char printMethod = ' ';

    cout << "\tEntered function summaryByMethod" << endl;

    for(int i = 0; i < vShirtOrders.size(); i++)
    {
        printMethod = vShirtOrders.at(i).getPrintMethod();

        //calculates cost for chosen printing type
        if (printMethod == 's' || printMethod == 'S') {
            silkScreenTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostSS += vShirtOrders.at(i).getPrintingCost();
            shirtCostSS += vShirtOrders.at(i).getBlankCost();
        } else if (printMethod == 'i' || printMethod == 'I') {
            ironOnTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostI += vShirtOrders.at(i).getPrintingCost();
            shirtCostI += vShirtOrders.at(i).getBlankCost();
        } else if(printMethod == 'e' || printMethod == 'E') {
            embroiderTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostE += vShirtOrders.at(i).getPrintingCost();
            shirtCostE += vShirtOrders.at(i).getBlankCost();
        }else{
            noneTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostN += vShirtOrders.at(i).getPrintingCost();
            shirtCostN += vShirtOrders.at(i).getBlankCost();
        }

    }//end for loop to traverse arrays

    cout << setw(12) << "print method" << setw(22) << "blank shirt" << setw(22)
         << "printing cost"<< setw(22) << "final cost" << endl;
    cout << setw(12) << "silk screen" << setw(22) << shirtCostSS << setw(22) << printCostSS
         << setw(22) << silkScreenTotalCost << endl;
    cout << setw(12) << "iron on" << setw(22) << shirtCostI << setw(22) << printCostI
         << setw(22) << ironOnTotalCost << endl;
    cout << setw(12) << "embroider" << setw(22) << shirtCostE << setw(22) << printCostE
         << setw(22) << embroiderTotalCost << endl;
    cout << setw(12) << "none" << setw(22) << shirtCostN << setw(22) << printCostN << setw(22)
         << noneTotalCost << endl;

    cout << "\tExiting function.\n" << endl;
}
void summaryByRegion(const vector<ShirtOrder>& vShirtOrders)
{
    //variables for function
    double nTotalCost = 0;
    double printCostN = 0;
    double shirtCostN = 0;
    double sTotalCost = 0;
    double printCostS = 0;
    double shirtCostS = 0;
    double eTotalCost = 0;
    double printCostE = 0;
    double shirtCostE = 0;
    double wTotalCost = 0;
    double printCostW = 0;
    double shirtCostW = 0;
    double oTotalCost = 0;
    double printCostO = 0;
    double shirtCostO = 0;
    string regionName = "";

    cout << "\tEntered function summaryByRegion" << endl;

    for(int i = 0; i < vShirtOrders.size(); i++)
    {
        regionName = vShirtOrders.at(i).getRegion();

        //calculates cost for chosen printing type
        if (regionName == "North") {
            nTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostN += vShirtOrders.at(i).getPrintingCost();
            shirtCostN += vShirtOrders.at(i).getBlankCost();
        } else if (regionName == "South") {
            sTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostS += vShirtOrders.at(i).getPrintingCost();
            shirtCostS += vShirtOrders.at(i).getBlankCost();
        } else if(regionName == "East") {
            eTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostE += vShirtOrders.at(i).getPrintingCost();
            shirtCostE += vShirtOrders.at(i).getBlankCost();
        } else if(regionName == "West") {
            wTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostW += vShirtOrders.at(i).getPrintingCost();
            shirtCostW += vShirtOrders.at(i).getBlankCost();
        }else if(regionName == "Other") {
            oTotalCost += vShirtOrders.at(i).getTotalCost();
            printCostO += vShirtOrders.at(i).getPrintingCost();
            shirtCostO += vShirtOrders.at(i).getBlankCost();
        }

    }//end for loop to traverse arrays

    cout << setw(12) << "region" << setw(22) << "blank shirt" << setw(22)
         << "printing cost"<< setw(22) << "final cost" << endl;
    cout << setw(12) << "North" << setw(22) << shirtCostN << setw(22) << printCostN
         << setw(22) << nTotalCost << endl;
    cout << setw(12) << "South" << setw(22) << shirtCostS << setw(22) << printCostS
         << setw(22) << sTotalCost << endl;
    cout << setw(12) << "East" << setw(22) << shirtCostE << setw(22) << printCostE
         << setw(22) << eTotalCost << endl;
    cout << setw(12) << "West" << setw(22) << shirtCostW << setw(22) << printCostW << setw(22)
         << wTotalCost << endl;
    cout << setw(12) << "Other" << setw(22) << shirtCostO << setw(22) << printCostO << setw(22)
         << oTotalCost << endl;

    cout << "\tExiting function.\n" << endl;
}

void clearAllData(vector<ShirtOrder>& vShirtOrders)
{
    cout << "\tEntered function clearAllData" << endl;
    cout << "Clearing " << vShirtOrders.size() << " elements from vectors." << endl;
    vShirtOrders.clear();
    cout << "\tExiting function.\n" << endl;
}//END function clear all data

/****************************************************************************
****************************************************************************
** **
** function getRegionName(string) implementation code **
** **
** This code is provided to students **
** in COSC 1020 Fall 2023 to use in **
** part or in total for class projects. **
** Students may use this code as their **
** own, without any attribution. **
** **
** **
** REQUIRES enumerated data type REGION_INDEXES defined in global space **
** REQUIRES constant array REGION_NAMES defined in global space **
** **
** **
** **
** I tested this on the class server. It should work on Windows **
** and Mac as well. If any issues are found, please let me know. **
** **
** **
** There are probably better ways to accomplish the same thing. **
** Feel free to write your own version if you want to experiment. **
** **
** **
****************************************************************************
****************************************************************************/
string getRegionName( string s )
{
    string r = ""; // will store the region by the time the function ends
    string justFileName = ""; // just the input file name without extension
    string fileNameWithExt = ""; // entire input file name with the extension
    int lastSlash = 0; // store index of the last back slash or forward slash in the path
    int i = 0; // location where file name starts
    int subStringLength = 0; // how much of the file name will be used to search for region name
    string startOfFileName = ""; // may be entire file name or just start of the file name
    int longestRegionName = 0; // the number of characters in the longest region name
// In Unix and OSX, the last forward slash '/' should indicate the end of the path
// and the start of the file name.
// In Windows, the last back slash '\' should indicate the end of the path
// and the start of the file name.
    lastSlash = 0;
    for ( int i=0; i<s.length(); i++ ) { if (s.at(i)=='/' || s.at(i)=='\\')
        { lastSlash = i; } }
// Loop to extract just the file name from the path and file name string.
// If neither a back slash nor forward slash was found, then there must not
// be a path stored in the filename string.
    i = ( (lastSlash==0) ? lastSlash : lastSlash + 1 );
    while ( i < s.length() && s.at(i)!='.' ) { justFileName += s.at(i++); }
// Loop to extract the file name and extension from the path and file name string.
    i = ( (lastSlash==0) ? lastSlash : lastSlash + 1 );
    while ( i < s.length() ) { fileNameWithExt += s.at(i++); }
// Determine how much of the file name to search for the region name.
    longestRegionName = 0;
    subStringLength = 0;
// Find the longest region name.
    for ( string reg : REGION_NAMES )
    {
        longestRegionName =
                ( (reg.length() > longestRegionName) ? reg.length() : longestRegionName );
    }
// If the file name is at least as long as the longest region then search
// just the first part of file name for a match in the region list.
// If the file name is shorter than the longest region,
// then search the entire file name for a match in the region list.
    if (justFileName.length() >= longestRegionName)
        subStringLength = longestRegionName;
    else
        subStringLength = justFileName.length();
// May search the entire file name or just first few characters for a region match.
    startOfFileName = justFileName.substr(0, subStringLength);
    r = "Other"; // will store region name to return, start with Other in case no match is found
    for ( unsigned long ri = 0; ri < sizeof(REGION_INDEXES); ri++ )
    {
        if (startOfFileName.find( REGION_NAMES[ri] ) != string::npos)
        {
            r = REGION_NAMES[ri];
//cout << "Found \"" << r << "\" in the file name " << fileNameWithExt << endl;
        }
    }
// Return the region found at the star of the file name or just Other if not found
    return r;
} // END function getRegionName