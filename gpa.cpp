#include <iostream>
#include <string>//for strings
#include <math.h>
#include <iomanip>//for setw
#include <fstream>//for files
#include <cstdlib>//for exit

using namespace std;

int const REQ_MAX = 50;
int const COURSE_MAX = 50;
int const REQ_COURSE_MAX = 50;

class Course
{
  public:
    Course();

    void getName(string& name);
    void getTime(string& time);
    void getNumber(string& number);
    void getGrade(char& grade);
    void getHours(int& hour);
    void getAvailability(bool& availability);

    string getName();
    string getTime();
    string getNumber();
    char getGrade();
    int getHours();
    bool getAvailability();

    void setName(string name);
    void setTime(string time);
    void setNumber(string number);
    void setGrade(char grade);
    void setHours(int hour);
    void setAvailability(bool availability);

    void print() const;

  private:
    string courseName;
    string courseTime;
    string courseNumber;
    char grade;
    int hours;
    bool availability;
};

Course::Course()
{
  courseName = "END";
  courseTime = "Fall 2015";
  courseNumber = "CSCE 2004";
  grade = 'A';
  hours = 4;
  availability = true;
}

//GET METHODS
void Course::getName(string& name)
{
  name = this->courseName;
}
void Course::getTime(string& time)
{
  time = this->courseTime;
}
void Course::getNumber(string& number)
{
  number = this->courseNumber;
}
void Course::getGrade(char& grade)
{
  grade = this->grade;
}
void Course::getHours(int& hour)
{
  hour = this->hours;
}
void Course::getAvailability(bool& availability)
{
  availability = this->availability;
}

//GET RETURN METHODS
string Course::getName()
{
  return this->courseName;
}
string Course::getTime()
{
  return this->courseTime;
}
string Course::getNumber()
{
  return this->courseNumber;
}
char Course::getGrade()
{
  return this->grade;
}
int Course::getHours()
{
  return this->hours;
}
bool Course::getAvailability()
{
  return this->availability;
}

//SET METHODS
void Course::setName(string name)
{
  this->courseName = name;
}
void Course::setTime(string time)
{
  this->courseTime = time;
}
void Course::setNumber(string number)
{
  this->courseNumber = number;
}
void Course::setGrade(char grade)
{
  this->grade = grade;
}
void Course::setHours(int hours)
{
  this->hours = hours;
}
void Course::setAvailability(bool availability)
{
  this->availability = availability;
}

void Course::print() const
{
  const char s = ' ';
  const int w = 40;

  cout << left << setw(w) << setfill(s) << this->courseName;
  cout << left << setw(w) << setfill(s) << this->courseTime;
  cout << left << setw(w) << setfill(s) << this->courseNumber;
  cout << left << setw(w) << setfill(s) << this->grade;
  cout << left << setw(w) << setfill(s) << this->hours;
  cout << left << setw(w) << setfill(s) << this->availability;
  cout << endl;
}

class Req
{
  public:
    Req();

    void getGroup(string& group);
    void getSubGroup(string& subGroup);
    void getHourSum(int& hourSum);
    void getCourses(Course courses[]);
    void getStatus(bool& status);

    string getGroup();
    string getSubGroup();
    int getHourSum();
    Course getCourses();
    bool getStatus();

    void setGroup(string group);
    void setSubGroup(string subGroup);
    void setHourSum(int hourSum);
    void setCourses(Course courses[]);
    void setStatus(bool status);

  private:
    string group;
    string subGroup;
    int hourSum;
    Course courses[REQ_COURSE_MAX];
    bool status;
};

