#include "Register.h" //Source file needs to include header file
#include <iostream> //Includes iostream for output and input
#include <iomanip> //Includes iomanip for manipulating text when printed out

/* processTransaction */
//Called by the register object to go through the entire transaction process
bool Register::processTransaction()
{
    setFileName(getFileName());
    bool successfulAttempt = readFromFile();
    printFile();
    dateVector.clear();
    transactionVector.clear();
    locationVector.clear();
    creditDebitVector.clear();
    return successfulAttempt;
}

/* getFileName */
//Prompts user for a filename and will keep prompting as long as it's invalid
string Register::getFileName()
{
    string input;
    cout << "\tPlease enter the filename: ";
    cin >> input;
    cout << "\tOpening the file <" << input << ">" << endl;
    setFileName(input);
    while(!readFromFile())
    {
        cout << "Error opening file. Please retry." << endl;
        cout << "\tPlease enter the filename: ";
        cin >> input;
        cout << "\tOpening the file <" << input << ">" << endl;
        setFileName(input);
    }
    return input;
}

/* setFileName */
//Sets the filename variable to the input
void Register::setFileName(string input)
{
    filename = input;
}

/* readFromFile */
//Is used to populate the vectors as well as confirm a file name
bool Register::readFromFile()
{
    //fileReader object opens the file
    fileReader.open(filename);
    //As long as validatingFileName is true (is set to true upon object creation, and made false once the object has a file name)
    //It will try to check for a valid file name and return the appropriate bool
    if(validatingFileName)
    {
        if(fileReader)  
        {
            validatingFileName = false;
            fileReader.close();
            return true;
        }
        else
        {
            fileReader.close();
            return false;
        }
    }
    
    //Checks if fileReader is still valid
    if(fileReader)
    {
        //Column counter increments with each new thing read from the file
        int columnCounter = 0;
        string inputFromFile;

        //While there is information to read in from the file...
        while(fileReader >> inputFromFile)
        {
            //Column % 4 checks which vector needs to be populated
            int column = columnCounter % 4;
            if(column == 0)
            {
                dateVector.push_back(inputFromFile);
            }
            else if(column == 1)
            {
                //Checks what is read in from the file and populates the transaction vector with the appropriate enumerated variable
                if(inputFromFile == "RESTAURANT")
                {
                    transactionVector.push_back(RESTAURANT);
                }
                else if(inputFromFile == "MERCHANDISE")
                {
                    transactionVector.push_back(MERCHANDISE);
                }
                else if(inputFromFile == "UTILITY")
                {
                    transactionVector.push_back(UTILITY);
                }
                else if(inputFromFile == "COFFEESHOP")
                {
                    transactionVector.push_back(COFFEESHOP);
                }
                else if(inputFromFile == "AUTOMOTIVE")
                {
                    transactionVector.push_back(AUTOMOTIVE);
                }
                else if(inputFromFile == "DEPOSIT")
                {
                    transactionVector.push_back(DEPOSIT);
                }
                else
                {
                    transactionVector.push_back(OTHER);
                }
            }
            else if (column == 2)
            {
                locationVector.push_back(inputFromFile);
            }
            else
            {
                creditDebitVector.push_back(stod(inputFromFile));
            }
            columnCounter ++;
        }
    }
    else
    {
        return false;
    }
    fileReader.close();
    return true;
}

/* printFile */
//Used to print the transaction ledger in a formatted way
void Register::printFile()
{
    cout << "Printing Transaction Ledger" << endl;
    //Will iterate through the size of the dateVector since all 4 should be the same size
    for(int i = 0; i < static_cast<int>(dateVector.size()); i ++)
    {
        //Outputs the first 3 columns with break lines and appropriate spacing
        cout << right << setw(11) << dateVector[i] << " |";
        cout << right << setw(15) << locationVector[i] << " |";
        cout << right << setw(10) << fixed << setprecision(2) << creditDebitVector[i] << " |";
        //Switch statement to check which enumerated type is in the transaction vector
        switch(transactionVector[i])
        {
            case RESTAURANT:
                cout << right << setw(20) << "Restaurant" << endl << endl;
                break;
            case MERCHANDISE:
                cout << right << setw(20) << "Merchandise" << endl << endl;
                break;
            case UTILITY:
                cout << right << setw(20) << "Utility" << endl << endl;
                break;
            case COFFEESHOP:
                cout << right << setw(20) << "Coffeeshop" << endl << endl;
                break;
            case AUTOMOTIVE:
                cout << right << setw(20) << "Automotive" << endl << endl;
                break;
            case DEPOSIT:
                cout << right << setw(20) << "Deposit" << endl << endl;
                break;
            default:
                cout << right << setw(20) << "Other" << endl << endl;
        }
    }
}