Req::Req()
{
  group = "END";
  subGroup = "END";
  hourSum = 0;
  courses[REQ_COURSE_MAX];
  status = false;//fail until proven otherwise
}
//get
void Req::getGroup(string& group)
{
  group = this->group;
}
void Req::getSubGroup(string& subGroup)
{
  subGroup = this->subGroup;
}
void Req::getHourSum(int& hourSum)
{
  hourSum = this->hourSum;
}
void Req::getCourses(Course courses[])
{
  for(int z = 0;z < REQ_COURSE_MAX;z++)
  {
    courses[z].setName(this->courses[z].getName());
    courses[z].setTime(this->courses[z].getTime());
    courses[z].setNumber(this->courses[z].getNumber());
    courses[z].setGrade(this->courses[z].getGrade());
    courses[z].setHours(this->courses[z].getHours());
    courses[z].setAvailability(this->courses[z].getAvailability());
  }
}
void Req::getStatus(bool& status)
{
  status = this->status;
}
//get return
string Req::getGroup()
{
  return this->group;
}
string Req::getSubGroup()
{
  return this->subGroup;
}
int Req::getHourSum()
{
  return this->hourSum;
}
Course Req::getCourses()
{
  return this->courses[REQ_COURSE_MAX];
}
bool Req::getStatus()
{
  return this->status;
}
//set
void Req::setGroup(string group)
{
  this->group = group;
}
void Req::setSubGroup(string subGroup)
{
  this->subGroup = subGroup;
}
void Req::setHourSum(int hourSum)
{
  this->hourSum = hourSum;
}
void Req::setCourses(Course courses[])
{
  for(int z = 0;z < REQ_COURSE_MAX;z++) {
    this->courses[z] = courses[z];
  }
}
void Req::setStatus(bool status)
{
  this->status = status;
}

bool reading(const char filename[], int& n, int capacity, Course courseClasses[])
{
  ifstream file;
  file.open(filename);

  if(file.fail())
  {
    cout << "Failed to open file named: " << filename << endl;
    cout << "Error in reading the deafult file. Terminating..." << endl;
    exit(EXIT_FAILURE);
  }

  if(file.is_open())
  {
    //gets first line
    file >> n;
    file.ignore();

    if(n < capacity)
    {
      string tempName;
      string tempTime;
      string tempNumber;
      char tempGrade;
      int tempHours;

      for(int z = 0;z < n;z++)
      {
        cout << "Reading class " << z + 1 << endl;
        getline(file,tempName);
        getline(file,tempTime);
        getline(file,tempNumber);
        file >> tempGrade;
        file >> tempHours;
        file.ignore();

        //class
        courseClasses[z].setName(tempName);
        courseClasses[z].setTime(tempTime);
        courseClasses[z].setNumber(tempNumber);
        courseClasses[z].setGrade(tempGrade);
        courseClasses[z].setHours(tempHours);
      }
    }
    else
    {
      cout << "specified size on text file: " << filename << " is too large" << endl;
    }
  }

  file.close();

  return true;
}

bool writing(const char filename[], Course courseClasses[], int n)
{
  ofstream file;
  file.open(filename);

  if(file.fail())
  {
    cout << "Failed to recreate and open file named: " << filename << endl;
    exit(EXIT_FAILURE);
  }

  if(file.is_open())
  {
    file << n << endl;

    string tempName;
    string tempTime;
    string tempNumber;
    char tempGrade;
    int tempHours;

    for(int z = 0;z < n;z++)
    {
      courseClasses[z].getName(tempName);
      courseClasses[z].getTime(tempTime);
      courseClasses[z].getNumber(tempNumber);
      courseClasses[z].getGrade(tempGrade);
      courseClasses[z].getHours(tempHours);

      cout << "Writing class " << z + 1 << endl;
      file << tempName << endl;
      file << tempTime << endl;
      file << tempNumber << endl;
      file << tempGrade << endl;
      file << tempHours << endl;
    }
  }

  file.close();

  return true;
}

double gpa(int n, Course courseClasses[])
{
  char tempGrade;
  int tempHours;

  double tempGradePointsSum = 0;
  double tempCreditHoursSum = 0;
  double tempGradePointRep = -1;

  for(int z = 0; z < n; z++)
  {
    courseClasses[z].getGrade(tempGrade);
    courseClasses[z].getHours(tempHours);

    if(tempGrade == 'A')
    {
      tempGradePointRep = 4;
    }
    else if(tempGrade == 'B')
    {
      tempGradePointRep = 3;
    }
    else if(tempGrade == 'C')
    {
      tempGradePointRep = 2;
    }
    else if(tempGrade == 'D')
    {
      tempGradePointRep = 1;
    }
    else if(tempGrade == 'F')
    {
      tempGradePointRep = 0;
    }
    else
    {
      tempGradePointRep = -1;
    }

    if(tempGradePointRep >= 0)
    {
      tempGradePointsSum += (tempHours * tempGradePointRep);
      tempCreditHoursSum += tempHours;
    }
  }

  if(tempCreditHoursSum > 0)
    return (tempGradePointsSum / tempCreditHoursSum);
  else
    cout << "An error occured" << endl;
}

double semesterGpa(int n, Course courseClasses[], string semester)
{
  double tempGradePointsSum = 0;
  double tempCreditHoursSum = 0;
  double tempGradePointRep = -1;

  string tempTime;
  char tempGrade;
  int tempHours;

  for(int z = 0; z < n; z++)
  {
    courseClasses[z].getTime(tempTime);
    courseClasses[z].getGrade(tempGrade);
    courseClasses[z].getHours(tempHours);

    if(tempTime == semester)
    {
      if(tempGrade == 'A')
      {
        tempGradePointRep = 4;
      }
      else if(tempGrade == 'B')
      {
        tempGradePointRep = 3;
      }
      else if(tempGrade == 'C')
      {
        tempGradePointRep = 2;
      }
      else if(tempGrade == 'D')
      {
        tempGradePointRep = 1;
      }
      else if(tempGrade == 'F')
      {
        tempGradePointRep = 0;
      }
      else
      {
        tempGradePointRep = -1;
      }

      if(tempGradePointRep >= 0)
      {
        tempGradePointsSum += (tempHours * tempGradePointRep);
        tempCreditHoursSum += tempHours;
      }
    }
  }

  if(tempCreditHoursSum > 0)
    return (tempGradePointsSum / tempCreditHoursSum);
  else
    cout << "An error occured" << endl;
}

int DRule(int n, Course courseClasses[])
{
  char tempGrade;
  int tempHours;

  int calculation = 0;

  for(int z = 0;z < n;z++)
  {
    courseClasses[z].getGrade(tempGrade);
    courseClasses[z].getHours(tempHours);

    if(tempGrade == 'D')
    {
      calculation += tempHours;
    }
  }

  return calculation;
}

void print(int n, Course courseClasses[])
{
  cout << endl;

  cout << "Displaying (" << n << " of " << n << ") courses." << endl << endl;

  const char s = ' ';
  const int w = 40;

  cout << left << setw(w) << setfill(s) << "Course Name";
  cout << left << setw(w) << setfill(s) << "Semester";
  cout << left << setw(w) << setfill(s) << "Course Number";
  cout << left << setw(w) << setfill(s) << "Grade";
  cout << left << setw(w) << setfill(s) << "Hour";
  cout << endl << endl;

  string tempName;
  string tempTime;
  string tempNumber;
  char tempGrade;
  int tempHours;

  //lists all courses
  for(int z = 0;z<n;z++)
  {
    courseClasses[z].getName(tempName);
    courseClasses[z].getTime(tempTime);
    courseClasses[z].getNumber(tempNumber);
    courseClasses[z].getGrade(tempGrade);
    courseClasses[z].getHours(tempHours);

    cout << left << setw(w) << setfill(s) << tempName;
    cout << left << setw(w) << setfill(s) << tempTime;
    cout << left << setw(w) << setfill(s) << tempNumber;
    cout << left << setw(w) << setfill(s) << tempGrade;
    cout << left << setw(w) << setfill(s) << tempHours;
    cout << endl;
  }

  cout << endl;
}

void getCourse(int n, Course& courseClass)
{
  string tempName;
  string tempTime;
  string tempNumber;
  char tempGrade;
  int tempHours;

  //name
  cout << "Enter the course name (e.g. Programming Foundations I) for class number " << n << endl;
  getline(cin,tempName);

  while(tempName == "")
  {
    cout << "Invalid input. Please try again." << endl;
    getline(cin,tempName);
  }
  //time
  cout << "Enter the semester (e.g. Spring 2016) for class number " << n << endl;
  getline(cin,tempTime);

  while(tempTime == "")
  {
    cout << "Invalid input. Please try again." << endl;
    getline(cin,tempTime);
  }
  //number
  cout << "Enter the course number (e.g. CSCE 2004) for class number " << n << endl;
  getline(cin,tempNumber);

  while(tempNumber == "")
  {
    cout << "Invalid input. Please try again." << endl;
    getline(cin,tempNumber);
  }
  //grade
  string tempString = "";
  while(tempString == "")
  {
    cout << "Enter the grade (A,B,C,D,F,W,I) for class number " << n << endl;
    getline(cin,tempString);

    if(tempString == "A" || tempString == "a")
    {
      tempGrade = 'A';
    }
    else if(tempString == "B" || tempString == "b")
    {
      tempGrade = 'B';
    }
    else if(tempString == "C" || tempString == "c")
    {
      tempGrade = 'C';
    }
    else if(tempString == "D" || tempString == "d")
    {
      tempGrade = 'D';
    }
    else if(tempString == "F" || tempString == "f")
    {
      tempGrade = 'F';
    }
    else if(tempString == "W" || tempString == "w")
    {
      tempGrade = 'W';
    }
    else if(tempString == "I" || tempString == "i")
    {
      tempGrade = 'I';
    }
    else
    {
      tempString = "";
      cout << "Invalid user input, please try again" << endl;
    }
  }
  //number
  cout << "Enter the course hours (1 ... 5) for class number " << n << endl;
  cin >> tempHours;

  while(tempHours < 1 && tempHours > 5)
  {
    cout << "Invalid user input, please try again." << endl;
    cout << "Enter the course hours (1 ... 5) for class number " << n << endl;
    cin >> tempHours;
  }

  cin.ignore();

  courseClass.setName(tempName);
  courseClass.setTime(tempTime);
  courseClass.setNumber(tempNumber);
  courseClass.setGrade(tempGrade);
  courseClass.setHours(tempHours);
}

char menu()
{
  string tempString;

  //return overrides while loop
  while(true)
  {
    cout << "Please enter the character next to the choice you wish to pick." << endl;
    cout << "Here are your options:" << endl;
    cout << "A(a) . Compute the GPA of all courses" << endl;
    cout << "B(b) . List all courses" << endl;
    cout << "C(c) . Compute the total credit hours of the courses with grade D" << endl;
    cout << "D(d) . Compute the GPA for a particular semester" << endl;
    cout << "E(e) . Add another course to the course list" << endl;
    cout << "F(f) . Delete a course from the course list" << endl;
    cout << "G(g) . Check current classes against University Core degree audit" << endl;
    cout << "Q(q) . Quit the program" << endl;
    cout << "Please choose one of the above" << endl;

    getline(cin,tempString);

    if(tempString == "A" || tempString == "a")
    {
      return 'A';
    }
    else if(tempString == "B" || tempString == "b")
    {
      return 'B';
    }
    else if(tempString == "C" || tempString == "c")
    {
      return 'C';
    }
    else if(tempString == "D" || tempString == "d")
    {
      return 'D';
    }
    else if(tempString == "E" || tempString == "e")
    {
      return 'E';
    }
    else if(tempString == "F" || tempString == "f")
    {
      return 'F';
    }
    else if(tempString == "G" || tempString == "g")
    {
      return 'G';
    }
    else if(tempString == "Q" || tempString == "q")
    {
      return 'Q';
    }
    else
    {
      cout << "Invalid selection. Please try again." << endl;
    }
  }
}

int main ()
{
  string selectedFilename;

  int courses = 0;
  string mode = "";
  string tempString = "";

  //init all vars
  //initalizes all array vars based on defined validated input above
  Req reqClasses[REQ_MAX];
  Course courseClasses[COURSE_MAX];

  cout << "Welcome to PFI course management system v1" << endl;
  cout << "Would you like to read the courses taken from a file?" << endl;
  cout << "Please enter y for yes and n for no" << endl;
  getline(cin, mode);

  while(mode != "y" && mode != "n")
  {
    cout << "The character entered is " << mode << ". That is not y or n";
    cout << "Would you like to read the courses taken from a file?" << endl;
    cout << "Please enter y for yes and n for no" << endl;
    getline(cin, mode);
  }

  if(mode == "y")
  {
    string stock = "";

    cout << "Would you like to use the default file?" << endl;
    cout << "Please enter y for yes and n for no" << endl;
    getline(cin, stock);

    while(stock != "y" && stock != "n")
    {
      cout << "The character entered is " << stock << ". That is not y or n";
      cout << "Would you like to use the default file?" << endl;
      cout << "Please enter y for yes and n for no" << endl;
      getline(cin, stock);
    }

    if(mode == "y")
    {
      reading("courses.txt", courses, COURSE_MAX, courseClasses);
    }
    else
    {
      cout << "Enter your file name" << endl;
      getline(cin, selectedFilename);

      while(selectedFilename == "")
      {
        cout << "Invalid filename. Please try again." << endl;
        getline(cin, selectedFilename);
      }

      reading(selectedFilename.c_str(), courses, COURSE_MAX, courseClasses);
    }
  }

  if(courses == 0)
  {
    cout << "Interactive mode was selected." << endl;
    cout << "Enter the number of classes for the system [1," << COURSE_MAX << "]" << endl;
    cin >> courses;

    while(courses <= 0 && courses >= COURSE_MAX)
    {
      cout << "The supplied input was not within specified bounds. Please try again." << endl;
      cin >> courses;
    }

    cin.ignore();

    for(int step = 0;step < courses;step++)
    {
      //comeback
      getCourse(courses, courseClasses[step]);
    }
  }

  cout << "Welcome to the interactive menu-driven part of the GPA and Course storage program." << endl;

  while(true)
  {
    char menuSelector = menu();

    if(menuSelector == 'A')
    {
      cout << "Congratulations, your GPA was " << gpa(courses, courseClasses) << endl;
    }
    else if(menuSelector == 'B')
    {
      print(courses, courseClasses);
    }
    else if(menuSelector == 'C')
    {
      cout << "Total hours with D grades are " << DRule(courses, courseClasses) << endl;
    }
    else if(menuSelector == 'D')
    {
      double tempGPA = 0;
      string selectedSemester = "";
      int semesterIndex;

      cout << "Please input desired semester for calculation" << endl;
      getline(cin,selectedSemester);

      double tempClasses = 0;

      string tempTime;

      while(tempClasses == 0)
      {
        for(int z = 0; z<courses;z++)
        {
          courseClasses[z].getTime(tempTime);

          if(tempTime == selectedSemester)
          {
            tempClasses++;
          }
        }
        if(tempClasses == 0)
        {
          cout << "Desired semester: " << selectedSemester << " was not found. Please try again." << endl;
          cout << "Please input desired semester for calculation" << endl;
          getline(cin,selectedSemester);
        }
      }

      cout << "Congratulations, your GPA was " << semesterGpa(courses, courseClasses, selectedSemester) << " in " << selectedSemester << endl;
    }
    else if(menuSelector == 'E')
    {
      if(courses + 1 < COURSE_MAX)
      {
        courses++;

        getCourse(courses, courseClasses[courses - 1]);
      }
      else
      {
        cout << "Unable to add more than " << COURSE_MAX << " classes" << endl;
      }
    }
    else if(menuSelector == 'F')
    {
      if(courses - 1 >= 0)
      {
        int selection = 0;
        cout << "Select from 1 to " << courses << " for the course to be deleted" << endl;
        cin >> selection;
        cin.ignore();

        while(selection < 0 && selection > courses)
        {
          cout << "Invalid selection. Please try again" << endl;
          cin >> selection;
          cin.ignore();
        }

        string tempName;
        string tempTime;
        string tempNumber;
        char tempGrade;
        int tempHours;

        //move elemnts left 1
        for(int z = selection;z < courses;z++)
        {
          //name
          courseClasses[z].getName(tempName);
          courseClasses[z - 1].setName(tempName);
          //time
          courseClasses[z].getTime(tempTime);
          courseClasses[z - 1].setTime(tempTime);
          //number
          courseClasses[z].getNumber(tempNumber);
          courseClasses[z - 1].setNumber(tempNumber);
          //grade
          courseClasses[z].getGrade(tempGrade);
          courseClasses[z - 1].setGrade(tempGrade);
          //hours
          courseClasses[z].getHours(tempHours);
          courseClasses[z - 1].setHours(tempHours);
        }

        courses--;
      }
      else
      {
        cout << "There are not any courses to remove" << endl;
      }
    }
    else if(menuSelector == 'G')
    {
      //checks number of
      int empty = 0;
      ifstream file;
      string filename = "CSCErequirements.txt";
      file.open(filename.c_str());
      if(file.fail())
      {
        cout << "Failed to open file named: CSCErequirements" << endl;
        cout << "Error in reading the deafult file. Terminating..." << endl;
        exit(EXIT_FAILURE);
      }
      if(file.is_open())
      {
        //checks if number of reqs is too large for REQ_MAX
        string line;
        while(getline(file, line))
        {
          if(line.empty())
          {
            empty++;
          }
        }

        if(empty < REQ_MAX)
        {
          //go back to first line
          file.clear();
          file.seekg(0, ios::beg);

          //placeholders for later use
          int tempInt;
          string tempString;

          //begin logic for
          int obj = -1;
          while(getline(file, line))
          {
            if(!line.empty())
            {
              obj++;
              reqClasses[obj].setGroup(line);

              getline(file,tempString);

              reqClasses[obj].setSubGroup(tempString);

              file >> tempInt;
              file.ignore();
              reqClasses[obj].setHourSum(tempInt);

              int reqCourseCount = 0;
              bool escape = false;
              Course reqCourseClasses[REQ_COURSE_MAX];
              while(!escape)
              {
                getline(file,tempString);

                if(tempString.empty())
                {
                  escape = true;
                }
                else
                {
                  cout << "overwriting req obj for " << line << "[" << tempString << "]" << endl;
                  //overwrite constructor
                  reqCourseClasses[reqCourseCount].setName("REQ");
                  reqCourseClasses[reqCourseCount].setTime("REQ");

                  //set number
                  reqCourseClasses[reqCourseCount].setNumber(tempString);

                  //set hours
                  file >> tempInt;
                  file.ignore();
                  reqCourseClasses[reqCourseCount].setHours(tempInt);

                  reqCourseCount++;
                }
              }
              reqClasses[obj].setCourses(reqCourseClasses);
            }
          }

          cout << obj << " requirement objects generated" << endl;

          //iterate through all reqs for comparision against courseClasses
          for(int r = 0;r < obj;r++)
          {
            Course targetRC[COURSE_MAX];

            //gets courses into a targetRequirementClasses var
            reqClasses[r].getCourses(targetRC);

            //iterate through all req[r]courses
            int reqCourseCount = 0;
            //holds temp int for hours calculation
            int reqCourseHours = 0;
            //holds escape logic
            string targetRCname = "START";

            while(targetRCname != "END")
            {
              //get name from courses
              targetRCname = targetRC[reqCourseCount].getName();

              if(reqCourseHours >= reqClasses[r].getHourSum())
              {
                cout << "Passing with " << reqCourseHours << " out of " << reqClasses[r].getHourSum() << endl;

                //req has been met
                reqClasses[r].setStatus(true);

                //force while to end
                targetRCname = "END";
              }
              else
              {
                if(targetRCname == "END")
                {
                  break;
                }

                cout << "REQCOURSE id :" << reqCourseCount << endl;

                cout << "LOOKING FOR: " << targetRC[reqCourseCount].getNumber() << endl;

                //iterate through all courses
                for(int c = 0;c < courses;c++)
                {
                  //check if reqCourseHours has been met
                  if(courseClasses[c].getAvailability())
                  {
                    //compare couresNumbers
                    if(targetRC[reqCourseCount].getNumber() == courseClasses[c].getNumber())
                    {
                      //store grade in temp var
                      char tempGrade = courseClasses[c].getGrade();

                      //check if passed class
                      if(tempGrade != 'F' || tempGrade != 'W' || tempGrade != 'I')
                      {
                        //add credits into tempHolder
                        reqCourseHours += courseClasses[c].getHours();

                        cout << "Setting " << courseClasses[c].getNumber() << " status to false" << endl;

                        //setAvailability false
                        courseClasses[c].setAvailability(false);
                      }
                      else
                      {
                        //NOTE
                        //this application assumes that the end user could have
                        //taken a particular class mutliple time, therefore
                        //does not set the status of a requirement to failed
                        //as the user may have duplicate classes in the
                        //courseClasses array. The following commented
                        //logic is for IF IT DID.

                        //setStatus of req to false (failed)
                        //reqClasses[r].setStatus(false);
                        //force while to end
                        //targetRCname = "END";
                      }
                    }
                  }
                }
              }
              reqCourseCount++;
            }
          }

          //lastly output results
          for(int r = 0;r < obj;r++)
          {
            if(reqClasses[r].getStatus())
              cout << "PASS: " << reqClasses[r].getGroup() << "[" << reqClasses[r].getSubGroup() << "]" << endl;
            else
              cout << "FAIL: " << reqClasses[r].getGroup() << "[" << reqClasses[r].getSubGroup() << "]" << endl;
          }
        }
        else
        {
          cout << "Too many requirement objects listed in CSCErequirements.txt file" << endl;
        }
      }
      file.close();
    }
    else if(menuSelector == 'Q')
    {
      if(selectedFilename == "")
      {
        writing("courses.txt", courseClasses, courses);
      }
      else
      {
        writing(selectedFilename.c_str(), courseClasses, courses);
      }
      //"escapes all logic"
      return 0;
    }
  }
}
